#include "Pokedex.h"

void Pokedex::setup(Menu* menu)
{
	m_menu = menu;

	//m_menu->setupPokedexData(&m_pokedexDisplayData);		//TODO: REMOVE
	MenuSetup::setupPokedexData(m_menu, &m_pokedexDisplayData);

	m_ringBuffer.init();

	populateEntries();
	sort(SortMethod::A_TO_Z);
}

void Pokedex::run()
{
	m_ringBuffer.reset();
	m_scrollIndex = 0;
	m_menu->reset(MenuScene::POKEDEX);

	populateScrollData();
	populateDisplayData();
	updateHoverIndex();

	int sortSelection = NONE;
	m_menu->setRequestedData(&sortSelection);
	m_menu->setscene(MenuScene::POKEDEX);
	m_menu->preRun();


	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_menu->leaveRequested())
			break;

		if (sortSelection != NONE)
		{
			sortDisplayList(sortSelection);
			sortSelection = NONE;
			continue;
		}

		adjustScrollVertically();
	}

	m_menu->clearRequestedData();
	m_menu->postRun();
	m_menu->setscene(MenuScene::NONE);
}

std::string Pokedex::save()
{
	std::string value = std::to_string((int)m_previousSortMethod) + ",";

	for (PokedexEntry entry : m_entries)
		value += std::to_string((int)entry.status) + ",";

	return value;
}

void Pokedex::load(std::vector<std::string> data)
{
	sort(SortMethod(std::stoi(data.at(0))));
	data.erase(data.begin() + 0);

	for (int i = 0; i < data.size(); i++)
	{
		m_entries.at(i).status = EncounterStatus(std::stoi(data.at(i)));

		switch (EncounterStatus(std::stoi(data.at(i))))
		{
		case EncounterStatus::CAUGHT:
			m_pokemonCaught++;
		case EncounterStatus::SEEN:
			m_pokemonSeen++;
		default:
			break;
		}
	}

	m_pokedexDisplayData.pokemonSeen = "Seen: " + formatPokedexNumber(m_pokemonSeen);
	m_pokedexDisplayData.pokemonCaught = "Caught: " + formatPokedexNumber(m_pokemonCaught);
}

void Pokedex::spotPokemon(PokemonID id)
{
	if (!binarySetStatus(id, EncounterStatus::SEEN, 0, m_entries.size() - 1))
		return;
	
	m_pokemonSeen++;

	m_pokedexDisplayData.pokemonSeen = "Seen: " + formatPokedexNumber(m_pokemonSeen);
}

void Pokedex::obtainPokemon(PokemonID id)
{
	spotPokemon(id);
	if (!binarySetStatus(id, EncounterStatus::CAUGHT, 0, m_entries.size() - 1))
	{

		return;
	}

	m_pokemonCaught++;
	m_pokedexDisplayData.pokemonCaught = "Caught: " + formatPokedexNumber(m_pokemonCaught);
	displayNewPokemon(id);
}

bool Pokedex::hasObtainedPokemon(PokemonID id)
{
	return idHasBeenObtained(id, 0, m_entries.size() - 1);
}

bool Pokedex::binarySetStatus(PokemonID id, EncounterStatus status, int bottomIndex, int topIndex)
{
	bool topHalf = true;

	int middleIndex = bottomIndex + (topIndex - bottomIndex) / 2;

	if (m_entries.at(middleIndex).speciesID == id)
	{
		if (m_entries.at(middleIndex).status < status)
		{
			m_entries.at(middleIndex).status = status;
			return true;
		}
		return false;
	}

	switch (m_previousSortMethod)
	{
	case SortMethod::A_TO_Z:
		if (isLessThan(getSpeciesFromID(id).name, getSpeciesFromID(m_entries.at(middleIndex).speciesID).name))
			topHalf = false;
		break;
	case SortMethod::Z_TO_A:
		if (!isLessThan(getSpeciesFromID(id).name, getSpeciesFromID(m_entries.at(middleIndex).speciesID).name))
			topHalf = false;
		break;
	case SortMethod::LOWEST_NUMBER:
		if (id < m_entries.at(middleIndex).speciesID)
			topHalf = false;
		break;
	case SortMethod::HIGHEST_NUMBER:
		if (!(id < m_entries.at(middleIndex).speciesID))
			topHalf = false;
		break;
	}

	if (topHalf)
		return binarySetStatus(id, status, middleIndex + 1, topIndex);
	else
		return binarySetStatus(id, status, bottomIndex, middleIndex - 1);
}

bool Pokedex::idHasBeenObtained(PokemonID id, int bottomIndex, int topIndex)
{
	bool topHalf = true;

	int middleIndex = bottomIndex + (topIndex - bottomIndex) / 2;

	if (m_entries.at(middleIndex).speciesID == id)
	{
		if (m_entries.at(middleIndex).status == EncounterStatus::CAUGHT)
			return true;
		return false;
	}

	switch (m_previousSortMethod)
	{
	case SortMethod::A_TO_Z:
		if (isLessThan(getSpeciesFromID(id).name, getSpeciesFromID(m_entries.at(middleIndex).speciesID).name))
			topHalf = false;
		break;
	case SortMethod::Z_TO_A:
		if (!isLessThan(getSpeciesFromID(id).name, getSpeciesFromID(m_entries.at(middleIndex).speciesID).name))
			topHalf = false;
		break;
	case SortMethod::LOWEST_NUMBER:
		if (id < m_entries.at(middleIndex).speciesID)
			topHalf = false;
		break;
	case SortMethod::HIGHEST_NUMBER:
		if (!(id < m_entries.at(middleIndex).speciesID))
			topHalf = false;
		break;
	}

	if (topHalf)
		return idHasBeenObtained(id, middleIndex + 1, topIndex);
	else
		return idHasBeenObtained(id, bottomIndex, middleIndex - 1);
}

void Pokedex::populateEntries()
{
	for (int i = 0; (PokemonID)i != PokemonID::POKEMONID_END; i++)
		m_entries.push_back(PokedexEntry{ (PokemonID)i, EncounterStatus::NOT_SEEN });
}

void Pokedex::sort(SortMethod method)
{
	switch (method)
	{
	case SortMethod::A_TO_Z:
		sortAToZ(&m_entries, 0, m_entries.size() - 1);
		m_pokedexDisplayData.sortArrow.dynamicImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_UP_ARROW];
		m_pokedexDisplayData.sortArrow.percentageY = (313.0f / 563.0f) * 100.0f;
		break;
	case SortMethod::Z_TO_A:
		sortZToA(&m_entries, 0, m_entries.size() - 1);
		m_pokedexDisplayData.sortArrow.dynamicImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_DOWN_ARROW];
		m_pokedexDisplayData.sortArrow.percentageY = (313.0f / 563.0f) * 100.0f;
		break;
	case SortMethod::LOWEST_NUMBER:
		sortLowNumber(&m_entries, 0, m_entries.size() - 1);
		m_pokedexDisplayData.sortArrow.dynamicImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_UP_ARROW];
		m_pokedexDisplayData.sortArrow.percentageY = (188.0f / 563.0f) * 100.0f;
		break;
	case SortMethod::HIGHEST_NUMBER:
		sortHighNumber(&m_entries, 0, m_entries.size() - 1);
		m_pokedexDisplayData.sortArrow.dynamicImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_DOWN_ARROW];
		m_pokedexDisplayData.sortArrow.percentageY = (188.0f / 563.0f) * 100.0f;
		break;
	default:
		sortAToZ(&m_entries, 0, m_entries.size() - 1);
		break;
	}

	m_previousSortMethod = method;
}

void Pokedex::sortAToZ(std::vector<PokedexEntry>* entries, int start, int end)
{
	if (start >= end)
		return;

	int pivotIndex = end;

	std::string pivotValue = getSpeciesFromID(entries->at(end).speciesID).name;

	int tailIndex = start - 1;

	for (int target = start; target < end; target++)
	{
		if (isLessThan(getSpeciesFromID(entries->at(target).speciesID).name , pivotValue))
		{
			tailIndex += 1;

			PokedexEntry tempValue = entries->at(tailIndex);

			entries->at(tailIndex) = entries->at(target);
			entries->at(target) = tempValue;
		}
	}

	tailIndex += 1;

	PokedexEntry tempValue = entries->at(tailIndex);

	entries->at(tailIndex) = entries->at(end);
	entries->at(end) = tempValue;

	sortAToZ(entries, start, tailIndex - 1);
	sortAToZ(entries, tailIndex + 1, end);
}

void Pokedex::sortZToA(std::vector<PokedexEntry>* entries, int start, int end)
{
	if (start >= end)
		return;

	int pivotIndex = start;

	std::string pivotValue = getSpeciesFromID(entries->at(start).speciesID).name;

	int tailIndex = end + 1;

	for (int target = end; target > start; target--)
	{
		if (isLessThan(getSpeciesFromID(entries->at(target).speciesID).name , pivotValue))
		{
			tailIndex -= 1;

			PokedexEntry tempValue = entries->at(tailIndex);

			entries->at(tailIndex) = entries->at(target);
			entries->at(target) = tempValue;
		}
	}

	tailIndex -= 1;

	PokedexEntry tempValue = entries->at(tailIndex);

	entries->at(tailIndex) = entries->at(start);
	entries->at(start) = tempValue;

	sortZToA(entries, start, tailIndex - 1);
	sortZToA(entries, tailIndex + 1, end);
}

void Pokedex::sortLowNumber(std::vector<PokedexEntry>* entries, int start, int end)
{
	if (start >= end)
		return;

	int pivotIndex = end;

	int pivotValue = entries->at(pivotIndex).speciesID;

	int tailIndex = start - 1;

	for (int target = start; target < end; target++)
	{
		if (entries->at(target).speciesID < pivotValue)
		{
			tailIndex += 1;

			PokedexEntry tempValue = entries->at(tailIndex);

			entries->at(tailIndex) = entries->at(target);
			entries->at(target) = tempValue;
		}
	}

	tailIndex += 1;

	PokedexEntry tempValue = entries->at(tailIndex);

	entries->at(tailIndex) = entries->at(end);
	entries->at(end) = tempValue;

	sortLowNumber(entries, start, tailIndex - 1);
	sortLowNumber(entries, tailIndex + 1, end);
}

void Pokedex::sortHighNumber(std::vector<PokedexEntry>* entries, int start, int end)
{
	if (start >= end)
		return;

	int pivotIndex = start;

	int pivotValue = entries->at(start).speciesID;

	int tailIndex = end + 1;

	for (int target = end; target > start; target--)
	{
		if (entries->at(target).speciesID < pivotValue)
		{
			tailIndex -= 1;

			PokedexEntry tempValue = entries->at(tailIndex);

			entries->at(tailIndex) = entries->at(target);
			entries->at(target) = tempValue;
		}
	}

	tailIndex -= 1;

	PokedexEntry tempValue = entries->at(tailIndex);

	entries->at(tailIndex) = entries->at(start);
	entries->at(start) = tempValue;

	sortHighNumber(entries, start, tailIndex - 1);
	sortHighNumber(entries, tailIndex + 1, end);
}

bool Pokedex::isLessThan(std::string value1, std::string value2)
{
	int size = value1.size();
	if (value2.size() < value1.size())
		size = value2.size();

	for (int i = 0; i < size; i++)
	{
		if ((int)value1.at(i) < (int)value2.at(i))
			return true;
		else if ((int)value1.at(i) > (int)value2.at(i))
			return false;
	}

	if (value1.size() <= value2.size())
		return true;
	return false;
}

void Pokedex::populateScrollData()
{
	std::vector<int> order = m_ringBuffer.getIndexOrder();

	updateScrollButton(order.at(0), -3);
	updateScrollButton(order.at(1), -2);
	updateScrollButton(order.at(2), -1);
	updateScrollButton(order.at(3),  0);
	updateScrollButton(order.at(4),  1);
	updateScrollButton(order.at(5),  2);
	updateScrollButton(order.at(6),  3);
}

void Pokedex::populateDisplayData()
{


	std::string name = "vvvv";
	std::string type1 = "";
	std::string type2 = "";
	std::string pokemonImage = "";
	std::string description = "";
	std::string height = "Height: vvvv";
	std::string weight = "Weight: vvvv";




	if (m_entries.at(m_scrollIndex).status >= EncounterStatus::SEEN)
	{

		name = getSpeciesFromID(m_entries.at(m_scrollIndex).speciesID).name;
		pokemonImage = pokemonFrontTexture(getSpeciesFromID(m_entries.at(m_scrollIndex).speciesID).name);

		if (m_entries.at(m_scrollIndex).status == EncounterStatus::CAUGHT)
		{
			type1 = g_typeTextureLocations[getSpeciesFromID(m_entries.at(m_scrollIndex).speciesID).type1];
			type2 = g_typeTextureLocations[getSpeciesFromID(m_entries.at(m_scrollIndex).speciesID).type2];
			description = getSpeciesFromID(m_entries.at(m_scrollIndex).speciesID).description;
			height = "Height: " + getSpeciesFromID(m_entries.at(m_scrollIndex).speciesID).height;
			weight = "Weight: " + getSpeciesFromID(m_entries.at(m_scrollIndex).speciesID).weight + "lbs";
		}
	}

	m_pokedexDisplayData.pokemonSelectedData.pokemonName = name;
	m_pokedexDisplayData.pokemonSelectedData.pokemonNumber = formatPokedexNumber(m_entries.at(m_scrollIndex).speciesID);
	m_pokedexDisplayData.pokemonSelectedData.pokemonHeight = height;
	m_pokedexDisplayData.pokemonSelectedData.pokemonWight =  weight;
	m_pokedexDisplayData.pokemonSelectedData.pokemonDescription = description;
	m_pokedexDisplayData.pokemonSelectedData.pokemonDescription = description;

	m_pokedexDisplayData.pokemonSelectedData.pokemonImage.dynamicImage = pokemonImage;
	m_pokedexDisplayData.pokemonSelectedData.pokemonType1.dynamicImage = type1;
	m_pokedexDisplayData.pokemonSelectedData.pokemonType2.dynamicImage = type2;

	if (m_pokedexDisplayData.pokemonSelectedData.pokemonType2.dynamicImage == "")
	{
		m_pokedexDisplayData.pokemonSelectedData.pokemonType1.percentageX = (260.0f / 1000.0f) * 100.0f;
	}
	else
	{
		m_pokedexDisplayData.pokemonSelectedData.pokemonType1.percentageX = (207.5f / 1000.0f) * 100.0f;
		m_pokedexDisplayData.pokemonSelectedData.pokemonType2.percentageX = (312.5f / 1000.0f) * 100.0f;
	}
	
}

void Pokedex::updateHoverIndex()
{
	int menuButtonIndex = m_menu->getButtonIndex();

	if (menuButtonIndex == 7 || menuButtonIndex == 8)
	{
		if (m_previousHoverIndex == menuButtonIndex)
			return;

		float dimenstionMultiplier = 2.0f;
		float percentX = (916.0f / 1000.0f) * 100.0f;
		float percentY = 0.0f;
		float width = ((102.0f / 1000.0f) * 100.0f) / dimenstionMultiplier;
		float height = ((93.0f / 563.0f) * 100.0f) / dimenstionMultiplier;

		if (menuButtonIndex == 7)
			percentY = (283.5f / 563.0f) * 100.0f;
		else
			percentY = (158.5f / 563.0f) * 100.0f;

		m_pokedexDisplayData.selectionHighlight.percentageX = percentX;
		m_pokedexDisplayData.selectionHighlight.percentageY = percentY;
		m_pokedexDisplayData.selectionHighlight.widthPercent = width;
		m_pokedexDisplayData.selectionHighlight.heightPercent = height;
		m_pokedexDisplayData.selectionHighlight.dynamicImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_HIGHLIGHT_SORT];

		m_previousHoverIndex = menuButtonIndex;

		return;
	}


	PokedexScrollButton* button = getButtonFromRingIndex(m_ringBuffer.getCenterIndex());

	if (button->buttonRenderData.percentageX == m_pokedexDisplayData.selectionHighlight.percentageX && m_previousHoverIndex == m_ringBuffer.getCenterIndex())
		return;

	float dimensionMulitplier = 2.0f;

	m_pokedexDisplayData.selectionHighlight.percentageX = button->buttonRenderData.percentageX;
	m_pokedexDisplayData.selectionHighlight.percentageY = button->buttonRenderData.percentageY;
	m_pokedexDisplayData.selectionHighlight.widthPercent = button->buttonRenderData.widthPercent / dimensionMulitplier;
	m_pokedexDisplayData.selectionHighlight.heightPercent = button->buttonRenderData.heightPercent / dimensionMulitplier;
	m_pokedexDisplayData.selectionHighlight.dynamicImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_HIGHLIGHT_BUTTON];

	m_previousHoverIndex = m_ringBuffer.getCenterIndex();
}

void Pokedex::displayNewPokemon(PokemonID id)
{
	m_pokedexDisplayData.pokemonSelectedData.pokemonName = getSpeciesFromID(id).name;
	m_pokedexDisplayData.pokemonSelectedData.pokemonNumber = "No: " + formatPokedexNumber((int)id);
	m_pokedexDisplayData.pokemonSelectedData.pokemonHeight = "Height: " + getSpeciesFromID(id).height;
	m_pokedexDisplayData.pokemonSelectedData.pokemonWight = "Weight: " + getSpeciesFromID(id).weight + "lbs";
	m_pokedexDisplayData.pokemonSelectedData.pokemonDescription = getSpeciesFromID(id).description;

	m_pokedexDisplayData.newPokemonImage.dynamicImage = pokemonFrontTexture(getSpeciesFromID(id).name);

	m_menu->setscene(MenuScene::NEW_POKEMON);
	m_menu->preRun();

	m_menu->sleep(0.2f);

	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_menu->anyButtonPressed())
			break;

	}

	m_menu->clearRequestedData();
	m_menu->postRun();

	m_menu->setscene(MenuScene::NONE);
	m_menu->setOverlay(MenuOverlay::NONE);
}

PokedexScrollButton* Pokedex::getButtonFromRingIndex(int buttonRingIndex)
{
	switch (buttonRingIndex)
	{
	case 0:
		return &m_pokedexDisplayData.button4;
	case 1:
		return &m_pokedexDisplayData.button1;
	case 2:
		return &m_pokedexDisplayData.button2;
	case 3:
		return &m_pokedexDisplayData.button3;
	case 4:
		return &m_pokedexDisplayData.button5;
	case 5:
		return &m_pokedexDisplayData.button6;
	case 6:
		return &m_pokedexDisplayData.button7;
	default:
		return nullptr;
	}
}

void Pokedex::sortDisplayList(int sortSelection)
{
	if (sortSelection == 0)
	{
		if (m_previousSortMethod == SortMethod::A_TO_Z)
			sort(SortMethod::Z_TO_A);
		else
			sort(SortMethod::A_TO_Z);
	}
	else
	{
		if (m_previousSortMethod == SortMethod::LOWEST_NUMBER)
			sort(SortMethod::HIGHEST_NUMBER);
		else
			sort(SortMethod::LOWEST_NUMBER);
	}

	populateScrollData();
	populateDisplayData();
	updateHoverIndex();
}

void Pokedex::adjustScrollVertically()
{
	int menuButtonIndex = m_menu->getButtonIndex();

	if (menuButtonIndex == 7 || menuButtonIndex == 8)
	{
		updateHoverIndex();
		return;
	}

	int centerIndex = m_ringBuffer.getCenterIndex();

	if (menuButtonIndex == centerIndex)
	{
		updateHoverIndex();
		return;
	}

	int aboveCenterIndex = m_ringBuffer.getAboveCenterIndex();
	int belowCenterIndex = m_ringBuffer.getBelowCenterIndex();

	if (menuButtonIndex == aboveCenterIndex)
	{
		if (m_scrollIndex == 0)
		{
			m_ringBuffer.rotateUp();
			populateScrollData();
			updateHoverIndex();
			return;
		}

		// Animate Rotation Up

		m_ringBuffer.rotateUp();
		m_scrollIndex--;

		// Render New Pokemon Data
		// TODO: When we scroll we only need to update the one button
		populateScrollData();
		populateDisplayData();
		updateHoverIndex();
		
	}
	else
	{
		if (m_scrollIndex == m_entries.size() - 1)
		{
			m_ringBuffer.rotateDown();
			populateScrollData();
			updateHoverIndex();
			return;
		}

		// Animate Rotation Down
		
		m_ringBuffer.rotateDown();
		m_scrollIndex++;

		// Render New Pokemon Data
		populateScrollData();
		populateDisplayData();
		updateHoverIndex();

		// TODO: When we scroll we only need to update the one button
	}
}

void Pokedex::updateScrollButton(int buttonRingIndex, int distanceFromCenter)
{
	PokedexScrollButton* button = getButtonFromRingIndex(buttonRingIndex);

	int entryIndex = m_scrollIndex + distanceFromCenter;

	if (entryIndex < 0 || entryIndex > m_entries.size() - 1 || abs(distanceFromCenter) == 3)
		makeInvisibleButton(button);
	else
		makeVisibleButton(button, entryIndex, distanceFromCenter);
}

void Pokedex::makeInvisibleButton(PokedexScrollButton* button)
{
	button->pokemonName.value = "";
	button->pokemonNumber.value = "";
	button->buttonRenderData = ButtonRenderData{ 0.0f, 0.0f, 0.0f, 0.0f, Color::WHITE, NONE, &m_invisibleButton, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], false };
	button->pokemonCaughtImage = DynamicImageRenderData{ 0.0f, 0.0f, 0.0f, 0.0f, ""};
}

void Pokedex::makeVisibleButton(PokedexScrollButton* button, int entryIndex, int distanceFromCenter)
{
	glm::vec2 coordPercentages = getCoordinatePercentages(distanceFromCenter);

	std::string name = "vvvv";

	if (m_entries.at(entryIndex).status == EncounterStatus::CAUGHT || m_entries.at(entryIndex).status == EncounterStatus::SEEN)
		name = getSpeciesFromID(m_entries.at(entryIndex).speciesID).name;


	// Pokemon Name
	{
		float nameXPercentOffset = 11.0f;
		float nameYPercentOffset = -2.0f;

		button->pokemonName.value = name;
		button->pokemonName.renderData = TextBoxRenderData{ coordPercentages.x + nameXPercentOffset, coordPercentages.y + nameYPercentOffset, 2.0f, Color::BLACK, Alignment::RIGHT_ALIGN };
	}

	// Pokemon Number
	{
		float numberXPercentOffset = -9.5f;
		float numberYPercentOffset = -2.0f;

		button->pokemonNumber.value = formatPokedexNumber(m_entries.at(entryIndex).speciesID);
		button->pokemonNumber.renderData = TextBoxRenderData{ coordPercentages.x + numberXPercentOffset, coordPercentages.y + numberYPercentOffset, 2.0f, Color::BLACK, Alignment::LEFT_ALIGN };
	}
	
	// Button
	{
		float buttonWidth = ((125.0f / 1000.0f) * 100.0f) * 2.0f;
		float buttonHeight = ((42.0f / 563.0f) * 100.0f) * 1.2f;

		//TODO: Button Images Later Maybe
		button->buttonRenderData = ButtonRenderData{ coordPercentages.x, coordPercentages.y, buttonWidth, buttonHeight, Color::WHITE, NONE, &m_visibleButton, g_overlayTextureLocations[MenuOverlay::MOVE_OUTLINE], false };

	}
	
	// Catch Image
	{
		float caughtImageXPercentOffset = -10.5f;
		float caughtImageYPercentOffset = 0.0f;

		float imageScale = 10.0f;

		float imageWidth = 9.0f / imageScale;
		float imageHeight = 16.0f / imageScale;

		std::string caughtImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_NOT_CAUGHT];
		if (m_entries.at(entryIndex).status == EncounterStatus::CAUGHT)
			caughtImage = g_overlayTextureLocations[MenuOverlay::POKEDEX_CAUGHT];

		button->pokemonCaughtImage = DynamicImageRenderData{ coordPercentages.x + caughtImageXPercentOffset, coordPercentages.y + caughtImageYPercentOffset, imageWidth, imageHeight, caughtImage };
	}
}

void Pokedex::animateScrollUp()
{

}

void Pokedex::animateScrollDown()
{

}

glm::vec2 Pokedex::getCoordinatePercentages(int distanceFromCenter)
{
	int pos = -distanceFromCenter + 3;

	float bottomButtonY = 14.5;
	float buttonYGap = 26.5f;
	float buttonHeight = 42.0f;

	float buttonY = bottomButtonY + (buttonHeight * pos) + (buttonYGap * pos);


	float curveWidth = 1.0f / 500.0f;
	float xIntercept = 670;
	float yIntercept = 218;

	float buttonX = (curveWidth * pow((buttonY - yIntercept), 2)) + xIntercept;

	return glm::vec2((buttonX / 1000.0f) * 100.0f, (buttonY / 563.0f) * 100.0f);
}

std::string Pokedex::formatPokedexNumber(int number)
{
	std::string value;

	if (number < 100)
		value += "0";
	if (number < 10)
		value += "0";
	value += std::to_string(number);

	return value;
}

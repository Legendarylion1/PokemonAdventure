#include "PC.h"

void PC::setup(Trainer* trainer, Menu* menu)
{
	m_trainer = trainer;
	m_menu = menu;

	m_pcData.movePokemonHighlightData.visible = &m_inMove;
	MenuSetup::setupPCData(m_menu, &m_pcData);
}

bool PC::addPokemon(Pokemon pokemon)
{
	for (int boxCount = 0; boxCount < NUMBER_OF_BOXES; boxCount++)
	{
		for (int pokemonIndex = 0; pokemonIndex < POKEMON_IN_BOX; pokemonIndex++)
		{
			if (m_pcPokemon[boxCount][pokemonIndex].getLevel() == 0)
			{
				m_pcPokemon[boxCount][pokemonIndex] = pokemon;
				return true;
			}
		}
	}

	return false;
}

void PC::run()
{
	// Reset Data
	{
		m_currentPokemonIndex = NONE;
		m_previousPokemonIndex = NONE;
		m_pokemonStatsIndex = NONE;
		m_currentBox = 0;
		m_currentPokemonIndex = 0;

		m_previousBox = NONE;
		m_previousPokemonIndex = NONE;
		setMoveHighlight(false);
	}

	m_menu->setCanLeave(true);
	m_menu->setscene(MenuScene::USE_PC);
	m_menu->setRequestedData(&m_menuSelection);
	m_menu->preRun();

	//TODO: PC Open animation
	{
		float count = 0.0f;
		float target = 0.2f;

		while (count < target)
		{
			if (m_menu->shouldClose())
				break;

			m_menu->onUpdate();
			count += m_menu->getDeltaTime();
		}
	}

	updateAllDisplays();

	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_menu->leaveRequested())
		{
			if (!m_inMove)
				break;

			//We cancel swap
			setMoveHighlight(false);
			continue;
		}

		if (m_menuSelection == NONE)
			continue;

		if (m_menuSelection == arrowDirections::RIGHT)
		{
			moveBoxRight();
			m_menuSelection = NONE;
			continue;
		}
		else if (m_menuSelection == arrowDirections::LEFT)
		{
			moveBoxLeft();
			m_menuSelection = NONE;
			continue;
		}

		if (!m_inMove)
		{
			if (pokemonAtMenuIndex())
				runOverlay();
			m_menuSelection = NONE;
			continue;
		}

		m_currentPokemonIndex = m_menu->getButtonIndex();
		swapPokemon();
		

		m_menuSelection = NONE;
	}

	m_menu->setCanLeave(false);
	m_menu->clearRequestedData();
	m_menu->reset(MenuScene::USE_PC);
	m_menu->postRun();
}

bool PC::pokemonAtMenuIndex()
{

	int index = m_menu->getButtonIndex();

	if (index < 30)
	{
		if (m_pcPokemon[m_currentBox][index].getLevel() != 0)
			return true;
		return false;
	}

	if (m_trainer->getPokemon(index - 30).getLevel() != 0)
		return true;
	return false;
}

void PC::setupOverlay()
{
	int index = m_menu->getButtonIndex();

	if (index < 30)
		setupBoxOverlay(index);
	else
		setupRosterOverlay(index);

	setupOptions();
}

void PC::setupBoxOverlay(int index)
{
	//TODO: Get values from shared value file
	float topLeftBoxX = (500.0f / 1000.0f) * 100.0f;
	float topLeftBoxY = (450.0f / 563.0f) * 100.0f;

	float boxSizeMulitplier = 1.25f;
	float boxWidth = 9.0f / boxSizeMulitplier;
	float boxHeight = 16.0f / boxSizeMulitplier;

	float boxXGap = boxWidth + ((10.0f / 1000.0f) * 100.0f);
	float boxYGap = boxHeight + ((10.0f / 563.0f) * 100.0f);

	int boxX = (index % 5);
	int boxY = floor(index / 5.0f);

	m_pcSelectionY = topLeftBoxY - (boxYGap * boxY);

	switch (boxX)
	{
	case 0:
		m_pcSelectionX = topLeftBoxX + (boxXGap * -2);
		break;
	case 1:
		m_pcSelectionX = topLeftBoxX + (boxXGap * -1);
		break;
	case 2:
		m_pcSelectionX = topLeftBoxX + (boxXGap * 0);
		break;
	case 3:
		m_pcSelectionX = topLeftBoxX + (boxXGap * 1);
		break;
	case 4:
		m_pcSelectionX = topLeftBoxX + (boxXGap * 2);
		break;
	};
}

void PC::setupRosterOverlay(int index)
{
	float boxSizeMulitplier = 1.25f;
	float boxWidth = 9.0f / boxSizeMulitplier;
	float boxHeight = 16.0f / boxSizeMulitplier;

	float boxXGap = boxWidth + ((10.0f / 1000.0f) * 100.0f);
	float boxYGap = boxHeight + ((10.0f / 563.0f) * 100.0f);

	float rosterLeftBoxX = (875.0f / 1000.0f) * 100.0f;
	float rosterLeftBoxY = ((450.0f / 563.0f) * 100.0f) + (boxHeight / 2.0f);
	float rosterBoxOffset = boxHeight / 2.0f;

	int rosterIndex = index - 30;

	m_pcSelectionX = rosterLeftBoxX;
	m_pcSelectionY = rosterLeftBoxY;

	if (rosterIndex % 2 == 1)
		m_pcSelectionX += (boxXGap * 1);

	switch (rosterIndex)
	{
	case 0:
		m_pcSelectionY -= (boxYGap * 2) - (rosterBoxOffset * 0);
		break;
	case 1:
		m_pcSelectionY -= (boxYGap * 2) + (rosterBoxOffset * 1);
		break;
	case 2:
		m_pcSelectionY -= (boxYGap * 3) - (rosterBoxOffset * 0);
		break;
	case 3:
		m_pcSelectionY -= (boxYGap * 3) + (rosterBoxOffset * 1);
		break;
	case 4:
		m_pcSelectionY -= (boxYGap * 4) - (rosterBoxOffset * 0);
		break;
	case 5:
		m_pcSelectionY -= (boxYGap * 4) + (rosterBoxOffset * 1);
		break;
	default:
		std::cout << "[PC] Setup Roster Overlay Error Index: " << index << std::endl;
		exit(1);
		break;
	}
}

void PC::setupOptions()
{
	//TODO: Shared File
	float boxSizeMulitplier = 1.25f;
	float boxWidth = 9.0f / boxSizeMulitplier;
	float boxHeight = 16.0f / boxSizeMulitplier;

	float optionWidth = boxWidth;
	float optionHeight = boxHeight / 4.0f;

	float leftAdjustment = optionWidth + (optionWidth / 8.0f);

	m_pcData.overlayBackgroundLocation.percentageX = m_pcSelectionX - leftAdjustment;
	m_pcData.overlayBackgroundLocation.percentageY = m_pcSelectionY;

	m_pcData.moveButtonData.percentageX = m_pcSelectionX - leftAdjustment;
	m_pcData.moveButtonData.percentageY = m_pcSelectionY + (optionHeight * 1.5f);
	m_pcData.moveButtonData.color = Color::WHITE;

	m_pcData.summaryButtonData.percentageX = m_pcSelectionX - leftAdjustment;
	m_pcData.summaryButtonData.percentageY = m_pcSelectionY + (optionHeight * 0.5f);
	m_pcData.summaryButtonData.color = Color::WHITE;

	m_pcData.renameButtonData.percentageX = m_pcSelectionX - leftAdjustment;
	m_pcData.renameButtonData.percentageY = m_pcSelectionY - (optionHeight * 0.5f);
	m_pcData.renameButtonData.color = Color::WHITE;

	m_pcData.deleteButtonData.percentageX = m_pcSelectionX - leftAdjustment;
	m_pcData.deleteButtonData.percentageY = m_pcSelectionY - (optionHeight * 1.5f);
	m_pcData.deleteButtonData.color = Color::WHITE;
}

void PC::setMoveHighlight(bool moveStatus)
{
	m_inMove = moveStatus;
	if (m_inMove == false)
		return;

	m_pcData.movePokemonHighlightData.percentageX = m_pcSelectionX;
	m_pcData.movePokemonHighlightData.percentageY = m_pcSelectionY;
}

void PC::runOverlay()
{
	/// Have them select their mode with the overlay
	/// 
	/// If move
	///	 - Set previous pokemon index
	///  - Set in move to true
	/// 
	/// if summary show the summary
	/// 
	/// if rename then rename
	/// 
	/// if delete then show the delete overlay
	/// 
	/// moveButton->data = 0;
	/// summaryButton->data = 1;
	/// renameButton->data = 2;
	/// deleteButton->data = 3;
	/// 
	
	int preSelectionButtonIndex = m_menu->getButtonIndex();

	setupOverlay();
	m_currentPokemonIndex = m_menu->getButtonIndex();
	m_menu->setOverlay(MenuOverlay::PC_SELECTION);
	m_menuSelection = NONE;

	while (!m_menu->shouldClose())
	{
		if (m_menu->shouldClose())
			break;

		m_menu->run();

		if (m_menu->leaveRequested())
		{
			m_menuSelection = NONE;
			m_menu->setOverlay(MenuOverlay::NONE);
			m_menu->setscene(MenuScene::USE_PC);
			return;
		}

		if (m_menuSelection != NONE)
			break;
	}

	//m_menuSelection = 0;	//TODO: Remove

	if (m_menuSelection == 0)
		setSwapPokemon();
	else if (m_menuSelection == 1)
		displayPokemonSummary();
	else if (m_menuSelection == 2)
	{
		renamePokemon(preSelectionButtonIndex);
		m_menu->setButtonIndex(preSelectionButtonIndex);
	}
	else
		deletePokemon();
	

	m_menuSelection = NONE;
	m_menu->setOverlay(MenuOverlay::NONE);
	m_menu->setscene(MenuScene::USE_PC);
}

void PC::swapPokemon()
{
	//TODO: Dont allow player to move the last pokemon out of their box
	{
		Pokemon pokemon;
		
		if (m_previousPokemonIndex < 30 && m_currentPokemonIndex < 30)	//	Box to Box
		{
			pokemon = m_pcPokemon[m_previousBox][m_previousPokemonIndex];
			m_pcPokemon[m_previousBox][m_previousPokemonIndex] = m_pcPokemon[m_currentBox][m_currentPokemonIndex];
			m_pcPokemon[m_currentBox][m_currentPokemonIndex] = pokemon;
		}
		else if (m_previousPokemonIndex < 30 && m_currentPokemonIndex >= 30)	//	Box to Trainer
		{
			pokemon = m_pcPokemon[m_previousBox][m_previousPokemonIndex];
			m_pcPokemon[m_previousBox][m_previousPokemonIndex] = m_trainer->getPokemon(m_currentPokemonIndex - 30);
			m_trainer->setPokemon(m_currentPokemonIndex - 30, pokemon);
		}
		else if (m_previousPokemonIndex >= 30 && m_currentPokemonIndex < 30) //Trainer to Box
		{
			if (playerHasEnoughPokemon())
			{
				pokemon = m_trainer->getPokemon(m_previousPokemonIndex - 30);
				m_trainer->setPokemon(m_previousPokemonIndex - 30, m_pcPokemon[m_currentBox][m_currentPokemonIndex]);
				m_pcPokemon[m_currentBox][m_currentPokemonIndex] = pokemon;
			}
			else
			{
				std::cout << "Cannot Move Final Pokemon Out of Trainer Box" << std::endl;
			}
		}
		else //Trainer to Trainer
		{
			pokemon = m_trainer->getPokemon(m_previousPokemonIndex - 30);
			m_trainer->setPokemon(m_previousPokemonIndex - 30, m_trainer->getPokemon(m_currentPokemonIndex - 30));
			m_trainer->setPokemon(m_currentPokemonIndex - 30, pokemon);
		}

	}

	m_previousPokemonIndex = NONE;
	setMoveHighlight(false);
	updateAllDisplays();
}

void PC::moveBoxRight()
{
	m_currentPokemonIndex = NONE;
	if (m_currentBox < 7)
		m_currentBox++;
	else
		m_currentBox = 0;

	updateBoxDisplay();
	updatePokemonStats();
}

void PC::moveBoxLeft()
{
	m_currentPokemonIndex = NONE;

	if (m_currentBox > 0)
		m_currentBox--;
	else
		m_currentBox = 7;

	updateBoxDisplay();
	updatePokemonStats();
}

void PC::updateAllDisplays()
{
	updateBoxDisplay();
	updatePokemonStats();
	updateRosterDisplay();
}

void PC::updateBoxDisplay()
{
	//system("CLS");
	//std::cout << "\tCurrent Box: " << m_currentBox << std::endl;

	//TODO: Box updates too often

	SharedString* columnData = nullptr;

	for (int col = 0; col < 6; col++)
	{
		if (col == 0)
			columnData = &m_pcData.pcTextures0;
		else if (col == 1)
			columnData = &m_pcData.pcTextures1;
		else if (col == 2)
			columnData = &m_pcData.pcTextures2;
		else if (col == 3)
			columnData = &m_pcData.pcTextures3;
		else if (col == 4)
			columnData = &m_pcData.pcTextures4;
		else if (col == 5)
			columnData = &m_pcData.pcTextures5;

		for (int row = 0; row < 5; row++)
		{
			std::string data = "";

			if (m_pcPokemon[m_currentBox][row + (col * 5)].getLevel() != 0)
				data = pokemonFrontTexture(m_pcPokemon[m_currentBox][row + (col * 5)].getSpecies().name);
	
			if (row == 0)
				columnData->string1 = data;
			else if (row == 1)
				columnData->string2 = data;
			else if (row == 2)
				columnData->string3 = data;
			else if (row == 3)
				columnData->string4 = data;
			else if (row == 4)
				columnData->string5 = data;
		}
	
		std::cout << std::endl;
	}
}

void PC::updatePokemonStats()
{
	int index = getPokemonStatIndex();

	if (index == -1 || index == m_pokemonStatsIndex)
		return;

	m_pokemonStatsIndex = index;

	Pokemon displayPokemon;

	if (m_pokemonStatsIndex < 30)
		displayPokemon = m_pcPokemon[m_currentBox][m_pokemonStatsIndex];
	else
		displayPokemon = m_trainer->getPokemon(m_pokemonStatsIndex - 30);



	//std::cout << "\t~ Pokemon Stats ~\n";
	//if (displayPokemon.getLevel() == 0)
	//{
	//	std::cout << "\t   ~ NONE ~";
	//	return;
	//}

	//std::cout << displayPokemon.getName() << "\tLv." << displayPokemon.getLevel() << std::endl;
	//std::cout << displayPokemon.getSpecies().name << std::endl;
	//
	//std::cout << "-----------------------\n";
	//
	//std::cout << displayPokemon.getCurHealth() << "/" << displayPokemon.getStats().hp << std::endl;
	//std::cout << "Attack : " << displayPokemon.getStats().attack << std::endl;
	//std::cout << "Defense: " << displayPokemon.getStats().defense << std::endl;
	//std::cout << "SP. ATK: " << displayPokemon.getStats().spAttack << std::endl;
	//std::cout << "SP. DEF: " << displayPokemon.getStats().spDefense << std::endl;
	//std::cout << "Speed  : " << displayPokemon.getStats().speed << std::endl;
	//
	//std::cout << "-----------------------\n\n";
	//std::cout << "Moves Learned\n";
	//std::cout << getAttackFromID(displayPokemon.getMoveset().move1)->getName() << std::endl;
	//std::cout << getAttackFromID(displayPokemon.getMoveset().move2)->getName() << std::endl;
	//std::cout << getAttackFromID(displayPokemon.getMoveset().move3)->getName() << std::endl;
	//std::cout << getAttackFromID(displayPokemon.getMoveset().move4)->getName() << std::endl;

}

void PC::updateRosterDisplay()
{
	for (int i = 0; i < 6; i++)
	{
		std::string texture;
		if (m_trainer->getRoster()[i].getLevel() == 0)
			texture = "";
		else
			texture = pokemonFrontTexture(m_trainer->getRoster()[i].getSpecies().name);

		if (i == 0)
			m_pcData.trainerRosterTextures.string1 = texture;
		else if (i == 1)
			m_pcData.trainerRosterTextures.string2 = texture;
		else if (i == 2)
			m_pcData.trainerRosterTextures.string3 = texture;
		else if (i == 3)
			m_pcData.trainerRosterTextures.string4 = texture;
		else if (i == 4)
			m_pcData.trainerRosterTextures.string5 = texture;
		else if (i == 5)
			m_pcData.trainerRosterTextures.string6 = texture;
	}
}

int PC::getPokemonStatIndex()
{
	int currentIndex = m_menu->getButtonIndex();

	if (currentIndex >= 36)
		return - 1;

	return currentIndex;
}

bool PC::playerHasEnoughPokemon()
{
	//If player has > 1 pokemon we return true
	//else false
	int count = 0;

	for (int i = 0; i < 6; i++)
	{
		if (count == 2)
			return true;

		if (m_trainer->getPokemon(i).getLevel() > 0)
			count++;
	}

	if (count == 2)
		return true;

	return false;
}

bool PC::isValidSelection()
{
	if (m_currentPokemonIndex < 30)
	{
		if (m_pcPokemon[m_currentBox][m_currentPokemonIndex].getLevel() == 0)
			return false;
	}
	else
	{
		if (m_trainer->getPokemon(m_currentPokemonIndex - 30).getLevel() == 0)
			return false;
	}
	return true;
}

void PC::setSwapPokemon()
{
	if (!isValidSelection())
		return;
	
	m_previousPokemonIndex = m_menu->getButtonIndex();
	m_previousBox = m_currentBox;
	setMoveHighlight(true);
}

void PC::displayPokemonSummary()
{
	m_menu->setOverlay(MenuOverlay::NONE);
	int index = m_menu->getButtonIndex();

	if (index < 30)
		MenuFunction::pokemonSummary(m_menu, m_pcPokemon[m_currentBox][index]);
	else
		MenuFunction::pokemonSummary(m_menu, m_trainer->getRoster()[index - 30]);

	m_menu->setCanLeave(true);
	m_menu->setRequestedData(&m_menuSelection);
	m_menu->preRun();
}

void PC::renamePokemon(int index)
{
	std::string pokemonName;

	if (index < 30)
	{
		m_pcData.selectedPokemonTexture = pokemonFrontTexture(m_pcPokemon[m_currentBox][index].getSpecies().name);
		pokemonName = m_pcPokemon[m_currentBox][index].getName();
	}
	else
	{
		m_pcData.selectedPokemonTexture = pokemonFrontTexture(m_trainer->getRoster()[index - 30].getSpecies().name);
		pokemonName = m_trainer->getRoster()[index - 30].getName();
	}	

	std::string newPokemonName = MenuFunction::keyboard(m_menu, MenuScene::RENAME_POKEMON, pokemonName, true);

	m_menu->setCanLeave(true);
	m_menu->setRequestedData(&m_menuSelection);
	m_menu->preRun();

	if (newPokemonName == "!")
		return;

	if (index < 30)
		m_pcPokemon[m_currentBox][index].setName(newPokemonName);
	else
		m_trainer->getRoster()[index - 30].setName(newPokemonName);
}

void PC::deletePokemon()
{
	//TODO: Pokemon Free Message needs to be adjusted when text renderer changed
	m_menuSelection = NONE;

	m_menu->setOverlay(MenuOverlay::NONE);
	int index = m_menu->getButtonIndex();
	m_menu->setOverlay(MenuOverlay::FREE_POKEMON_CONFIRMATION);

	m_pcData.freePokemonMessage = "Free " + m_pcPokemon[m_currentBox][index].getName() + "?";
	m_pcData.selectedPokemonTexture = pokemonFrontTexture(m_pcPokemon[m_currentBox][index].getSpecies().name);

	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_menu->leaveRequested())
			break;

		if (m_menuSelection == NONE)
			continue;

		if (m_menuSelection == 0)
		{
			setPokemon(m_currentBox, index, Pokemon());
			updateBoxDisplay();
		}
		
		break;
	}

	m_menuSelection = NONE;
	m_menu->setOverlay(MenuOverlay::NONE);
	m_menu->setscene(MenuScene::USE_PC);
}

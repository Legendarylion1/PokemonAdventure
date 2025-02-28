#include "InteractionHandler.h"

void InteractionHandler::setup(Trainer* player, MapHandler* mapHandler, Menu* menu, PC* pc, Battle* battleSimulator, DialogueRenderer* dialogueRenderer, Renderer* renderer)
{
	m_player = player;
	m_mapHandler = mapHandler;
	m_menu = menu;
	m_pc = pc;
	m_battleSimulator = battleSimulator;
	m_dialogueRenderer = dialogueRenderer;
	m_renderer = renderer;

	//m_menu->setupInteractionData(&m_availableItems, &m_playerBalance, &m_nursePokeballData);	//TODO: Remove
	MenuSetup::setupInteractionData(m_menu, &m_availableItems, &m_playerBalance, &m_nursePokeballData);
}

void InteractionHandler::evaluateInteraction()
{
	Coordinate interactionTile = m_player->position.coords;

	if (m_player->position.direction == Direction::UP)
		interactionTile.yTile += 1;
	else if (m_player->position.direction == Direction::DOWN)
		interactionTile.yTile -= 1;
	else if (m_player->position.direction == Direction::LEFT)
		interactionTile.xTile -= 1;
	else if (m_player->position.direction == Direction::RIGHT)
		interactionTile.xTile += 1;

	char tile = m_mapHandler->getTile(interactionTile);

	if (tile == 'N')
		nurseInteraction();
	else if (tile == 'I')
		buyItems(true);
	else if (tile == 'W')
		buyItems(false);
	else if (tile == 'C')
		m_pc->run();
	else if (tile == 'A')
		aiInteraction(interactionTile);
}

void InteractionHandler::nurseInteraction()
{

	// Intro Dialogue		| Step1
	// Place Pokeballs		| Step2
	// Flash Gold to heal	| Step3
	// Remove Pokeballs		| Step4
	// Outro data			| Step5


	resetPlayerPokemonData();

	int playerPokemonCount = 0;


	// Step 1
	if (!nurseShouldHeal())
		return;


	m_menu->setOverlay(MenuOverlay::NURSE_POKEBALL);
	m_menu->preRun();
	m_menu->setCanLeave(false);

	float count = 0.0f;
	float pauseDuration = 0.5f;

	int pokeballsPlaced = 0;

	for (int i = 0; i < 6; i++)
	{
		if (m_player->getRoster()[i].getLevel() == 0)
			continue;
		playerPokemonCount++;
	}

	//TODO: Possibly do first pokeball and then entire while for the rest. So that there is no delay for the first pokeball

	// Step 2
	while (!m_menu->shouldClose())
	{
		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_dialogueRenderer->renderDialogue();
		m_menu->onUpdate();

		count += m_menu->getDeltaTime();

		if (count >= pauseDuration)
		{
			if (pokeballsPlaced == playerPokemonCount)
				break;

			count = 0.0f;
			pokeballsPlaced += 1;

			if (pokeballsPlaced == 1)
				m_nursePokeballData.visibility.bool1 = true;
			else if (pokeballsPlaced == 2)
				m_nursePokeballData.visibility.bool2 = true;
			else if (pokeballsPlaced == 3)
				m_nursePokeballData.visibility.bool3 = true;
			else if (pokeballsPlaced == 4)
				m_nursePokeballData.visibility.bool4 = true;
			else if (pokeballsPlaced == 5)
				m_nursePokeballData.visibility.bool5 = true;
			else if (pokeballsPlaced == 6)
				m_nursePokeballData.visibility.bool6 = true;
		}
	}

	// Step 3
	flashPokeballs();

	// Step 4
	m_menu->setCanLeave(true);
	m_menu->postRun();
	m_menu->setOverlay(MenuOverlay::NONE);


	// Step 5
	renderDialogue("I've restored your pokemon", "to full health", m_nurseName, true);
	renderDialogue("Come again soon!", "", m_nurseName, true);
}

void InteractionHandler::buyItems(bool buyBattleItems)
{
	PokeMart mart = PokeMart(m_mapHandler, m_player, m_menu, buyBattleItems);

	 mart.run(m_renderer);
}

void InteractionHandler::aiInteraction(Coordinate aiPosition)
{

	NPT* ai = m_mapHandler->getAI(aiPosition);

	turnAIToPlayer(ai);

	for (Dialogue dialogue : ai->getDialogue())
		renderDialogue(dialogue.topLine, dialogue.botLine, ai->getName(), true);

	if (ai == nullptr)
	{
		std::cout << "AI doesnt exist. Interaction Handler. Handle error. Position entered (" << aiPosition.xTile << "," << aiPosition.yTile << ")" << std::endl;
		exit(ErrorCodes::OUTSIDE_SCOPE);
	}
	

	if (ai->wantsToBattle())
	{
		m_battleSimulator->beginBattle(ai);


		if (m_player->unableToBattle())
		{
			// TODO: Animate Whiteout
			m_mapHandler->respawnAfterWhiteOut();
		}
	}
}

void InteractionHandler::resetPlayerPokemonData()
{
	m_nursePokeballData.visibility.bool1 = false;
	m_nursePokeballData.visibility.bool2 = false;
	m_nursePokeballData.visibility.bool3 = false;
	m_nursePokeballData.visibility.bool4 = false;
	m_nursePokeballData.visibility.bool5 = false;
	m_nursePokeballData.visibility.bool6 = false;

	for (int i = 0; i < 6; i++)
	{
		if (m_player->getRoster()[i].getLevel() == 0)
			continue;

		std::string textureLocation;

		switch (m_player->getRoster()[i].getPokeball())
		{
		case ItemID::POKEBALL:
			textureLocation = g_overlayTextureLocations[MenuOverlay::NURSE_POKEBALL];
			break;
		case ItemID::GREATBALL:
			textureLocation = g_overlayTextureLocations[MenuOverlay::NURSE_GREATBALL];
			break;
		case ItemID::ULTRABALL:
			textureLocation = g_overlayTextureLocations[MenuOverlay::NURSE_ULTRABALL];
			break;
		case ItemID::MASTERBALL:
			textureLocation = g_overlayTextureLocations[MenuOverlay::NURSE_MASTERBALL];
			break;
		default:
			std::cout << "Invalid Pokeball in interaction Handler" << std::endl;
			break;
		}

		switch (i)
		{
		case 0:
			m_nursePokeballData.textures.string1 = textureLocation;
			break;
		case 1:
			m_nursePokeballData.textures.string2 = textureLocation;
			break;
		case 2:
			m_nursePokeballData.textures.string3 = textureLocation;
			break;
		case 3:
			m_nursePokeballData.textures.string4 = textureLocation;
			break;
		case 4:
			m_nursePokeballData.textures.string5 = textureLocation;
			break;
		case 5:
			m_nursePokeballData.textures.string6 = textureLocation;
			break;
		}

		m_player->getRoster()[i].fullRestore();
		Moveset moveset = m_player->getRoster()[i].getMoveset();

		if (moveset.move1 != NONE)
			moveset.move1pp = getAttackFromID(moveset.move1)->getPP();

		if (moveset.move2 != NONE)
			moveset.move2pp = getAttackFromID(moveset.move2)->getPP();

		if (moveset.move3 != NONE)
			moveset.move3pp = getAttackFromID(moveset.move3)->getPP();

		if (moveset.move4 != NONE)
			moveset.move4pp = getAttackFromID(moveset.move4)->getPP();

		m_player->getRoster()[i].setMoveset(moveset);
	}
}

void InteractionHandler::flashPokeballs()
{
	for (int timesToFlash = 0; timesToFlash < 4; timesToFlash++)
	{
		for (int i = 0; i < 5; i++)
		{

			changeImageNumber(&m_nursePokeballData.textures.string1, i);
			changeImageNumber(&m_nursePokeballData.textures.string2, i);
			changeImageNumber(&m_nursePokeballData.textures.string3, i);
			changeImageNumber(&m_nursePokeballData.textures.string4, i);
			changeImageNumber(&m_nursePokeballData.textures.string5, i);
			changeImageNumber(&m_nursePokeballData.textures.string6, i);

			float count = 0.0f;
			float target = 0.07f;

			while (count < target)
			{
				if (m_menu->shouldClose())
					break;

				m_mapHandler->onUpdate();
				m_player->onUpdate(m_renderer);
				m_dialogueRenderer->renderDialogue();
				m_menu->onUpdate();

				count += m_menu->getDeltaTime();
			}
		}
	}
}

void InteractionHandler::changeImageNumber(std::string* textureLocation, int newNumber)
{
	std::string newString = *textureLocation;
	if (newString == "")
		return;

	newString[newString.size() - 5] = '0' + newNumber;
	
	*textureLocation = newString;
}

bool InteractionHandler::nurseShouldHeal()
{
	renderDialogue("Welcome to the pokemon center","", m_nurseName, true);

	int shouldHeal = NONE;
	renderDialogue("Would you like me to","restore your pokemon's health?", m_nurseName, true, &shouldHeal, "Yes", "No");

	if ((bool)shouldHeal)
		renderDialogue("Okay I'll take your pokemon", "for a few seconds", m_nurseName, true);
	else
		renderDialogue("Okay come again soon!", "", m_nurseName, true);

	return (bool)shouldHeal;
}

void InteractionHandler::updateShopItems()
{
	//std::vector<ItemID> items = m_mapHandler->getAvailableItems();
	//
	//int count = 0;
	//int itemCount = 0;
	//
	//for (ItemID id : items)
	//{
	//	if (itemCount != m_itemIndex)
	//	{
	//		itemCount++;
	//		continue;
	//	}
	//
	//	if (count == 6)
	//		break;
	//
	//	if (count == 0)
	//		m_availableItems.string1 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
	//	else if (count == 1)
	//		m_availableItems.string2 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
	//	else if (count == 2)
	//		m_availableItems.string3 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
	//	else if (count == 3)
	//		m_availableItems.string4 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
	//	else if (count == 4)
	//		m_availableItems.string5 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
	//	else if (count == 5)
	//		m_availableItems.string6 = getItemFromID(id)->getName() + " -> " + std::to_string(getItemFromID(id)->getCost());
	//
	//	count++;
	//}
}

void InteractionHandler::purchaseItem(int index)
{
	//ItemID id = m_mapHandler->getAvailableItems().at(index + m_itemIndex);
	//int itemCost = getItemFromID(id)->getCost();
	//if (m_player->getBalance() >= itemCost)
	//{
	//	m_player->reduceMoney(itemCost);
	//	m_playerBalance = "Balance: " + std::to_string(m_player->getBalance());
	//	m_player->addItem(id);
	//}

}

void InteractionHandler::turnAIToPlayer(NPT* npt)
{
	switch (m_player->position.direction)
	{
	case Direction::UP:
		npt->position.direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		npt->position.direction = Direction::UP;
		break;
	case Direction::LEFT:
		npt->position.direction = Direction::RIGHT;
		break;
	case Direction::RIGHT:
		npt->position.direction = Direction::LEFT;
		break;
	}
}

void InteractionHandler::renderDialogue(std::string topLine, std::string botLine, std::string speakerName, bool awaitClick, int* requestedData, std::string topOption, std::string bottomOption)
{
	m_dialogueRenderer->setSpeakerName(speakerName);
	m_dialogueRenderer->setDialogue(topLine, botLine, awaitClick, false, requestedData, topOption, bottomOption);

	while (m_dialogueRenderer->rendereringDialogue())
	{
		if (m_menu->shouldClose())
			break;

		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_dialogueRenderer->renderDialogue();
		m_renderer->onUpdate();
	}
}

#include "PauseHandler.h"

void PauseHandler::setup(Menu* menu, Trainer* player, Input* input, DataManager* dataManager, Renderer* renderer, CharacterMover* characterMover, Timer* timer, RosterDisplayData* rosterData, Pokedex* pokedex, DialogueRenderer* dialogueRenderer, MapHandler* mapHandler)
{
	m_menu = menu;
	m_player = player;
	m_input = input;
	m_dataManager = dataManager;
	m_renderer = renderer;
	m_characterMover = characterMover;
	m_timer = timer;
	m_rosterData = rosterData;
	m_pokedex = pokedex;
	m_dialogueRenderer = dialogueRenderer;
	m_mapHandler = mapHandler;

	//m_menu->setupPauseData(&m_items, &m_pauseMenuData, m_rosterData, &m_pauseSettingData);		//TODO: REMOVE
	MenuSetup::setupPauseData(m_menu, &m_items, &m_pauseMenuData, m_rosterData, &m_pauseSettingData);
}

void PauseHandler::run(CutSceneID currentScene)
{
	m_selection = NONE;
	m_menu->setCanLeave(true);
	m_menu->setscene(MenuScene::PAUSE_MENU);
	m_menu->setRequestedData(&m_selection);
	m_menu->preRun();

	m_pauseMenuData.playerBalance = std::to_string(m_player->getBalance());
	m_pauseMenuData.playTime = m_timer->getPlayTimeDisplay();

	setBadgeVisibility();
	setPauseButtonVisibility(currentScene);

	while (!m_menu->shouldClose())
	{
		//system("CLS");
		m_menu->run();

		if (m_menu->leaveRequested())
			break;

		if (m_menu->getButtonIndex() == 1)
			m_pauseMenuData.pokedexHighlightVisible = true;
		else if (m_menu->getButtonIndex() == 2)
			m_pauseMenuData.mapHighlightVisible = true;
		else
		{
			m_pauseMenuData.pokedexHighlightVisible = false;
			m_pauseMenuData.mapHighlightVisible = false;
		}

		if (m_selection != NONE)
		{
			switch (m_selection)
			{
			case 0:
				handleRoster();
				break;
			case 1:
				handleItems();
				break;
			case 2:
				handleMap();
				break;
			case 3:
				handleSettings();
				break;
			case 4:
				handleSave();
				break;
			case 5:
				//m_dataManager->saveGame();	//TODO: SAFE EXIT HERE TOO!!!!
				//std::cout << "Game Saved!" << std::endl;
				//exit(0);
				glfwSetWindowShouldClose(m_renderer->getWindow(), GLFW_TRUE);
				break;
			case 6:
				m_pokedex->run();
				m_menu->setRequestedData(&m_selection);
				m_menu->preRun();
				break;
			}

			m_menu->setscene(MenuScene::PAUSE_MENU);

			m_selection = NONE;
			m_playTime = m_timer->getPlayTimeDisplay();
		}

	}

	m_menu->clearRequestedData();
	m_menu->reset(MenuScene::PAUSE_MENU);
	m_menu->setscene(MenuScene::NONE);
	m_menu->postRun();

}

void PauseHandler::handleRoster()
{
	enum RosterMode
	{
		HOVER,
		SWAP,
		VIEW,
	};

	updateDisplayPokemon(m_player, m_rosterData);
	m_selection = NONE;
	int swapIndex = NONE;

	RosterMode mode = RosterMode::HOVER;

	int hoveredIndex = -1;

	m_menu->preRun();
	while (!m_menu->shouldClose())
	{
		updateDisplayPokemonStats(&hoveredIndex, m_player, m_menu->getButtonIndex(), m_rosterData);
		m_menu->run();

		if (m_menu->leaveRequested())
		{
			if (mode == RosterMode::SWAP)
			{
				swapIndex = NONE;
				mode = RosterMode::HOVER;
				continue;
			}

			break;
		}


		if (m_selection == NONE)
			continue;

		if (m_player->getPokemon(m_selection).getLevel() == 0 && mode != RosterMode::SWAP)
		{
			m_selection = NONE;
			continue;
		}

		if (mode == RosterMode::HOVER)
		{
			int option = MenuFunction::displayRosterOptions(std::vector<std::string>{"SWAP", "VIEW"}, m_selection, m_menu, m_renderer);

			if (option == 0)
				mode = RosterMode::SWAP;
			else if (option == 1)
				mode = RosterMode::VIEW;
		}

		if (mode == RosterMode::SWAP)
		{
			if (swapIndex == NONE)
			{
				//TODO: Highlight selected pokemon with an arrow or something
				swapIndex = m_selection;
			}
			else
			{
				Pokemon toSwap = m_player->getPokemon(swapIndex);

				m_player->setPokemon(swapIndex, m_player->getPokemon(m_selection));
				m_player->setPokemon(m_selection, toSwap);

				hoveredIndex = -1;
				swapIndex = NONE;
				mode = RosterMode::HOVER;

				updateDisplayPokemon(m_player, m_rosterData);
			}
		}

		if (mode == RosterMode::VIEW)
		{
			MenuFunction::pokemonSummary(m_menu, m_player->getRoster()[m_selection]);
			mode = RosterMode::HOVER;
		}
		
		m_menu->setscene(MenuScene::PAUSE_ROSTER);
		m_menu->setRequestedData(&m_selection);
		m_menu->preRun();
		m_selection = NONE;
	}
	m_menu->postRun();
}

void PauseHandler::handleItems()
{
	// World Items need to be handled by something else
	// Heals -> Heal Pokemon
	// Non usable items shouldnt be selectable
	//
	m_bagIndex = 0;
	m_selection = NONE;

	updatePlayerItems();	

	m_menu->setscene(MenuScene::PAUSE_BAG);

	m_menu->preRun();
	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_menu->leaveRequested())
		{
			m_menu->reset(MenuScene::PAUSE_BAG);
			return;
		}

		if (m_selection == NONE)
			continue;

		if (m_selection == arrowDirections::UP)
		{
			moveWindowUp();
			continue;
		}
		else if (m_selection == arrowDirections::DOWN)
		{
			moveWindowDown();
			continue;
		}

		ItemID selectedItem = getSelectedItem();

		Item* item = getItemFromID(selectedItem);

		switch (item->getType())
		{
		case ItemType::MEDICINE:
			if (usedMedicine(item))
				m_player->removeItem(selectedItem);
		case ItemType::WORLD:
		case ItemType::POKEBALL:
		default:
			m_selection = NONE;
			updatePlayerItems();
			m_menu->setscene(MenuScene::PAUSE_BAG);
			m_menu->setOverlay(MenuOverlay::NONE);
			m_menu->preRun();
			continue;
			break;

		}

	}

	m_menu->postRun();
}

void PauseHandler::handleSettings()
{
	m_selection = NONE;
	m_menu->preRun();
	m_input->updateKeyBinds(&m_pauseSettingData);
	m_renderer->adjustRenderSettings(&m_pauseSettingData);
	m_dialogueRenderer->adjustPauseDisplay(&m_pauseSettingData.fasterText);
	m_mapHandler->adjustPauseDisplay(&m_pauseSettingData.autoSave);

	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_menu->leaveRequested())
		{
			m_menu->reset(MenuScene::PAUSE_SETTINGS);
			m_menu->setscene(MenuScene::PAUSE_MENU);
			return;
		}
		
		if (m_selection == NONE)
			continue;

		if (m_selection < 16)
		{
			selectNewInput(ControlType::KEYBOARD);
			m_input->updateKeyBinds(&m_pauseSettingData);
		}
		else if (m_selection >= 21)
		{
			selectNewInput(ControlType::CONTROLLER_BUTTON);
			m_input->updateKeyBinds(&m_pauseSettingData);
		}
		else if (m_selection == 16)
		{
			selectResolution();
			m_renderer->adjustRenderSettings(&m_pauseSettingData);
		}
		else if (m_selection == 17)
		{
			m_renderer->toggleFullScreen();
			m_renderer->adjustRenderSettings(&m_pauseSettingData);
		}
		else if (m_selection == 18)
		{
			m_renderer->toggleShowFPS();
			m_renderer->adjustRenderSettings(&m_pauseSettingData);
		}
		else if (m_selection == 19)
		{
			// AutoSave
			m_mapHandler->toggleFasterText();
			m_mapHandler->adjustPauseDisplay(&m_pauseSettingData.autoSave);
			
		}
		else if (m_selection == 20)
		{
			// Faster Text
			m_dialogueRenderer->toggleFasterText();
			m_dialogueRenderer->adjustPauseDisplay(&m_pauseSettingData.fasterText);
		}

		m_selection = NONE;
	}
	m_menu->postRun();
}

void PauseHandler::handleMap()
{
	InteractiveMap map = InteractiveMap(m_renderer, m_input, MapSubSectionID::ROUTE_1);
	map.run(m_mapHandler->getSubsection());
}

void PauseHandler::handleSave()
{
	m_dataManager->saveGame();

	m_selection = NONE;
	m_menu->setOverlay(MenuOverlay::SAVE_COMPLETE);

	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_selection != NONE)
			break;
	}
}

void PauseHandler::selectResolution()
{
	m_selection = NONE;
	m_menu->setCanLeave(true);

	while (!m_menu->shouldClose())
	{
		
		m_menu->run();

		if (m_menu->leaveRequested())
			break;

		if (m_selection == NONE)
			continue;

		switch (m_selection)
		{
		case RendererResolutiion::_1280x720:
			m_renderer->setResolution(RendererResolutiion::_1280x720);
			break;
		case RendererResolutiion::_1920x1080:
			m_renderer->setResolution(RendererResolutiion::_1920x1080);
			break;
		case RendererResolutiion::_2560x1440:
			m_renderer->setResolution(RendererResolutiion::_2560x1440);
			break;
		default:
			break;
		}

		m_characterMover->setTileSize(m_renderer->getTileSize());
		break;
		
	}

	m_menu->setCanLeave(false);
}

void PauseHandler::selectNewInput(ControlType type)
{
	KeyPriority priority = KeyPriority::MAIN;
	InputRequest request = InputRequest::EMPTY;
	float currentDelay = 0.0f;
	float preSwapDelay = 0.1f;
	float postSwapDelay = 0.1f;

	if ((m_selection < 16 && m_selection % 2 == 1) || (m_selection >= 21 && m_selection % 2 == 0 ))
			priority = KeyPriority::ALT;

	int requestValue = m_selection;

	if (requestValue >= 21)
		requestValue -= 21;

	requestValue = (int)floor(requestValue / 2.0f);

	if (requestValue == 0)
		request = InputRequest::UP;
	else if (requestValue == 1)
		request = InputRequest::DOWN;
	else if (requestValue == 2)
		request = InputRequest::LEFT;
	else if (requestValue == 3)
		request = InputRequest::RIGHT;
	else if (requestValue == 4)
		request = InputRequest::SELECT;
	else if (requestValue == 5)
		request = InputRequest::BACK;
	else if (requestValue == 6)
		request = InputRequest::PAUSE;
	else if (requestValue == 7)
		request = InputRequest::SPRINT;

	m_menu->preRun();

	while (currentDelay < preSwapDelay)
	{
		if (m_menu->shouldClose())
			break;

		m_timer->onUpdate();
		currentDelay += m_timer->getDelta();
		m_menu->renderMenu();
		m_input->onUpdate();
		m_renderer->onUpdate();

		std::cout << "In Pre delay" << std::endl;
	}

	while (m_input->changingInput(type, priority, request))
	{
		if (m_menu->shouldClose())
			break;

		m_menu->run();
	}

	currentDelay = 0.0f;
	while (currentDelay < postSwapDelay)
	{
		if (m_menu->shouldClose())
			break;

		m_timer->onUpdate();
		currentDelay += m_timer->getDelta();
		m_menu->renderMenu();
		m_input->onUpdate();
		m_renderer->onUpdate();
		//m_input->refreshKeyPresses();

		std::cout << "In Post delay" << std::endl;
	}

	m_menu->setOverlay(MenuOverlay::NONE);
	m_selection = NONE;
	m_menu->preRun();
}

void PauseHandler::updatePlayerItems()
{
	int count = 0;
	int indexCount = 0;

	for (auto i = m_player->getItemStorage()->getAllItems()->begin(); i != m_player->getItemStorage()->getAllItems()->end(); i++)
	{
		if (indexCount != m_bagIndex)
		{
			indexCount++;
			continue;
		}
		if (count == 5)
			break;
		if (i->second == 0)
			continue;


		switch (count)
		{
		case 0:
			//TODO: What is the purpose of this function lmfao
			formatRosterData(&m_items.itemName.string1, getItemFromID(i->first)->getName());
			m_items.itemAmount.string1 = "x" + std::to_string(i->second);
			m_items.itemTexture.string1 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
			break;
		case 1:
			formatRosterData(&m_items.itemName.string2, getItemFromID(i->first)->getName());
			m_items.itemAmount.string2 = "x" + std::to_string(i->second);
			m_items.itemTexture.string2 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
			break;
		case 2:
			formatRosterData(&m_items.itemName.string3, getItemFromID(i->first)->getName());
			m_items.itemAmount.string3 = "x" + std::to_string(i->second);
			m_items.itemTexture.string3 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
			break;
		case 3:
			formatRosterData(&m_items.itemName.string4, getItemFromID(i->first)->getName());
			m_items.itemAmount.string4 = "x" + std::to_string(i->second);
			m_items.itemTexture.string4 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
			break;
		case 4:
			formatRosterData(&m_items.itemName.string5, getItemFromID(i->first)->getName());
			m_items.itemAmount.string5 = "x" + std::to_string(i->second);
			m_items.itemTexture.string5 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
			break;
		}


		count++;
	}

	for (int i = count; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			formatRosterData(&m_items.itemName.string1, "NONE");
			m_items.itemAmount.string1 = "";
			m_items.itemTexture.string1 = "";
			break;
		case 1:
			formatRosterData(&m_items.itemName.string2, "NONE");
			m_items.itemAmount.string2 = "";
			m_items.itemTexture.string2 = "";
			break;
		case 2:
			formatRosterData(&m_items.itemName.string3, "NONE");
			m_items.itemAmount.string3 = "";
			m_items.itemTexture.string3 = "";
			break;
		case 3:
			formatRosterData(&m_items.itemName.string4, "NONE");
			m_items.itemAmount.string4 = "";
			m_items.itemTexture.string4 = "";
			break;
		case 4:
			formatRosterData(&m_items.itemName.string5, "NONE");
			m_items.itemAmount.string5 = "";
			m_items.itemTexture.string5 = "";
			break;
		}
	}


}

void PauseHandler::moveWindowUp()
{
	if (m_bagIndex > 0)
		m_bagIndex--;

	m_selection = NONE;
	updatePlayerItems();
}

void PauseHandler::moveWindowDown()
{
	int testIndex = m_bagIndex + 1;

	int count = 0;
	int itemWindowScroll = 0;

	for (auto i = m_player->getItemStorage()->getAllItems()->begin(); i != m_player->getItemStorage()->getAllItems()->end(); i++)
	{
		if (itemWindowScroll != testIndex)
		{
			itemWindowScroll++;
			continue;
		}

		if (count == 5)
		{
			count++;
			m_bagIndex++;
			updatePlayerItems();
			break;
		}

		if (i->second == 0)
			continue;

		count++;
	}

	if (count == 5)
	{
		m_bagIndex++;
		updatePlayerItems();
	}

	m_selection = NONE;
}

ItemID PauseHandler::getSelectedItem()
{
	int count = 0;
	int itemWindowScroll = 0;

	for (auto i = m_player->getItemStorage()->getAllItems()->begin(); i != m_player->getItemStorage()->getAllItems()->end(); i++)
	{
		if (itemWindowScroll != m_bagIndex)
		{
			itemWindowScroll++;
			continue;
		}

		if (count == 5)
			break;

		if (i->second == 0)
			continue;

		if (count == m_selection)
		{
			return i->first;
		}

		count++;
	}


	std::cout << "Item Not Found" << std::endl;
	return ItemID::POKEBALL;
}

bool PauseHandler::usedMedicine(Item* item)
{
	// Select From Roster

	// Invalid Selection Continue

	// Back go Back

	// Valid Selection
	//	- Watch pokemon health go up
	//  - See status get cleared
	//  - Display Message go back to items


	updateDisplayPokemon(m_player, m_rosterData);
	m_menu->setscene(MenuScene::BATTLE_ROSTER);

	m_selection = NONE;

	int hoveredIndex = -1;

	m_menu->preRun();
	while (!m_menu->shouldClose())
	{
		updateDisplayPokemonStats(&hoveredIndex, m_player, m_menu->getButtonIndex(), m_rosterData);
		m_menu->run();

		if (m_menu->leaveRequested())
		{
			break;
		}


		if (m_selection == NONE)
			continue;

		Pokemon pokemon = m_player->getPokemon(m_selection);
		Pokemon dataPokemon = pokemon;

		if (pokemon.getLevel() == 0)
		{
			m_selection = NONE;
			continue;
		}

		if (MenuFunction::displayRosterOptions(std::vector<std::string>{"SELECT", "VIEW"}, m_selection, m_menu, m_renderer) == 1)
		{
			MenuFunction::pokemonSummary(m_menu, m_player->getRoster()[m_selection]);

			m_menu->setscene(MenuScene::BATTLE_ROSTER);
			m_menu->setRequestedData(&m_selection);
			m_selection = NONE;
			m_menu->preRun();
			continue;
		}
		

		if (item->canBeUsedOnPokemon(&pokemon))
		{
			animateHeal(item, &pokemon, &dataPokemon, &hoveredIndex);
			
			m_player->setPokemon(m_selection, pokemon);
			m_menu->setRequestedData(&m_selection);
			return true;
		}
		else
		{
			m_menu->setRequestedData(&m_selection);
			m_selection = NONE;
		}

	}
	m_menu->postRun();
	m_menu->setRequestedData(&m_selection);

	return false;
}

void PauseHandler::animateHeal(Item* item, Pokemon* pokemon, Pokemon* dataPokemon, int* hoveredIndex)
{
	std::vector<SimulationCommand> commands = item->getItemData(dataPokemon, SelectedUser::PLAYER, m_selection);

	for (SimulationCommand command : commands)
	{
		if (command.type == SimulationType::ITEM)
		{
			for (int i = 0; i < command.itemData.healAmount; i++)
			{
				pokemon->adjustCurHealth(1);
				m_player->setPokemon(m_selection, *pokemon);
				updateDisplayPokemon(m_player, m_rosterData);
				updateDisplayPokemonStats(hoveredIndex, m_player, m_menu->getButtonIndex(), m_rosterData);

				float dripCount = 0;
				float rate = 0.0005f;

				while (dripCount < rate)
				{
					if (m_menu->shouldClose())
						break;

					m_menu->renderMenu();
					m_renderer->onUpdate();
					dripCount += m_timer->getDelta();
				}
			}

			if (command.itemData.message != "")
			{
				m_dialogueRenderer->setDialogue(command.itemData.message, "", true);

				while (m_dialogueRenderer->rendereringDialogue())
				{
					if (m_menu->shouldClose())
						break;

					m_dialogueRenderer->renderDialogue();
					m_renderer->onUpdate();
				}
			}

		}
		else if (command.type == SimulationType::STATUS)
		{
			pokemon->removeMajorStatus();
			m_player->setPokemon(m_selection, *pokemon);
			updateDisplayPokemon(m_player, m_rosterData);
			updateDisplayPokemonStats(hoveredIndex, m_player, m_menu->getButtonIndex(), m_rosterData);


			if (command.statusData.message == "")
			{
				m_dialogueRenderer->setDialogue(command.statusData.message, "", true);

				while (m_dialogueRenderer->rendereringDialogue())
				{
					if (m_menu->shouldClose())
						break;

					m_dialogueRenderer->renderDialogue();
					m_renderer->onUpdate();
				}
			}

		}
	}
}

//void PauseHandler::formatMoveStringData(Pokemon displayPokemon, MoveStringData* data, int moveIndex)
//{
//	Attack* attack = nullptr;
//
//	if (moveIndex == 1)
//	{
//		attack = getAttackFromID(displayPokemon.getMoveset().move1);
//		data->currentPP = std::to_string(displayPokemon.getMoveset().move1pp);
//	}
//	else if (moveIndex == 2)
//	{
//		attack = getAttackFromID(displayPokemon.getMoveset().move2);
//		data->currentPP = std::to_string(displayPokemon.getMoveset().move2pp);
//	}
//	else if (moveIndex == 3)
//	{
//		attack = getAttackFromID(displayPokemon.getMoveset().move3);
//		data->currentPP = std::to_string(displayPokemon.getMoveset().move3pp);
//	}
//	else
//	{
//		attack = getAttackFromID(displayPokemon.getMoveset().move4);
//		data->currentPP = std::to_string(displayPokemon.getMoveset().move4pp);
//	}
//
//	if (attack->getName() != getAttackFromID(NONE)->getName())
//	{
//		data->moveName = attack->getName();
//		data->maxPP = std::to_string(attack->getPP());
//		data->moveTextureLocation = g_typeTextureLocations[attack->getType()];
//	}
//	else
//	{
//		data->moveName = "NONE";
//		data->currentPP = "0";
//		data->maxPP = "NONE";
//		data->moveTextureLocation = "";
//	}
//	
//}

void PauseHandler::setHighlightedPokemonHP(Pokemon displayPokemon)
{
	float maxPercent = 13.8f;

	m_pausePokemonData.hpPercent = maxPercent * ((float)displayPokemon.getCurHealth() / (float)displayPokemon.getStats().hp);
}

void PauseHandler::setBadgeVisibility()
{
	switch (m_player->getBadgeCount())
	{
	case 8:
		m_pauseMenuData.badgeData.dragonBadgeVisibility = true;
	case 7:
		m_pauseMenuData.badgeData.waterBadgeVisibility = true;
	case 6:
		m_pauseMenuData.badgeData.rockBadgeVisibility = true;
	case 5:
		m_pauseMenuData.badgeData.normalBadgeVisibility = true;
	case 4:
		m_pauseMenuData.badgeData.iceBadgeVisibility = true;
	case 3:
		m_pauseMenuData.badgeData.grassBadgeVisibility = true;
	case 2:
		m_pauseMenuData.badgeData.flyingBadgeVisibility = true;
	case 1:
		m_pauseMenuData.badgeData.fireBadgeVisibility = true;
		break;
	default:
		break;
	}
}

void PauseHandler::setPauseButtonVisibility(CutSceneID currentScene)
{
	//We need to check the scene after the ability was given

	if ((int)currentScene < (int)CutSceneID::RECIEVE_MAP_FROM_MOM + 1)
		m_pauseMenuData.mapButtonUsable = false;
	else
		m_pauseMenuData.mapButtonUsable = true;
	
	if ((int)currentScene < (int)CutSceneID::ENTER_PROFESSOR_LAB + 1)
		m_pauseMenuData.pokedexButtonUsable = false;
	else
		m_pauseMenuData.pokedexButtonUsable = true;
}

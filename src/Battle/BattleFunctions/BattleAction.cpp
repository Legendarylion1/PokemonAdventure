#include "BattleAction.h"

BattleAction::BattleAction()
{
}

void BattleAction::setup(Trainer* trainer, Menu* menu, SimulationCommand* playerCommand, SimulationCommand* aiCommand, int* playerPokemonIndex, int* opponentPokemonIndex, BattleMenuGraphics* battleMenuGraphics, Timer* timer)
{
	m_trainer = trainer;
	m_menu = menu;
	m_playerCommand = playerCommand;
	m_aiCommand = aiCommand;
	m_playerPokemonIndex = playerPokemonIndex;
	m_opponentPokemonIndex = opponentPokemonIndex;
	m_battleMenuGraphics = battleMenuGraphics;
	m_timer = timer;
}

void BattleAction::setOpponent(NPT* npt)
{
	m_npt = npt;
	m_wildPokemon = nullptr;
}

void BattleAction::setOpponent(Pokemon* pokemon)
{
	m_npt = nullptr;
	m_wildPokemon = pokemon;
}

void BattleAction::getAction()
{
	if (playerHasForcedAttack())
		return;

	updateAllGraphics();
	m_menu->setCanLeave(false);
	
	resetBattleAction();

	m_menu->preRun();
	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_playerCommand->selection1 == NONE)
			continue;

		if (m_playerCommand->selection1 == SimulationType::ATTACK_SELECTED)	//TODO: Use the command type. Send attacks to command1 and command2 is for forced moves
		{
			m_playerCommand->type = SimulationType::ATTACK_SELECTED;
			if (moveSelected())
				break;
		}
		else if (m_playerCommand->selection1 == SimulationType::POKEMON_SELECTED)
		{
			m_playerCommand->type = SimulationType::POKEMON_SELECTED;
			if (pokemonSelected())
				break;
		}
		else if (m_playerCommand->selection1 == SimulationType::ITEM_SELECTED)
		{
			m_playerCommand->type = SimulationType::ITEM_SELECTED;
			if (itemSelected())
				break;
		}
		else
		{
			m_playerCommand->type = SimulationType::FLEE_SELECTED;
			if (fleeSelected())
				break;
			// TODO: Gonna need dialogue renderer here
			//		Cant flee from trainer battles
		}

		resetBattleAction();
	}
	m_menu->postRun();
	m_menu->clearRequestedData();

	generateAICommand();
}

void BattleAction::updateAllGraphics()
{
	m_battleMenuGraphics->updateAllGraphics(m_itemWindowDisposition);
}

bool BattleAction::playerHasForcedAttack()
{
	if (m_trainer->getRoster()[*m_playerPokemonIndex].hasForcedAttack() == NONE)
		return false;

	m_playerCommand->type = SimulationType::ATTACK_SELECTED;
	m_playerCommand->commander = SelectedUser::PLAYER;
	m_playerCommand->selection2 = m_trainer->getRoster()[*m_playerPokemonIndex].hasForcedAttack();

	generateAICommand();

	return true;
}

void BattleAction::generateAICommand()
{
	Pokemon playerPokemon = m_trainer->getRoster()[*m_playerPokemonIndex];
	Pokemon opponentPokemon;

	if (m_wildPokemon != nullptr)
		opponentPokemon = *m_wildPokemon;
	else
		opponentPokemon = m_npt->getRoster()[*m_opponentPokemonIndex];

	m_aiCommand->type = SimulationType::ITEM_SELECTED;

	if (opponentPokemon.hasForcedAttack() != NONE)
	{
		m_aiCommand->type = SimulationType::ATTACK_SELECTED;
		m_aiCommand->selection2 = opponentPokemon.hasForcedAttack();
		return;
	}

	if (m_npt != nullptr)
	{
		bool healthCheck = opponentPokemon.getCurHealth() <= opponentPokemon.getStats().hp / 3.0f;
		bool statusCheck = opponentPokemon.getMajorStatus()->id != StatusID::NO_STATUS;

		if (healthCheck || statusCheck)
		{

			ItemStorage* storage = m_npt->getItemStorage();
			int count = 0;

			for (auto i = storage->getBattleItems()->begin(); i != storage->getBattleItems()->end(); i++)
			{
				if (i->second == 0)
				{
					count++;
					continue;
				}

				if (
					getItemFromID(i->first)->getStatus() != StatusID::NO_STATUS &&
					getItemFromID(i->first)->getStatus() == opponentPokemon.getMajorStatus()->id &&
					statusCheck
					)
				{
					m_aiCommand->itemData.id = getItemFromID(i->first)->getID();
					m_aiCommand->selection1 = count;
					m_aiCommand->selection2 = *m_opponentPokemonIndex;

					return;
				}
				else if (healthCheck && getItemFromID(i->first)->canBeUsedOnPokemon(&opponentPokemon))
				{
					m_aiCommand->itemData.id = getItemFromID(i->first)->getID();
					m_aiCommand->selection1 = count;
					m_aiCommand->selection2 = *m_opponentPokemonIndex;
					return;
				}

				count++;
			}

		}
	}




	m_aiCommand->type = ATTACK_SELECTED;


	std::vector<float> movePoints = { 0,0,0,0 };
	std::vector<int> highest = { 0 };

	for (int i = 0; i < 4; i++)
	{
		if (i == 0 && opponentPokemon.getMoveset().move1pp == 0)
			continue;
		else if (i == 1 && opponentPokemon.getMoveset().move2pp == 0)
			continue;
		else if (i == 2 && opponentPokemon.getMoveset().move3pp == 0)
			continue;
		else if (i == 3 && opponentPokemon.getMoveset().move4pp == 0)
			continue;

		Attack* attack = getAttackFromID(getAIMoveFromCommand(i));

		// Points for Damage
		movePoints.at(i) += attack->getPotentialDamage(&opponentPokemon, &playerPokemon) / 10.0f;


		// Points for Status
		if (canHaveStatus(&opponentPokemon, getAttackFromID(getAIMoveFromCommand(i))->getStatus()))
		{
			float statusMultiplier = (opponentPokemon.getLevel() + 100.0f) / 200.0f;
			movePoints.at(i) += (attack->getStatusOdds(&opponentPokemon, &playerPokemon) / 10.0f) * statusMultiplier;
		}

		// Points for buffs n stuff
		{
			float playerMultiplier = (randomNumber(101) / 20.0f) + ((opponentPokemon.getLevel() + 50) / 100.0f);
			float opponentMultiplier = (randomNumber(101) / 20.0f) + ((opponentPokemon.getLevel() + 50) / 100.0f);


			//TODO: Add accuracy here and all other places referenced
			if (attack->getPlayerStat().attack + attack->getPlayerStat().defense + attack->getPlayerStat().spAttack + attack->getPlayerStat().spDefense + attack->getPlayerStat().evasiveness + attack->getPlayerStat().speed < 0)
				playerMultiplier *= -1;


			movePoints.at(i) += calculateStatChange(attack->getPlayerStat(), &playerPokemon) * playerMultiplier;
			movePoints.at(i) += calculateStatChange(attack->getOpponentStat(), &playerPokemon) * opponentMultiplier;
		}
	}


	for (int i = 1; i < 4; i++)
	{
		if (movePoints.at(i) > movePoints.at(highest.at(0)))
		{
			highest.clear();
			highest.push_back(i);
		}
		else if (movePoints.at(i) == movePoints.at(highest.at(0)))
			highest.push_back(i);
	}


	m_aiCommand->selection1 = highest.at(randomNumber((int)highest.size()));

	if (movePoints.at(m_aiCommand->selection1) == 0)
		m_aiCommand->selection1 = MOVE_FIVE;

}

void BattleAction::resetBattleAction()
{
	m_playerCommand->selection1 = NONE;
	m_playerCommand->selection2 = NONE;

	m_aiCommand->selection1 = NONE;
	m_aiCommand->selection2 = NONE;

	m_playerMoveset = m_trainer->getRoster()[*m_playerPokemonIndex].getMoveset();

	m_menu->setscene(MenuScene::BATTLE);
	m_menu->setOverlay(MenuOverlay::BATTLE_OPTIONS);
	m_menu->setRequestedData(&m_playerCommand->selection1);
}

bool BattleAction::moveSelected()
{
	//m_menu->setRequestedData(&m_playerCommand->selection2);
	m_playerCommand->selection1 = NONE;
	//TODO: Make sure that overlays and scene switches are automatic

	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_menu->leaveRequested())
			return false;

		if (m_playerCommand->selection1 == NONE)
			continue;
		
		switch (m_playerCommand->selection1)
		{
		case MoveSelection::MOVE_ONE:
			if (m_playerMoveset.move1 != NONE && m_playerMoveset.move1pp != 0)
				return true;
			break;
		case MoveSelection::MOVE_TWO:
			if (m_playerMoveset.move2 != NONE && m_playerMoveset.move2pp != 0)
				return true;
			break;
		case MoveSelection::MOVE_THREE:
			if (m_playerMoveset.move3 != NONE && m_playerMoveset.move3pp != 0)
				return true;
			break;
		case MoveSelection::MOVE_FOUR:
			if (m_playerMoveset.move4 != NONE && m_playerMoveset.move4pp != 0)
				return true;
			break;

		default:
			break;
		}

		if ((m_playerMoveset.move1 == NONE || m_playerMoveset.move1pp == 0) &&
			(m_playerMoveset.move2 == NONE || m_playerMoveset.move2pp == 0) &&
			(m_playerMoveset.move3 == NONE || m_playerMoveset.move3pp == 0) &&
			(m_playerMoveset.move4 == NONE || m_playerMoveset.move4pp == 0)) {

			m_playerCommand->selection1 = MoveSelection::MOVE_FIVE;
			return true;
		}
		
		m_menu->setOverlay(MenuOverlay::ATTACK_SELECT);
		m_menu->setButtonIndex(m_playerCommand->selection1);
		m_playerCommand->selection1 = NONE;
	}

	return false;
}

bool BattleAction::pokemonSelected(bool canSelectSelf, bool canSelectZeroHP)
{
	m_menu->setRequestedData(&m_playerCommand->selection2);
	m_menu->preRun();
	m_battleMenuGraphics->resetPreviousRosterHoverIndex();

	while (!m_menu->shouldClose())
	{
		m_battleMenuGraphics->updatePokemonStats();
		m_menu->run();

		if (m_menu->leaveRequested())
			return false;

		if (m_playerCommand->selection2 == NONE)
			continue;

		if (m_trainer->getRoster()[m_playerCommand->selection2].getLevel() == 0)
		{
			m_playerCommand->selection2 = NONE;
			continue;
		}

		if (!canSelectSelf && (m_playerCommand->selection2 == *m_playerPokemonIndex))
		{
			if (MenuFunction::displayRosterOptions(std::vector<std::string>{ "View" }, m_playerCommand->selection2, m_menu, m_menu->getRenderer()) == 0)
				MenuFunction::pokemonSummary(m_menu, m_trainer->getPokemon(m_playerCommand->selection2));

			m_menu->setscene(MenuScene::BATTLE_ROSTER);
			m_menu->preRun();
			m_menu->setRequestedData(&m_playerCommand->selection2);
			m_playerCommand->selection2 = NONE;
			continue;
		}

		if (!canSelectZeroHP && m_trainer->getRoster()[m_playerCommand->selection2].getCurHealth() == 0)
		{
			if (MenuFunction::displayRosterOptions(std::vector<std::string>{ "View" }, m_playerCommand->selection2, m_menu, m_menu->getRenderer()) == 0)
				MenuFunction::pokemonSummary(m_menu, m_trainer->getPokemon(m_playerCommand->selection2));

			m_menu->setscene(MenuScene::BATTLE_ROSTER);
			m_menu->preRun();
			m_menu->setRequestedData(&m_playerCommand->selection2);
			m_playerCommand->selection2 = NONE;
			continue;
		}

		
		if (MenuFunction::displayRosterOptions(std::vector<std::string>{"Select", "View"}, m_playerCommand->selection2, m_menu, m_menu->getRenderer()) == 1)
		{
			MenuFunction::pokemonSummary(m_menu, m_trainer->getPokemon(m_playerCommand->selection2));

			m_menu->setscene(MenuScene::BATTLE_ROSTER);
			m_menu->preRun();
			m_menu->setRequestedData(&m_playerCommand->selection2);
			m_playerCommand->selection2 = NONE;
			continue;
		}

		return true;
	}

	return false;
}

bool BattleAction::itemSelected()
{
	m_menu->setRequestedData(&m_playerCommand->selection2);

	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (m_menu->leaveRequested())
			return false;

		if (m_playerCommand->selection2 == NONE)
			continue;

		//TODO: Check for moving up and down the window list
		if (m_playerCommand->selection2 == arrowDirections::UP)
		{
			moveWindowUp();
			continue;
		}
		else if (m_playerCommand->selection2 == arrowDirections::DOWN)
		{
			moveWindowDown();
			continue;
		}


		if (!itemFound())
		{
			m_playerCommand->selection2 = NONE;
			continue;
		}

		if (m_playerCommand->itemData.pokeballData.isPokeball && m_npt == nullptr)
			return true;
		else if (m_playerCommand->itemData.pokeballData.isPokeball && m_npt != nullptr)
		{
			//TODO: cant catch trainer pokemon dialogue
			return false;			
		}
		else if (!m_playerCommand->itemData.pokeballData.isPokeball && itemRecipientPicked())
			return true;

		m_playerCommand->selection2 = NONE;
		continue;
	}

	return false;
}

bool BattleAction::fleeSelected()
{
	return true;
}

int BattleAction::getAIMoveFromCommand(int commandMove)
{
	Pokemon opponentPokemon;

	if (m_npt != nullptr)
		opponentPokemon = m_npt->getRoster()[*m_opponentPokemonIndex];
	else
		opponentPokemon = *m_wildPokemon;

	switch (commandMove)
	{
	case MOVE_ONE:
		return opponentPokemon.getMoveset().move1;
	case MOVE_TWO:
		return opponentPokemon.getMoveset().move2;
	case MOVE_THREE:
		return opponentPokemon.getMoveset().move3;
	case MOVE_FOUR:
		return opponentPokemon.getMoveset().move4;
	default:
		logger->log(LogLevel::CRITICAL, "Invalid AI Move choice: " + std::to_string((int)commandMove), "getMoveFromCommand", "OldBattleSimulator");
		logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
		break;
	}

	return 0;
}

bool BattleAction::itemFound()
{
	int count = 0;
	int itemWindowScroll = 0;

	for (auto i = m_trainer->getItemStorage()->getBattleItems()->begin(); i != m_trainer->getItemStorage()->getBattleItems()->end(); i++)
	{
		if (itemWindowScroll != m_itemWindowDisposition)
		{
			itemWindowScroll++;
			continue;
		}

		if (count == 5)
			break;

		if (i->second == 0)
			continue;

		if (count == m_playerCommand->selection2)
		{
			Item* item = getItemFromID(i->first);

			if (isPokeball(*item))
				m_playerCommand->itemData.pokeballData.isPokeball = true;

			m_playerCommand->itemData.id = item->getID();

			return true;
		}

		count++;
	}

	return false;
}

bool BattleAction::itemRecipientPicked()
{
	m_playerCommand->selection2 = NONE;

	while (!m_menu->shouldClose())
	{
		if (pokemonSelected(true, true))
		{
			if (getItemFromID(m_playerCommand->itemData.id)->canBeUsedOnPokemon(&m_trainer->getRoster()[*m_playerPokemonIndex]))
				return true;
			else
				continue;
		}
		else
			return false;
	}
	return false;
}

void BattleAction::moveWindowUp()
{
	if (m_itemWindowDisposition > 0)
		m_itemWindowDisposition--;


	m_battleMenuGraphics->updateItemList(m_itemWindowDisposition);

	m_playerCommand->selection1 = NONE;
}

void BattleAction::moveWindowDown()
{
	int testDisposition = m_itemWindowDisposition + 1;

	int count = 0;
	int itemWindowScroll = 0;

	for (auto i = m_trainer->getItemStorage()->getBattleItems()->begin(); i != m_trainer->getItemStorage()->getBattleItems()->end(); i++)
	{
		if (itemWindowScroll != testDisposition)
		{
			itemWindowScroll++;
			continue;
		}

		if (count == 5)
		{
			count++;
			m_itemWindowDisposition++;
			m_battleMenuGraphics->updateItemList(m_itemWindowDisposition);
			break;
		}

		if (i->second == 0)
			continue;

		count++;
	}

	if (count == 5)
	{
		m_itemWindowDisposition++;
		m_battleMenuGraphics->updateItemList(m_itemWindowDisposition);
	}

	m_playerCommand->selection1 = NONE;
}

void BattleAction::reducePP()
{

	if (m_playerCommand->selection1 == SimulationType::ATTACK)
	{
		switch (m_playerCommand->selection2)
		{
		case 0:
			m_playerMoveset.move1pp--;
			break;
		case 1:
			m_playerMoveset.move2pp--;
			break;
		case 2:
			m_playerMoveset.move3pp--;
			break;
		case 3:
			m_playerMoveset.move4pp--;
			break;
		default:
			break;
		}

		m_trainer->getRoster()[*m_playerPokemonIndex].setMoveset(m_playerMoveset);
	}
}

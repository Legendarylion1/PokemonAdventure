#include "BattleExperience.h"

void BattleFaintHandler::setup(Trainer* trainer, Pokedex* pokedex, Menu* menu, AnimationStream* animator, BattleMenuGraphics* battleMenuGraphics, Timer* timer, Input* input, DialogueRenderer* dialogueRenderer, int* playerPokemonIndex, int* opponentPokemonIndex)
{
	m_trainer = trainer;
	m_menu = menu;
	m_animator = animator;
	m_playerPokemonIndex = playerPokemonIndex;
	m_opponentPokemonIndex = opponentPokemonIndex;
	m_battleMenuGraphics = battleMenuGraphics;
	m_dialogueRenderer = dialogueRenderer;
	m_timer = timer;
	m_input = input;
	m_pokedex = pokedex;
}

void BattleFaintHandler::setOpponent(NPT* npt)
{
	m_npt = npt;
	m_wildPokemon = nullptr;

	m_pokedex->spotPokemon(m_npt->getRoster()[*m_opponentPokemonIndex].getSpecies().id);

	reset();
}

void BattleFaintHandler::setOpponent(Pokemon* pokemon)
{
	m_npt = nullptr;
	m_wildPokemon = pokemon;

	m_pokedex->spotPokemon(m_wildPokemon->getSpecies().id);

	reset();
}

void BattleFaintHandler::handleFaints()
{
	updateXPRecords();
	animateXP();
	swapPokemon();
}

void BattleFaintHandler::updateXPRecords()
{
	if (m_playerIndex != *m_playerPokemonIndex)
	{
		m_playerIndex = *m_playerPokemonIndex;
		if (m_trainer->getRoster()[m_playerIndex].getCurHealth() != 0)
			addRecord();
	}

	if (m_trainer->getRoster()[m_playerIndex].getCurHealth() == 0)
		removeRecord();
}

void BattleFaintHandler::animateXP()
{
	Pokemon* opponentPokemon = m_wildPokemon;
	if (m_npt != nullptr)
		opponentPokemon = &m_npt->getRoster()[*m_opponentPokemonIndex];

	if (opponentPokemon->getCurHealth() > 0)
		return;

	//TODO: Say that foes <Pokemon Name> has fainted
	//TODO: Say the wild <Pokemon Name> has fainted

	distributeEVs();
	distributeXP();
}

void BattleFaintHandler::swapPokemon()
{
	Pokemon* opponentPokemon = m_wildPokemon;
	if (m_npt != nullptr)
		opponentPokemon = &m_npt->getRoster()[*m_opponentPokemonIndex];

	/// 
	///								OPTIMIZED IDEA
	/// 
	/// - Is our opponent out of pokemon				1.0.0
	///		- Yes
	///			- RETURN FROM ALL FUNCTIONS			
	/// - Is the player out of pokemon					2.0.0
	///		- Yes
	///			- RETURN FROM ALL FUNCTIONS
	/// 
	/// - Did Opponent Pokemon Faint					3.0.0
	///		- Yes
	///			- Has the player Pokemon Fainted		3.1.0
	///				- Yes
	///					- Swap AI Pokemon
	///					- Swap Player Pokemon
	///				- No
	///					- Would the player like to swap	3.1.1
	///						- Yes
	///							- Swap AI Pokemon
	///							- INFORM PLAYER OF SWAP
	///							- Swap Player Pokemon
	///						- No
	///							- Swap AI Pokemon
	///							- Keep Player Pokemon
	///		- No
	///			- Has Player Pokemon Fainted			3.2.1
	///				- Yes
	///					- Swap Player Pokemon
	///				- No
	///					- RETURN FROM ALL FUNCTIONS

	if (aSideIsUnableToBattle())
		return;

	if (opponentPokemon->getCurHealth() == 0)
	{
		resetFaintedPokemon(opponentPokemon);

		if (m_trainer->getRoster()[m_playerIndex].getCurHealth() == 0)
		{
			resetFaintedPokemon(&m_trainer->getRoster()[m_playerIndex]);
			*m_playerPokemonIndex = getPlayerPokemonSwap(false);
			swapAIPokemon();
			sendOutPokemon(SelectedUser::PLAYER);
		}
		else
		{
			if (playerWantsToSwapPokemon())
			{
				int swapIndex = getPlayerPokemonSwap(true);

				if (swapIndex != NONE)
				{
					swapAIPokemon();
					withdrawPlayerPokemon();

					*m_playerPokemonIndex = swapIndex;
					sendOutPokemon(SelectedUser::PLAYER);
				}
				else
					swapAIPokemon();
			}
			else
				swapAIPokemon();
		}
	}
	else if( m_trainer->getRoster()[m_playerIndex].getCurHealth() == 0)
	{
		resetFaintedPokemon(&m_trainer->getRoster()[m_playerIndex]);
		*m_playerPokemonIndex = getPlayerPokemonSwap(false);
		sendOutPokemon(SelectedUser::PLAYER);
	}
	
}

void BattleFaintHandler::addRecord()
{
	if (std::find(m_xpRecords[*m_opponentPokemonIndex].begin(), m_xpRecords[*m_opponentPokemonIndex].end(), m_playerIndex) == m_xpRecords[*m_opponentPokemonIndex].end())
		m_xpRecords[*m_opponentPokemonIndex].push_back(m_playerIndex);
}

void BattleFaintHandler::removeRecord()
{
	for (int i = 0; i < 6; i++)
	{
		if (std::find(m_xpRecords[i].begin(), m_xpRecords[i].end(), m_playerIndex) != m_xpRecords[i].end())
		{
			int recordIndex = 0;

			for (size_t x = 0; x < m_xpRecords[i].size(); x++)
			{
				if (m_xpRecords[i].at(x) == m_playerIndex)
				{
					m_xpRecords[i].erase(m_xpRecords[i].begin() + x);
					break;
				}
			}
		}
	}
}

void BattleFaintHandler::recordEvolution(int index)
{
	if (m_trainer->getRoster()[index].readyToEvolve())
		m_evolutionCandidates.push_back(index);

}

void BattleFaintHandler::distributeEVs()
{
	int evSplit = (int)m_xpRecords[*m_opponentPokemonIndex].size();

	if (evSplit == 0)
		return;

	Pokemon* opponentPokemon = m_wildPokemon;
	if (m_npt != nullptr)
		opponentPokemon = &m_npt->getRoster()[*m_opponentPokemonIndex];

	PokemonStats evReward{};
	Species opponentSpecies = opponentPokemon->getSpecies();

	evReward.hp = (int)ceil(opponentSpecies.evYield.hp / (float)evSplit);
	evReward.speed = (int)ceil(opponentSpecies.evYield.speed / (float)evSplit);
	evReward.attack = (int)ceil(opponentSpecies.evYield.attack / (float)evSplit);
	evReward.defense = (int)ceil(opponentSpecies.evYield.defense / (float)evSplit);
	evReward.spAttack = (int)ceil(opponentSpecies.evYield.spAttack / (float)evSplit);
	evReward.spDefense = (int)ceil(opponentSpecies.evYield.spDefense / (float)evSplit);


	for (size_t i = 0; i < m_xpRecords[*m_opponentPokemonIndex].size(); i++)
	{
		m_trainer->getRoster()[m_xpRecords[*m_opponentPokemonIndex].at(i)].gainEVs(evReward);
	}
}

void BattleFaintHandler::distributeXP()
{
	if (m_xpRecords[*m_opponentPokemonIndex].size() == 0)
		return;

	Pokemon* opponentPokemon = m_wildPokemon;
	if (m_npt != nullptr)
		opponentPokemon = &m_npt->getRoster()[*m_opponentPokemonIndex];

	int b = opponentPokemon->getSpecies().expYield;
	int L = opponentPokemon->getLevel();
	float a = (m_npt == nullptr) ? 1.0f : 1.5f;
	float s = 1.0f / m_xpRecords[*m_opponentPokemonIndex].size();

	int xpYield = int(((b * L) / 7.0f) * s * a);

	float dripCount = 0;

	for (size_t i = 0; i < m_xpRecords[*m_opponentPokemonIndex].size(); i++)
	{

		renderDialogue(m_trainer->getRoster()[m_xpRecords[*m_opponentPokemonIndex].at(i)].getName() + " has gained", std::to_string(xpYield) + " exp", true);

		for (int x = 0; x < xpYield; x++)
		{
			m_trainer->getRoster()[m_xpRecords[*m_opponentPokemonIndex].at(i)].gainXP();
			if (*m_playerPokemonIndex == m_xpRecords[*m_opponentPokemonIndex].at(i))
				m_battleMenuGraphics->updateXPPercentage();

			dripCount = 0;
			while (dripCount < m_xpDripRate)
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_animator->updateRenderer();
				dripCount += m_timer->getDelta();
			}

			if (m_trainer->getRoster()[m_xpRecords[*m_opponentPokemonIndex].at(i)].readyToLevel())
			{

				if (*m_playerPokemonIndex == m_xpRecords[*m_opponentPokemonIndex].at(i))
				{
					m_animator->setAnimation(Animation::XP_LEVEL_UP_UI);
					while (m_animator->animationPlaying())
					{
						if (m_menu->shouldClose())
							break;

						m_menu->renderMenu();
						m_animator->stream();
						m_animator->updateRenderer();
					}
					m_animator->stopAnimation();

					m_animator->setAnimation(Animation::XP_GAIN);
					while (m_animator->animationPlaying())
					{
						if (m_menu->shouldClose())
							break;

						m_menu->renderMenu();
						m_animator->stream();
						m_animator->updateRenderer();
					}
					m_animator->stopAnimation();

					m_battleMenuGraphics->updatePokemonDisplay(SelectedUser::PLAYER);
				}

				levelPokemon(m_xpRecords[*m_opponentPokemonIndex].at(i));
				teachMove(m_xpRecords[*m_opponentPokemonIndex].at(i));
				recordEvolution(m_xpRecords[*m_opponentPokemonIndex].at(i));
			}
		}
	}
	m_xpRecords[*m_opponentPokemonIndex].clear();
}

void BattleFaintHandler::levelPokemon(int index)
{
	PokemonStats statIncrease = m_trainer->getRoster()[index].levelUp();
	PokemonStats stats = m_trainer->getRoster()[index].getStats();
	m_battleMenuGraphics->updatePokemonDisplay(SelectedUser::PLAYER);

	std::string name = m_trainer->getRoster()[index].getName();
	std::string level = "Lv" + std::to_string(m_trainer->getRoster()[index].getLevel());

	std::string hp =		(statIncrease.hp > 0) ?			"+" + std::to_string(statIncrease.hp)		: "-" + std::to_string(statIncrease.hp);
	std::string attack =	(statIncrease.attack > 0) ?		"+" + std::to_string(statIncrease.attack)	: "-" + std::to_string(statIncrease.attack);
	std::string defense =	(statIncrease.defense > 0) ?	"+" + std::to_string(statIncrease.defense)	: "-" + std::to_string(statIncrease.defense);
	std::string spAttack =	(statIncrease.spAttack > 0) ?	"+" + std::to_string(statIncrease.spAttack)	: "-" + std::to_string(statIncrease.spAttack);
	std::string spDef =		(statIncrease.spDefense > 0) ?	"+" + std::to_string(statIncrease.spDefense): "-" + std::to_string(statIncrease.spDefense);
	std::string speed =		(statIncrease.speed > 0) ?		"+" + std::to_string(statIncrease.speed)	: "-" + std::to_string(statIncrease.speed);



	SharedString pokemonStatDifference = SharedString{ hp, attack, defense, spAttack, spDef, speed };
	
	
	SharedString pokemonStatValue = SharedString{ std::to_string(stats.hp), std::to_string(stats.attack), std::to_string(stats.defense), std::to_string(stats.spAttack),
													std::to_string(stats.spDefense), std::to_string(stats.speed) };

	m_battleMenuGraphics->updateLevelUpStats(name, level, pokemonStatDifference, pokemonStatValue);

	m_menu->setOverlay(MenuOverlay::LEVEL_UP_STAT_CHANGE);

	float count = 0.0f;
	float target = 0.1f;

	while (count < target)
	{
		if (m_menu->shouldClose())
			break;

		count += m_timer->getDelta();
		m_menu->renderMenu();
		m_animator->updateRenderer();
	}

	while (true)
	{
		if (m_menu->shouldClose())
			break;

		if (m_input->anyButtonPressed())
			break;

		m_menu->renderMenu();
		m_animator->updateRenderer();
	}

	count = 0.0f;

	m_menu->setOverlay(MenuOverlay::LEVEL_UP_STAT_VALUE);

	while (!m_menu->shouldClose())
	{
		if (m_input->anyButtonPressed())
			break;

		m_menu->renderMenu();
		m_animator->updateRenderer();
	}
}

void BattleFaintHandler::teachMove(int index)
{
	bool moveSwapped = false;
	int newMove = m_trainer->getRoster()[index].readyToLearnMove();
	if (newMove == NONE)
		return;

	if (m_trainer->getRoster()[index].getMoveset().move1 == NONE)
	{
		m_trainer->getRoster()[index].learnMove(MOVE_ONE, newMove, getAttackFromID(newMove)->getPP());
		moveSwapped = true;
	}
	else if (m_trainer->getRoster()[index].getMoveset().move2 == NONE)
	{
		m_trainer->getRoster()[index].learnMove(MOVE_TWO, newMove, getAttackFromID(newMove)->getPP());
		moveSwapped = true;
	}
	else if (m_trainer->getRoster()[index].getMoveset().move3 == NONE)
	{
		m_trainer->getRoster()[index].learnMove(MOVE_THREE, newMove, getAttackFromID(newMove)->getPP());
		moveSwapped = true;
	}
	else if (m_trainer->getRoster()[index].getMoveset().move4 == NONE)
	{
		m_trainer->getRoster()[index].learnMove(MOVE_FOUR, newMove, getAttackFromID(newMove)->getPP());
		moveSwapped = true;
	}

	if (moveSwapped)
	{
		renderDialogue(m_trainer->getRoster()[index].getName() + " learned", getAttackFromID(newMove)->getName(), true);
		return;
	}

	std::string pokemonName = m_trainer->getRoster()[index].getName();
	std::string moveName = getAttackFromID(newMove)->getName();

	renderDialogue(pokemonName + " wants to learn", moveName, true);
	renderDialogue(pokemonName + " already knows", "four moves", true);
	renderDialogue("Should a move be", "replaced with " + moveName, true);

	//TODO: Yes No option here

	int option = NONE;
	m_menu->setRequestedData(&option);
	m_menu->setscene(MenuScene::BATTLE);
	m_menu->setOverlay(MenuOverlay::LEARN_MOVE);
	m_menu->preRun();


	while (option == NONE)
	{
		if (m_menu->shouldClose())
			break;

		m_menu->run();
		if (m_menu->leaveRequested())
		{
			option = (int)false;
			return;
		}
	}

	m_menu->clearRequestedData();
	m_menu->postRun();

	//logger->log(LogLevel::DEBUG, "Replacing move", "teachMove", "OldBattleSimulator");
	//std::cout << "Do you want to replace a move?\n1) Yes\n2) No\n" << std::endl;
	//std::cin >> option;
	//std::cin.clear();

	if (option == (int)false)
	{
		renderDialogue(pokemonName + " did not", "learn " + moveName, true);
		return;
	}

	renderDialogue("Which Move Should", "be forgotten", true);



	//TODO: Present Current Moves
	//TODO: Present New Move To Learn
	//TODO: In the game it shows power accuracy and a description which is fair
	option = NONE;
	m_battleMenuGraphics->resetPreviousLearnMoveHoverIndex();

	m_menu->setRequestedData(&option);
	m_menu->setscene(MenuScene::LEARN_MOVE);
	m_menu->preRun();

	while ((option == NONE || option == 4 ))
	{
		if (m_menu->shouldClose())
			break;

		m_battleMenuGraphics->updateLearnMoveScene(index, m_menu->getButtonIndex(), newMove);

		m_menu->run();
		if (m_menu->leaveRequested())
		{
			m_menu->setscene(MenuScene::BATTLE);
			return;
		}
	}

	m_menu->clearRequestedData();
	m_menu->postRun();

	m_menu->setscene(MenuScene::BATTLE);

	if (!m_menu->leaveRequested())
	{
		renderDialogue(pokemonName + " has learned", moveName, true);
		m_trainer->getRoster()[index].learnMove(option, newMove, getAttackFromID(newMove)->getPP());
		//logger->log(LogLevel::DEBUG, "pokemon has learned new move id: " + std::to_string(newMove), "teachMove", "OldBattleSimulator");
		//std::cout << "Pokemon has learned " << getAttackFromID(newMove)->getName() << std::endl;
		//system("pause");
	}
	else
	{
		renderDialogue(pokemonName + " did not", "learn " + moveName, true);
	}
}

void BattleFaintHandler::resetFaintedPokemon(Pokemon* pokemon)
{
	pokemon->getMinorStatus()->clear();
	pokemon->removeBattleStats();
}

bool BattleFaintHandler::aSideIsUnableToBattle()
{
	if (m_trainer->unableToBattle())
		return true;

	if (m_npt != nullptr && m_npt->unableToBattle())
		return true;

	if (m_npt == nullptr && m_wildPokemon->getCurHealth() == 0)
		return true;

	return false;
}

bool BattleFaintHandler::playerWantsToSwapPokemon()
{
	renderDialogue("Opponent is about to send", "in " + m_npt->getRoster()[*m_opponentPokemonIndex].getName(), true);

	int playerSelection = NONE;

	m_menu->setRequestedData(&playerSelection);
	m_menu->setOverlay(MenuOverlay::SWAP_POKEMON_QUESTION);
	m_menu->preRun();

	while (playerSelection == NONE)
	{
		if (m_menu->shouldClose())
			break;

		m_menu->run();
	}

	m_menu->clearRequestedData();
	m_menu->postRun();

	return (bool)playerSelection;
}

int BattleFaintHandler::getPlayerPokemonSwap(bool canLeave)
{
	int playerSelection = NONE;
	m_menu->setRequestedData(&playerSelection);
	m_menu->setscene(MenuScene::BATTLE_ROSTER);
	m_menu->preRun();

	m_battleMenuGraphics->resetPreviousRosterHoverIndex();

	while (true)
	{
		if (m_menu->shouldClose())
			break;

		m_battleMenuGraphics->updatePokemonStats();
		m_menu->run();

		if (m_menu->leaveRequested() && canLeave)
		{
			m_menu->clearRequestedData();
			m_menu->setscene(MenuScene::BATTLE);
			return NONE;
		}

		if (playerSelection == NONE)
			continue;

		if (m_trainer->getPokemon(playerSelection).getLevel() == 0)
		{
			playerSelection = NONE;
			continue;
		}

		if (m_trainer->getPokemon(playerSelection).getCurHealth() == 0)
		{
			if (MenuFunction::displayRosterOptions(std::vector<std::string>{"VIEW"}, playerSelection, m_menu, m_menu->getRenderer()) == 0)
				MenuFunction::pokemonSummary(m_menu, m_trainer->getRoster()[playerSelection]);

			playerSelection = NONE;
			m_menu->setRequestedData(&playerSelection);
			m_menu->setscene(MenuScene::BATTLE_ROSTER);
			m_menu->preRun();
			continue;
		}

		int option = MenuFunction::displayRosterOptions(std::vector<std::string>{"SELECT","VIEW"}, playerSelection, m_menu, m_menu->getRenderer());

		if (option == 0)
			break;
		else if (option == 1)
		{
			MenuFunction::pokemonSummary(m_menu, m_trainer->getRoster()[playerSelection]);
			playerSelection = NONE;
			m_menu->setRequestedData(&playerSelection);
			m_menu->setscene(MenuScene::BATTLE_ROSTER);
			m_menu->preRun();
		}
		else
		{
			playerSelection = NONE;
			m_menu->setRequestedData(&playerSelection);
			m_menu->setscene(MenuScene::BATTLE_ROSTER);
			m_menu->preRun();
		}
		
	}
	m_menu->clearRequestedData();
	m_menu->postRun();

	m_menu->setscene(MenuScene::BATTLE);
	return playerSelection;
}

void BattleFaintHandler::swapAIPokemon()
{
	*m_opponentPokemonIndex += 1;
	m_pokedex->spotPokemon(m_npt->getRoster()[*m_opponentPokemonIndex].getSpecies().id);
	sendOutPokemon(SelectedUser::AI);
}

void BattleFaintHandler::sendOutPokemon(SelectedUser user)
{
	m_battleMenuGraphics->updatePokemonDisplay(user);

	if (user == SelectedUser::PLAYER)
	{
		for (int i = 0; i < 16; i++)
		{
			BattleAnimations::sendOutPlayerPokemon(i, m_battleMenuGraphics->getPlayerRenderData());

			m_menu->renderMenu();
			m_animator->updateRenderer();
		}
	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			BattleAnimations::sendOutOpponentPokemon(i, m_battleMenuGraphics->getOpponentRenderData());

			m_menu->renderMenu();
			m_animator->updateRenderer();
		}
	}
}

void BattleFaintHandler::withdrawPlayerPokemon()
{
	for (int i = 0; i < 15; i++)
	{
		BattleAnimations::playerPokemonWithdraw(i, m_battleMenuGraphics->getPlayerRenderData());

		m_menu->renderMenu();
		m_animator->updateRenderer();
	}
}

void BattleFaintHandler::renderDialogue(std::string topText, std::string botText, bool awaitClick)
{
	m_dialogueRenderer->setDialogue(topText, botText, awaitClick, true);

	while (m_dialogueRenderer->rendereringDialogue())
	{
		if (m_menu->shouldClose())
			break;

		m_dialogueRenderer->renderDialogue();
		m_animator->updateRenderer();
	}
}

void BattleFaintHandler::reset()
{
	m_playerIndex = -1;
	m_evolutionCandidates.clear();

	for (int i = 0; i < 6; i++)
		m_xpRecords[i].clear();
}

#include "Battle.h"

void Battle::setup(Trainer* trainer, Pokedex* pokedex, Menu* menu, RosterDisplayData* rosterData, DialogueRenderer* dialogueRenderer, AnimationStream* animator, Renderer* renderer, Input* input, Timer* timer)
{
	m_battleMenuGraphics.setup(trainer, menu, &m_playerPokemonIndex, &m_opponentPokemonIndex, rosterData);
	m_battleAction.setup(trainer, menu, &m_playerCommand, &m_aiCommand, &m_playerPokemonIndex, &m_opponentPokemonIndex, &m_battleMenuGraphics, timer);
	m_dataGenerator.setup(trainer, &m_playerCommand, &m_aiCommand, &m_playerPokemonIndex, &m_opponentPokemonIndex, &m_endCondition, renderer);
	m_dataSimulator.setup(trainer, menu, renderer, dialogueRenderer, animator, &m_battleMenuGraphics, timer, &m_playerPokemonIndex, &m_opponentPokemonIndex);
	m_faintHandler.setup(trainer, pokedex, menu, animator, &m_battleMenuGraphics, timer, input, dialogueRenderer, &m_playerPokemonIndex, &m_opponentPokemonIndex);

	m_trainer = trainer;
	m_pokedex = pokedex;
	m_menu = menu;
	m_dialogueRenderer = dialogueRenderer;
	m_animator = animator;
	m_timer = timer;
}

void Battle::beginBattle(NPT* npt)
{
	m_endCondition = NONE;
	m_npt = npt;

	m_battleAction.setOpponent(npt);
	m_battleMenuGraphics.setOpponent(npt);
	m_dataGenerator.setOpponent(npt);
	m_dataSimulator.setOpponent(npt);
	m_faintHandler.setOpponent(npt);

	givePokemonPP(npt);

	playBattle();

	if (m_npt->unableToBattle())
		npt->setHasBeenDefeated(true);
}

Pokemon Battle::beginBattle(Pokemon pokemon)
{
	m_endCondition = NONE;
	m_npt = nullptr;
	m_wildPokemon = pokemon;
	m_battleAction.setOpponent(&m_wildPokemon);
	m_battleMenuGraphics.setOpponent(&m_wildPokemon);
	m_dataGenerator.setOpponent(&m_wildPokemon);
	m_dataSimulator.setOpponent(&m_wildPokemon);
	m_faintHandler.setOpponent(&m_wildPokemon);

	givePokemonPP(&m_wildPokemon);

	playBattle();

	if (m_endCondition == SimulationType::POKEMON)
	{
		if (!m_pokedex->hasObtainedPokemon(m_wildPokemon.getSpecies().id))
		{
			m_menu->setscene(MenuScene::BATTLE);
			renderDialogue(m_wildPokemon.getSpecies().name + "'s data has been", "added to the pokedex", true);
			m_menu->setscene(MenuScene::NONE);
		}

		m_pokedex->obtainPokemon(m_wildPokemon.getSpecies().id);
		return m_wildPokemon;
	}
	return Pokemon();
}

void Battle::givePokemonPP(NPT* npt)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_npt->getRoster()[i].getLevel() == 0)
			return;

		givePokemonPP(&m_npt->getRoster()[i]);
	}
}

void Battle::givePokemonPP(Pokemon* pokemon)
{
	Moveset moveset = pokemon->getMoveset();

	if (pokemon->getMoveset().move1 != NONE)
		moveset.move1pp = getAttackFromID(moveset.move1)->getPP();

	if (pokemon->getMoveset().move2 != NONE)
		moveset.move2pp = getAttackFromID(moveset.move2)->getPP();

	if (pokemon->getMoveset().move3 != NONE)
		moveset.move3pp = getAttackFromID(moveset.move3)->getPP();

	if (pokemon->getMoveset().move4 != NONE)
		moveset.move4pp = getAttackFromID(moveset.move4)->getPP();

	pokemon->setMoveset(moveset);
}

void Battle::loadAnimations()		//TODO: REMOVE FUNCTION
{
	//TODO: Worry about another animation lol
	//while (!m_animator->animationLoaded(Animation::THROW_MASTERBALL))
	//{
	//	if (m_menu->shouldClose())
	//		break;
	//
	//	m_menu->onUpdate();
	//	m_animator->updateRenderer();
	//	//TODO: Add a loading card for when a battle starts that gives us time to load these animations
	//	//std::cout << "Waiting on animations to load" << std::endl;
	//}
}

void Battle::playBattle()
{
	m_inBattle = true;
	m_menu->setCanLeave(false);
	m_menu->setscene(MenuScene::BATTLE);

	//loadAnimations();

	fadeIntoBattle();

	while (!battleOver())
	{
		if (m_menu->shouldClose())
			break;

		// Battle Action
		m_battleAction.getAction();

		// Battle Data Generator
		// Battle Simulator
		m_dataSimulator.runSimulation(m_dataGenerator.generateData());
	}

	rewardPlayer();
	evolvePokemon();
	resetAllPokemon();

	m_menu->setscene(MenuScene::NONE);
	m_menu->setCanLeave(true);

	if (!m_menu->shouldClose())
		m_inBattle = false;

	m_menu->reset(MenuOverlay::BATTLE_OPTIONS);
	m_menu->reset(MenuOverlay::ATTACK_SELECT);
	m_menu->reset(MenuScene::BATTLE_ROSTER);
	m_menu->reset(MenuScene::BATTLE_ITEMS);

	fadeOutOfBattle();
}

bool Battle::battleOver()
{
	if (m_endCondition == SimulationType::FLEE)
		return true;
	if (m_endCondition == SimulationType::POKEMON)
		return true;

	if (m_trainer->unableToBattle())
		return true;

	if (m_npt != nullptr && m_npt->unableToBattle())
	{
		m_faintHandler.handleFaints();
		return true;
	}

	if (m_npt == nullptr && m_wildPokemon.getCurHealth() == 0)
	{
		m_faintHandler.handleFaints();
		return true;
	}

	m_faintHandler.handleFaints();
	return false;
}

void Battle::rewardPlayer()
{
	//TODO: Opponent Slides onto the screen.

	if (m_npt == nullptr || m_trainer->unableToBattle())
		return;

	renderDialogue("Player Defeated", m_npt->getName(), true);

	for (Dialogue dialogue : m_npt->getDialogue())
		renderDialogue(dialogue.topLine, dialogue.botLine, true);

	renderDialogue(m_trainer->getName() + " got " + std::to_string(m_npt->getBalance()), "for winning", true);
	m_trainer->giveMoney(m_npt->getBalance());
}

void Battle::evolvePokemon()
{
	std::vector<int> pokemonToEvolve = m_faintHandler.getEvolutionCandidates();

	for (int i = 0; i < pokemonToEvolve.size(); i++)
	{
		evolutionAnimated(m_trainer->getRoster()[pokemonToEvolve.at(i)].getSpecies().id, m_trainer->getRoster()[pokemonToEvolve.at(i)].getSpecies().Evolution.pokemon, m_trainer->getRoster()[pokemonToEvolve.at(i)].getName());
		m_trainer->getRoster()[pokemonToEvolve.at(i)].evolve();

		if (!m_pokedex->hasObtainedPokemon(m_trainer->getRoster()[pokemonToEvolve.at(i)].getSpecies().id))
		{
			m_menu->setscene(MenuScene::EVOLUTION);

			std::string pokemonName = m_trainer->getRoster()[pokemonToEvolve.at(i)].getSpecies().name;

			m_dialogueRenderer->setDialogue(pokemonName + "'s data has been", "added to the pokedex", true);

			while (m_dialogueRenderer->rendereringDialogue())
			{
				if (m_menu->shouldClose())
					break;

				m_dialogueRenderer->renderDialogue();
				m_animator->updateRenderer();
			}
		}

		m_pokedex->obtainPokemon(m_trainer->getRoster()[pokemonToEvolve.at(i)].getSpecies().id);
	}
}

void Battle::resetAllPokemon()
{
	for (int i = 0; i < 6; i++)
	{
		m_trainer->getRoster()[i].getMinorStatus()->clear();
		m_trainer->getRoster()[i].removeBattleStats();

		if (m_npt != nullptr)
		{
			m_npt->getRoster()[i].getMinorStatus()->clear();
			m_npt->getRoster()[i].removeBattleStats();
		}
	}

	if (m_npt == nullptr)
	{
		m_wildPokemon.getMinorStatus()->clear();
		m_wildPokemon.removeBattleStats();
	}
}

bool Battle::evolutionAnimated(int preEvolution, int postEvolution, std::string pokemonName)
{
	//TODO: Fade out and in

	m_menu->setscene(MenuScene::EVOLUTION);
	m_menu->setCanLeave(false);

	std::string preEvolutionTexture = pokemonFrontTexture(getSpeciesFromID((PokemonID)preEvolution).name);
	std::string postEvolutionTexture = pokemonFrontTexture(getSpeciesFromID((PokemonID)postEvolution).name);

	DynamicImageRenderData* preEvolutionData = m_battleMenuGraphics.getPlayerRenderData();
	DynamicImageRenderData* postEvolutionData = m_battleMenuGraphics.getOpponentRenderData();

	*preEvolutionData = DynamicImageRenderData{};
	*postEvolutionData = DynamicImageRenderData{};

	preEvolutionData->dynamicImage = preEvolutionTexture;
	postEvolutionData->dynamicImage = postEvolutionTexture;

	preEvolutionData->percentageX = 50.0f;
	preEvolutionData->percentageY = 50.0f;
	preEvolutionData->widthPercent = 9.0f;
	preEvolutionData->heightPercent = 16.0f;

	postEvolutionData->percentageX = 50.0f;
	postEvolutionData->percentageY = 50.0f;
	postEvolutionData->widthPercent = 9.0f;
	postEvolutionData->heightPercent = 16.0f;

	postEvolutionData->alpha = 255.0f;
	postEvolutionData->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);

	float startingAnimationSpeed = 0.05f;

	shrinkEvolution(postEvolutionData, &startingAnimationSpeed, false);
	
	// TODO: Potential Background animation. Can be done by swapping out background textures
	renderDialogue("What " + pokemonName + " is", "evolving", true);

	// TODO: Pre Animation for evolution

	changeEvolutionColor(preEvolutionData, true);
	//postEvolutionData->alpha = 0.0f;

	for (int i = 0; i < 10; i++)
	{
		shrinkEvolution(preEvolutionData, &startingAnimationSpeed);
		growEvolution(postEvolutionData, &startingAnimationSpeed);
		shrinkEvolution(postEvolutionData, &startingAnimationSpeed);
		growEvolution(preEvolutionData, &startingAnimationSpeed);
	}
	shrinkEvolution(preEvolutionData, &startingAnimationSpeed);
	growEvolution(postEvolutionData, &startingAnimationSpeed);

	preEvolutionData->alpha = 255.0f;

	changeEvolutionColor(postEvolutionData, false);

	// TODO: Post Animation for Evolution

	renderDialogue("Congrats your " + pokemonName, " evolved into " + getSpeciesFromID((PokemonID)postEvolution).name, true);

	return true;
}

void Battle::shrinkEvolution(DynamicImageRenderData* evolutionData, float* animationSpeed, bool animate)
{
	float target = *animationSpeed;

	for (int i = 1; i < 11; i++)
	{
		BattleAnimations::shrinkEvolutionPokemon(i, evolutionData);

		if (!animate)
			continue;

		float count = 0.0f;
		
		while (count < target)
		{
			if (m_menu->shouldClose())
				break;

			m_menu->renderMenu();
			m_animator->updateRenderer();
			count += m_timer->getDelta();
		}
	}

	if (animate)
		*animationSpeed *= .9f;
}

void Battle::growEvolution(DynamicImageRenderData* evolutionData, float* animationSpeed)
{
	float target = *animationSpeed;
	for (int i = 1; i < 11; i++)
	{
		float count = 0.0f;
		

		while (count < target)
		{
			if (m_menu->shouldClose())
				break;

			BattleAnimations::growEvolutionPokemon(i, evolutionData);

			m_menu->renderMenu();
			m_animator->updateRenderer();
			count += m_timer->getDelta();
		}
	}
	*animationSpeed *= .9f;
}

void Battle::changeEvolutionColor(DynamicImageRenderData* evolutionData, bool turnWhite)
{
	for (int i = 0; i < 10; i++)
	{
		float count = 0.0f;
		float target = 0.05f;

		while (count < target)
		{
			if (m_menu->shouldClose())
				break;

			if (turnWhite)
				BattleAnimations::normalToWhite(i, evolutionData);
			else
				BattleAnimations::WhiteToNormal(i, evolutionData);

			m_menu->renderMenu();
			m_animator->updateRenderer();
			count += m_timer->getDelta();
		}
	}
}

void Battle::renderDialogue(std::string topLine, std::string bottomLine, bool awaitClick)
{
	m_dialogueRenderer->setDialogue(topLine, bottomLine, awaitClick, true);

	while (m_dialogueRenderer->rendereringDialogue())
	{
		if (m_menu->shouldClose())
			break;

		m_dialogueRenderer->renderDialogue();
		m_animator->updateRenderer();
	}
}

void Battle::fadeIntoBattle()
{
	m_battleAction.updateAllGraphics();

	m_animator->setAnimation(Animation::FADE_IN);

	while (m_animator->animationPlaying() && !m_menu->shouldClose())
	{
		m_menu->renderMenu();
		m_animator->stream(true);
	}

	m_animator->stopAnimation();
}

void Battle::fadeOutOfBattle()
{
	m_animator->setAnimation(Animation::FADE_OUT);

	while (m_animator->animationPlaying() && !m_menu->shouldClose())
	{
		m_menu->renderMenu();
		m_animator->stream(true);
	}

	m_animator->stopAnimation();
}

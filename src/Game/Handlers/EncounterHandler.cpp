#include "EncounterHandler.h"

//EncounterHandler::EncounterHandler(MapHandler* mapHandler, MovingStatus* movingStatus, Trainer* trainer, Menu* menu, SharedString* rosterData)
//{
//	m_mapHandler = mapHandler;
//	m_movingStatus = movingStatus;
//	m_battleSim.setup(trainer, menu, rosterData);
//}

void EncounterHandler::setup(Battle* battleSimulator, MapHandler* mapHandler, Trainer* trainer, PC* pc, Menu* menu, CharacterMover* characterMover, RosterDisplayData* rosterData, DialogueRenderer* dialogueRenderer, AnimationStream* animator, Renderer* renderer, Input* input, Timer* timer)
{
	m_mapHandler = mapHandler;
	m_player = trainer;
	m_pc = pc;
	m_animator = animator;
	
	m_characterMover = characterMover;
	m_renderer = renderer;

	m_dialogueRenderer = dialogueRenderer;

	m_battleSim = battleSimulator;
}

void EncounterHandler::onUpdate()
{
	for (NPT* ai : m_mapHandler->getAllAI())
	{
		if (ai->wantsToBattle() && ai->getMovingStatus() != MovingStatus::MOVING && inRangeOfPlayer(ai))
		{
			spotPlayer();
			moveAIToPlayer(ai);
			playAiDialogue(ai);
			m_battleSim->beginBattle(ai);

			if (m_player->unableToBattle())
			{
				m_mapHandler->respawnAfterWhiteOut();
				fadeIntoMap();
				return;
			}

			fadeIntoMap();
		}
	}

	if (m_player->getMovingStatus() == MovingStatus::STOPPED)
	{
		char tile = m_mapHandler->getPlayerTile();
		if (tile == 'G' && m_player->position != m_lastPosition)
			attemptPokemonEncounter();
		m_lastPosition = m_player->position;
	}
}

void EncounterHandler::attemptPokemonEncounter()
{
	if (outOfHundred(10))	//TODO: Refine encounter rate
	{
		std::vector<PokemonSpawn> mapSpawns = m_mapHandler->getPokemonSpawns();
		std::vector<PokemonID> spawnPool;

		int rarity = randomNumber(Rarity::COUNT);

		for (PokemonSpawn spawn: mapSpawns)
		{
			if (rarity >= spawn.rarity)
				spawnPool.push_back(spawn.pokemon);
		}

		int minLevel = m_mapHandler->getPokemonMinLevel();
		int maxLevel = m_mapHandler->getPokemonMaxLevel();

		int pokemonLevel = minLevel;
		pokemonLevel += randomNumber(maxLevel - minLevel) + 1;

		PokemonID spawnedPokemon = spawnPool.at(randomNumber(spawnPool.size()));

		runEnocunterAnimation();

		Pokemon capturedPokemon = m_battleSim->beginBattle(Pokemon(getSpeciesFromID(spawnedPokemon), pokemonLevel));

		if (m_player->unableToBattle())
		{
			m_mapHandler->respawnAfterWhiteOut();
			fadeIntoMap();
			return;
		}

		addPokemon(capturedPokemon);

		fadeIntoMap();
	}
}

void EncounterHandler::addPokemon(Pokemon pokemon)
{
	if (pokemon.getLevel() == 0)
		return;


	for (int i = 0; i < 6; i++)
	{
		if (m_player->getPokemon(i).getLevel() == 0)
		{
			m_player->setPokemon(i, pokemon);
			return;
		}
	}

	if (!m_pc->addPokemon(pokemon))
	{
		std::cout << "Pokemon Box is full\n";
	}
}

bool EncounterHandler::inRangeOfPlayer(NPT* npt)
{
	Coordinate potentialLocation = npt->position.coords;

	for (int i = 0; i < npt->getSpotDistance(); i++)
	{
		if (npt->position.direction == Direction::UP)
			potentialLocation.yTile++;
		else if (npt->position.direction == Direction::DOWN)
			potentialLocation.yTile--;
		else if (npt->position.direction == Direction::LEFT)
			potentialLocation.xTile--;
		else
			potentialLocation.xTile++;

		if (potentialLocation == m_player->position.coords)
			return true;
	}

	return false;
}

void EncounterHandler::spotPlayer()
{
	std::cout << "\n!\n" << std::endl;
	//system("pause");
	//TODO: Re-implement exclamation point
}

void EncounterHandler::moveAIToPlayer(NPT* npt)
{
	m_characterMover->setPriorityOnly(true);
	int tilesToMoveAI = 0;
	int tilesAIHasMoved = 0;


	if (npt->position.direction == Direction::UP) {
		tilesToMoveAI = m_player->position.coords.yTile - npt->position.coords.yTile - 1;
	}
	else if (npt->position.direction == Direction::DOWN)
	{
		tilesToMoveAI = npt->position.coords.yTile - m_player->position.coords.yTile - 1;
	}
	else if (npt->position.direction == Direction::LEFT)
	{
		tilesToMoveAI = npt->position.coords.xTile - m_player->position.coords.xTile - 1;
	}
	else {
		tilesToMoveAI = m_player->position.coords.xTile - npt->position.coords.xTile - 1;
	}

	bool incrementCounter = false;

	while (tilesToMoveAI != tilesAIHasMoved)
	{
		if (m_renderer->shouldClose())
			break;

		m_characterMover->onUpdate();
		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_animator->updateRenderer();
		
		


		if (!m_characterMover->priorityQueueEmpty())
			continue;

		if (incrementCounter)
		{
			tilesAIHasMoved++;
			incrementCounter = false;
			continue;
		}

		incrementCounter = true;
		m_characterMover->moveCharacter(npt, npt->position.direction);
	}

	Direction lookingAtAi{};

	if (npt->position.direction == Direction::UP)
		lookingAtAi = Direction::DOWN;
	else if (npt->position.direction == Direction::DOWN)
		lookingAtAi = Direction::UP;
	else if (npt->position.direction == Direction::LEFT)
		lookingAtAi = Direction::RIGHT;
	else if (npt->position.direction == Direction::RIGHT)
		lookingAtAi = Direction::LEFT;
	// Turn Player to face AI after


	m_characterMover->turnCharacter(m_player, lookingAtAi);

	while (!m_characterMover->priorityQueueEmpty())
	{
		if (m_renderer->shouldClose())
			break;

		m_characterMover->onUpdate();
		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_animator->updateRenderer();
	}

	m_characterMover->setPriorityOnly(false);
}

void EncounterHandler::playAiDialogue(NPT* npt)
{
	for (Dialogue dialogue : npt->getDialogue())
	{
		std::cout << dialogue.topLine << "\n" << dialogue.botLine << std::endl;
		m_dialogueRenderer->setSpeakerName(npt->getName());
		m_dialogueRenderer->setDialogue(dialogue.topLine, dialogue.botLine, true);
		while (m_dialogueRenderer->rendereringDialogue())
		{
			if (m_renderer->shouldClose())
				break;

			m_mapHandler->onUpdate();
			m_player->onUpdate(m_renderer);
			m_dialogueRenderer->renderDialogue();
			m_animator->updateRenderer();
		}
	}
}

void EncounterHandler::runEnocunterAnimation()
{
	m_animator->setAnimation(Animation::GRASS_ENCOUNTER);

	while (m_animator->animationPlaying() && !m_renderer->shouldClose())
	{
		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_animator->stream(true);
	}

	m_animator->stopAnimation();
}

void EncounterHandler::fadeIntoMap()
{
	m_animator->setAnimation(Animation::FADE_IN);

	while (m_animator->animationPlaying() && !m_renderer->shouldClose())
	{
		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_animator->stream(true);
	}

	m_animator->stopAnimation();
}

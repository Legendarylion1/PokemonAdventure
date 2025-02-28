#include "Story.h"

Story::Story(MapHandler* mapHandler, CharacterMover* characterMover, Trainer* player, Renderer* renderer, DialogueRenderer* dialogueRenderer, Menu* menu, Battle* battleSim, Pokedex* pokedex)
{
	m_mapHandler = mapHandler;
	m_characterMover = characterMover;
	m_player = player;
	m_renderer = renderer;
	m_dialogueRenderer = dialogueRenderer;
	m_menu = menu;
	m_battleSim = battleSim;
	m_pokedex = pokedex;

	initCutscenes();
}

void Story::onUpdate()
{
	if (m_player->getMovingStatus() != MovingStatus::STOPPED)
		return;

	if (m_mapHandler->getTile(m_player->position.coords) != 'U')
		return;

	if (shouldPlayNextCutscene())
		playCutscene();
}

bool Story::shouldPlayNextCutscene()
{
	if (m_mapLocations.find(m_mapHandler->getCurrentSection()) == m_mapLocations.end())
		return false;

	if (m_mapLocations[m_mapHandler->getCurrentSection()].find(m_player->position.coords) == m_mapLocations[m_mapHandler->getCurrentSection()].end())
		return false;
	
	if (m_mapLocations[m_mapHandler->getCurrentSection()][m_player->position.coords].id != m_currentScene)
		return false;

	return true;
}

void Story::playCutscene()
{
	m_player->setSprinting(false);
	m_characterMover->setPriorityOnly(true);
	m_forceLeaveStory = false;

	StoryData sceneToPlay = m_mapLocations[m_mapHandler->getCurrentSection()][m_player->position.coords];

	std::vector<CutsceneInstruction> instructions = m_cutscenes[sceneToPlay.id](m_mapHandler, m_player, sceneToPlay.variant, m_pokedex);

	for (CutsceneInstruction instruction : instructions)
	{
		if (leaveStory())
			break;

		if (instruction.type == InstructionType::MOVE || instruction.type == InstructionType::TURN)
			addCharacterToMover(instruction);
		else if (instruction.type == InstructionType::PLAY)
			moveCharacters();
		else if (instruction.type == InstructionType::DIALOGUE)
			displayDialogue(instruction.dialogue);
		else if (instruction.type == InstructionType::SET_POSITION)
			setCharacterPosition(instruction);
		else if (instruction.type == InstructionType::ACQUIRE_ITEM)
			acquireItem(instruction);
		else if (instruction.type == InstructionType::PLAY_OVERLAY)
			playOverlay(instruction.menuFunction);
		else if (instruction.type == InstructionType::BATTLE)
			playBattle(instruction.character, instruction.battleData);
		else if (instruction.type == InstructionType::HEAL_POKEMON)
			healPokemon(instruction.character, instruction.index);
	}

	m_characterMover->setPriorityOnly(false);

	if (!leaveStory())
		setCutSceneID((int)m_currentScene + 1);
}

void Story::initCutscenes()
{
	setupMapLocations();
	setupStoryBoardMap();
}

bool Story::leaveStory()
{
	return m_renderer->shouldClose() || m_forceLeaveStory;
}


void Story::setCutSceneID(int id)
{
	m_currentScene = (CutSceneID)id;
	m_mapHandler->removeNPTOnCutscene(m_currentScene);
}

void Story::setupMapLocations()
{
	// Player Room
	addMapLocation(SectionID::START_HOUSE_ROOM, { 5,3 }, {CutSceneID::MOM_CALLS_DOWNSTAIRS});
	addMapLocation(SectionID::START_HOUSE_ROOM, { 5,2 }, {CutSceneID::MOM_CALLS_DOWNSTAIRS});
	addMapLocation(SectionID::START_HOUSE_ROOM, { 5,1 }, {CutSceneID::MOM_CALLS_DOWNSTAIRS});
	addMapLocation(SectionID::START_HOUSE_ROOM, { 5,0 }, {CutSceneID::MOM_CALLS_DOWNSTAIRS});


	addMapLocation(SectionID::START_HOUSE_BASE_FLOOR, { 10, 5 }, {CutSceneID::MEET_FRIEND_TELL_TO_GO_TO_PROF, 0});
	addMapLocation(SectionID::START_HOUSE_BASE_FLOOR, { 10, 4 }, {CutSceneID::MEET_FRIEND_TELL_TO_GO_TO_PROF, 1});

	addMapLocation(SectionID::START_HOUSE_BASE_FLOOR, { 1,0 }, {CutSceneID::RECIEVE_MAP_FROM_MOM, 0});
	addMapLocation(SectionID::START_HOUSE_BASE_FLOOR, { 2,1 }, {CutSceneID::RECIEVE_MAP_FROM_MOM, 1});
	addMapLocation(SectionID::START_HOUSE_BASE_FLOOR, { 3,1 }, {CutSceneID::RECIEVE_MAP_FROM_MOM, 2});
	addMapLocation(SectionID::START_HOUSE_BASE_FLOOR, { 4,1 }, {CutSceneID::RECIEVE_MAP_FROM_MOM, 3});
	addMapLocation(SectionID::START_HOUSE_BASE_FLOOR, { 5,0 }, {CutSceneID::RECIEVE_MAP_FROM_MOM, 4});

	addMapLocation(SectionID::PROFESSOR_LAB, { 7,1 }, {CutSceneID::ENTER_PROFESSOR_LAB, 0});

	addMapLocation(SectionID::HOME_VILLAGE_ROUTE_1, { 15, 26 }, {CutSceneID::FIRST_RIVAL_FIGHT, 0});
	addMapLocation(SectionID::HOME_VILLAGE_ROUTE_1, { 16, 26 }, {CutSceneID::FIRST_RIVAL_FIGHT, 0});
	addMapLocation(SectionID::HOME_VILLAGE_ROUTE_1, { 17, 26 }, {CutSceneID::FIRST_RIVAL_FIGHT, 0});
}

void Story::setupStoryBoardMap()
{
	// This is a function to keep the header clean and so that I can organize thoughts better

	setCutscene(CutSceneID::MOM_CALLS_DOWNSTAIRS, StoryBoard::momCallsDownstairs);
	setCutscene(CutSceneID::MEET_FRIEND_TELL_TO_GO_TO_PROF, StoryBoard::meetFriendAndTellToGoToProf);
	setCutscene(CutSceneID::RECIEVE_MAP_FROM_MOM, StoryBoard::recieveMapFromMom);


	// When entering prof lab
	// - Player will get pokedex
	// - Player will get their first pokemon
	// - Player also gets 5 pokeballs from professor
	setCutscene(CutSceneID::ENTER_PROFESSOR_LAB, StoryBoard::enterProfessorLab);

	// First Rival Fight starter vs starter
	// - Player can lose
	setCutscene(CutSceneID::FIRST_RIVAL_FIGHT, StoryBoard::firstRivalFight);
}

void Story::addCharacterToMover(CutsceneInstruction instruction)
{
	if (instruction.type == InstructionType::MOVE)
		m_characterMover->moveCharacter(instruction.character, instruction.direction);
	else
		m_characterMover->turnCharacter(instruction.character, instruction.direction);
}

void Story::moveCharacters()
{
	m_mapHandler->onUpdate();
	m_player->onUpdate(m_renderer);
	m_renderer->onUpdate();

	while (!m_characterMover->priorityQueueEmpty())
	{
		if (m_renderer->shouldClose())
			break;

		m_characterMover->onUpdate();
		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_renderer->onUpdate();
	}

}

void Story::displayDialogue(Dialogue dialogue)
{
	m_dialogueRenderer->setSpeakerName(dialogue.speaker);
	m_dialogueRenderer->setDialogue(dialogue.topLine, dialogue.botLine, true);

	while (m_dialogueRenderer->rendereringDialogue())
	{
		if (m_renderer->shouldClose())
			break;

		m_mapHandler->onUpdate();
		m_player->onUpdate(m_renderer);
		m_dialogueRenderer->renderDialogue();
		m_renderer->onUpdate();
	}
}

void Story::setCharacterPosition(CutsceneInstruction instruction)
{
	instruction.character->position.coords = instruction.coord;
	instruction.character->position.direction = instruction.direction;
}

void Story::acquireItem(CutsceneInstruction instruction)
{
	MenuFunction::playerAcquireArtifact(
		instruction.artifact.artifactName,
		instruction.artifact.artifactPath,
		instruction.artifact.comments,
		m_mapHandler,
		m_player,
		m_menu,
		m_renderer);
}

void Story::playOverlay(void(*function)(MapHandler* mapHandler, Trainer* trainer, Menu* menu, Renderer* renderer, Pokedex* pokedex))
{
	function(m_mapHandler, m_player, m_menu, m_renderer, m_pokedex);
}

void Story::playBattle(Trainer* opponent, BattleData data)
{
	for (int i = 0; i < data.opponentPokemon.size(); i++)
	{
		opponent->setPokemon(i, data.opponentPokemon.at(i));
	}

	for (int i = data.opponentPokemon.size(); i < 6; i++)
	{
		opponent->setPokemon(i, Pokemon());
	}

	m_battleSim->beginBattle((NPT*)opponent);

	
	if (data.mustWin && m_player->unableToBattle())
	{
		// TODO: Animate Whiteout
		m_forceLeaveStory = true;
		m_mapHandler->respawnAfterWhiteOut();
	}
}

void Story::healPokemon(Trainer* trainer, int index)
{
	trainer->getRoster()[index].fullRestore();
}

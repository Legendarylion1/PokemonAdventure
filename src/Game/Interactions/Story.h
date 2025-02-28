#pragma once

#include "StoryBoard.h"
#include "../../Battle/Battle.h"

struct StoryData
{
	CutSceneID id;
	int variant = 0;
};

class Story
{
public:
	Story(){};

	Story(MapHandler* mapHandler, CharacterMover* characterMover, Trainer* player, Renderer* renderer, DialogueRenderer* dialogueRenderer, Menu* menu, Battle* battleSim, Pokedex* pokedex);

	void onUpdate();

	void setCutSceneID(int id);

	CutSceneID getCurrentScene() { return m_currentScene; };
private:

	bool shouldPlayNextCutscene();

	void playCutscene();

	void initCutscenes();
	
	bool leaveStory();

	void setupMapLocations();
	void setupStoryBoardMap();

	void addMapLocation(SectionID section, Coordinate coord, StoryData data) { m_mapLocations[section][coord] = data; }

	void setCutscene(CutSceneID id, std::vector<CutsceneInstruction>(*function)(MapHandler* mapHandler, Trainer* player, int variant, Pokedex* pokedex)) { m_cutscenes[id] = function; }

private:

	void addCharacterToMover(CutsceneInstruction instruction);
	void moveCharacters();
	void displayDialogue(Dialogue dialogue);
	void setCharacterPosition(CutsceneInstruction instruction);
	void acquireItem(CutsceneInstruction instruction);
	void playOverlay(void (*function)(MapHandler* mapHandler, Trainer* trainer, Menu* menu, Renderer* renderer, Pokedex* pokedex));
	void playBattle(Trainer* opponent, BattleData data);
	void healPokemon(Trainer* trainer, int index);

	CutSceneID m_currentScene = MOM_CALLS_DOWNSTAIRS;

	MapHandler* m_mapHandler = nullptr;
	CharacterMover* m_characterMover = nullptr;
	Trainer* m_player = nullptr;
	Renderer* m_renderer = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	Menu* m_menu = nullptr;
	Battle* m_battleSim = nullptr;
	Pokedex* m_pokedex = nullptr;

	bool m_forceLeaveStory = false;

	std::unordered_map<SectionID, std::unordered_map<Coordinate, StoryData, CoordinateHashFunction>> m_mapLocations;

	// Need to know if we are looking at the correct map
	// We need to know if we are on the correct tile

	std::unordered_map<CutSceneID, std::vector<CutsceneInstruction>(*)(MapHandler* mapHandler, Trainer* player, int variant, Pokedex* pokedex)> m_cutscenes;
};
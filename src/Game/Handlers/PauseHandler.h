#pragma once
#include "../../Menu/Menu.h"
#include "../../Menu/MenuFunction/MenuSetup.h"
#include "../../Characters/Trainer/Trainer.h"
#include "../Input/Input.h"
#include "../../Battle/Attack/Attack.h"
#include "../../ExternalData/DataManager.h"
#include "../../Characters/CharacterMover.h"
#include "../../Graphics/DialogueRenderer.h"
#include "../../Map/WorldMap/InteractiveMap.h"

class PauseHandler
{
public:
	PauseHandler() {};
	void setup(Menu* menu, Trainer* player, Input* input, DataManager* dataManager, Renderer* renderer, CharacterMover* characterMover, Timer* timer, RosterDisplayData* rosterData, Pokedex* pokedex, DialogueRenderer* dialogueRenderer, MapHandler* mapHandler);


	void run(CutSceneID currentScene);

	PauseSettingsData* getPauseSettingData() { return &m_pauseSettingData; };

private:
	void handleRoster();
	void handleItems();
	void handleSettings();
	void handleMap();
	void handleSave();

	void selectResolution();
	void selectNewInput(ControlType type);

private:
	//void updateDisplayPokemons();
	//void displayPokemonStats(int* hoveredIndex);
	void updatePlayerItems();
	void moveWindowUp();
	void moveWindowDown();
	ItemID getSelectedItem();
	bool usedMedicine(Item* item);

	void animateHeal(Item* item, Pokemon* pokemon, Pokemon* dataPokemon, int* hoveredIndex);

	//void formatMoveStringData(Pokemon displayPokemon, MoveStringData* data, int moveIndex);
	void setHighlightedPokemonHP(Pokemon displayPokemon);
	void setBadgeVisibility();
	void setPauseButtonVisibility(CutSceneID currentScene);

private:
	Menu* m_menu = nullptr;
	Trainer* m_player = nullptr;
	Input* m_input = nullptr;
	DataManager* m_dataManager = nullptr;
	Renderer* m_renderer = nullptr;
	CharacterMover* m_characterMover = nullptr;
	Timer* m_timer = nullptr;
	Pokedex* m_pokedex = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	MapHandler* m_mapHandler = nullptr;

	PauseMenuData m_pauseMenuData;

	PokemonStringData m_pokemonStringData;	//TODO: Replace
	TrainerBadgeData m_badgeData;
	PausePokemonData m_pausePokemonData;
	PauseSettingsData m_pauseSettingData;
	RosterDisplayData* m_rosterData = nullptr;
	ItemDisplayData m_items;
	SharedString m_rosterTypings;
	std::string m_playerBalance;
	std::string m_playTime;

	int m_selection = NONE;
	int m_bagIndex = 0;
};
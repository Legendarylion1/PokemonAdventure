#pragma once

#include "../Menu.h"

namespace MenuSetup
{
	void setupDialogueRenderer(Menu* menu, DialogueRendererData* dialogueData);
	void setupKeyboard(Menu* menu, AlphabetStringData* alphabet, std::string* input);
	void setupIntroData(Menu* menu, bool* studioVisible, bool* pressAnyButtonVisible, bool* showMaleIcon, bool* showFemaleIcon);
	void setupStartupData(Menu* menu, SharedString* header1, SharedString* header2, SharedString* header3, bool* f1Visible, bool* f2Visible, bool* f3Visible);
	void setupBattleData(Menu* menu, SharedString* moves, SimulationCommand* menuCommand, RosterDisplayData* rosterData, ItemDisplayData* battleItemData, BattlePokemonData* battleData, DynamicImageRenderData* playerPokemon, DynamicImageRenderData* oppPokemon, LearnMoveData* learnMoveData);
	void setupInteractionData(Menu* menu, SharedString* items, std::string* balance, NurseHealData* nurseHealData);
	void setupPauseData(Menu* menu, ItemDisplayData* items, PauseMenuData* pauseMenuData, RosterDisplayData* rosterData, PauseSettingsData* settingData);
	void setupPokedexData(Menu* menu, PokedexDisplayData* pokedexDisplayData);
	void setupPCData(Menu* menu, PCData* pcData);
	void setupSummaryData(Menu* menu, SummaryData* data);
	void setupSaveAndExit(Menu* menu);
	void setupSelectPlayerGender(Menu* menu, bool* boyHighlight, bool* girlHighlight);
	void setupPlayerAcqiuresItem(Menu* menu, AcquireItemData* data);
	void setupProfTablePokemonSelection(Menu* menu, SelectProfPokemonData* data);
	void setupBuyItems(Menu* menu, BuyItemData* data);
	void setupRosterOptions(Menu* menu, std::vector<std::string> data);
}
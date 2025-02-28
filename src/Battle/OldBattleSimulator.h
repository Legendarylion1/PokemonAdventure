#pragma once

#include <unordered_map>
#include <algorithm>
#include "Attack/Attack.h"
#include "../Characters/Trainer/NPT.h"
#include "../Menu/Menu.h"
#include "../Graphics/DialogueRenderer.h"
#include "../Graphics/Animator.h"
#include "BattleAnimations.h"


///	===============================================================
/// 
///					~ Deprecated Code ~	
/// 
///	This class has been completely refactored and renamed to Battle
/// The new file is Battle.h
/// 
/// I am keeping this file here as reference for my Battle Class
/// 
/// This class will be deleted eventually, but I want to spend some
/// time to make sure that everything in here has been transfererd
/// 
/// Currently Battle.h has more functionality than this class, but
/// just in case this file will be kept for reference
/// 
/// ===============================================================

class OldBattleSimulator
{
public:
	void setup(Trainer* trainer, Menu* menu, RosterDisplayData* rosterData, DialogueRenderer* dialogueRenderer, OldAnimator* animator, Input* input, Timer* timer);

	void beginBattle(NPT* npt);
	Pokemon beginBattle(Pokemon pokemon);
private:

	void updatePlayerItems();
	bool canIncrementItemList();

	void setupTrainer();
	void setupNPT(NPT* npt);
	void setupPokemon(Pokemon pokemon);
	void setupXP();


	bool simulateBattle();
	bool runSimulation();
	bool battleOver();

	void grantNPTRewards();
	Pokemon handleCatch();

	void onUpdate();



private:	// Generate Simulation Data
	void generateSimulationData(SimulationCommand playerCommand, SimulationCommand aiCommand);
	void generateStatusData(SelectedUser user, IncrementTime afflictionTime);
	SimulationCommand getAICommand();

	int getMoveFromCommand(int commandMove, SelectedUser user);
	ItemID getItemFromCommand(int itemIndex, SelectedUser user);

	void generateAttack(SelectedUser attacker, SimulationCommand command);
	bool generateItem(SelectedUser commander, SimulationCommand command);
	SimulationCommand generateForcedAttack(SelectedUser commander);

	void handleAttack(SimulationCommand playerCommand, SimulationCommand aiCommand);
	void handlePokemonSwap(SimulationCommand playerCommand, SimulationCommand aiCommand);
	void handleItemSelection(SimulationCommand playerCommand, SimulationCommand aiCommand);
	void handleFleeSelection(SimulationCommand aiCommand);
	void handleFaintSelection(SelectedUser swapper);

	void appendCommands(std::vector<SimulationCommand> commands);

private:	// Run Simulation Data
	void simulateAttack(SimulationCommand command);
	void simulatePokemon(SimulationCommand command);
	void simulateItem(SimulationCommand command);
	void simulateFlee(SimulationCommand command);
	void simulateStatus(SimulationCommand command);
	void simulateStat(SimulationCommand command);

	bool attackMissed(SimulationCommand command);

	void handleFaintXP(SelectedUser user);
	void dripDamage(SelectedUser pokemonToDamage, int value);
	void addToXpRecord();
	void removeXpRecord();
	void grantEVs();
	void grantXP();
	void levelPokemon(int index);
	void evolvePokemon(int index);
	void teachMove(int index);
	void displayFaintMessage(SelectedUser user);

private:
	void reducePP(SelectedUser attacker, int move);
	void updatePP(SelectedUser user);
	void updatePlayerAttacks();

	void renderDialogue(std::string topLine, std::string bottomLine, bool awaitClick);
	void resetMenu();

private:

	void adjustPokemonDisplay(SelectedUser user);
	void adjustHealthPercentage(SelectedUser user);
	void adjustXPPercentage();
	bool validItemSelection(int selection);

private:
	Menu* m_menu = nullptr;
	SharedString m_playerAttacks;
	ItemDisplayData m_playerBattleItems;
	RosterDisplayData* m_rosterData = nullptr;
	BattlePokemonData m_battleData;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	OldAnimator* m_animator = nullptr;
	Input* m_input = nullptr;
	Timer* m_timer = nullptr;

	SimulationCommand m_menuCommand{};

	bool m_flee = false;
	bool m_pokemonCaught = false;

	int m_itemIndex = 0;
	int m_playerPokemonIndex = 0;
	int m_opponentPokemonIndex = 0;

	int m_displayPokemonIndex = 0;
	int m_hoverIndex = -1;

	Pokemon* m_playerDisplayPokemon = nullptr;
	Pokemon m_playerTestPokemon[6];
	DynamicImageRenderData m_playerPokemonData = { 25.5f, (253.5f / 563.0f) * 100.0f, 20.0f * (9.0f / 16.0f), 20.0f};

	Pokemon m_opponentDisplayPokemon[6];
	Pokemon m_opponentTestPokemon[6];
	DynamicImageRenderData m_opponentPokemonData = { 74.4f, (443.0f / 563.0f) * 100.0f, 10.0f, 10.0f * (16.0f / 9.0f)};

	std::vector<SimulationCommand> m_commands;
	Moveset m_p1moveset;

	Trainer* m_player = nullptr;
	NPT* m_npt = nullptr;

	std::map<ItemID, int>* m_battleItems = nullptr;
	std::unordered_map<int, std::vector<int>> m_xpRecords = {	
		{0,{}},
		{1,{}},
		{2,{}},
		{3,{}},
		{4,{}},
		{5,{}},
	};
};
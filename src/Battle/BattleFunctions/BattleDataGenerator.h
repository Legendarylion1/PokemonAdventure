#pragma once

#include "../../Characters/Trainer/NPT.h"

// Generate Test Data
//		Use Test Pokemon to generate sim data
//		Consider stats when level up
//		DO NOT TOUCH DISPLAY POKEMON
//		Trainer inventory reduced
//		Anything related to adjusting trainer is here


// Trainer Pokemon
// Trainer Items
// AI Pokemon
// No Rendering here

class BattleDataGenerator
{
public:
	BattleDataGenerator();

	void setup(Trainer* trainer, SimulationCommand* playerCommand, SimulationCommand* aiCommand, int* playerPokemonIndex, int* opponentPokemonIndex, int* endCondition, Renderer* renderer);	//TODO: In future AI and player commands dont need to be sim commands

	void setOpponent(NPT* npt);
	void setOpponent(Pokemon* pokemon);

	std::vector<SimulationCommand> generateData();

private:
	void setupTestPokemon();
	void setupTrainerPokemon();

	void handleAttack();
	void handlePokemonSwap();
	void handleItemSelection();
	void handleFleeSelection();

private:
	bool stopGenerating();
	void generateAttack(SelectedUser user);
	void generateItem(SelectedUser user);
	void generateStatusData(SelectedUser user, IncrementTime afflictionTime, bool appendData = true);

	bool pokemonCaught();

	int getMoveFromCommand(SimulationCommand command, SelectedUser user);

	void appendCommands(std::vector<SimulationCommand> commands);

	ItemID getAIItemFromCommand(int selection);

private:
	Renderer* m_renderer = nullptr;

	Trainer* m_trainer = nullptr;
	NPT* m_npt = nullptr;

	Pokemon m_playerPokemon;
	Pokemon m_opponentPokemon;

	Pokemon* m_wildPokemon = nullptr;

	SimulationCommand* m_playerCommand = nullptr;
	SimulationCommand* m_aiCommand = nullptr;

	int* m_playerPokemonIndex = nullptr;
	int* m_opponentPokemonIndex = nullptr;

	int* m_endCondition = nullptr;

	int m_localPlayerPokemonIndex = 0;

	std::vector<SimulationCommand> m_commands;
};
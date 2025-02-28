#pragma once

#include "BattleMenuGraphics.h"
#include "../../Menu/MenuFunction/MenuFunction.h"

class BattleAction
{
public:
	BattleAction();

	void setup(Trainer* trainer, Menu* menu, SimulationCommand* playerCommand, SimulationCommand* aiCommand, int* playerPokemonIndex, int* opponentPokemonIndex, BattleMenuGraphics* battleMenuGraphics, Timer* timer);

	void setOpponent(NPT* npt);
	void setOpponent(Pokemon* pokemon);

	void getAction();

	void updateAllGraphics();

private:
	bool playerHasForcedAttack();
	void generateAICommand();	//On one hand I think AI command can be generated here, and on the other it can be generated with the other data

	void resetBattleAction();

	bool moveSelected();
	bool pokemonSelected(bool canSelectSelf = false, bool canSelectZeroHP = false);
	bool itemSelected();
	bool fleeSelected();

private:
	int getAIMoveFromCommand(int commandMove);		

	bool itemFound();
	bool itemRecipientPicked();

	void moveWindowUp();
	void moveWindowDown();

	void reducePP();

private:
	Menu* m_menu = nullptr;
	Timer* m_timer = nullptr;

	Trainer* m_trainer = nullptr;
	NPT* m_npt = nullptr;
	Pokemon* m_wildPokemon = nullptr;

	Moveset m_playerMoveset;

	SimulationCommand* m_playerCommand = nullptr;
	SimulationCommand* m_aiCommand = nullptr;

	int* m_playerPokemonIndex = nullptr;
	int* m_opponentPokemonIndex = nullptr;
	int m_itemWindowDisposition = 0;

	BattleMenuGraphics* m_battleMenuGraphics = nullptr;
};
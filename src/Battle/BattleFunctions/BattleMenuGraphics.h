#pragma once

#include "../../Characters/Trainer/NPT.h"
#include "../../Menu/Menu.h"
#include "../../Menu/MenuFunction/MenuSetup.h"

class BattleMenuGraphics
{
public:
	void setup(Trainer* trainer, Menu* menu, int* playerPokemonIndex, int* opponentPokemonIndex, RosterDisplayData* rosterData);

	void setOpponent(NPT* npt);
	void setOpponent(Pokemon* pokemon);

	void resetPreviousRosterHoverIndex() { m_prevoiusRosterHoverIndex = -1; };
	void resetPreviousLearnMoveHoverIndex() { m_prevoiusLearnMoveHoverIndex = -1; };

public:

	void updateAllGraphics(int itemWindowDisposition = 0);
	void updateMoves();
	void updateItemList(int itemWindowDisposition);
	void updateRosterList();
	void updatePokemonStats();
	void updateLevelUpStats(std::string name, std::string level, SharedString statDifference, SharedString statValue);

	void updatePokemonDisplay(SelectedUser user);
	void updateHealthPercentage(SelectedUser user);
	void updateXPPercentage();

	void updateLearnMoveScene(int pokemonIndex, int hoverIndex, int newAttackID);

	DynamicImageRenderData* getPlayerRenderData() { return &m_playerPokemonData; };
	DynamicImageRenderData* getOpponentRenderData() { return &m_opponentPokemonData; };

private:

	void formatMoveStringData(MoveStringData* move, int attackID, int currentPP);

private:
	Trainer* m_trainer = nullptr;
	NPT* m_npt = nullptr;
	Menu* m_menu = nullptr;

	Pokemon* m_wildPokemon = nullptr;

	int* m_playerPokemonIndex = nullptr;
	int* m_opponentPokemonIndex = nullptr;

private:
	SharedString m_playerMoves;
	ItemDisplayData m_playerBattleItems;
	RosterDisplayData* m_rosterData = nullptr;
	BattlePokemonData m_battleData;
	LearnMoveData m_learnMoveData;
	DynamicImageRenderData m_playerPokemonData = { 25.5f, (253.5f / 563.0f) * 100.0f, 20.0f * (9.0f / 16.0f), 20.0f };
	DynamicImageRenderData m_opponentPokemonData = { 74.4f, (443.0f / 563.0f) * 100.0f, 10.0f, 10.0f * (16.0f / 9.0f) };

	int m_prevoiusRosterHoverIndex = -1;
	int m_prevoiusLearnMoveHoverIndex = -1;
};
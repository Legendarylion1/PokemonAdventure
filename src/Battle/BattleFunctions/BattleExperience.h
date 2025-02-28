#pragma once
#include "../../Characters/Trainer/NPT.h"
#include "../../Graphics/Animator.h"
#include "../../Menu/Menu.h"
#include "BattleMenuGraphics.h"
#include "../../Graphics/DialogueRenderer.h"
#include "../BattleAnimations.h"
#include "../../Game/Pokedex/Pokedex.h"

class BattleFaintHandler
{
public:
	BattleFaintHandler() {};

	void setup(Trainer* trainer, Pokedex* pokedex, Menu* menu, AnimationStream* animator, BattleMenuGraphics* battleMenuGraphics, Timer* timer, Input* input, DialogueRenderer* dialogueRenderer, int* playerPokemonIndex, int* opponentPokemonIndex);

	void setOpponent(NPT* npt);
	void setOpponent(Pokemon* pokemon);


	void handleFaints();
	std::vector<int> getEvolutionCandidates() { return m_evolutionCandidates; };

private:

	void updateXPRecords();
	void animateXP();
	void swapPokemon();

	void addRecord();
	void removeRecord();
	void recordEvolution(int index);

	void distributeEVs();
	void distributeXP();

	void levelPokemon(int index);
	void teachMove(int index);

	void resetFaintedPokemon(Pokemon* pokemon);

private:

	bool aSideIsUnableToBattle();
	bool playerWantsToSwapPokemon();

	int getPlayerPokemonSwap(bool canLeave);
	void swapAIPokemon();

	void sendOutPokemon(SelectedUser user);
	void withdrawPlayerPokemon();

	void renderDialogue(std::string topText, std::string botText, bool awaitClick);

private:
	void reset();

	Menu* m_menu = nullptr;
	AnimationStream* m_animator = nullptr;
	BattleMenuGraphics* m_battleMenuGraphics = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	Timer* m_timer = nullptr;
	Input* m_input = nullptr;

	Trainer* m_trainer = nullptr;
	NPT* m_npt = nullptr;
	Pokedex* m_pokedex = nullptr;
	Pokemon* m_wildPokemon = nullptr;

	int* m_playerPokemonIndex = nullptr;
	int* m_opponentPokemonIndex = nullptr;

	int m_playerIndex = -1;

	float m_xpDripRate = 0.02f;

	std::vector<int> m_evolutionCandidates;

	std::unordered_map<int, std::vector<int>> m_xpRecords = {
		{0,{}},
		{1,{}},
		{2,{}},
		{3,{}},
		{4,{}},
		{5,{}},
	};
};
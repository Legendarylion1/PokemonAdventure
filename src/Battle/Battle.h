#pragma once

#include <unordered_map>
#include <algorithm>
#include "Attack/Attack.h"
#include "../Characters/Trainer/NPT.h"
#include "../Menu/Menu.h"
#include "../Graphics/DialogueRenderer.h"
#include "../Graphics/Animator.h"
#include "BattleAnimations.h"
#include "BattleFunctions/BattleAction.h"
#include "BattleFunctions/BattleDataSimulator.h"
#include "BattleFunctions/BattleDataGenerator.h"
#include "BattleFunctions/BattleExperience.h"

class Battle
{
public:

	void setup(Trainer* trainer, Pokedex* pokedex, Menu* menu, RosterDisplayData* rosterData, DialogueRenderer* dialogueRenderer, AnimationStream* animator, Renderer* renderer, Input* input, Timer* timer);

	void beginBattle(NPT* npt);
	Pokemon beginBattle(Pokemon pokemon);

	bool inBattle() { return m_inBattle; }

private:

	void givePokemonPP(NPT* npt);
	void givePokemonPP(Pokemon* pokemon);

	void loadAnimations();

	void playBattle();
	bool battleOver();

	void rewardPlayer();
	void evolvePokemon();
	void resetAllPokemon();

	bool evolutionAnimated(int preEvolution, int postEvolution, std::string pokemonName);

	void shrinkEvolution(DynamicImageRenderData* evolutionData, float* animationSpeed, bool animate = true);
	void growEvolution(DynamicImageRenderData* evolutionData, float* animationSpeed);

	void changeEvolutionColor(DynamicImageRenderData* evolutionData, bool turnWhite);

	void renderDialogue(std::string topLine, std::string bottomLine, bool awaitClick);

private:
	void fadeIntoBattle();
	void fadeOutOfBattle();

private:

	Trainer* m_trainer = nullptr;
	NPT* m_npt = nullptr;
	Pokedex* m_pokedex = nullptr;
	Pokemon m_wildPokemon;
	Menu* m_menu = nullptr;

	BattleAction m_battleAction;
	BattleDataGenerator m_dataGenerator;
	BattleDataSimulator m_dataSimulator;
	BattleFaintHandler m_faintHandler;

	BattleMenuGraphics m_battleMenuGraphics;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	AnimationStream* m_animator = nullptr;
	Timer* m_timer = nullptr;


private:

	SimulationCommand m_playerCommand;
	SimulationCommand m_aiCommand;

	int m_playerPokemonIndex = 0;
	int m_opponentPokemonIndex = 0;
	int m_endCondition = NONE;

	bool m_inBattle = false;
};
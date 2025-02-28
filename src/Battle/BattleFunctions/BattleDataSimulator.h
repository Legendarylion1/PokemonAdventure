#pragma once

#include "../../Characters/Trainer/NPT.h"
#include "../BattleAnimations.h"
#include "../../Menu/Menu.h"
#include "../../Graphics/DialogueRenderer.h"
#include "../../Graphics/Animator.h"
#include "BattleMenuGraphics.h"

//		Simulate Battle based on the data
//		Faints are not handled here
//		Evolution is not handled here
//		Level up move select is done here


//
class BattleDataSimulator
{
public:
	BattleDataSimulator();

	void setup(Trainer* trainer, Menu* menu, Renderer* renderer, DialogueRenderer* dialogueRenderer, AnimationStream* animator, BattleMenuGraphics* battleMenuGraphics, Timer* timer, int* playerPokemonIndex, int* opponentPokemonIndex);

	void setOpponent(NPT* npt);
	void setOpponent(Pokemon* pokemon);

	void runSimulation(std::vector<SimulationCommand> commands);

private:
	void simulateAttack(SimulationCommand command);
	void simulatePokemon(SimulationCommand command);
	void simulateItem(SimulationCommand command);
	void simulateFlee(SimulationCommand command);
	void simulateStatus(SimulationCommand command);
	void simulateStat(SimulationCommand command);

	bool attackMissed(SimulationCommand command);
	void dripDamage(SelectedUser pokemonToDamage, int value);
	void dripHeal(SelectedUser pokemonToHeal, int value);
	void renderDialogue(std::string topLine, std::string bottomLine, bool awaitClick);
	void throwPokeball(SimulationCommand command);
	void withdrawPlayerPokemon();
	void sendOutPlayerPokemon();
	void pokemonTakeDamageAnimation(SelectedUser user);
	void faintPokemon(SelectedUser user);

	void manageDripRate(float dripRate);


	void setupPokemon();
	void onUpdate();



private:
	Trainer* m_trainer = nullptr;
	NPT* m_npt = nullptr;

	Pokemon* m_playerPokemon = nullptr;
	Pokemon* m_opponentPokemon = nullptr;

	Pokemon* m_wildPokemon = nullptr;

	Menu* m_menu = nullptr;
	Renderer* m_renderer = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	AnimationStream* m_animator = nullptr;
	BattleMenuGraphics* m_battleMenuGraphics = nullptr;
	Timer* m_timer = nullptr;

	int* m_playerPokemonIndex = nullptr;
	int* m_opponentPokemonIndex = nullptr;

private:

	float m_damageDripRate = 0.0002f;
	float m_healDripRate =   0.0005f;
};
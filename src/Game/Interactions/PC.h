#pragma once
#include "../../Characters/Trainer/Trainer.h"
#include "../../Menu/Menu.h"
#include "../../Battle/Attack/Attack.h"
#include "../../Menu/MenuFunction/MenuFunction.h"
#include "../../Menu/MenuFunction/MenuSetup.h"


const static int NUMBER_OF_BOXES = 8;
const static int POKEMON_IN_BOX = 30;

class PC
{
public:

	PC() {};

	void setup(Trainer* trainer, Menu* menu);

	bool addPokemon(Pokemon pokemon);

	Pokemon getPokemon(int box, int index) { return m_pcPokemon[box][index]; };
	void setPokemon(int box, int index, Pokemon pokemon) { m_pcPokemon[box][index] = pokemon; };
	void run();

private:

	bool pokemonAtMenuIndex();
	void setupOverlay();
	void setupBoxOverlay(int index);
	void setupRosterOverlay(int index);
	void setupOptions();

	void setMoveHighlight(bool moveStatus);

	void runOverlay();

	void swapPokemon();

	void moveBoxRight();
	void moveBoxLeft();

	void updateAllDisplays();

	void updateBoxDisplay();
	void updatePokemonStats();
	void updateRosterDisplay();

	int getPokemonStatIndex();

	bool playerHasEnoughPokemon();
	bool isValidSelection();

private:

	void setSwapPokemon();
	void displayPokemonSummary();
	void renamePokemon(int index);
	void deletePokemon();

private:
	Pokemon m_pcPokemon[NUMBER_OF_BOXES][POKEMON_IN_BOX];
	Trainer* m_trainer = nullptr;
	Menu* m_menu = nullptr;

	PCData m_pcData;

	int m_pokemonStatsIndex = NONE;

	int m_currentBox = 0;
	int m_currentPokemonIndex = 0;

	int m_previousBox = 0;
	int m_previousPokemonIndex = 0;

	int m_menuSelection = NONE;

private:
	bool m_inMove = false;

	float m_pcSelectionX = 0.0f;
	float m_pcSelectionY = 0.0f;
	
};
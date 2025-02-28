#pragma once
#include "../../Menu/Menu.h"
#include "../../Menu/MenuFunction/MenuSetup.h"
#include "../../Characters/Pokemon/PokemonSpecies.h"
#include "../../GlobalData/globalIDs.h"
#include "PokedexRingBuffer.h"

enum class EncounterStatus
{
	NOT_SEEN,
	SEEN,
	CAUGHT
};

enum class SortMethod
{
	A_TO_Z,
	Z_TO_A,
	LOWEST_NUMBER,
	HIGHEST_NUMBER
};

struct PokedexEntry
{
	PokemonID speciesID;
	EncounterStatus status;
};

class Pokedex
{
public:
	Pokedex() {};

	void setup(Menu* menu);
	void run();

	std::string save();
	void load(std::vector<std::string> data);

	void spotPokemon(PokemonID id);
	void obtainPokemon(PokemonID id);

	bool hasObtainedPokemon(PokemonID id);

private:

	bool idHasBeenObtained(PokemonID id, int bottomIndex, int topIndex);

	void populateEntries();
	bool binarySetStatus(PokemonID id, EncounterStatus status, int bottomIndex, int topIndex);

private:
	void sort(SortMethod method);

	void sortAToZ(std::vector<PokedexEntry>* entries, int start, int end);
	void sortZToA(std::vector<PokedexEntry>* entries, int start, int end);
	void sortLowNumber(std::vector<PokedexEntry>* entries, int start, int end);
	void sortHighNumber(std::vector<PokedexEntry>* entries, int start, int end);

	bool isLessThan(std::string value1, std::string value2);

private:

	void populateScrollData();
	void populateDisplayData();
	void updateHoverIndex();
	void displayNewPokemon(PokemonID id);

	PokedexScrollButton* getButtonFromRingIndex(int buttonRingIndex);

	void sortDisplayList(int sortSelection);

	void adjustScrollVertically();

	void updateScrollButton(int buttonRingIndex, int distanceFromCenter);
	void makeInvisibleButton(PokedexScrollButton* button);
	void makeVisibleButton(PokedexScrollButton* button, int entryIndex, int distanceFromCenter);

	void animateScrollUp();
	void animateScrollDown();

	glm::vec2 getCoordinatePercentages(int distanceFromCenter);
	std::string formatPokedexNumber(int number);

private:
	Menu* m_menu = nullptr;

	PokedexRingBuffer m_ringBuffer;
	int m_scrollIndex = 0;
	int m_previousHoverIndex = 0;

	int m_pokemonSeen = 0;
	int m_pokemonCaught = 0;

	bool m_visibleButton = true;
	bool m_invisibleButton = false;

	PokedexDisplayData m_pokedexDisplayData;
	SortMethod m_previousSortMethod = SortMethod::A_TO_Z;
	std::vector<PokedexEntry> m_entries;
};
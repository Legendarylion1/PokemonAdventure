#pragma once

#include "../../Graphics/Renderer.h"
#include "../../GlobalData/globalIDs.h"
#include "PokemonSpecies.h"
#include "../../GlobalData/helperFunctions.h"
#include "../../ExternalData/saveData.h"

struct Moveset
{
	int move1 = NONE, move2 = NONE, move3 = NONE, move4 = NONE;
	int move1pp = 0, move2pp = 0, move3pp = 0, move4pp = 0;
};

struct IV
{
	int hp, attack, defense, speed, special;
};

//Can add a casterID so that we know who casted the ability
//Really only matters for minor Status conditions
struct StatusTracker
{
	StatusID id = StatusID::NO_STATUS;

	int turnCount = 0;

	bool isBlocker = false;
	bool isEvasive = false;
	int forcedAttackID = NONE;
};

//IVs are randomly selected when a pokemon is created. They are like the genes of a pokemon

//
//In Generation I and II, only four IVs are stored for each individual Pokémon: Attack, Defense, Speed, and Special. Each of these is used to determine their associated stat, with the HP IV determined from the IVs stored for the other four. 
// IVs range from 0-15 (in binary 0000-1111).
// The HP IV is calculated by taking the least significant bit(the final binary digit) of the Attack, Defense, Speed, and Special IVs, then creating a binary string by placing them in that order.
// As such, a Pokémon with an odd - number Attack IV has 8 added to its HP IV, an odd - number Defense IV has 4 added, an odd - number Speed IV has 2 added, and an odd - number Special IV has 1 added.
//


// 65535 maximum per stat. Square root of that number is about 255. Thats how we get the number of EVS already owned.
// 510 EVs overall is maximum for a fully trained pokemon

//TODO: Store which ball a pokemon is stored in
//TODO: Update nurse to reflect which pokeball a pokemon is in
class Pokemon
{

public:
	Pokemon(Moveset newMoveset, Species pokemonSpecies, int level);
	Pokemon(Species pokemonSpecies, int level);
	Pokemon() {};

	void load(PokemonSave save);

	void fullRestore();
	void gainXP() { m_curXP++; };
	void gainEVs(PokemonStats newEVs);
	bool readyToLevel() { return m_curXP == m_xpNeeded; };
	bool readyToEvolve() { return m_species.Evolution.level == m_level; };
	int readyToLearnMove();

	PokemonStats levelUp();
	void evolve();
	void learnMove(int index, int move, int pp);

	std::string getName() { return m_name; }
	int getCurHealth() { return m_curHealth; };
	StatusTracker* getMajorStatus() { return &m_majorStatus; };
	std::vector<StatusTracker>* getMinorStatus() { return &m_minorStatus; };
	int getCurXP() { return m_curXP; };
	int getXPNeeded() { return m_xpNeeded; };
	int getLevel() { return m_level; };
	Species getSpecies() { return m_species; };
	PokemonStats getStats() { return m_stats; };
	PokemonStats getEvs() { return m_evs; };
	PokemonStats* getBattleStats() { return &m_battleStats; };
	Moveset getMoveset() { return m_moveset; };
	StatusID getAttackBlocker();
	ItemID getPokeball() { return m_pokeball; };
	int hasForcedAttack();
	StatusID hasEvasiveStatus();

	void setName(std::string name) { m_name = name; };
	void setMoveset(Moveset Moveset) { m_moveset = Moveset; };
	void setPokeball(ItemID pokeball) { m_pokeball = pokeball; };
	void adjustCurHealth(int value) { m_curHealth += value; };

	void applyMajorStatus(StatusID id, bool isBlocker);
	void applyMinorStatus(StatusID id, bool isBlocker, bool isEvasive, int forcedAttackID);
	void addBattleStats(PokemonStats stats) { m_battleStats += stats; };

	void removeMajorStatus();
	void removeMinorStatus(StatusID id);
	void removeBattleStats() { m_battleStats = PokemonStats{}; };

public:
	operator PokemonSave const()
	{
		PokemonSave saveData{};	//TODO: Save Status

		saveData.name = m_name;
		saveData.species = m_species.id;
		saveData.level = m_level;
		saveData.currentHealth = m_curHealth;
		saveData.currentXP = m_curXP;

		saveData.hpIv = m_ivs.hp;
		saveData.attackIv = m_ivs.attack;
		saveData.defenseIv = m_ivs.defense;
		saveData.speedIv = m_ivs.speed;
		saveData.specialIv = m_ivs.special;

		saveData.hpEv = m_evs.hp;
		saveData.attackEv = m_evs.attack;
		saveData.defenseEv = m_evs.defense;
		saveData.spattackEv = m_evs.spAttack;
		saveData.spDefenseEv = m_evs.spDefense;
		saveData.speedEv = m_evs.speed;
		saveData.evasionEv = m_evs.evasiveness;
		saveData.accuracyEv = m_evs.accuracy;

		saveData.move1 = m_moveset.move1;
		saveData.move2 = m_moveset.move2;
		saveData.move3 = m_moveset.move3;
		saveData.move4 = m_moveset.move4;

		saveData.move1pp = m_moveset.move1pp;
		saveData.move2pp = m_moveset.move2pp;
		saveData.move3pp = m_moveset.move3pp;
		saveData.move4pp = m_moveset.move4pp;

		saveData.statusID = (int)m_majorStatus.id;
		saveData.turnCount = m_majorStatus.turnCount;
		saveData.isBlocker = m_majorStatus.isBlocker;
		saveData.isEvasive = m_majorStatus.isEvasive;
		saveData.forcedAttack = m_majorStatus.forcedAttackID;

		return saveData;
	}

private:
	PokemonStats updateStats();
	void randomizeMoveset();

private:
	Species m_species{};
	StatusTracker m_majorStatus;
	std::vector<StatusTracker> m_minorStatus;

	IV m_ivs{};

	PokemonStats m_stats{};
	PokemonStats m_evs{};
	PokemonStats m_battleStats{};

	ItemID m_pokeball = ItemID::POKEBALL;

	std::string m_name;

	int m_curHealth = 0;
	int m_level = 0;

	int m_curXP = 0;
	int m_xpNeeded = 0;
	
	Moveset m_moveset;
};
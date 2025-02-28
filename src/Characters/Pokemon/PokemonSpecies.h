#pragma once
#include <string>
#include <math.h>
#include <unordered_map>
#include "../../ExternalData/Logger.h"

enum Rarity
{
	COMMON,
	UNCOMMON,
	RARE,
	SUPERRARE,
	COUNT	//Count is the number of rarities. Dont use it as a rarity lol
};

enum class LevelingRate
{
	Slow,
	MediumSlow,
	MediumFast,
	Fast,
	Fluctuating
};

namespace StatBoost
{
	static const int NONE = 0;
	static const int INCREASE = 1;
	static const int SHARP_INCREASE = 2;
	static const int DECREASE = -1;
	static const int SHARP_DECREASE = -2;
	static const int MAX = 6;
	static const int MIN = -6;
};

struct PokemonStats
{
	int hp;
	int attack;
	int defense;
	int spAttack;
	int spDefense;
	int speed;
	int evasiveness;
	int accuracy;

public :
	PokemonStats operator-(PokemonStats other)
	{
		PokemonStats value{};
		value.hp = this->hp - other.hp;
		value.speed = this->speed - other.speed;
		value.attack = this->attack - other.attack;
		value.defense = this->defense - other.defense;
		value.accuracy = this->accuracy - other.accuracy;
		value.spAttack = this->spAttack - other.spAttack;
		value.spDefense = this->spDefense - other.spDefense;
		value.evasiveness = this->evasiveness - other.evasiveness;
		return value;
	}
	void operator+=(PokemonStats other)
	{
		this->hp = this->hp + other.hp;
		this->speed = this->speed + other.speed;
		this->attack = this->attack + other.attack;
		this->defense = this->defense + other.defense;
		this->spAttack = this->spAttack + other.spAttack;
		this->accuracy = this->accuracy + other.accuracy;
		this->spDefense = this->spDefense + other.spDefense;
		this->evasiveness = this->evasiveness + other.evasiveness;
	}
};

struct Evolution
{
	int level;
	PokemonID pokemon;
};

//TODO: Load the species from JSON. It will be easier to edit pokemon data there
struct Species
{ 
	std::string name;
	PokemonID id;
	Type type1;
	Type type2;

	std::string height;
	std::string weight;
	std::string description;

	PokemonStats baseStats;
	LevelingRate levelRate;
	int expYield;
	PokemonStats evYield;
	std::unordered_map<int, AttackID> movesLearned;
	Evolution Evolution;
};

static int calculateXPNeeded(int level, LevelingRate levelRate)
{
	switch (levelRate)
	{
	case LevelingRate::Slow:		//(5(n)^3)/4
		return (int)((5 * pow(level, 3)) / 4.0f);
	case LevelingRate::MediumSlow:
		// ((6/5)n^3)-15n^2+100n-140
		return (int)(((6.0f / 5.0f) * pow(level, 3)) - (15 * pow(level, 2)) + (100 * level) - 140);
	case LevelingRate::MediumFast:	// n^3
		return (int)pow(level, 3);
	case LevelingRate::Fast:		// (4n^3)/5
		return (int)((4 * pow(level, 3)) / 5.0f);
	case LevelingRate::Fluctuating:
		//	n < 153
		//	(n^3(floor((n+1)/3) + 24) ) / 50
		// 
		// n >= 15 and n < 30
		// 
		// (n^3(n+14) ) / 50
		// 
		// else
		// (n^3(floor(n/2) + 32)) / 50
		if (level < 15)
			return (int)(pow(level, 3) * (floor((level + 1.0f) / 3.0f) + 24.0f) / 50.0f);
		else if (level < 30)
			return (int)((pow(level, 3) * (level + 14)) / 50.0f);
		else
			return (int)((pow(level, 3) * (floor(level / 2.0f) + 32)) / 50.0f);
	default:
		return -1;
	}
}

static int calculateHPStat(int baseValue, int iv, int ev, int level)
{
	return (int)(floor(((((baseValue + iv) * 2) + floor(sqrt(ev) / 4.0f)) * level) / 100.0f) + level + 10);
}

//HP is calculated differently so use the HP Stat calculator for HP
static int calculateStat(int baseValue, int iv, int ev, int level)
{
	return (int)(floor(((((baseValue + iv) * 2) + floor(sqrt(ev) / 4.0f)) * level) / 100.0f) + 5);
}

static int calculateEvGain(int* evTotal, int currentEv, int newEv)
{
	int totalEvMax = 260100;
	int evMax = 65535;

	if (*evTotal + newEv > totalEvMax)
		newEv = totalEvMax - *evTotal;
	if (currentEv + newEv > evMax)
		newEv = evMax - currentEv;

	*evTotal += newEv;
	return newEv;
}

////TODO: Gina wanted bery to be water and grass

static Species getSpeciesFromID(PokemonID id)
{
	switch (id)
	{
		case PokemonID::Baroot:
			return Species{ "Baroot", PokemonID::Baroot,Type::GRASS, Type::NONE, "2' 4''", "3", "A loving plant", {50, 75, 35, 70, 30, 40}, LevelingRate::MediumFast, 25, {0,1,0,0,0,0}, {{1, AttackID::LEAF_SMACK}, {5, AttackID::TORPID_PUNCH}, {7, AttackID::BONERUSH}}, {15, PokemonID::Bery} };
		case PokemonID::Bery:
			return Species{ "Bery", PokemonID::Bery, Type::WATER, Type::NONE, "1' 2''", "2", "A cute bery", {45, 35, 45, 62, 53, 35}, LevelingRate::MediumFast, 25, {0,0,0,1,0,0}, {{1, AttackID::SPLASH}, {5, AttackID::TORPID_PUNCH}, {7, AttackID::GET_PUMPED}}, {25, PokemonID::Fitty} };
		case PokemonID::Fitty:
			return Species{ "Fitty", PokemonID::Fitty, Type::FIRE, Type::NONE, "0' 9''", "11", "A fiery cat who likes to play outside and explore terrain around the world of pokemon.", {45, 65, 40, 60, 40, 70}, LevelingRate::MediumFast, 32, {0,0,0,0,0,1}, {{1, AttackID::EMBER}, {5, AttackID::TORPID_PUNCH}, {7, AttackID::HYPERFANG}}, {16, PokemonID::Baroot} };
		default:
			return Species{};
	}
}
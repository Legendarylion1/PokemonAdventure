#pragma once

#include <String>
#include <vector>
#include <unordered_map>
#include <mutex>

#include "../Status/Status.h"

enum class PowerType
{
	PHYSICAL,
	SPECIAL
};

class Attack
{

public:
	explicit Attack(std::string name, Type type, PowerType powerType, int power, int pp, int critChance, int accuracy, std::string description);
	Attack() {};

	std::string getName() { return m_name; };
	Type getType() { return m_type; };
	PowerType getPowerType() { return m_powerType; };
	int getPower() { return m_power; };
	int getPP() { return m_pp; };
	int getCritChance() { return m_critChance; };
	int getAccuracy() { return m_accuracy; };
	std::string getDescription() { return m_description; };

	int calculateAttackDamage(Pokemon* attacker, Pokemon* defender, Attack* attack, bool applyDamage = false, AttackCommand* command = nullptr);
public:
	void getMissedAttackData(Pokemon* attacker, SelectedUser commander, std::vector<SimulationCommand>* attackData);
	SimulationCommand getNotEffectedData(Pokemon* defender, SelectedUser commander);

	virtual std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	virtual int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 0; };
	virtual StatusID getStatus() { return StatusID::NO_STATUS; };
	virtual PokemonStats getPlayerStat() { return PokemonStats{ 0,0,0,0,0,0,0,0 }; };
	virtual PokemonStats getOpponentStat() { return PokemonStats{ 0,0,0,0,0,0,0,0 }; };
	virtual int getPotentialDamage(Pokemon* attacker, Pokemon* defender) { return calculateAttackDamage(attacker, defender, this); };

private:
	std::string m_name;

	Type m_type = Type::NORMAL;
	PowerType m_powerType = PowerType::PHYSICAL;
	int m_power = 0;
	int m_pp = 0;
	int m_critChance = 0;
	int m_accuracy = 0;

	std::string m_description;
};

static std::unordered_map<Type, std::unordered_map<Type, float>> typeChart
{
	{Type::NONE,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::NORMAL,

		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 0.5f},
			{Type::GHOST, 0.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::FIRE,

		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 0.5f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 2.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 2.0f},
			{Type::ROCK, 0.5f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 0.5f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 2.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::WATER,

		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 2.0f},
			{Type::WATER, 0.5f},
			{Type::GRASS, 0.5f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 2.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 0.5f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::GRASS,

		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 2.0f},
			{Type::GRASS, 0.5f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 2.0f},
			{Type::FLYING, 0.5f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 0.5f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 0.5f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::ELECTRIC,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 2.0f},
			{Type::GRASS, 0.5f},
			{Type::ELECTRIC, 0.5f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 0.0f},
			{Type::FLYING, 2.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 0.5f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::ICE,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 0.5f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 0.5f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 2.0f},
			{Type::FLYING, 2.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 2.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::FIGHTING,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 2.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 2.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 0.5f},
			{Type::PSYCHIC, 0.5f},
			{Type::BUG, 0.5f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 0.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 2.0f},
			{Type::STEEL, 2.0f},
			{Type::FAIRY, 0.5f}
			}}
	},
	{Type::POISON,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 0.5f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 0.5f},
			{Type::GHOST, 0.5f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.0f},
			{Type::FAIRY, 2.0f}
			}}
	},
	{Type::GROUND,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 2.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 0.5f},
			{Type::ELECTRIC, 2.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 2.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 0.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 0.5f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 2.0f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::FLYING,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 0.5f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 2.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 2.0f},
			{Type::ROCK, 0.5f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::PSYCHIC,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 2.0f},
			{Type::POISON, 2.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 0.5f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 0.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
	{Type::BUG,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 2.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 0.5f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 0.5f},
			{Type::PSYCHIC, 2.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 0.5f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 2.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 0.5f}
			}}
	},
	{ Type::ROCK,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 2.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 2.0f},
			{Type::FIGHTING, 0.5f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 0.5f},
			{Type::FLYING, 2.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 2.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
		}}
	},
	{ Type::GHOST,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 0.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 2.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 2.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 0.5f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 1.0f}
		}}
	},
	{Type::DRAGON,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 2.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 0.0f}
			}}
	},
	{ Type::DARK,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 1.0f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 0.5f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 2.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 2.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 0.5f},
			{Type::STEEL, 1.0f},
			{Type::FAIRY, 0.5f}
			}}
	},
	{ Type::STEEL,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 0.5f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 0.5f},
			{Type::ICE, 2.0f},
			{Type::FIGHTING, 1.0f},
			{Type::POISON, 1.0f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 2.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 1.0f},
			{Type::DARK, 1.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 2.0f}
			}}
	},
	{ Type::FAIRY,
		{ std::unordered_map<Type, float> {
			{Type::NONE, 1.0f},
			{Type::NORMAL, 1.0f},
			{Type::FIRE, 0.5f},
			{Type::WATER, 1.0f},
			{Type::GRASS, 1.0f},
			{Type::ELECTRIC, 1.0f},
			{Type::ICE, 1.0f},
			{Type::FIGHTING, 2.0f},
			{Type::POISON, 0.5f},
			{Type::GROUND, 1.0f},
			{Type::FLYING, 1.0f},
			{Type::PSYCHIC, 1.0f},
			{Type::BUG, 1.0f},
			{Type::ROCK, 1.0f},
			{Type::GHOST, 1.0f},
			{Type::DRAGON, 2.0f},
			{Type::DARK, 2.0f},
			{Type::STEEL, 0.5f},
			{Type::FAIRY, 1.0f}
			}}
	},
};

static StatusID calculateMajorStatus(Pokemon* defender, StatusID id, int applicationOdds)
{
	if (outOfHundred(applicationOdds) && canHaveStatus(defender, id))
	{
		defender->applyMajorStatus(id, getStatusFromID(id)->getData().isBlocker);
		return id;
	}
	else
		return StatusID::NO_STATUS;
}

static StatusID calculateMinorStatus(Pokemon* targetPokemon, StatusID id, int applicationOdds)
{
	if (outOfHundred(applicationOdds) && canHaveStatus(targetPokemon, id))
	{
		targetPokemon->applyMinorStatus(id, getStatusFromID(id)->getData().isBlocker, getStatusFromID(id)->getData().isEvasive, getStatusFromID(id)->getData().forcedAttackID);
		return id;
	}
	else
		return StatusID::NO_STATUS;
}


// Adjusts stat parameter to a useable value
// returns 0 there is no stat change
// returns 1 for normal change
// returns 2 for sharp change
static int calculateStatChange(PokemonStats stats, Pokemon* pokemon, bool applyChange = false)
{
	//TODO: Think about moving stats to its own file. It may deserve it considering how important it is
	int value = 0;

	stats.hp = 0;

	for (int i = 0; i < 2; i++)
	{
		if (stats.attack == StatBoost::NONE)
			break;
		if ((stats.attack > 0 && stats.attack + pokemon->getBattleStats()->attack <= StatBoost::MAX) || (stats.attack < 0 && stats.attack + pokemon->getBattleStats()->attack >= StatBoost::MIN))
		{
			if ((stats.attack == StatBoost::INCREASE || stats.attack == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.attack == StatBoost::SHARP_INCREASE || stats.attack == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.attack > 0)
			stats.attack += StatBoost::DECREASE;
		else
			stats.attack += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.defense == StatBoost::NONE)
			break;
		if ((stats.defense > 0 && stats.defense + pokemon->getBattleStats()->defense <= StatBoost::MAX) || (stats.defense < 0 && stats.defense + pokemon->getBattleStats()->defense >= StatBoost::MIN))
		{
			if ((stats.defense == StatBoost::INCREASE || stats.defense == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.defense == StatBoost::SHARP_INCREASE || stats.defense == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.defense > 0)
			stats.defense += StatBoost::DECREASE;
		else
			stats.defense += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.spAttack == StatBoost::NONE)
			break;
		if ((stats.spAttack > 0 && stats.spAttack + pokemon->getBattleStats()->spAttack <= StatBoost::MAX) || (stats.spAttack < 0 && stats.spAttack + pokemon->getBattleStats()->spAttack >= StatBoost::MIN))
		{
			if ((stats.spAttack == StatBoost::INCREASE || stats.spAttack == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.spAttack == StatBoost::SHARP_INCREASE || stats.spAttack == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.spAttack > 0)
			stats.spAttack += StatBoost::DECREASE;
		else
			stats.spAttack += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.spDefense == StatBoost::NONE)
			break;
		if ((stats.spDefense > 0 && stats.spDefense + pokemon->getBattleStats()->spDefense <= StatBoost::MAX) || (stats.spDefense < 0 && stats.spDefense + pokemon->getBattleStats()->spDefense >= StatBoost::MIN))
		{
			if ((stats.spDefense == StatBoost::INCREASE || stats.spDefense == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.spDefense == StatBoost::SHARP_INCREASE || stats.spDefense == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.spDefense > 0)
			stats.spDefense += StatBoost::DECREASE;
		else
			stats.spDefense += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.speed == StatBoost::NONE)
			break;
		if ((stats.speed > 0 && stats.speed + pokemon->getBattleStats()->speed <= StatBoost::MAX) || (stats.speed < 0 && stats.speed + pokemon->getBattleStats()->speed >= StatBoost::MIN))
		{
			if ((stats.speed == StatBoost::INCREASE || stats.speed == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.speed == StatBoost::SHARP_INCREASE || stats.speed == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.speed > 0)
			stats.speed += StatBoost::DECREASE;
		else
			stats.speed += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.evasiveness == StatBoost::NONE)
			break;
		if ((stats.evasiveness > 0 && stats.evasiveness + pokemon->getBattleStats()->evasiveness <= StatBoost::MAX) || (stats.evasiveness < 0 && stats.evasiveness + pokemon->getBattleStats()->evasiveness >= StatBoost::MIN))
		{
			if ((stats.evasiveness == StatBoost::INCREASE || stats.evasiveness == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.evasiveness == StatBoost::SHARP_INCREASE || stats.evasiveness == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.evasiveness > 0)
			stats.evasiveness += StatBoost::DECREASE;
		else
			stats.evasiveness += StatBoost::INCREASE;
	}

	for (int i = 0; i < 2; i++)
	{
		if (stats.accuracy == StatBoost::NONE)
			break;
		if ((stats.accuracy > 0 && stats.accuracy + pokemon->getBattleStats()->accuracy <= StatBoost::MAX) || (stats.accuracy < 0 && stats.accuracy + pokemon->getBattleStats()->accuracy >= StatBoost::MIN))
		{
			if ((stats.accuracy == StatBoost::INCREASE || stats.accuracy == StatBoost::DECREASE) && value < 1)
				value = 1;
			else if (stats.accuracy == StatBoost::SHARP_INCREASE || stats.accuracy == StatBoost::SHARP_DECREASE)
				value = 2;
			break;
		}

		if (stats.accuracy > 0)
			stats.accuracy += StatBoost::DECREASE;
		else
			stats.accuracy += StatBoost::INCREASE;
	}


	if (applyChange)
		pokemon->addBattleStats(stats);

	return value;
}
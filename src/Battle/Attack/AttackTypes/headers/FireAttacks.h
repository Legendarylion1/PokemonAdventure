#pragma once

#include "../../BaseAttack.h"

class Ember : public Attack
{
public:
	explicit Ember(std::string name, Type type, PowerType damageType, int damage, int pp, int critChance, int accuracy, std::string description) : Attack(name, type, damageType, damage, pp, critChance, accuracy, description) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 100; };
	StatusID getStatus() { return StatusID::BURN; };
};

class Dig : public Attack
{
public:
	explicit Dig(std::string name, Type type, PowerType damageType, int damage, int pp, int critChance, int accuracy, std::string description) : Attack(name, type, damageType, damage, pp, critChance, accuracy, description) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	StatusID getStatus() { return StatusID::BURRIED; };
	int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 100; };
};
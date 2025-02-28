#pragma once

#include "../../BaseAttack.h"

class BoneRush : public Attack
{
public:
	explicit BoneRush(std::string name, Type type, PowerType damageType, int damage, int pp, int critChance, int accuracy, std::string description) : Attack(name, type, damageType, damage, pp, critChance, accuracy, description) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	int getPotentialDamage(Pokemon* attacker, Pokemon* defender);
};

class LongJab : public Attack
{
public:
	explicit LongJab(std::string name, Type type, PowerType damageType, int damage, int pp, int critChance, int accuracy, std::string description) : Attack(name, type, damageType, damage, pp, critChance, accuracy, description) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	StatusID getStatus() { return StatusID::FLINCH; };
	int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 70; };
};
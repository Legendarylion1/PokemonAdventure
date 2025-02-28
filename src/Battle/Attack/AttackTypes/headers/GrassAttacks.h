#pragma once

#include "../../BaseAttack.h"

class HyperFang : public Attack
{
public:
	explicit HyperFang(std::string name, Type type, PowerType damageType, int damage, int pp, int critChance, int accuracy, std::string description) : Attack(name, type, damageType, damage, pp, critChance, accuracy, description) {};
};

class TorpidPunch : public Attack
{
public:
	explicit TorpidPunch(std::string name, Type type, PowerType damageType, int damage, int pp, int critChance, int accuracy, std::string description) : Attack(name, type, damageType, damage, pp, critChance, accuracy, description) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	int getStatusOdds(Pokemon* attacker, Pokemon* defender) { return 100 - (int)(100 * (defender->getCurHealth() / (float)defender->getStats().hp)); };	//TODO: Cap Percent at like 75 or something
	StatusID getStatus() { return StatusID::SLEEP; };
};
#pragma once

#include "../../BaseAttack.h"

class GetPumped : public Attack
{
public:
	explicit GetPumped(std::string name, Type type, PowerType damageType, int damage, int pp, int critChance, int accuracy, std::string description) : Attack(name, type, damageType, damage, pp, critChance, accuracy, description) {};
	std::vector<SimulationCommand> getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander);
	PokemonStats getPlayerStat() { return { 0,StatBoost::SHARP_INCREASE,0,0,0,0,0,0 }; };
};
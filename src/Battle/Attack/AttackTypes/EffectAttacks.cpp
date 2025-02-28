#include "headers/EffectAttacks.h"

std::vector<SimulationCommand> GetPumped::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	std::vector<SimulationCommand> allAttackData;

	SimulationCommand attackData{};

	attackData.commander = commander;
	attackData.type = SimulationType::ATTACK;
	attackData.attackData.message = attacker->getName() + " used " + getName();

	allAttackData.push_back(attackData);


	SimulationCommand statData{};

	statData.type = SimulationType::STAT;
	statData.statData.recipient = commander;
	statData.statData.stats = getPlayerStat();

	int value = calculateStatChange(statData.statData.stats, attacker, true);

	if (value == 2)
		statData.statData.message = attacker->getName() + " attack rose sharply!!";
	else if (value == 1)
		statData.statData.message = attacker->getName() + " attack rose";
	else
		statData.statData.message = attacker->getName() + "'s attack wont go any higher";

	allAttackData.push_back(statData);

	return allAttackData;
};

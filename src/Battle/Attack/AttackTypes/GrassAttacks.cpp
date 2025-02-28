#include "headers/GrassAttacks.h"

std::vector<SimulationCommand> TorpidPunch::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	// More odds of them falling asleep the lower their health ratio is

	std::vector<SimulationCommand> allAttackData;
	SimulationCommand attackData{};

	//				~ Generate Attack ~
	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;

	attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);

	if (attackData.attackData.damage == 0)
		getMissedAttackData(attacker, commander, &allAttackData);
	else
		attackData.attackData.statusGiven = calculateMajorStatus(defender, getStatus(), getStatusOdds(attacker, defender));


	allAttackData.push_back(attackData);


	SelectedUser recipient = SelectedUser::AI;
	if (commander == SelectedUser::AI)
		recipient = SelectedUser::PLAYER;

	if (attackData.attackData.statusGiven != StatusID::NO_STATUS)
		allAttackData.push_back(getStatusFromID(attackData.attackData.statusGiven)->getApplicationCommand(defender, recipient));

	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "TorpidPunch");
	return allAttackData;
}

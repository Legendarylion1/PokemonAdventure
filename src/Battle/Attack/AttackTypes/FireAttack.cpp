#include "headers/FireAttacks.h"

std::vector<SimulationCommand> Ember::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
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


	//				~ Push back final data ~
	allAttackData.push_back(attackData);


	SelectedUser recipient = SelectedUser::AI;
	if (commander == SelectedUser::AI)
		recipient = SelectedUser::PLAYER;

	if (attackData.attackData.statusGiven != StatusID::NO_STATUS)
		allAttackData.push_back(getStatusFromID(attackData.attackData.statusGiven)->getApplicationCommand(defender, recipient));

	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "Ember");
	return allAttackData;
}

std::vector<SimulationCommand> Dig::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	std::vector<SimulationCommand> allAttackData;

	SimulationCommand attackData{};

	//				~ Generate Attack ~
	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;


	if (attacker->hasEvasiveStatus() == StatusID::BURRIED)
	{

		attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);

		if (attackData.attackData.damage == 0)
			getMissedAttackData(attacker, commander, &allAttackData);


		//				~ Push back final data ~
		allAttackData.push_back(attackData);

		attacker->removeMinorStatus(StatusID::BURRIED);
		allAttackData.push_back(getStatusFromID(StatusID::BURRIED)->getCureCommand(attacker, commander));
	}
	else
	{
		attackData.attackData.damage = 0;

		attackData.attackData.statusGiven = calculateMinorStatus(attacker, getStatus(), getStatusOdds(attacker, defender));

		//				~ Push back final data ~
		allAttackData.push_back(attackData);

		if (attackData.attackData.statusGiven != StatusID::NO_STATUS)
			allAttackData.push_back(getStatusFromID(attackData.attackData.statusGiven)->getApplicationCommand(attacker, commander));
	}



	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "Dig");
	return allAttackData;
}

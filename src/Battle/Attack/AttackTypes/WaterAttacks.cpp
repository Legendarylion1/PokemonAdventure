#include "headers/WaterAttacks.h"

int BoneRush::getPotentialDamage(Pokemon* attacker, Pokemon* defender)
{
	int count = 0;

	for (int i = 0; i < 5; i++)
	{
		if (i >= 3 && outOfHundred(50))
			break;

		count += calculateAttackDamage(attacker, defender, this);
	}

	return count;
}

std::vector<SimulationCommand> BoneRush::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	//Hits 3-5 times
	std::vector<SimulationCommand> allAttackData;
	int missedHits = 0;

	SimulationCommand attackData{};

	attackData.commander = commander;
	attackData.type = SimulationType::ATTACK;
	attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);

	if (attackData.attackData.damage == 0)
		getMissedAttackData(attacker, commander, &allAttackData);
	else
	{
		missedHits--;
		allAttackData.push_back(attackData);
	}




	for (int i = 1; i < 5; i++)
	{
		if (i >= 3 && outOfHundred(50))
		{

			//TODO: Test further

			//SimulationCommand messageData{};
			//messageData.commander = commander;
			//messageData.type = SimulationType::ATTACK;
			//messageData.attackData.message = "It hit " + std::to_string(i - missedHits) + " times!";
			//allAttackData.push_back(messageData);

			break;
		}

		SimulationCommand nextAttack{};

		nextAttack.commander = commander;
		nextAttack.type = SimulationType::ATTACK;
		nextAttack.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &nextAttack.attackData);

		if (nextAttack.attackData.damage == -1)
			break;

		if (nextAttack.attackData.damage == 0)
		{
			nextAttack.attackData.message = attacker->getName() + " missed!";
			missedHits++;
		}
		else
		{
			nextAttack.attackData.message = "It hit " + std::to_string(i - missedHits) + " times!";
		}

		allAttackData.push_back(nextAttack);
	}

	return allAttackData;
}

std::vector<SimulationCommand> LongJab::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
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
		attackData.attackData.statusGiven = calculateMinorStatus(defender, getStatus(), getStatusOdds(attacker, defender));

	allAttackData.push_back(attackData);



	SelectedUser recipient = SelectedUser::AI;
	if (commander == SelectedUser::AI)
		recipient = SelectedUser::PLAYER;

	if (attackData.attackData.statusGiven != StatusID::NO_STATUS)
		allAttackData.push_back(getStatusFromID(attackData.attackData.statusGiven)->getApplicationCommand(defender, recipient));


	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "LongJab");
	return allAttackData;
}

#include "BaseAttack.h"

Attack::Attack(std::string name, Type type, PowerType powerType, int power, int pp, int critChance, int accuracy, std::string description)
{
	m_name = name;

	m_type = type;
	m_powerType = powerType;

	m_power = power;
	m_pp = pp;
	m_critChance = critChance;
	m_accuracy = accuracy;
	m_description = description;
}

std::vector<SimulationCommand> Attack::getAttackData(Pokemon* attacker, Pokemon* defender, SelectedUser commander)
{
	std::vector<SimulationCommand> allAttackData;
	SimulationCommand attackData{};

	//				~ Generate Attack ~
	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;

	attackData.attackData.damage = calculateAttackDamage(attacker, defender, this, true, &attackData.attackData);

	if (attackData.attackData.damage == 0)
		getMissedAttackData(attacker, commander, &allAttackData);
	else if (attackData.attackData.damage == -2)
		allAttackData.push_back(getNotEffectedData(defender, commander));	//TODO: Generate Miss data so that we print the move that was used and the fact that they arent effected


	//				~ Push back final data ~
	allAttackData.push_back(attackData);

	logger->log(LogLevel::INFO, "Attack Data Created", "getAttackData", "Attack");
	return allAttackData;
}

// Returns 0 if there was an evasion
// Returns -1 if the opponent has fainted
// Returns -2 if it doesnt effect the pokemon
// Else damage of the move
int Attack::calculateAttackDamage(Pokemon* attacker, Pokemon* defender, Attack* attack, bool applyDamage, AttackCommand* command)
{
	if (defender->getCurHealth() == 0)
		return -1;

	if (defender->hasEvasiveStatus() != StatusID::NO_STATUS)
		return 0;


	float userAccuracy = 1.0f;
	float targetEvasion = 1.0f;

	if (attacker->getBattleStats()->accuracy > 0)
		userAccuracy = (2.0f + attacker->getBattleStats()->accuracy) / 2.0f;
	else if (attacker->getBattleStats()->accuracy < 0)
		userAccuracy = 2.0f / (2.0f + abs(attacker->getBattleStats()->accuracy));

	if (attacker->getBattleStats()->evasiveness > 0)
		targetEvasion = (2.0f + attacker->getBattleStats()->evasiveness) / 2.0f;
	else if (attacker->getBattleStats()->evasiveness < 0)
		targetEvasion = 2.0f / (2.0f + abs(attacker->getBattleStats()->evasiveness));


	float accuracy = attack->getAccuracy() * userAccuracy * targetEvasion;

	if (!outOfHundred((int)accuracy))
	{
		//if (command != nullptr)
		//	command->message = attacker->getName() + " missed!";

		return 0;
	}


	//TODO: Possibly make attack command default to nullptr
	int critical = 1;
	if (outOfHundred(attack->getCritChance()))
	{
		if (command != nullptr)
			command->crit = true;
		critical = 2;
	}

	float statDamage = ((2.0f * attacker->getLevel() * critical) / 5.0f) + 2.0f;


	float attackMultiplier = 1.0f;
	float defenseMultiplier = 1.0f;

	if (attack->getPowerType() == PowerType::PHYSICAL)
	{
		if (attacker->getBattleStats()->attack > 0)
			attackMultiplier = (2.0f + attacker->getBattleStats()->attack) / 2.0f;
		else if (attacker->getBattleStats()->attack < 0)
			attackMultiplier = 2.0f / (2.0f + abs(attacker->getBattleStats()->attack));

		if (attacker->getBattleStats()->defense > 0)
			defenseMultiplier = (2.0f + attacker->getBattleStats()->defense) / 2.0f;
		else if (attacker->getBattleStats()->defense < 0)
			defenseMultiplier = 2.0f / (2.0f + abs(attacker->getBattleStats()->defense));
	}
	else
	{
		if (attacker->getBattleStats()->spAttack > 0)
			attackMultiplier = (2.0f + attacker->getBattleStats()->spAttack) / 2.0f;
		else if (attacker->getBattleStats()->spAttack < 0)
			attackMultiplier = 2.0f / (2.0f + abs(attacker->getBattleStats()->spAttack));

		if (attacker->getBattleStats()->spDefense > 0)
			defenseMultiplier = (2.0f + attacker->getBattleStats()->spDefense) / 2.0f;
		else if (attacker->getBattleStats()->spDefense < 0)
			defenseMultiplier = 2.0f / (2.0f + abs(attacker->getBattleStats()->spDefense));
	}






	float powerRatio = (attacker->getStats().attack * attackMultiplier) / (float)(defender->getStats().defense * defenseMultiplier);
	if (attack->getPowerType() == PowerType::SPECIAL)
		powerRatio = (attacker->getStats().spAttack * attackMultiplier) / (float)(defender->getStats().spDefense * defenseMultiplier);


	float baseDamage = ((statDamage * attack->getPower() * powerRatio) / 50.0f) + 2;

	if (attack->getType() == attacker->getSpecies().type1 || attack->getType() == attacker->getSpecies().type2)
		baseDamage *= 1.5;

	baseDamage *= typeChart[attack->getType()][defender->getSpecies().type1];
	baseDamage *= typeChart[attack->getType()][defender->getSpecies().type2];


	if (typeChart[attack->getType()][defender->getSpecies().type1] * typeChart[attack->getType()][defender->getSpecies().type2] == 0)
		return -2;

	float random = (randomNumber(41) + 215.0f) / 255.0f;

	baseDamage *= random;

	if (baseDamage < 1)
		baseDamage = 1;

	int damage = (int)baseDamage;


	if (command != nullptr)
	{
		command->message = attacker->getName() + " used " + attack->getName();

		if (typeChart[attack->getType()][defender->getSpecies().type1] * typeChart[attack->getType()][defender->getSpecies().type2] <= .50f)
		{
			command->effectiveness = EffectiveStatus::NOT_VERY;
		}
		else if (typeChart[attack->getType()][defender->getSpecies().type1] * typeChart[attack->getType()][defender->getSpecies().type2] >= 1.5)
		{
			command->effectiveness = EffectiveStatus::SUPER;
		}
		else
		{
			command->effectiveness = EffectiveStatus::EFFECTIVE;
		}
	}


	if (defender->getCurHealth() - damage < 0)
		damage = defender->getCurHealth();

	if (applyDamage)
		defender->adjustCurHealth(-damage);

	return damage;
}

//TODO: Make this say that it missed too
void Attack::getMissedAttackData(Pokemon* attacker, SelectedUser commander, std::vector<SimulationCommand>* attackData)
{
	SimulationCommand usedData{};

	usedData.type = SimulationType::ATTACK;
	usedData.commander = commander;
	usedData.attackData.damage = 0;
	usedData.attackData.message = attacker->getName() + " used " + this->getName();

	attackData->push_back(usedData);


	SimulationCommand missData{};

	missData.type = SimulationType::ATTACK;
	missData.commander = commander;
	missData.attackData.damage = 0;
	missData.attackData.message = "It missed!";

	attackData->push_back(missData);
}

SimulationCommand Attack::getNotEffectedData(Pokemon* defender, SelectedUser commander)
{
	SimulationCommand attackData{};

	attackData.type = SimulationType::ATTACK;
	attackData.commander = commander;
	attackData.attackData.damage = 0;
	attackData.attackData.message = "It doesnt affect " + defender->getName();
	return SimulationCommand();
}
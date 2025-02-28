#include "Pokemon.h"

//Will be changed for setting trainer pokemon and npt pokemon
Pokemon::Pokemon(Moveset newMoveset, Species pokemonSpecies, int level)
{
	m_moveset = newMoveset;
	m_species = pokemonSpecies;
	m_name = pokemonSpecies.name;
	m_level = level;

	m_ivs.attack = randomNumber(16);
	m_ivs.defense = randomNumber(16);
	m_ivs.speed = randomNumber(16);
	m_ivs.special = randomNumber(16);
	
	
	if (m_ivs.attack % 2 == 1)
		m_ivs.hp += 8;
	if (m_ivs.defense % 2 == 1)
		m_ivs.hp += 4;
	if (m_ivs.speed % 2 == 1)
		m_ivs.hp += 2;
	if (m_ivs.special % 2 == 1)
		m_ivs.hp += 1;

	updateStats();

	logger->log(LogLevel::INFO, "Trainer pokemon " + m_name + " has been created", "Pokemon", "Pokemon");
}

//Wild Pokemon
Pokemon::Pokemon(Species pokemonSpecies, int level)
{
	m_species = pokemonSpecies;
	m_name = pokemonSpecies.name;
	m_level = level;

	m_ivs.attack = randomNumber(16);
	m_ivs.defense = randomNumber(16);
	m_ivs.speed = randomNumber(16);
	m_ivs.special = randomNumber(16);
	
	
	if (m_ivs.attack % 2 == 1)
		m_ivs.hp += 8;
	if (m_ivs.defense % 2 == 1)
		m_ivs.hp += 4;
	if (m_ivs.speed % 2 == 1)
		m_ivs.hp += 2;
	if (m_ivs.special % 2 == 1)
		m_ivs.hp += 1;

	updateStats();
	m_curHealth = m_stats.hp;	//TODO: Maybe increase curhealth whem we level up based on difference

	randomizeMoveset();



	logger->log(LogLevel::INFO, "Wild pokemon " + m_name + " has been created", "Pokemon", "Pokemon");
}

void Pokemon::load(PokemonSave save)
{
	m_name = save.name;
	m_species = getSpeciesFromID(save.species);
	m_level = save.level;
	m_curHealth = save.currentHealth;
	m_curXP = save.currentXP;

	m_ivs.hp = save.hpIv;
	m_ivs.attack = save.attackIv;
	m_ivs.defense = save.defenseIv;
	m_ivs.speed = save.speedIv;
	m_ivs.special = save.specialIv;

	m_evs.hp = save.hpEv;
	m_evs.attack = save.attackEv;
	m_evs.defense = save.defenseEv;
	m_evs.spAttack = save.spattackEv;
	m_evs.spDefense = save.spDefenseEv;
	m_evs.speed = save.speedEv;
	m_evs.evasiveness = save.evasionEv;
	m_evs.accuracy = save.accuracyEv;

	m_moveset.move1 = save.move1;
	m_moveset.move2 = save.move2;
	m_moveset.move3 = save.move3;
	m_moveset.move4 = save.move4;

	m_moveset.move1pp = save.move1pp;
	m_moveset.move2pp = save.move2pp;
	m_moveset.move3pp = save.move3pp;
	m_moveset.move4pp = save.move4pp;

	m_majorStatus.id = (StatusID)save.statusID;
	m_majorStatus.turnCount = save.turnCount;
	m_majorStatus.isBlocker = save.isBlocker;
	m_majorStatus.isEvasive = save.isEvasive;
	m_majorStatus.forcedAttackID = save.forcedAttack;

	updateStats();
}

void Pokemon::fullRestore()	//TODO: Rename a bit more accurately
{
	m_curHealth = m_stats.hp;
	m_majorStatus = StatusTracker{};
	m_minorStatus.clear();
}

void Pokemon::gainEVs(PokemonStats newEVs)
{
	// 65535 maximum per stat. Square root of that number is about 255. Thats how we get the number of EVS already owned.
	// 510 EVs overall is maximum for a fully trained pokemon

	int evTotal = m_evs.hp + m_evs.attack + m_evs.speed + m_evs.defense + m_evs.spAttack + m_evs.spDefense;

	m_evs.hp += calculateEvGain(&evTotal, m_evs.hp, newEVs.hp);
	m_evs.speed += calculateEvGain(&evTotal, m_evs.speed, newEVs.speed);
	m_evs.attack += calculateEvGain(&evTotal, m_evs.attack, newEVs.attack);
	m_evs.defense +=  calculateEvGain(&evTotal, m_evs.defense, newEVs.defense);
	m_evs.spAttack += calculateEvGain(&evTotal, m_evs.spAttack, newEVs.spAttack);
	m_evs.spDefense += calculateEvGain(&evTotal, m_evs.spDefense, newEVs.spDefense);

	return;
}

// NONE for no new move to learn
// Otherwise the ID of the move
int Pokemon::readyToLearnMove()
{
	if (m_species.movesLearned.find(m_level) != m_species.movesLearned.end())
		return m_species.movesLearned[m_level];
	return NONE;
}

PokemonStats Pokemon::levelUp()
{
	m_curXP = 0;
	m_level += 1;
	return updateStats();
}

void Pokemon::evolve()
{
	m_species = getSpeciesFromID(m_species.Evolution.pokemon);
	updateStats();
}

void Pokemon::learnMove(int index, int move, int pp)
{
	switch (index)
	{
	case 0:
		m_moveset.move1 = move;
		m_moveset.move1pp = pp;
		break;
	case 1:
		m_moveset.move2 = move;
		m_moveset.move2pp = pp;
		break;
	case 2:
		m_moveset.move3 = move;
		m_moveset.move3pp = pp;
		break;
	case 3:
		m_moveset.move4 = move;
		m_moveset.move4pp = pp;
		break;
	default:
		//TODO: Check if this is a critical error
		logger->log(LogLevel::ERROR, "Move Index Doesnt Exist", "learnMove", "Pokemon");
		break;
	}
}

StatusID Pokemon::getAttackBlocker()
{
	if (m_curHealth <= 0)
		return StatusID::FAINTED;

	for (StatusTracker data : m_minorStatus)
	{
		if (data.isBlocker)
			return data.id;
	}

	switch (m_majorStatus.id)
	{
	case StatusID::SLEEP:
	case StatusID::FREEZE:
		return m_majorStatus.id;
	default:
		return StatusID::NO_STATUS;
	}
}

int Pokemon::hasForcedAttack()
{

	for (StatusTracker data : m_minorStatus)
	{
		if (data.forcedAttackID != NONE)
			return data.forcedAttackID;
	}

	return NONE;
}

StatusID Pokemon::hasEvasiveStatus()
{
	for (size_t i = 0; i < m_minorStatus.size(); i++)
	{
		if (m_minorStatus.at(i).isEvasive)
			return m_minorStatus.at(i).id;
	}

	return StatusID::NO_STATUS;
}

void Pokemon::applyMajorStatus(StatusID id, bool isBlocker)
{
	m_majorStatus.id = id;
	m_majorStatus.turnCount = 0;
	m_majorStatus.isBlocker = isBlocker;
}

void Pokemon::applyMinorStatus(StatusID id, bool isBlocker, bool isEvasive, int forcedAttackID)
{
	m_minorStatus.push_back(StatusTracker{ id,0, isBlocker, isEvasive, forcedAttackID });
}

void Pokemon::removeMajorStatus()
{
	m_majorStatus.id = StatusID::NO_STATUS;
	m_majorStatus.turnCount = 0;
}

void Pokemon::removeMinorStatus(StatusID id)
{
	for (size_t i = 0; i < m_minorStatus.size(); i++)
	{
		if (m_minorStatus.at(i).id == id)
		{
			m_minorStatus.erase(m_minorStatus.begin() + i);
			return;
		}
	}
}

PokemonStats Pokemon::updateStats()
{
	PokemonStats oldStats = m_stats;

	m_xpNeeded = calculateXPNeeded(m_level, m_species.levelRate);

	m_stats.hp = calculateHPStat(m_species.baseStats.hp, m_ivs.hp, m_evs.hp, m_level);
	m_stats.speed = calculateStat(m_species.baseStats.speed, m_ivs.speed, m_evs.speed, m_level);
	m_stats.attack = calculateStat(m_species.baseStats.attack, m_ivs.attack, m_evs.attack, m_level);
	m_stats.defense = calculateStat(m_species.baseStats.defense, m_ivs.defense, m_evs.defense, m_level);
	m_stats.spAttack = calculateStat(m_species.baseStats.spAttack, m_ivs.special, m_evs.spAttack, m_level);
	m_stats.spDefense = calculateStat(m_species.baseStats.spDefense, m_ivs.special, m_evs.spDefense, m_level);

	return m_stats - oldStats;
}

void Pokemon::randomizeMoveset()
{
	std::vector<AttackID> possibleAttacks;

	for (auto i = m_species.movesLearned.begin(); i != m_species.movesLearned.end(); i++)
	{
		if (m_level >= i->first)
			possibleAttacks.push_back(i->second);
	}

	int index = 0;
	int attackIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		if (possibleAttacks.size() == 0)
			break;

		attackIndex = randomNumber((int)possibleAttacks.size());
		int selectedAttack = possibleAttacks.at(attackIndex);

		if (index == 0)
			m_moveset.move1 = selectedAttack;
		else if (index == 1)
			m_moveset.move2 = selectedAttack;
		else if (index == 2)
			m_moveset.move3 = selectedAttack;
		else
			m_moveset.move4 = selectedAttack;

		possibleAttacks.erase(possibleAttacks.begin() + attackIndex);
		index++;
	}
}

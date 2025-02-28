#pragma once

#include <mutex>
#include "../SimulationCommands.h"

enum class StatusType
{
	MAJOR,
	MINOR
};

enum class IncrementTime
{
	BEFORE,
	DURING,
	AFTER
};

struct StatusData
{
	StatusID id;
	StatusType type;
	IncrementTime time;

	float percentMaxHealth;

	int turnToCure;
	int cureOdds;
	bool isBlocker;
	bool isEvasive;
	int forcedAttackID = NONE;
};

class Status
{
public:
	Status(StatusData data, std::string applicationMessage, std::string afflictionMessage, std::string cureMessage)
	{
		m_data = data;
		m_applicationMessage = applicationMessage;
		m_afflictionMessage = afflictionMessage;
		m_cureMessage = cureMessage;
	};

	virtual std::vector<SimulationCommand> getStatusData(Pokemon* affectedPokemon, SelectedUser pokemonOwner);

	StatusData getData() { return m_data; };
	SimulationCommand getApplicationCommand(Pokemon* targetPokemon, SelectedUser recipient) {

		SimulationCommand applicationCommand;

		applicationCommand.commander = recipient;
		applicationCommand.type = SimulationType::STATUS;
		applicationCommand.statusData.recipient = recipient;
		applicationCommand.statusData.statusGiven = getData().id;

		if (m_applicationMessage.size() != 0)
			applicationCommand.statusData.message = targetPokemon->getName() + m_applicationMessage;

		return applicationCommand;
	};
	SimulationCommand getCureCommand(Pokemon* targetPokemon, SelectedUser owner)
	{
		SimulationCommand cureData;
		cureData.commander = owner;
		cureData.type = SimulationType::STATUS;

		cureData.statusData.curedStatus = getData().id;

		if (getCureMessage().size() != 0)
			cureData.statusData.message = targetPokemon->getName() + getCureMessage();

		return cureData;
	}
	std::string getAfflictionMessage() { return m_afflictionMessage; };
	std::string getCureMessage() { return m_cureMessage; };
private:
	StatusData m_data;

	std::string m_applicationMessage;
	std::string m_afflictionMessage;
	std::string m_cureMessage;
};
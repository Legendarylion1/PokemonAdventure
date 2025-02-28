#pragma once

#include "MajorStatus.h"
#include "MinorStatus.h"

class StatusSingleton {
public:
	// Deleting the copy constructor to prevent copies
	StatusSingleton(const StatusSingleton& obj) = delete;

	// Static method to get the Singleton instance
	static StatusSingleton* getInstance() {
		if (instancePtr == nullptr) {
			std::lock_guard<std::mutex> lock(mtx);
			if (instancePtr == nullptr) {
				instancePtr = new StatusSingleton();
			}
		}
		return instancePtr;
	}

	Status* getStatus(StatusID id);

private:

	// Static pointer to the Singleton instance
	static StatusSingleton* instancePtr;

	// Mutex to ensure thread safety
	static std::mutex mtx;

	// Private Constructor
	StatusSingleton() {}

	static Status* m_status;
	static int m_currentID;
};

static Status* getStatusFromID(StatusID id)
{
	return StatusSingleton::getInstance()->getStatus(id);
}

//For incrementing and curing status
static std::vector<SimulationCommand> incrementStatusTimer(Pokemon* pokemon, StatusTracker* tracker, SelectedUser user)
{
	if (tracker->id == StatusID::NO_STATUS || pokemon->getCurHealth() == 0)
		return std::vector<SimulationCommand>();

	tracker->turnCount += 1;

	Status* status = getStatusFromID(tracker->id);

	if (status->getData().turnToCure != tracker->turnCount && !outOfHundred(status->getData().cureOdds))
		return std::vector<SimulationCommand>();

	std::vector<SimulationCommand> statusCureData;
	statusCureData.push_back(status->getCureCommand(pokemon, user));

	if (status->getData().type == StatusType::MAJOR)
		pokemon->removeMajorStatus();
	else
		pokemon->removeMinorStatus(tracker->id);

	return statusCureData;
}

static bool canHaveStatus(Pokemon* pokemon, StatusID id)
{
	if (id == StatusID::NO_STATUS)
		return false;

	if (getStatusFromID(id)->getData().type == StatusType::MAJOR)
	{
		if (pokemon->getMajorStatus()->id == StatusID::NO_STATUS)
			return true;
		return false;
	}
	else
	{
		for (StatusTracker data : *pokemon->getMinorStatus())
		{
			if (data.id == id)
				return false;
		}
		return true;
	}
}
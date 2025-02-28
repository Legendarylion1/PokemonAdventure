#include "Status.h"

StatusSingleton* StatusSingleton::instancePtr = nullptr;
std::mutex StatusSingleton::mtx;

Status* StatusSingleton::m_status = nullptr;
int StatusSingleton::m_currentID = -2;

//TODO: Break cure conditions onto seperate lines
Status* StatusSingleton::getStatus(StatusID id)
{
	if ((int)id == m_currentID)
		return m_status;

	if (m_status != nullptr)
		delete m_status;

	switch (id)
	{
	case StatusID::BURN:
		m_status = new Status({ StatusID::BURN, StatusType::MAJOR, IncrementTime::AFTER, 6.25f, 3, NONE, false, false, NONE }, " has been burned", " is suffering from its burn", " has been cured of its burn");
		break;
	case StatusID::SLEEP:
		m_status = new Status({ StatusID::SLEEP, StatusType::MAJOR, IncrementTime::BEFORE, 0.0f, 5, 40, true, false, NONE }, " has fallen asleep", " is fast asleep", " has woken up");
		break;
	case StatusID::PARALYSIS:
		m_status = new Status({ StatusID::PARALYSIS, StatusType::MAJOR, IncrementTime::BEFORE, 0.0f, 5, 40, true, false, NONE }, " has been paralyzed", " is unable to move", " is cured of its paralysis");
		break;
	case StatusID::FLINCH:
		m_status = new Status({ StatusID::FLINCH, StatusType::MINOR, IncrementTime::AFTER, 0.0f, 1, NONE, true, false, NONE }, "", " flinched", "");
		break;
	case StatusID::BURRIED:
		m_status = new Status({ StatusID::BURRIED, StatusType::MINOR, IncrementTime::BEFORE, 0.0f, NONE, NONE, false, true, AttackID::DIG }, " has dug underground", " is underground", " is no longer underground");
		break;
	default:
		m_status = new Status({},"","","");
	}

	m_currentID = (int)id;
	return m_status;
}
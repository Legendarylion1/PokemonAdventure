#pragma once

#include "AttackTypes/headers/EffectAttacks.h"
#include "AttackTypes/headers/FireAttacks.h"
#include "AttackTypes/headers/WaterAttacks.h"
#include "AttackTypes/headers/GrassAttacks.h"

//TODO: Consider adding priority moves. We currently have none
//TODO: Fix Move Typing and balance moves

//		~ Move Ideas ~
// 
// Parasytic seed - Steals opponents stats

class AttackSingleton {
public:
	// Deleting the copy constructor to prevent copies
	AttackSingleton(const AttackSingleton& obj) = delete;

	// Static method to get the Singleton instance
	static AttackSingleton* getInstance() {
		if (instancePtr == nullptr) {
			std::lock_guard<std::mutex> lock(mtx);
			if (instancePtr == nullptr) {
				instancePtr = new AttackSingleton();
			}
		}
		return instancePtr;
	}

	Attack* getAttack(int id);

private:

	// Static pointer to the Singleton instance
	static AttackSingleton* instancePtr;

	// Mutex to ensure thread safety
	static std::mutex mtx;

	// Private Constructor
	AttackSingleton() {}

	static Attack* m_attack;
	static int m_currentID;
};


static Attack* getAttackFromID(int id)
{
	return AttackSingleton::getInstance()->getAttack(id);
}
#pragma once

#include "ItemTypes/PokeballItem.h"
#include "ItemTypes/HealItem.h"
#include "ItemTypes/StatBoostItem.h"

class ItemSingleton {
public:
	// Deleting the copy constructor to prevent copies
	ItemSingleton(const ItemSingleton& obj) = delete;

	// Static method to get the Singleton instance
	static ItemSingleton* getInstance() {
		if (instancePtr == nullptr) {
			std::lock_guard<std::mutex> lock(mtx);
			if (instancePtr == nullptr) {
				instancePtr = new ItemSingleton();
			}
		}
		return instancePtr;
	}

	Item* getItem(ItemID id);

private:

	// Static pointer to the Singleton instance
	static ItemSingleton* instancePtr;

	// Mutex to ensure thread safety
	static std::mutex mtx;

	// Private Constructor
	ItemSingleton() {}

	static Item* m_item;
	static int m_currentID;
};

static Item* getItemFromID(ItemID id)
{
	return ItemSingleton::getInstance()->getItem(id);
}

static bool isPokeball(Item item)
{
	return item.getType() == ItemType::POKEBALL;
}
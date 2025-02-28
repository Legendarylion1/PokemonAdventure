#pragma once
#include "../../Battle/Item/Item.h"
#include <map>
#include <vector>
#include <iostream>

class ItemStorage
{
public:
	ItemStorage();

	void addItem(ItemID item);
	void removeItem(ItemID item);


	std::map<ItemID, int>* getBattleItems();
	std::map<ItemID, int>* getAllItems();
private:

	std::map<ItemID, int> m_allItems;
	std::map<ItemID, int> m_battleItems;
};
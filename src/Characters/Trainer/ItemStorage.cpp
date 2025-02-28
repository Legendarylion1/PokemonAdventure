#include "ItemStorage.h"

ItemStorage::ItemStorage()
{
	for (int i = (int)ItemID::NO_ITEM + 1; i < (int)ItemID::END_ITEM; i++)
	{

		m_allItems[ItemID(i)] = 0;

		if (getItemFromID(ItemID(i))->getType() != ItemType::WORLD)
			m_battleItems[ItemID(i)] = 0;
	}
}

void ItemStorage::addItem(ItemID item)
{
	if (m_allItems.find(item) != m_allItems.end()) {
		m_allItems[item] += 1;
	}
	else
	{
		//TODO: Remove the else when the code is complete
		//TODO: Raise an Error because an item hasnt been added to all items
		logger->log(LogLevel::CRITICAL, " Item is not in all ItemsID:" + std::to_string((int)item), "addItem", "ItemStorage");
		logger->reportCriticalError(ErrorCodes::UNIDENTIFIED_ITEM);
		exit(1);
	}


	if (m_battleItems.find(item) != m_battleItems.end()) {
		m_battleItems[item] += 1;
	}
	else
	{
		//TODO: Remove the else when the code is complete
		//TODO: Raise an Error because an item hasnt been added to all items
		logger->log(LogLevel::DEBUG, " Item is not in all Items ID:" + std::to_string((int)item), "addItem", "ItemStorage");
	}
}

void ItemStorage::removeItem(ItemID item)
{
	if (m_allItems.find(item) != m_allItems.end() && m_allItems[item] > 0) {
		m_allItems[item] -= 1;
	}
	else
	{
		logger->log(LogLevel::CRITICAL, " Cannot Remove Item with ID:" + std::to_string((int)item), "addItem", "ItemStorage");
		logger->reportCriticalError(ErrorCodes::UNIDENTIFIED_ITEM);
	}

	if (m_battleItems.find(item) != m_battleItems.end() && m_battleItems[item] > 0) {
		m_battleItems[item] -= 1;
	}
	else
	{
		logger->log(LogLevel::DEBUG, " Cannot Remove Item with ID:" + std::to_string((int)item), "addItem", "ItemStorage");
	}
}

std::map<ItemID, int>* ItemStorage::getBattleItems()
{
	return &m_battleItems;
}

std::map<ItemID, int>* ItemStorage::getAllItems()
{
	return &m_allItems;
}

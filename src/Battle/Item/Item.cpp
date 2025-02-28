#include "Item.h"

ItemSingleton* ItemSingleton::instancePtr = nullptr;
std::mutex ItemSingleton::mtx;

Item* ItemSingleton::m_item = nullptr;
int ItemSingleton::m_currentID = -2;

Item* ItemSingleton::getItem(ItemID id)
{
	if (id == m_currentID)
		return m_item;

	if (m_item != nullptr)
		delete m_item;

	switch (id)
	{
	case ItemID::SMALL_POTION:
		m_item = new Heal("Small Potion", ItemID::SMALL_POTION, 100, 10, false);
		break;
	case ItemID::MEDIUM_POTION:
		m_item = new Heal("Medium Potion", ItemID::MEDIUM_POTION, 200, 20, false);
		break;
	case ItemID::LARGE_POTION:
		m_item = new Heal("Large Potion", ItemID::LARGE_POTION, 300, 50, false);
		break;
	case ItemID::POKEBALL:
		m_item = new Pokeball("Pokeball", ItemID::POKEBALL, 100, 1.0f);
		break;
	case ItemID::GREATBALL:
		m_item = new Pokeball("GreatBall", ItemID::GREATBALL, 200, 1.5f);
		break;
	case ItemID::ULTRABALL:
		m_item = new Pokeball("UltraBall", ItemID::ULTRABALL, 300, 2.0f);
		break;
	case ItemID::MASTERBALL:
		m_item = new Pokeball("MasterBall", ItemID::MASTERBALL, 0, 2.0f);
		break;
	case ItemID::ROID_JUICE:
		m_item = new StatBooster("RoidJuice", ItemID::ROID_JUICE, 50, { 0, StatBoost::SHARP_INCREASE, 0, 0, 0, 0, 0, 0 });
		break;
	default:
		m_item = new Item();
		break;
	}

	return m_item;
}

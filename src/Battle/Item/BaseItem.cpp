#include "BaseItem.h"

Item::Item() :
	m_id(ItemID::SMALL_POTION), m_cost(0), m_type(ItemType::WORLD)
{
}

Item::Item(std::string itemName, ItemID itemID, int cost, ItemType type)
{
	m_name = itemName;
	m_id = itemID;
	m_cost = cost;
	m_type = type;
}


std::vector<SimulationCommand> Item::getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex)
{
	return std::vector<SimulationCommand>();
}
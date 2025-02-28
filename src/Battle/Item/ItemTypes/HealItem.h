#pragma once

#include "../BaseItem.h"

class Heal : public Item
{
public:
	explicit Heal() : Item() {};
	explicit Heal(std::string itemName, ItemID itemID, int cost, int flatHeal, bool revive, StatusID status = StatusID::NO_STATUS)
		: Item(itemName, itemID, cost, ItemType::MEDICINE), m_healingValue(flatHeal), m_statusID(status), m_revive(revive) {};

	std::vector<SimulationCommand> getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex);
	bool canBeUsedOnPokemon(Pokemon* pokemon);
	StatusID getStatus() { return m_statusID; };

private:
	int m_healingValue = 0;
	bool m_revive = false;
	StatusID m_statusID;
};
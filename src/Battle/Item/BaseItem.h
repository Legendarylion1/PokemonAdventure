#pragma once

#include <string>
#include <unordered_map>

#include "../../Characters/Pokemon/Pokemon.h"
#include "../Status/Status.h"

#include "../SimulationCommands.h"

enum class ItemType
{
	POKEBALL,
	MEDICINE,
	WORLD
};

class Item
{
public:
	Item();
	Item(std::string itemName, ItemID itemID, int cost, ItemType type);

	virtual std::vector<SimulationCommand> getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex);
	virtual bool canBeUsedOnPokemon(Pokemon* pokemon) { return false; };
	virtual int getHealingValue() { return 0; };
	virtual StatusID getStatus() { return StatusID::NO_STATUS; };

	std::string getName() { return m_name; };
	ItemID getID() { return m_id; };
	int getCost() { return m_cost; };
	ItemType getType() { return m_type; }

private:
	std::string m_name;
	ItemID m_id;
	int m_cost;
	ItemType m_type;
};
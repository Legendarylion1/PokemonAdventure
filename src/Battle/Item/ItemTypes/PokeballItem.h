#pragma once

#include "../BaseItem.h"

class Pokeball : public Item
{
public:
	explicit Pokeball() : Item(), m_captureRate(255) {};
	explicit Pokeball(std::string itemName, ItemID itemID, int cost, float captureRate) : Item(itemName, itemID, cost, ItemType::POKEBALL) { m_captureRate = captureRate; };

	std::vector<SimulationCommand> getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex);


private:
	float m_captureRate;
};
#pragma once

#include "../BaseItem.h"

class StatBooster : public Item
{
public:
	explicit StatBooster() : Item() {};
	explicit StatBooster(std::string itemName, ItemID itemID, int cost, PokemonStats statBoost) : Item(itemName, itemID, cost, ItemType::MEDICINE) { m_statBoost = statBoost; };

	std::vector<SimulationCommand> getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex);
	bool canBeUsedOnPokemon(Pokemon* pokemon);

private:
	PokemonStats m_statBoost = PokemonStats();
};
#include "StatBoostItem.h"

std::vector<SimulationCommand> StatBooster::getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex)
{
	std::vector<SimulationCommand> allItemData;

	SimulationCommand itemData{};

	itemData.commander = commander;
	itemData.selection2 = pokemonIndex;
	itemData.type = SimulationType::ITEM;
	itemData.itemData.id = getID();


	itemData.itemData.statsToBoost = m_statBoost;

	return allItemData;
}

bool StatBooster::canBeUsedOnPokemon(Pokemon* pokemon)
{
	if (pokemon->getCurHealth() > 0)
		return true;
	return false;
}
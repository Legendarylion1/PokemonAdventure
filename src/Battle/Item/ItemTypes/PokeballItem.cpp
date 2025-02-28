#include "PokeballItem.h"

std::vector<SimulationCommand> Pokeball::getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex)
{
	std::vector<SimulationCommand> allItemData;

	SimulationCommand itemData{};

	itemData.commander = commander;
	itemData.selection2 = pokemonIndex;
	itemData.type = SimulationType::ITEM;
	itemData.itemData.id = getID();
	itemData.itemData.pokeballData.isPokeball = true;


	int maxValue = (3 * pokemon->getStats().hp);
	int curValue = (2 * pokemon->getCurHealth());

	if (maxValue > 255)
	{
		maxValue = (int)floor(maxValue / 4.0f);
		curValue = (int)floor(curValue / 4.0f);

		if (maxValue == 0)
		{
			maxValue = 1;
			curValue = 1;
		}
	}

	float numerator = (maxValue - curValue) * m_captureRate;
	float denominator = maxValue * 1.0f;

	int catchChance = (int)((numerator / denominator) * 255);
	if (catchChance < 1)
		catchChance = 1;

	//TODO: Check for pokemon status
	// Sleep or Freeze is + 10
	// Paralyze, poison, burn + 5

	int randomValue = randomNumber(256);

	if (randomValue <= catchChance)
	{
		itemData.itemData.pokeballData.shakes = 3;
	}
	else
	{
		int shakeProbability = (int)((randomValue - catchChance) / 2.0f);
		if (shakeProbability < 1)
			shakeProbability = 1;
		for (int i = 0; i < 3; i++)
		{

			if (randomNumber(256) < shakeProbability)
				break;

			itemData.itemData.pokeballData.shakes += 1;
		}
	}

	if (itemData.itemData.pokeballData.shakes == 3)
		itemData.itemData.pokeballData.caught = true;

	allItemData.push_back(itemData);
	logger->log(LogLevel::INFO, "Item Data Created", "getItemData", "Pokeball");

	return allItemData;
}
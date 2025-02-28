#include "HealItem.h"

std::vector<SimulationCommand> Heal::getItemData(Pokemon* pokemon, SelectedUser commander, int pokemonIndex)
{
	std::vector<SimulationCommand> allItemData;

	SimulationCommand itemData{};
	itemData.commander = commander;
	itemData.selection2 = pokemonIndex;
	itemData.type = SimulationType::ITEM;
	itemData.itemData.id = getID();


	if (m_revive)
		itemData.itemData.healAmount = int(pokemon->getStats().hp / 2.0f);
	int previous = itemData.itemData.healAmount;
	pokemon->adjustCurHealth(itemData.itemData.healAmount);


	if (pokemon->getCurHealth() + m_healingValue > pokemon->getStats().hp)
		itemData.itemData.healAmount += pokemon->getStats().hp - pokemon->getCurHealth();
	else
		itemData.itemData.healAmount += m_healingValue;

	pokemon->adjustCurHealth(itemData.itemData.healAmount - previous);



	//TODO: Test This
	itemData.itemData.message = pokemon->getName() + "'s health has been restored";
	allItemData.push_back(itemData);	//TODO: Generate a message for healing too


	if (pokemon->getMajorStatus()->id != StatusID::NO_STATUS && m_statusID != StatusID::NO_STATUS)
	{
		if (pokemon->getMajorStatus()->id == m_statusID || m_statusID == StatusID::ALL)
		{
			allItemData.push_back(getStatusFromID(pokemon->getMajorStatus()->id)->getCureCommand(pokemon, commander));
			pokemon->removeMajorStatus();
		}
	}



	logger->log(LogLevel::INFO, "Item Data Created", "getItemData", "Heal");
	return allItemData;
}

bool Heal::canBeUsedOnPokemon(Pokemon* pokemon)
{
	if (pokemon->getCurHealth() == 0 && m_revive == false)
		return false;

	if (pokemon->getCurHealth() == pokemon->getStats().hp)
		return false;

	if (pokemon->getMajorStatus()->id != StatusID::NO_STATUS && (m_statusID != StatusID::ALL || pokemon->getMajorStatus()->id != m_statusID) && m_healingValue == 0)
		return false;

	return true;
}
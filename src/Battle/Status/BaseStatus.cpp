#include "BaseStatus.h"

std::vector<SimulationCommand> Status::getStatusData(Pokemon* affectedPokemon, SelectedUser pokemonOwner)
{
    std::vector<SimulationCommand> allStatusData;
    SimulationCommand statusData{};

    statusData.type = SimulationType::STATUS;
    statusData.commander = pokemonOwner;


    //                          ~ Damage Calculation ~
    statusData.statusData.damage = (int)floor((m_data.percentMaxHealth / 100.0f) * affectedPokemon->getStats().hp);
    if (affectedPokemon->getCurHealth() - statusData.statusData.damage < 0)
        statusData.statusData.damage = affectedPokemon->getCurHealth();
    affectedPokemon->adjustCurHealth(-statusData.statusData.damage);

    if (m_afflictionMessage.size() != 0)
        statusData.statusData.message = affectedPokemon->getName() + m_afflictionMessage;



    allStatusData.push_back(statusData);
    return allStatusData;
}
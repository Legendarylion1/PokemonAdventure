#include "BattleDataGenerator.h"

BattleDataGenerator::BattleDataGenerator()
{
}

void BattleDataGenerator::setup(Trainer* trainer, SimulationCommand* playerCommand, SimulationCommand* aiCommand, int* playerPokemonIndex, int* opponentPokemonIndex, int* endCondition, Renderer* renderer)
{
	m_trainer = trainer;
	m_playerCommand = playerCommand;
	m_aiCommand = aiCommand;
    m_playerPokemonIndex = playerPokemonIndex;
    m_opponentPokemonIndex = opponentPokemonIndex;
    m_endCondition = endCondition;
    m_renderer = renderer;
}

void BattleDataGenerator::setOpponent(NPT* npt)
{
    m_npt = npt;
    m_wildPokemon = nullptr;
}

void BattleDataGenerator::setOpponent(Pokemon* pokemon)
{
    m_npt = nullptr;
    m_wildPokemon = pokemon;
}

std::vector<SimulationCommand> BattleDataGenerator::generateData()
{
    setupTestPokemon();
	m_commands.clear();

	switch (m_playerCommand->type)
	{

    case SimulationType::ATTACK_SELECTED:
        handleAttack();
        break;
    case SimulationType::POKEMON_SELECTED:
        handlePokemonSwap();
        break;
    case SimulationType::ITEM_SELECTED:
        handleItemSelection();
        break;
    case SimulationType::FLEE_SELECTED:
        handleFleeSelection();
        if (*m_endCondition == (int)SimulationType::FLEE)
            return m_commands;
        break;
    default:
        break;

	}

    if (m_commands.size() != 0)
    {
        generateStatusData(SelectedUser::AI, IncrementTime::AFTER);
        generateStatusData(SelectedUser::PLAYER, IncrementTime::AFTER);
    }

	return m_commands;
}

void BattleDataGenerator::setupTestPokemon()
{
    m_localPlayerPokemonIndex = *m_playerPokemonIndex;

    setupTrainerPokemon();

    if (m_wildPokemon != nullptr)
        m_opponentPokemon = *m_wildPokemon;
    else
        m_opponentPokemon = m_npt->getRoster()[*m_opponentPokemonIndex];

}

void BattleDataGenerator::setupTrainerPokemon()
{
    m_playerPokemon = m_trainer->getRoster()[m_localPlayerPokemonIndex];
}

void BattleDataGenerator::handleAttack()
{
    if (stopGenerating())
        return;

    if (m_aiCommand->type == ITEM_SELECTED)
    {
        generateItem(SelectedUser::AI);
        generateAttack(SelectedUser::PLAYER);
        return;
    }

    if (m_playerPokemon.getStats().speed > m_opponentPokemon.getStats().speed)
    {
        generateAttack(SelectedUser::PLAYER);
        generateAttack(SelectedUser::AI);
    }
    else if (m_playerPokemon.getStats().speed < m_opponentPokemon.getStats().speed)
    {
        generateAttack(SelectedUser::AI);
        generateAttack(SelectedUser::PLAYER);
    }
    else
    {
        if (outOfHundred(50))
        {
            generateAttack(SelectedUser::PLAYER);
            generateAttack(SelectedUser::AI);
        }
        else
        {
            generateAttack(SelectedUser::AI);
            generateAttack(SelectedUser::PLAYER);
        }
    }
}

void BattleDataGenerator::handlePokemonSwap()
{
    if (stopGenerating())
        return;

    SimulationCommand swapCommand{};
    swapCommand.type = SimulationType::POKEMON;
    swapCommand.commander = SelectedUser::PLAYER;
    swapCommand.selection1 = m_playerCommand->selection2;
    m_commands.push_back(swapCommand);

    m_localPlayerPokemonIndex = m_playerCommand->selection2;
    setupTrainerPokemon();

    if (m_aiCommand->type == ATTACK_SELECTED)
        generateAttack(SelectedUser::AI);
    else
        generateItem(SelectedUser::AI);
}

void BattleDataGenerator::handleItemSelection()
{
    if (stopGenerating())
        return;

    generateItem(SelectedUser::PLAYER);

    if (pokemonCaught())
    {
        *m_endCondition = (int)SimulationType::POKEMON;
        return;
    }

    if (m_aiCommand->type == SimulationType::ATTACK_SELECTED)
        generateAttack(SelectedUser::AI);
    else
        generateItem(SelectedUser::AI);
}

void BattleDataGenerator::handleFleeSelection()
{
    if (stopGenerating())
        return;

    if (m_playerPokemon.getStats().speed > m_opponentPokemon.getStats().speed && m_npt == nullptr)
    {
        SimulationCommand flee{};
        flee.type = SimulationType::FLEE;
        flee.selection1 = (int)true;
        m_commands.push_back(flee);

        *m_endCondition = (int)SimulationType::FLEE;
        return;
    }

    // TODO: Randomize flee here. Make it atleast possible to get away
    SimulationCommand flee{};
    flee.type = SimulationType::FLEE;
    flee.selection1 = (int)false;
    m_commands.push_back(flee);

    if (m_npt != nullptr)
        return;

    if (m_aiCommand->type == ATTACK_SELECTED)
        generateAttack(SelectedUser::AI);
    else
        generateItem(SelectedUser::AI);
}

bool BattleDataGenerator::stopGenerating()
{
    return m_renderer->shouldClose();
}

void BattleDataGenerator::generateAttack(SelectedUser user)
{
    generateStatusData(user, IncrementTime::BEFORE, false);

    SimulationCommand command;

    if (user == SelectedUser::PLAYER)
        command = *m_playerCommand;
    else
        command = *m_aiCommand;

    //generateStatusData(attacker, IncrementTime::BEFORE);

    if (user == SelectedUser::PLAYER)
    {
        StatusID attackerStatus = m_playerPokemon.getAttackBlocker();

        if (attackerStatus == StatusID::FAINTED)
            return;
        else if (attackerStatus == StatusID::NO_STATUS)
        {
            appendCommands(getAttackFromID(getMoveFromCommand(command, user))->getAttackData(&m_playerPokemon, &m_opponentPokemon, user));
        }
        else
        {
            appendCommands(getStatusFromID(attackerStatus)->getStatusData(&m_playerPokemon, SelectedUser::PLAYER));
        }
    }
    else
    {
        //TODO: Evaluate this statement post refactor
        //We use display pokemon here because we do not want the AI to cheat and know what new pokemon is coming out
        StatusID attackerStatus = m_opponentPokemon.getAttackBlocker();

        if (attackerStatus == StatusID::FAINTED)
            return;
        else if (attackerStatus == StatusID::NO_STATUS)
        {
            appendCommands(getAttackFromID(getMoveFromCommand(command, user))->getAttackData(&m_opponentPokemon, &m_playerPokemon, user));
        }
        else
        {
            appendCommands(getStatusFromID(attackerStatus)->getStatusData(&m_opponentPokemon, SelectedUser::AI));
        }
    }
}

void BattleDataGenerator::generateItem(SelectedUser user)
{
    Item* item = nullptr;

    if (user == SelectedUser::PLAYER)
    {
        item = getItemFromID(m_playerCommand->itemData.id);

        if (m_playerCommand->itemData.pokeballData.isPokeball)
            appendCommands(item->getItemData(&m_opponentPokemon, user, *m_opponentPokemonIndex));
        else
            appendCommands(item->getItemData(&m_playerPokemon, user, m_playerCommand->selection2));

        m_trainer->removeItem(item->getID());
    }
    else
    {
        item = getItemFromID(getAIItemFromCommand(m_aiCommand->selection1));
        appendCommands(item->getItemData(&m_opponentPokemon, user, m_aiCommand->selection2));
        m_npt->NPT::removeItem(item->getID());
    }
}

void BattleDataGenerator::generateStatusData(SelectedUser user, IncrementTime afflictionTime, bool appendData)
{
    if (stopGenerating())
        return;

    //Major Status
    if (user == SelectedUser::PLAYER)
    {
        if (m_playerPokemon.getMajorStatus()->id != StatusID::NO_STATUS && getStatusFromID(m_playerPokemon.getMajorStatus()->id)->getData().time == afflictionTime)
        {
            appendCommands(incrementStatusTimer(&m_playerPokemon, m_playerPokemon.getMajorStatus(), SelectedUser::PLAYER));

            if (m_playerPokemon.getMajorStatus()->id != StatusID::NO_STATUS && !m_playerPokemon.getMajorStatus()->isBlocker)
            {
                std::vector<SimulationCommand> commands = getStatusFromID(m_playerPokemon.getMajorStatus()->id)->getStatusData(&m_playerPokemon, SelectedUser::PLAYER);
                
                if (appendData)
                    appendCommands(commands);
            }
        }

        int playerStatusSize = m_playerPokemon.getMinorStatus()->size();


        for (int i = m_playerPokemon.getMinorStatus()->size() - 1; i >= 0; i--)
        {

            if (getStatusFromID(m_playerPokemon.getMinorStatus()->at(i).id)->getData().time != afflictionTime)
                continue;

            appendCommands(incrementStatusTimer(&m_playerPokemon, &m_playerPokemon.getMinorStatus()->at(i), SelectedUser::PLAYER));

            if (playerStatusSize != m_playerPokemon.getMinorStatus()->size())
            {
                playerStatusSize = m_playerPokemon.getMinorStatus()->size();
                continue;
            }

            if (m_playerPokemon.getMinorStatus()->at(i).isBlocker)
                continue;

            std::vector<SimulationCommand> commands = getStatusFromID(m_playerPokemon.getMinorStatus()->at(i).id)->getStatusData(&m_playerPokemon, SelectedUser::PLAYER);
            
            if (appendData)
                appendCommands(commands);
        }
    }
    else
    {
        if (m_opponentPokemon.getMajorStatus()->id != StatusID::NO_STATUS && getStatusFromID(m_opponentPokemon.getMajorStatus()->id)->getData().time == afflictionTime)
        {
            appendCommands(incrementStatusTimer(&m_opponentPokemon, m_opponentPokemon.getMajorStatus(), SelectedUser::AI));

            if (m_opponentPokemon.getMajorStatus()->id != StatusID::NO_STATUS && !m_opponentPokemon.getMajorStatus()->isBlocker)
            {
                std::vector<SimulationCommand> commands = getStatusFromID(m_opponentPokemon.getMajorStatus()->id)->getStatusData(&m_opponentPokemon, SelectedUser::AI);
                
                if (appendData)
                    appendCommands(commands);
            }
        }

        int opponentStatusSize = m_opponentPokemon.getMinorStatus()->size();
        for (int i = m_opponentPokemon.getMinorStatus()->size() - 1; i >= 0; i--)
        {


            if (getStatusFromID(m_opponentPokemon.getMinorStatus()->at(i).id)->getData().time != afflictionTime)
                continue;

            appendCommands(incrementStatusTimer(&m_opponentPokemon, &m_opponentPokemon.getMinorStatus()->at(i), SelectedUser::AI));

            if (opponentStatusSize != m_opponentPokemon.getMinorStatus()->size())
            {
                opponentStatusSize = m_opponentPokemon.getMinorStatus()->size();
                continue;
            }

            if (m_opponentPokemon.getMinorStatus()->at(i).isBlocker)
                continue;


            std::vector<SimulationCommand> commands = getStatusFromID(m_opponentPokemon.getMinorStatus()->at(i).id)->getStatusData(&m_opponentPokemon, SelectedUser::AI);

            if (appendData)
                appendCommands(commands);
        }
    }
}

bool BattleDataGenerator::pokemonCaught()
{
    for (const SimulationCommand& command : m_commands)
    {
        if (command.itemData.pokeballData.caught == true)
            return true;
    }
    return false;
}

int BattleDataGenerator::getMoveFromCommand(SimulationCommand command, SelectedUser user)
{
    //TODO: This function is a little overloaded for its name.

    if (command.selection2 != NONE)
        return command.selection2;

    if (command.selection1 == MOVE_FIVE)
        return AttackID::STRUGGLE;

    Moveset moveset = m_playerPokemon.getMoveset();

    if (user == SelectedUser::AI)
        moveset = m_opponentPokemon.getMoveset();

    int move = NONE;

    switch (command.selection1)
    {
    case MOVE_ONE:
        move = moveset.move1;
        moveset.move1pp--;
        break;
    case MOVE_TWO:
        move = moveset.move2;
        moveset.move2pp--;
        break;
    case MOVE_THREE:
        move = moveset.move3;
        moveset.move3pp--;
        break;
    case MOVE_FOUR:
        move = moveset.move4;
        moveset.move4pp--;
        break;
    default:
        logger->log(LogLevel::CRITICAL, "Invalid Player Move choice: " + std::to_string((int)command.selection1), "getMoveFromCommand", "OldBattleSimulator");
        logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
        break;
    }

    if (user == SelectedUser::PLAYER)
        m_trainer->getRoster()[m_localPlayerPokemonIndex].setMoveset(moveset);
    else
    {
        if (m_npt == nullptr)
            m_wildPokemon->setMoveset(moveset);
        else
            m_npt->getRoster()[*m_opponentPokemonIndex].setMoveset(moveset);
    }
    
    return move;
}

void BattleDataGenerator::appendCommands(std::vector<SimulationCommand> commands)
{
    for (SimulationCommand command : commands)
    {
        m_commands.push_back(command);
    }
}

ItemID BattleDataGenerator::getAIItemFromCommand(int selection)
{
    ItemStorage* storage = m_npt->getItemStorage();
    int count = 0;

    for (auto item = storage->getBattleItems()->begin(); item != storage->getBattleItems()->end(); item++)
    {
        if (count == selection)
            return item->first;
        count++;
    }
    return ItemID();
}


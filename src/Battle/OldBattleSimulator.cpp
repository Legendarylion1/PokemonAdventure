#include "OldBattleSimulator.h"
#include <iostream>
#include <cstdlib>

void OldBattleSimulator::setup(Trainer* trainer, Menu* menu, RosterDisplayData* rosterData, DialogueRenderer* dialogueRenderer, OldAnimator* animator, Input* input, Timer* timer)
{
    m_player = trainer;
    m_battleItems = trainer->getItemStorage()->getBattleItems();
    m_menu = menu;
    m_dialogueRenderer = dialogueRenderer;
    m_animator = animator;
    m_input = input;
    m_timer = timer;

    //m_menu->setupBattleData(&m_playerAttacks, &m_menuCommand, rosterData, &m_playerBattleItems, &m_battleData, &m_playerPokemonData, &m_opponentPokemonData);

    m_rosterData = rosterData;
    m_playerDisplayPokemon = m_player->getRoster();

    updatePlayerItems();
    logger->log(LogLevel::INFO, "Setup Complete", "setup", "OldBattleSimulator");
}

void OldBattleSimulator::beginBattle(NPT* npt)
{
    //TODO: Fade in and out of battle with some kinda animation
    logger->log(LogLevel::INFO, "npt Battle Started", "beginBattle", "OldBattleSimulator");
    setupTrainer();
    setupNPT(npt);
    setupXP();
    resetMenu();
    updatePlayerAttacks();
    updatePlayerItems();
    addToXpRecord();

    m_menu->setCanLeave(false);

    simulateBattle();

    if (!m_player->unableToBattle())
    {
        grantNPTRewards();
        npt->setHasBeenDefeated(true);
    }

    m_npt = nullptr;
    m_menu->setscene(MenuScene::NONE);
}

Pokemon OldBattleSimulator::beginBattle(Pokemon pokemon)
{
    logger->log(LogLevel::INFO, "pokemon Battle started", "beginBattle", "OldBattleSimulator");
    setupTrainer();
    setupPokemon(pokemon);
    setupXP();
    resetMenu();
    updatePlayerAttacks();
    updatePlayerItems();
    addToXpRecord();

    m_menu->setCanLeave(true);

    simulateBattle();

    if (m_pokemonCaught)
        return handleCatch();

    m_menu->setscene(MenuScene::NONE);
    return Pokemon();
}

void OldBattleSimulator::updatePlayerItems()
{
    int count = 0;
    int indexCount = 0;

    for (auto i = m_battleItems->begin(); i != m_battleItems->end(); i++)
    {
        if (indexCount != m_itemIndex)
        {
            indexCount++;
            continue;
        }
        if (count == 5)
            break;
        if (i->second == 0)
            continue;
        

        switch (count)
        {
        case 0:
            //TODO: What is the purpose of this function lmfao
            formatRosterData(&m_playerBattleItems.itemName.string1, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string1 = "x" + std::to_string(i->second);
            break;
        case 1:
            formatRosterData(&m_playerBattleItems.itemName.string2, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string2 = "x" + std::to_string(i->second);
            break;
        case 2:
            formatRosterData(&m_playerBattleItems.itemName.string3, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string3 = "x" + std::to_string(i->second);
            break;
        case 3:
            formatRosterData(&m_playerBattleItems.itemName.string4, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string4 = "x" + std::to_string(i->second);
            break;
        case 4:
            formatRosterData(&m_playerBattleItems.itemName.string5, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string5 = "x" + std::to_string(i->second);
            break;
        }


        count++;
    }

    for (int i = count; i < 5; i++)
    {
        switch (i)
        {
        case 0:
            formatRosterData(&m_playerBattleItems.itemName.string1, "NONE");
            m_playerBattleItems.itemAmount.string1 = "";
            break;
        case 1:
            formatRosterData(&m_playerBattleItems.itemName.string2, "NONE");
            m_playerBattleItems.itemAmount.string2 = "";
            break;
        case 2:
            formatRosterData(&m_playerBattleItems.itemName.string3, "NONE");
            m_playerBattleItems.itemAmount.string3 = "";
            break;
        case 3:
            formatRosterData(&m_playerBattleItems.itemName.string4, "NONE");
            m_playerBattleItems.itemAmount.string4 = "";
            break;
        case 4:
            formatRosterData(&m_playerBattleItems.itemName.string5, "NONE");
            m_playerBattleItems.itemAmount.string5 = "";
            break;
        }
    }
}

bool OldBattleSimulator::canIncrementItemList()
{
    //Note that if list size changes or we want to make modifications in any way then we need to adjust the count here and in other functions

    int count = 0;
    int indexCount = 0;
    for (auto i = m_battleItems->begin(); i != m_battleItems->end(); i++)
    {
        if (indexCount != m_itemIndex + 1)
        {
            indexCount++;
            continue;
        }
        if (count == 5)
            return true;
        count++;
    }

    if (count == 5)
        return true;

    return false;
}

void OldBattleSimulator::setupTrainer()
{
    m_playerPokemonData = { 25.5f, (253.5f / 563.0f) * 100.0f, 20.0f * (9.0f / 16.0f), 20.0f };

    for (int i = 0; i < 6; i++)
    {
        m_playerDisplayPokemon[i].removeBattleStats();
        m_playerTestPokemon[i] = m_playerDisplayPokemon[i];
    }

    for (int i = 0; i < 6; i++)
    {
        if (m_playerDisplayPokemon[i].getCurHealth() > 0)
        {
            m_playerPokemonIndex = i;
            m_p1moveset = m_playerDisplayPokemon[m_playerPokemonIndex].getMoveset();

            adjustPokemonDisplay(SelectedUser::PLAYER);
            break;
        }
    }

    m_flee = false;
    m_itemIndex = 0;
    
    updateDisplayPokemon(m_player, m_rosterData);
}

void OldBattleSimulator::setupNPT(NPT* npt)
{
    m_opponentPokemonIndex = 0;
    m_npt = npt;
    m_npt->restoreItems();

    for (int i = 0; i < 6; i++)
    {
        Moveset tempMoveSet = npt->getPokemon(i).getMoveset();

        tempMoveSet.move1pp = getAttackFromID(tempMoveSet.move1)->getPP();
        tempMoveSet.move2pp = getAttackFromID(tempMoveSet.move2)->getPP();
        tempMoveSet.move3pp = getAttackFromID(tempMoveSet.move3)->getPP();
        tempMoveSet.move4pp = getAttackFromID(tempMoveSet.move4)->getPP();


        m_opponentTestPokemon[i] = npt->getPokemon(i);
        m_opponentTestPokemon[i].setMoveset(tempMoveSet);

        m_opponentDisplayPokemon[i] = npt->getPokemon(i);
        m_opponentDisplayPokemon[i].setMoveset(tempMoveSet);
    }

    m_opponentPokemonData = { 74.4f, (443.0f / 563.0f) * 100.0f, 10.0f, 10.0f * (16.0f / 9.0f)};
    adjustPokemonDisplay(SelectedUser::AI);
}

void OldBattleSimulator::setupPokemon(Pokemon pokemon)
{
    Moveset tempMoveSet = pokemon.getMoveset();

    tempMoveSet.move1pp = getAttackFromID(tempMoveSet.move1)->getPP();
    tempMoveSet.move2pp = getAttackFromID(tempMoveSet.move2)->getPP();
    tempMoveSet.move3pp = getAttackFromID(tempMoveSet.move3)->getPP();
    tempMoveSet.move4pp = getAttackFromID(tempMoveSet.move4)->getPP();

    pokemon.setMoveset(tempMoveSet);


    m_opponentPokemonIndex = 0;
    m_opponentTestPokemon[0] = pokemon;
    m_opponentDisplayPokemon[0] = pokemon;
    m_opponentPokemonData = { 74.4f, (443.0f / 563.0f) * 100.0f, 10.0f, 10.0f * (16.0f / 9.0f) };
    adjustPokemonDisplay(SelectedUser::AI);

    for (int i = 1; i < 6; i++)
    {
        m_opponentTestPokemon[i] = Pokemon();
        m_opponentDisplayPokemon[i] = Pokemon();
    }
    m_npt = nullptr;
    m_pokemonCaught = false;
    
}

void OldBattleSimulator::setupXP()
{
    for (int i = 0; i < 6; i++)
    {
        m_xpRecords[i].clear();
    }
}

bool OldBattleSimulator::simulateBattle()
{
    while (!m_animator->loadingComplete() && !m_menu->shouldClose())
    {

        //TODO: Add a loading card for when a battle starts that gives us time to load these animations
        std::cout << "Waiting on animations to load" << std::endl;
    }
    logger->log(LogLevel::DEBUG, "simulation Starting", "simulateBattle", "OldBattleSimulator");
    m_menu->setCanLeave(true);
    m_menu->preRun();

    while (!m_menu->shouldClose())
    {

        if (m_playerDisplayPokemon[m_playerPokemonIndex].hasForcedAttack() == NONE)
        {
            m_menu->run();

            if (m_menu->getCurrentScene() == MenuScene::BATTLE_ROSTER)
                updateDisplayPokemonStats(&m_hoverIndex, m_player, m_menu->getButtonIndex(), m_rosterData);

            if (m_menuCommand.selection1 == NONE)
                continue;
        }
        else
            generateForcedAttack(SelectedUser::PLAYER);

        generateSimulationData(m_menuCommand, getAICommand());

        if (!runSimulation())
            continue;

        if (battleOver())
            break;
    }

    m_menu->postRun();
    return false;
}

void OldBattleSimulator::onUpdate()
{
    m_menu->renderMenu();
    m_animator->updateRenderer();
    
    //system("CLS");
    //std::cout << "\n";
    //std::cout << m_playerDisplayPokemon[m_displayPokemonIndex].getName() << "\n" << m_playerDisplayPokemon[m_displayPokemonIndex].getCurHealth() << " / " << m_playerDisplayPokemon[m_displayPokemonIndex].getStats().hp << " HP" << std::endl;
    //std::cout << m_opponentDisplayPokemon[m_opponentPokemonIndex].getName() << "\n" << m_opponentDisplayPokemon[m_opponentPokemonIndex].getCurHealth() << " / " << m_opponentDisplayPokemon[m_opponentPokemonIndex].getStats().hp << " HP" << std::endl;
    //std::cout << "\n";
}

void OldBattleSimulator::generateSimulationData(SimulationCommand playerCommand, SimulationCommand aiCommand)
{
    switch (playerCommand.type)
    {

    case SimulationType::ATTACK_SELECTED:
        handleAttack(playerCommand, aiCommand);
        break;
    case SimulationType::POKEMON_SELECTED:
        handlePokemonSwap(playerCommand, aiCommand);
        break;
    case SimulationType::ITEM_SELECTED:
        handleItemSelection(playerCommand, aiCommand);
        break;
    case SimulationType::FLEE_SELECTED:
        handleFleeSelection(aiCommand);
        break;
    default:
        logger->log(LogLevel::CRITICAL, "unhandled simulation data type: " + std::to_string((int)playerCommand.type), "generateSimulationData", "OldBattleSimulator");
        logger->reportCriticalError(ErrorCodes::UNHANDLED_SIM_DATA);
    }

    if (m_commands.size() != 0)
    {
        generateStatusData(SelectedUser::AI, IncrementTime::AFTER);
        generateStatusData(SelectedUser::PLAYER, IncrementTime::AFTER);
    }
}

void OldBattleSimulator::generateStatusData(SelectedUser user, IncrementTime afflictionTime)
{

    //Major Status
    if (user == SelectedUser::PLAYER)
    {
        if (m_playerTestPokemon[m_playerPokemonIndex].getMajorStatus()->id != StatusID::NO_STATUS && getStatusFromID(m_playerTestPokemon[m_playerPokemonIndex].getMajorStatus()->id)->getData().time == afflictionTime)
        {
            appendCommands(incrementStatusTimer(&m_playerTestPokemon[m_playerPokemonIndex], m_playerTestPokemon[m_playerPokemonIndex].getMajorStatus(), SelectedUser::PLAYER));

            if (m_playerTestPokemon[m_playerPokemonIndex].getMajorStatus()->id != StatusID::NO_STATUS && !m_playerTestPokemon[m_playerPokemonIndex].getMajorStatus()->isBlocker)
                appendCommands(getStatusFromID(m_playerTestPokemon[m_playerPokemonIndex].getMajorStatus()->id)->getStatusData(&m_playerTestPokemon[m_playerPokemonIndex], SelectedUser::PLAYER));
        }

        int playerStatusSize = m_playerTestPokemon[m_playerPokemonIndex].getMinorStatus()->size();
        

        for (int i = m_playerTestPokemon[m_playerPokemonIndex].getMinorStatus()->size() - 1; i >= 0; i--)
        {

            if (getStatusFromID(m_playerTestPokemon[m_playerPokemonIndex].getMinorStatus()->at(i).id)->getData().time != afflictionTime)
                continue;

            appendCommands(incrementStatusTimer(&m_playerTestPokemon[m_playerPokemonIndex], &m_playerTestPokemon[m_playerPokemonIndex].getMinorStatus()->at(i), SelectedUser::PLAYER));

            if (playerStatusSize != m_playerTestPokemon[m_playerPokemonIndex].getMinorStatus()->size())
            {
                playerStatusSize = m_playerTestPokemon[m_playerPokemonIndex].getMinorStatus()->size();
                continue;
            }

            if (m_playerTestPokemon[m_playerPokemonIndex].getMinorStatus()->at(i).isBlocker)
                continue;

            appendCommands(getStatusFromID(m_playerTestPokemon[m_playerPokemonIndex].getMinorStatus()->at(i).id)->getStatusData(&m_playerTestPokemon[m_playerPokemonIndex], SelectedUser::PLAYER));
        }
    }
    else
    {
        if (m_opponentTestPokemon[m_opponentPokemonIndex].getMajorStatus()->id != StatusID::NO_STATUS && getStatusFromID(m_opponentTestPokemon[m_opponentPokemonIndex].getMajorStatus()->id)->getData().time == afflictionTime)
        {
            appendCommands(incrementStatusTimer(&m_opponentTestPokemon[m_opponentPokemonIndex], m_opponentTestPokemon[m_opponentPokemonIndex].getMajorStatus(), SelectedUser::AI));

            if (m_opponentTestPokemon[m_opponentPokemonIndex].getMajorStatus()->id != StatusID::NO_STATUS && !m_opponentTestPokemon[m_opponentPokemonIndex].getMajorStatus()->isBlocker)
                appendCommands(getStatusFromID(m_opponentTestPokemon[m_opponentPokemonIndex].getMajorStatus()->id)->getStatusData(&m_opponentTestPokemon[m_opponentPokemonIndex], SelectedUser::AI));
        }

        int opponentStatusSize = m_opponentTestPokemon[m_opponentPokemonIndex].getMinorStatus()->size();
        for (int i = m_opponentTestPokemon[m_opponentPokemonIndex].getMinorStatus()->size() - 1; i >= 0; i--)
        {


            if (getStatusFromID(m_opponentTestPokemon[m_opponentPokemonIndex].getMinorStatus()->at(i).id)->getData().time != afflictionTime)
                continue;

            appendCommands(incrementStatusTimer(&m_opponentTestPokemon[m_opponentPokemonIndex], &m_opponentTestPokemon[m_opponentPokemonIndex].getMinorStatus()->at(i), SelectedUser::AI));

            if (opponentStatusSize != m_opponentTestPokemon[m_opponentPokemonIndex].getMinorStatus()->size())
            {
                opponentStatusSize = m_opponentTestPokemon[m_opponentPokemonIndex].getMinorStatus()->size();
                continue;
            }

            if (m_opponentTestPokemon[m_opponentPokemonIndex].getMinorStatus()->at(i).isBlocker)
                continue;

            appendCommands(getStatusFromID(m_opponentTestPokemon[m_opponentPokemonIndex].getMinorStatus()->at(i).id)->getStatusData(&m_opponentTestPokemon[m_opponentPokemonIndex], SelectedUser::AI));
        }
    }
}

bool OldBattleSimulator::runSimulation()
{
    if (m_commands.size() == 0)
    {
        m_menuCommand.selection1 = NONE;
        m_menu->setscene(MenuScene::BATTLE);
        m_menu->setOverlay(MenuOverlay::BATTLE_OPTIONS);
        return false;
    }

    for (const SimulationCommand &command : m_commands)
    {
        switch (command.type)
        {
        case SimulationType::ATTACK:
            simulateAttack(command);
            break;
        case SimulationType::POKEMON:
            simulatePokemon(command);
            break;
        case SimulationType::ITEM:
            simulateItem(command);
            break;
        case SimulationType::FLEE:
            simulateFlee(command);
            break;
        case SimulationType::STATUS:
            simulateStatus(command);
            break;
        case SimulationType::STAT:
            simulateStat(command);
            break;
        default:
            logger->log(LogLevel::CRITICAL, "Unhandled simulation type: " + std::to_string((int)command.type), "runSimulation", "OldBattleSimulator");
            logger->reportCriticalError(ErrorCodes::UNHANDLED_SIM_DATA);
        }
    }

    updateDisplayPokemon(m_player, m_rosterData);
    m_commands.clear();
    return true;
}

bool OldBattleSimulator::battleOver()
{
    if (m_flee || m_pokemonCaught)
        return true;

    bool playerContinue = false;
    bool aiContinue = false;


    if (!m_player->unableToBattle())
        playerContinue = true;

    for (int i = 0; i < 6; i++)
    {
        if (m_opponentDisplayPokemon[i].getCurHealth() > 0)
        {
            aiContinue = true;
            break;
        }
    }

    if (!aiContinue)
        handleFaintXP(SelectedUser::AI);

    if (!playerContinue || !aiContinue)
        return true;



    if (m_playerDisplayPokemon[m_displayPokemonIndex].getCurHealth() == 0 && m_opponentDisplayPokemon[m_opponentPokemonIndex].getCurHealth() == 0)
    {
        logger->log(LogLevel::INFO, "Both Pokemon Fainted", "battleOver", "OldBattleSimulator");
        handleFaintSelection(SelectedUser::BOTH);
    }
    else if (m_opponentDisplayPokemon[m_opponentPokemonIndex].getCurHealth() == 0)
    {
        logger->log(LogLevel::INFO, "AI Pokemon Fainted", "battleOver", "OldBattleSimulator");
        handleFaintSelection(SelectedUser::AI);
    }
    else if (m_playerDisplayPokemon[m_displayPokemonIndex].getCurHealth() == 0)
    {
        logger->log(LogLevel::INFO, "Player Pokemon Fainted", "battleOver", "OldBattleSimulator");
        handleFaintSelection(SelectedUser::PLAYER);
    }

    resetMenu();
    return false;
}

void OldBattleSimulator::grantNPTRewards()
{
    m_player->giveMoney(m_npt->getBalance());
}

Pokemon OldBattleSimulator::handleCatch()
{
    for (int i = 0; i < 6; i++)
    {
        if (m_playerDisplayPokemon[i].getLevel() == 0)
        {
            m_playerDisplayPokemon[i] = m_opponentDisplayPokemon[m_opponentPokemonIndex];

            return Pokemon();
        }
    }

    logger->log(LogLevel::INFO, "Pokemon Caught", "handleCatch", "OldBattleSimulator");
    return m_opponentDisplayPokemon[m_opponentPokemonIndex];
}

SimulationCommand OldBattleSimulator::getAICommand()
{
    SimulationCommand aiCommand{};
    aiCommand.type = SimulationType::ITEM_SELECTED;

    if (m_opponentTestPokemon[m_opponentPokemonIndex].hasForcedAttack() != NONE)
    {
        aiCommand.type = SimulationType::ATTACK_SELECTED;
        aiCommand.selection2 = m_opponentTestPokemon[m_opponentPokemonIndex].hasForcedAttack();
        return aiCommand;
    }

    if (m_npt != nullptr)
    {
        bool healthCheck = m_opponentTestPokemon[m_opponentPokemonIndex].getCurHealth() <= m_opponentTestPokemon[m_opponentPokemonIndex].getStats().hp / 3.0f;
        bool statusCheck = m_opponentTestPokemon[m_opponentPokemonIndex].getMajorStatus()->id != StatusID::NO_STATUS;

        if ( healthCheck || statusCheck)
        {

            ItemStorage* storage = m_npt->getItemStorage();
            int count = 0;

            for (auto i = storage->getBattleItems()->begin(); i != storage->getBattleItems()->end(); i++)
            {
                if (i->second == 0)
                {
                    count++;
                    continue;
                }

                if (
                    getItemFromID(i->first)->getStatus() != StatusID::NO_STATUS && 
                    getItemFromID(i->first)->getStatus() == m_opponentTestPokemon[m_opponentPokemonIndex].getMajorStatus()->id &&
                    statusCheck
                    )
                {
                    aiCommand.selection1 = count;
                    aiCommand.selection2 = m_opponentPokemonIndex;

                    return aiCommand;
                }
                else if (healthCheck && getItemFromID(i->first)->canBeUsedOnPokemon(&m_opponentTestPokemon[m_opponentPokemonIndex]))
                {
                    aiCommand.selection1 = count;
                    aiCommand.selection2 = m_opponentPokemonIndex;
                    return aiCommand;
                }

                count++;
            }

        }
    }
    

    

    aiCommand.type = ATTACK_SELECTED;


    std::vector<float> movePoints = { 0,0,0,0 };
    std::vector<int> highest = {0};

    for (int i = 0; i < 4; i++)
    {
        if (i == 0 && m_opponentTestPokemon[m_opponentPokemonIndex].getMoveset().move1pp == 0)
            continue;
        else if (i == 1 && m_opponentTestPokemon[m_opponentPokemonIndex].getMoveset().move2pp == 0)
            continue;
        else if (i == 2 && m_opponentTestPokemon[m_opponentPokemonIndex].getMoveset().move3pp == 0)
            continue;
        else if (i == 3 && m_opponentTestPokemon[m_opponentPokemonIndex].getMoveset().move4pp == 0)
            continue;

        Attack* attack = getAttackFromID(getMoveFromCommand(i, SelectedUser::AI));

        // Points for Damage
        movePoints.at(i) += attack->getPotentialDamage(&m_opponentTestPokemon[m_opponentPokemonIndex], &m_playerTestPokemon[m_playerPokemonIndex]) / 10.0f;


        // Points for Status
        if (canHaveStatus(&m_opponentTestPokemon[m_opponentPokemonIndex], getAttackFromID(getMoveFromCommand(i, SelectedUser::AI))->getStatus()))
        {
            float statusMultiplier = (m_opponentTestPokemon[m_opponentPokemonIndex].getLevel() + 100.0f) / 200.0f;
            movePoints.at(i) += (attack->getStatusOdds(&m_opponentTestPokemon[m_opponentPokemonIndex], &m_playerTestPokemon[m_playerPokemonIndex]) / 10.0f) * statusMultiplier;
        }

        // Points for buffs n stuff
        {
            float playerMultiplier = (randomNumber(101) / 20.0f)   + ((m_opponentTestPokemon[m_opponentPokemonIndex].getLevel() + 50) / 100.0f);
            float opponentMultiplier = (randomNumber(101) / 20.0f) + ((m_opponentTestPokemon[m_opponentPokemonIndex].getLevel() + 50) / 100.0f);


            //TODO: Add accuracy here and all other places referenced
            if (attack->getPlayerStat().attack + attack->getPlayerStat().defense + attack->getPlayerStat().spAttack + attack->getPlayerStat().spDefense + attack->getPlayerStat().evasiveness + attack->getPlayerStat().speed < 0)
                playerMultiplier *= -1;


            movePoints.at(i) += calculateStatChange(attack->getPlayerStat(), &m_playerTestPokemon[m_playerPokemonIndex]) * playerMultiplier;
            movePoints.at(i) += calculateStatChange(attack->getOpponentStat(), &m_playerTestPokemon[m_playerPokemonIndex]) * opponentMultiplier;
        }
    }


    for (int i = 1; i < 4; i++)
    {
        if (movePoints.at(i) > movePoints.at(highest.at(0)))
        {
            highest.clear();
            highest.push_back(i);
        }
        else if (movePoints.at(i) == movePoints.at(highest.at(0)))
            highest.push_back(i);
    }


    aiCommand.selection1 = highest.at(randomNumber((int)highest.size()));

    if (movePoints.at(aiCommand.selection1) == 0)
        aiCommand.selection1 = MOVE_FIVE;

    return aiCommand;
}

int OldBattleSimulator::getMoveFromCommand(int commandMove, SelectedUser user)
{
    if (commandMove == MOVE_FIVE)
        return AttackID::STRUGGLE;

    switch (user)
    {
    case SelectedUser::PLAYER:
        switch (commandMove)
        {
        case MOVE_ONE:
            return m_p1moveset.move1;
        case MOVE_TWO:
            return m_p1moveset.move2;
        case MOVE_THREE:
            return m_p1moveset.move3;
        case MOVE_FOUR:
            return m_p1moveset.move4;
        default:
            logger->log(LogLevel::CRITICAL, "Invalid Player Move choice: " + std::to_string((int)commandMove), "getMoveFromCommand", "OldBattleSimulator");
            logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
            break;
        }
    case SelectedUser::AI:
        switch (commandMove)
        {
        case MOVE_ONE:
            return m_opponentTestPokemon[m_opponentPokemonIndex].getMoveset().move1;
        case MOVE_TWO:
            return m_opponentTestPokemon[m_opponentPokemonIndex].getMoveset().move2;
        case MOVE_THREE:
            return m_opponentTestPokemon[m_opponentPokemonIndex].getMoveset().move3;
        case MOVE_FOUR:
            return m_opponentTestPokemon[m_opponentPokemonIndex].getMoveset().move4;
        default:
            logger->log(LogLevel::CRITICAL, "Invalid AI Move choice: " + std::to_string((int)commandMove), "getMoveFromCommand", "OldBattleSimulator");
            logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
            break;
        }
        break;
    default:
        logger->log(LogLevel::CRITICAL, "Invalid user choice: " + std::to_string((int)commandMove), "getMoveFromCommand", "OldBattleSimulator");
        logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
        break;
    }
        
    
    return 4;
}

ItemID OldBattleSimulator::getItemFromCommand(int itemIndex, SelectedUser user)
{
    int count = 0;
    if (user == SelectedUser::PLAYER)
    {
        for (auto item = m_battleItems->begin(); item != m_battleItems->end(); item++)      //TODO: Fix This
        {
            if (item->second == 0)
                continue;
            if (count == itemIndex)
                return item->first;
            count++;
        }
    }
    else
    {
        ItemStorage* storage = m_npt->getItemStorage();
        int count = 0;

        for (auto item = storage->getBattleItems()->begin(); item != storage->getBattleItems()->end(); item++)
        {
            if (count == itemIndex)
                return item->first;
            count++;
        }
    }
    
    logger->log(LogLevel::CRITICAL, "Unable to Retrieve Item", "getItemFromCommand", "OldBattleSimulator");
    logger->reportCriticalError(ErrorCodes::UNIDENTIFIED_ITEM);
    return ItemID();
}

void OldBattleSimulator::appendCommands(std::vector<SimulationCommand> commands)
{
    for (SimulationCommand command : commands)
    {
        m_commands.push_back(command);
    }
}

void OldBattleSimulator::generateAttack(SelectedUser attacker, SimulationCommand command)
{
    int move = command.selection2;
    if (move == NONE)
        move = getMoveFromCommand(command.selection1, attacker);

    generateStatusData(attacker, IncrementTime::BEFORE);

    if (attacker == SelectedUser::PLAYER)
    {
        
        StatusID attackerStatus = m_playerTestPokemon[m_playerPokemonIndex].getAttackBlocker();

        if (attackerStatus == StatusID::FAINTED)
            return;
        else if (attackerStatus == StatusID::NO_STATUS)
        {
            appendCommands(getAttackFromID(move)->getAttackData(&m_playerTestPokemon[m_playerPokemonIndex], &m_opponentTestPokemon[m_opponentPokemonIndex], attacker));
            reducePP(attacker, command.selection1);
        }
        else
        {
            appendCommands(getStatusFromID(attackerStatus)->getStatusData(&m_playerTestPokemon[m_playerPokemonIndex], SelectedUser::PLAYER));
        }
    }
    else
    {
        //We use display pokemon here because we do not want the AI to cheat and know what new pokemon is coming out
        StatusID attackerStatus = m_opponentTestPokemon[m_opponentPokemonIndex].getAttackBlocker();

        if (attackerStatus == StatusID::FAINTED)
            return;
        else if (attackerStatus == StatusID::NO_STATUS)
        {
            appendCommands(getAttackFromID(move)->getAttackData(&m_opponentTestPokemon[m_opponentPokemonIndex], &m_playerTestPokemon[m_playerPokemonIndex], attacker));
            reducePP(attacker, command.selection1);
        }
        else
        {
            appendCommands(getStatusFromID(attackerStatus)->getStatusData(&m_opponentTestPokemon[m_opponentPokemonIndex], SelectedUser::AI));
        }
    }
}

bool OldBattleSimulator::generateItem(SelectedUser commander, SimulationCommand command)
{
    if (command.selection1 == arrowDirections::UP)
    {
        if (m_itemIndex != 0)
        {
            m_itemIndex--;
            updatePlayerItems();
            m_menuCommand.selection1 = NONE;
            return false;
        }
        else
        {
            m_menuCommand.selection1 = NONE;
            return false;
        }

    }
    else if (command.selection1 == arrowDirections::DOWN)
    {
        if (canIncrementItemList())
        {
            m_itemIndex++;
            updatePlayerItems();
            m_menuCommand.selection1 = NONE;
            return false;
        }
        else
        {
            m_menuCommand.selection1 = NONE;
            return false;
        }

    }

    if (!validItemSelection(command.selection1))
        return false;

    Item* item = nullptr;

    if (commander == SelectedUser::PLAYER)
    {
        item = getItemFromID(getItemFromCommand(command.selection1 + m_itemIndex, SelectedUser::PLAYER));

        if (!isPokeball(*item))
        {
            m_menu->setRequestedData(&command.selection2);
            m_menu->setscene(MenuScene::BATTLE_ROSTER);
            m_menu->setCanLeave(false);
            m_menu->preRun();

            while (command.selection2 == NONE)
            {
                if (m_menu->shouldClose())
                    break;

                onUpdate();
                m_menu->run();

                if (m_menu->leaveRequested())
                {
                    m_menuCommand.selection1 = NONE;
                    m_menu->setCanLeave(true);
                    m_menu->setOverlay(MenuOverlay::BATTLE_OPTIONS);
                    m_menu->clearRequestedData();
                    return false;
                }

                if (command.selection2 != NONE && !item->canBeUsedOnPokemon(&m_playerTestPokemon[command.selection2]))
                    command.selection2 = NONE;  //TODO: Probably indicate invalid selection
            }

            m_menu->setCanLeave(true);
            m_menu->clearRequestedData();
            m_menu->postRun();
        }
        else if (m_npt != nullptr)
        {
            logger->log(LogLevel::ERROR, "Pokeball used on trainer pokemon", "generateItem", "OldBattleSimulator");
            return false;
        }
        else
        {
            appendCommands(item->getItemData(&m_opponentTestPokemon[m_opponentPokemonIndex], commander, m_opponentPokemonIndex));
            return true;
        }
    }
    else
    {
        item = getItemFromID(getItemFromCommand(command.selection1, SelectedUser::AI));
    }
    
    
    if (commander == SelectedUser::PLAYER)
    {
        appendCommands(item->getItemData(&m_playerTestPokemon[command.selection2 + m_itemIndex], commander, command.selection2));
    }
    else
    {
        appendCommands(item->getItemData(&m_opponentTestPokemon[command.selection2], commander, command.selection2));
    }
    return true;
}

SimulationCommand OldBattleSimulator::generateForcedAttack(SelectedUser commander)
{
    //Change selection 2 to whatever the forced move is

    if (commander == SelectedUser::PLAYER)
    {
        m_menuCommand.type = SimulationType::ATTACK_SELECTED;
        m_menuCommand.commander = commander;
        m_menuCommand.selection2 = m_playerDisplayPokemon[m_displayPokemonIndex].hasForcedAttack();

        return SimulationCommand();
    }
    else
    {
        SimulationCommand aiCommand;

        aiCommand.type = SimulationType::ATTACK_SELECTED;
        aiCommand.commander = commander;
        aiCommand.selection2 = m_opponentDisplayPokemon[m_opponentPokemonIndex].hasForcedAttack();

        return aiCommand;
    }
}

void OldBattleSimulator::handleAttack(SimulationCommand playerCommand, SimulationCommand aiCommand)
{
    if (playerCommand.selection1 != NONE)
    {
        bool reselectMove = false;

        if (playerCommand.selection1 == MOVE_ONE && m_p1moveset.move1pp == 0)
            reselectMove = true;
        else if (playerCommand.selection1 == MOVE_TWO && m_p1moveset.move2pp == 0)
            reselectMove = true;
        else if (playerCommand.selection1 == MOVE_THREE && m_p1moveset.move3pp == 0)
            reselectMove = true;
        else if (playerCommand.selection1 == MOVE_FOUR && m_p1moveset.move4pp == 0)
            reselectMove = true;


        if (reselectMove)
        {
            if (m_p1moveset.move1pp == 0 && m_p1moveset.move2pp == 0 && m_p1moveset.move3pp == 0 && m_p1moveset.move4pp == 0)
                playerCommand.selection1 = MOVE_FIVE;
            else
            {
                m_menuCommand.selection1 = NONE;
                return;
            }
        }
    }



    if (aiCommand.type == ITEM_SELECTED)
    {
        generateItem(SelectedUser::AI, aiCommand);
        generateAttack(SelectedUser::PLAYER, playerCommand);
        return;
    }

    if (m_playerTestPokemon[m_playerPokemonIndex].getStats().speed > m_opponentTestPokemon[m_opponentPokemonIndex].getStats().speed)
    {
        generateAttack(SelectedUser::PLAYER, playerCommand);
        generateAttack(SelectedUser::AI, aiCommand);
    }
    else if (m_playerTestPokemon[m_playerPokemonIndex].getStats().speed < m_opponentTestPokemon[m_opponentPokemonIndex].getStats().speed)
    {
        generateAttack(SelectedUser::AI, aiCommand);
        generateAttack(SelectedUser::PLAYER, playerCommand);
    }
    else
    {
        if (outOfHundred(50))
        {
            generateAttack(SelectedUser::PLAYER, playerCommand);
            generateAttack(SelectedUser::AI, aiCommand);
        }
        else
        {
            generateAttack(SelectedUser::AI, aiCommand);
            generateAttack(SelectedUser::PLAYER, playerCommand);
        }
    }
}

void OldBattleSimulator::handlePokemonSwap(SimulationCommand playerCommand, SimulationCommand aiCommand)
{
    m_menu->setscene(MenuScene::BATTLE);
    //m_menu->setOverlay(MenuOverlay::NONE);
    if (playerCommand.selection1 == m_playerPokemonIndex || m_playerDisplayPokemon[playerCommand.selection1].getCurHealth() <= 0)
    {
        //TODO: Display an error of some kind that the pokemon cannot be selected
        m_menuCommand.selection1 = NONE;
        m_menu->setOverlay(MenuOverlay::BATTLE_OPTIONS);
        logger->log(LogLevel::ERROR, "Cannot Swap to selected pokemon", "handlePokemonSwap", "OldBattleSimulator");
        return;
    }

    SimulationCommand swapCommand{};
    swapCommand.type = SimulationType::POKEMON;
    swapCommand.commander = SelectedUser::PLAYER;
    swapCommand.selection1 = playerCommand.selection1;
    m_commands.push_back(swapCommand);

    // All attacks need to be tested on the new pokemon
    // During the simulation the pokemon will be updated
    m_playerPokemonIndex = playerCommand.selection1;

    if (aiCommand.type == ATTACK_SELECTED)
        generateAttack(SelectedUser::AI, aiCommand);
    else
        generateItem(SelectedUser::AI, aiCommand);
}

void OldBattleSimulator::handleItemSelection(SimulationCommand playerCommand, SimulationCommand aiCommand)
{
    if (!generateItem(SelectedUser::PLAYER, playerCommand))
        return;

    if (aiCommand.type == ATTACK_SELECTED)
        generateAttack(SelectedUser::AI, aiCommand);
    else
        generateItem(SelectedUser::AI, aiCommand);
}

void OldBattleSimulator::handleFleeSelection(SimulationCommand aiCommand)
{
    if (m_playerDisplayPokemon[m_playerPokemonIndex].getStats().speed > m_opponentDisplayPokemon[m_opponentPokemonIndex].getStats().speed)
    {
        SimulationCommand flee{};
        flee.type = SimulationType::FLEE;
        flee.selection1 = (int)true;
        m_commands.push_back(flee);
        return;
    }

    SimulationCommand flee{};
    flee.type = SimulationType::FLEE;
    flee.selection1 = (int)false;
    m_commands.push_back(flee);


    if (aiCommand.type == ATTACK_SELECTED)
        generateAttack(SelectedUser::AI, aiCommand);
    else
        generateItem(SelectedUser::AI, aiCommand);
}

void OldBattleSimulator::handleFaintSelection(SelectedUser swapper)
{
    handleFaintXP(swapper);
    if (swapper == SelectedUser::PLAYER)
    {
        logger->log(LogLevel::DEBUG, "Player pokemon has fainted", "handleFaintSelection", "OldBattleSimulator");
        displayFaintMessage(swapper);
        int pokemonIndex = m_displayPokemonIndex;
        m_menu->setRequestedData(&pokemonIndex);
        m_menu->setscene(MenuScene::PAUSE_ROSTER);
        m_menu->clearScenes();
        m_menu->preRun();
        while (m_playerDisplayPokemon[pokemonIndex].getCurHealth() == 0 && !m_menu->shouldClose())
        {
            onUpdate();
            m_menu->run();
        }
        m_menu->clearRequestedData();
        m_menu->postRun();

        SimulationCommand swapCommand{};
        swapCommand.type = SimulationType::POKEMON;
        swapCommand.commander = SelectedUser::PLAYER;
        swapCommand.selection1 = pokemonIndex;

        simulatePokemon(swapCommand);
    }
    else if (swapper == SelectedUser::AI)
    {
        logger->log(LogLevel::DEBUG, "AI Pokemon has fainted", "handleFaintSelection", "OldBattleSimulator");
        SimulationCommand aiSwapCommand{};
        aiSwapCommand.type = SimulationType::POKEMON;
        aiSwapCommand.commander = SelectedUser::AI;
        aiSwapCommand.selection1 = m_opponentPokemonIndex + 1;


        int playerSelection = 0;
        std::cout << "Opponent is about to send in <NAME>\nWould you like to swap\n1) Swap Pokemon\n2) Keep Battling\n";
        while (playerSelection != 1 && playerSelection != 2)    //TODO: Implement
        {
            std::cin >> playerSelection;
            std::cin.clear();
        }

        if (playerSelection == 1)
        {
            int playerSelection = NONE;
            m_menu->setRequestedData(&playerSelection);
            m_menu->setscene(MenuScene::BATTLE_ROSTER);
            m_menu->preRun();

            while (( !(0 <= playerSelection && playerSelection <= 5) || !(m_playerDisplayPokemon[playerSelection].getCurHealth() > 0)) && !m_menu->shouldClose())
            {
                onUpdate();
                m_menu->run();

                if (m_menu->leaveRequested())
                {
                    m_menu->clearRequestedData();
                    simulatePokemon(aiSwapCommand);
                    return;
                }
            }
            m_menu->clearRequestedData();
            m_menu->postRun();
                    

            SimulationCommand playerSwapCommand{};
            playerSwapCommand.type = SimulationType::POKEMON;
            playerSwapCommand.commander = SelectedUser::PLAYER;
            playerSwapCommand.selection1 = playerSelection;

            simulatePokemon(aiSwapCommand);
            simulatePokemon(playerSwapCommand);
            return;
        }
        
        simulatePokemon(aiSwapCommand);
    }
    else
    {
        logger->log(LogLevel::DEBUG, "Player pokemon and AI has fainted", "handleFaintSelection", "OldBattleSimulator");
        displayFaintMessage(SelectedUser::PLAYER);
        int pokemonIndex = m_displayPokemonIndex;
        m_menu->setRequestedData(&pokemonIndex);
        m_menu->setscene(MenuScene::BATTLE_ROSTER);
        m_menu->preRun();
        while (m_playerDisplayPokemon[pokemonIndex].getCurHealth() == 0 && !m_menu->shouldClose())
        {
            onUpdate();
            m_menu->run();
        }
        m_menu->clearRequestedData();
        m_menu->postRun();

        //TODO: Consider if AI has a pokemon to swap to. This may have already been considered
        SimulationCommand swapCommand{};
        swapCommand.type = SimulationType::POKEMON;
        swapCommand.commander = SelectedUser::PLAYER;
        swapCommand.selection1 = pokemonIndex;
        simulatePokemon(swapCommand);

        displayFaintMessage(SelectedUser::AI);
        swapCommand.type = SimulationType::POKEMON;
        swapCommand.commander = SelectedUser::AI;
        swapCommand.selection1 = m_opponentPokemonIndex + 1;

        simulatePokemon(swapCommand);
    }
}

void OldBattleSimulator::simulateAttack(SimulationCommand command)
{
    if (m_pokemonCaught)
        return;

    if (attackMissed(command))
    {
        std::cout << command.attackData.message << std::endl;

        renderDialogue(command.attackData.message, "", true);
        return;
    }

    if (command.attackData.message.size() > 0)
    {
        std::cout << command.attackData.message << std::endl;
        renderDialogue(command.attackData.message, "", true);
    }
    

    if (command.commander == SelectedUser::PLAYER)
    {
        
        dripDamage(SelectedUser::AI, command.attackData.damage);
    }
    else
    {
        //Drip Damage
        dripDamage(SelectedUser::PLAYER, command.attackData.damage);
    }


    if (command.attackData.effectiveness == EffectiveStatus::NOT_VERY)
    {
        std::cout << "It was not very effective" << std::endl;
        renderDialogue("It was not", "very effective", true);
    }
    else if (command.attackData.effectiveness == EffectiveStatus::SUPER)
    {
        std::cout << "It was super effective!" << std::endl;
        renderDialogue("It was", "super effective", true);
    }

    if (command.attackData.crit)
    {
        std::cout << "It was a critical hit" << std::endl;
        renderDialogue("It was a", "critical hit", true);
    }
}

void OldBattleSimulator::simulatePokemon(SimulationCommand command)
{
    if (command.commander == SelectedUser::PLAYER)
    {
        //TODO: Swap return text and send out text
        //TODO: Animation between
        m_displayPokemonIndex = command.selection1;
        m_playerPokemonIndex = m_displayPokemonIndex;
        m_p1moveset = m_playerDisplayPokemon[m_displayPokemonIndex].getMoveset();
        m_menu->reset(MenuOverlay::ATTACK_SELECT);
        m_menu->reset(MenuScene::BATTLE);
        updatePlayerAttacks();
        addToXpRecord();
        adjustPokemonDisplay(command.commander);
    }
    else
    {
        m_opponentPokemonIndex = command.selection1;
        adjustPokemonDisplay(SelectedUser::AI);
    }
}

void OldBattleSimulator::simulateItem(SimulationCommand command)
{
    if (command.itemData.pokeballData.isPokeball)
    {
        // Need to find out what frame to stop on based on the number of shakes
        // Play the animation up until that point
        // Pause after capture for music to finish playing post capture
        //  - Then continue animation to fade out

        int frameToStop = 107;
        if (command.itemData.pokeballData.shakes == 0)
            frameToStop = 66;
        else if (command.itemData.pokeballData.shakes == 1)
            frameToStop = 78;
        else if (command.itemData.pokeballData.shakes == 2)
            frameToStop = 87;

        Animation escapeAnimation = Animation::ESCAPE_POKEBALL;

        switch (command.itemData.id)    //TODO: Also set a variable for the leave animation here too
        {
        case ItemID::POKEBALL:
            m_animator->setAnimation(Animation::THROW_POKEBALL);
            break;
        case ItemID::GREATBALL:
            m_animator->setAnimation(Animation::THROW_GREATBALL);
            escapeAnimation = Animation::ESCAPE_GREATBALL;
            break;
        case ItemID::ULTRABALL:
            m_animator->setAnimation(Animation::THROW_ULTRABALL);
            escapeAnimation = Animation::ESCAPE_ULTRABALL;
            break;
        case ItemID::MASTERBALL:
            m_animator->setAnimation(Animation::THROW_MASTERBALL);
            escapeAnimation = Animation::ESCAPE_MASTERBALL;
            break;
        default:
            //TODO: Error
            system("pause");
            system("pause");
            break;
        }

        m_menu->setscene(MenuScene::BATTLE);
        m_menu->setOverlay(MenuOverlay::NONE);

        while (m_animator->animationPlaying() && m_animator->getFrameCount() != frameToStop && !m_menu->shouldClose())
        {
            //TODO: Add add pause for music
            //TODO: Shrink pokemon into pokeball
            BattleAnimations::wildPokemonIntoPokeball(m_animator->getFrameCount(), &m_opponentPokemonData);

            m_menu->renderMenu();
            m_animator->playAnimation();
            m_animator->updateRenderer();
        }

        if (m_animator->getFrameCount() == frameToStop)
        {
            m_animator->setAnimation(escapeAnimation);
            while (m_animator->animationPlaying() && !m_menu->shouldClose())
            {
                BattleAnimations::wildPokemonEscapePokeball(m_animator->getFrameCount(), &m_opponentPokemonData);
                m_menu->renderMenu();
                m_animator->playAnimation();
                m_animator->updateRenderer();
                //TODO: Expand pokemon animation
            }
        }

        for (int i = 0; i < command.itemData.pokeballData.shakes; i++)
        {
            std::cout << "Pokeball Shook " << i + 1 << " time(s)" << std::endl;  //TODO: Add s for multiples
            //renderDialogue("Pokeball Shook", std::to_string(i + 1) + " time", false);
        }

        if (command.itemData.pokeballData.caught)
        {
            std::cout << "Pokemon was caught!!!!\n";
            renderDialogue("The Wild " + m_opponentDisplayPokemon[m_opponentPokemonIndex].getName(), " was caught", true);

            m_pokemonCaught = true;
            //system("pause");
        }
        else
        {
            logger->log(LogLevel::DEBUG, "The Wild " + m_opponentDisplayPokemon[m_opponentPokemonIndex].getName() + " has escaped", "simulateItem", "OldBattleSimulator");
            std::cout << "The Wild " << m_opponentDisplayPokemon[m_opponentPokemonIndex].getName() << " has escaped" << std::endl;
            renderDialogue("The Wild " + m_opponentDisplayPokemon[m_opponentPokemonIndex].getName(), "has escaped", false);
            
            //system("pause");
            //TODO: Consider pause in text after text is displayed. Research this
        }



    }
    else
    {
        if (command.commander == SelectedUser::PLAYER)
        {
            for (int i = 0; i < command.itemData.healAmount; i++)
            {
                m_playerDisplayPokemon[command.selection2].adjustCurHealth(1);
            }
        }
        else
        {
            for (int i = 0; i < command.itemData.healAmount; i++)
            {
                m_opponentDisplayPokemon[command.selection2].adjustCurHealth(1);
            }
        }
    }

    //TODO: Implement status cure

    if (command.commander == SelectedUser::PLAYER)
    {
        m_player->removeItem(command.itemData.id);
        updatePlayerItems();
    }
    else
    {
        m_npt->NPT::removeItem(command.itemData.id);
    }
}

void OldBattleSimulator::simulateFlee(SimulationCommand command)
{
    if (command.selection1 == (int)true)
    {
        m_flee = true;
        std::cout << "Flee was successful\n";
        logger->log(LogLevel::DEBUG, "Flee was successful", "simulateFlee", "OldBattleSimulator");
        renderDialogue("Flee was successful", "", false);
        return;
    }
    std::cout << "Flee was unsuccessful\n";
    renderDialogue("Flee was unsuccessful", "", false);
}

void OldBattleSimulator::simulateStatus(SimulationCommand command)
{
    if (m_pokemonCaught)
        return;


    if (command.statusData.curedStatus != StatusID::NO_STATUS)
    {
        if (command.commander == SelectedUser::PLAYER)
        {
            if (getStatusFromID(command.statusData.curedStatus)->getData().type == StatusType::MAJOR)
                m_playerDisplayPokemon[m_playerPokemonIndex].removeMajorStatus();
            else
                m_playerDisplayPokemon[m_playerPokemonIndex].removeMinorStatus(command.statusData.curedStatus);
        }
        else
        {
            if (getStatusFromID(command.statusData.curedStatus)->getData().type == StatusType::MAJOR)
                m_opponentDisplayPokemon[m_opponentPokemonIndex].removeMajorStatus();
            else
                m_opponentDisplayPokemon[m_opponentPokemonIndex].removeMinorStatus(command.statusData.curedStatus);
        }


    }

    if (command.statusData.message.size() != 0)
    {
        std::cout << command.statusData.message << std::endl;
        renderDialogue(command.statusData.message, "", true);

        //system("pause");
    }

    StatusID id = command.statusData.statusGiven;

    if (id != StatusID::NO_STATUS)
    {
        if (command.statusData.recipient == SelectedUser::PLAYER)
            m_playerDisplayPokemon[m_playerPokemonIndex].applyMinorStatus(id, getStatusFromID(id)->getData().isBlocker, getStatusFromID(id)->getData().isEvasive, getStatusFromID(id)->getData().forcedAttackID);
        else
            m_opponentDisplayPokemon[m_opponentPokemonIndex].applyMinorStatus(id, getStatusFromID(id)->getData().isBlocker, getStatusFromID(id)->getData().isEvasive, getStatusFromID(id)->getData().forcedAttackID);
    }
    

    dripDamage(command.commander, command.statusData.damage);
}

void OldBattleSimulator::simulateStat(SimulationCommand command)
{
    if (command.statData.recipient == SelectedUser::PLAYER)
        m_playerDisplayPokemon[m_playerPokemonIndex].addBattleStats(command.statData.stats);
    else if (command.statData.recipient == SelectedUser::AI)
        m_opponentDisplayPokemon[m_opponentPokemonIndex].addBattleStats(command.statData.stats);
    else
    {
        logger->log(LogLevel::CRITICAL, "Unknown Selected User", "simulateStat", "OldBattleSimulator");
        logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
    }

    std::cout << command.statData.message << std::endl;
    renderDialogue(command.statData.message, "", true);
}

bool OldBattleSimulator::attackMissed(SimulationCommand command)
{
    int count = 0;
    std::string missed = "missed";

    for (size_t i = 0; i < command.attackData.message.size(); i++)
    {
        if (count == missed.size())
            return true;

        if (command.attackData.message.at(i) == missed.at(count))
        {
            count += 1;
            continue;
        }

        count = 0;
    }

    return false;
}

void OldBattleSimulator::handleFaintXP(SelectedUser user)
{
    if (user == SelectedUser::PLAYER)
    {
        removeXpRecord();
    }
    else if (user == SelectedUser::AI)
    {
        std::string faintMessage;
        if (m_npt == nullptr)
            faintMessage = "Wild " + m_opponentDisplayPokemon[m_opponentPokemonIndex].getName();
        else
            faintMessage = "Foes " + m_opponentDisplayPokemon[m_opponentPokemonIndex].getName();
        renderDialogue(faintMessage, "has fainted", true);


        grantEVs();
        grantXP();
    }
    else
    {
        handleFaintXP(SelectedUser::PLAYER);
        handleFaintXP(SelectedUser::AI);
    }
}

void OldBattleSimulator::dripDamage(SelectedUser pokemonToDamage, int value)
{
    if (pokemonToDamage == SelectedUser::PLAYER)
    {
        for (int i = 0; i < value; i++)
        {
            m_playerDisplayPokemon[m_playerPokemonIndex].adjustCurHealth(-1);
            adjustHealthPercentage(pokemonToDamage);
            onUpdate();
        }
    }
    else
    {
        for (int i = 0; i < value; i++)
        {
            m_opponentDisplayPokemon[m_opponentPokemonIndex].adjustCurHealth(-1);
            adjustHealthPercentage(pokemonToDamage);
            onUpdate();
        }
    }
}

void OldBattleSimulator::addToXpRecord()
{

    if (std::find(m_xpRecords[m_opponentPokemonIndex].begin(), m_xpRecords[m_opponentPokemonIndex].end(), m_playerPokemonIndex) == m_xpRecords[m_opponentPokemonIndex].end())
        m_xpRecords[m_opponentPokemonIndex].push_back(m_playerPokemonIndex);
}

void OldBattleSimulator::removeXpRecord()
{
    for (int i = 0; i < 6; i++)
    {
        if (std::find(m_xpRecords[i].begin(), m_xpRecords[i].end(), m_playerPokemonIndex) != m_xpRecords[i].end())
        {
            int recordIndex = 0;

            for (size_t x = 0; x < m_xpRecords[i].size(); x++)
            {
                if (m_xpRecords[i].at(x) == m_playerPokemonIndex)
                {
                    m_xpRecords[i].erase(m_xpRecords[i].begin() + x);
                    break;
                }
            }
        }
    }
}

void OldBattleSimulator::grantEVs()
{
    int evSplit = (int)m_xpRecords[m_opponentPokemonIndex].size();

    if (evSplit == 0)
        return;

    PokemonStats evReward{};
    Species opponentSpecies = m_opponentDisplayPokemon[m_opponentPokemonIndex].getSpecies();

    evReward.hp = (int)ceil(opponentSpecies.evYield.hp / (float)evSplit);
    evReward.speed = (int)ceil(opponentSpecies.evYield.speed / (float)evSplit);
    evReward.attack = (int)ceil(opponentSpecies.evYield.attack / (float)evSplit);
    evReward.defense = (int)ceil(opponentSpecies.evYield.defense / (float)evSplit);
    evReward.spAttack = (int)ceil(opponentSpecies.evYield.spAttack / (float)evSplit);
    evReward.spDefense = (int)ceil(opponentSpecies.evYield.spDefense / (float)evSplit);


    for (size_t i = 0; i < m_xpRecords[m_opponentPokemonIndex].size(); i++)
    {
        m_playerDisplayPokemon[m_xpRecords[m_opponentPokemonIndex].at(i)].gainEVs(evReward);
    }
}

void OldBattleSimulator::grantXP()
{
    if (m_xpRecords[m_opponentPokemonIndex].size() == 0)
        return;

    int b = m_opponentDisplayPokemon[m_opponentPokemonIndex].getSpecies().expYield;
    int L = m_opponentDisplayPokemon[m_opponentPokemonIndex].getLevel();
    float a = (m_npt == nullptr) ? 1.0f : 1.5f;
    float s = 1.0f / m_xpRecords[m_opponentPokemonIndex].size();

    int xpYield = int(((b * L) / 7.0f) * s * a);

    float dripCount = 0;
    float dripCountTarget = 0.05f;

    
    for (size_t i = 0; i < m_xpRecords[m_opponentPokemonIndex].size(); i++)
    {
        renderDialogue(m_playerDisplayPokemon[m_xpRecords[m_opponentPokemonIndex].at(i)].getName() + " has gained", std::to_string(xpYield) + " exp", true);

        for (int x = 0; x < xpYield; x++)
        {
            m_playerDisplayPokemon[m_xpRecords[m_opponentPokemonIndex].at(i)].gainXP();
            if (m_playerPokemonIndex == m_xpRecords[m_opponentPokemonIndex].at(i))
                adjustXPPercentage();

            dripCount = 0;
            while (dripCount < dripCountTarget && !m_menu->shouldClose())
            {
                m_menu->renderMenu();
                m_animator->updateRenderer();
                dripCount += m_timer->getDelta();
            }

            if (m_playerDisplayPokemon[m_xpRecords[m_opponentPokemonIndex].at(i)].readyToLevel())
            {

                if (m_playerPokemonIndex == m_xpRecords[m_opponentPokemonIndex].at(i))
                {
                    m_animator->setAnimation(Animation::XP_LEVEL_UP_UI);
                    while (m_animator->animationPlaying() && !m_menu->shouldClose())
                    {
                        m_menu->renderMenu();
                        m_animator->playAnimation();
                        m_animator->updateRenderer();
                    }
                    
                    m_animator->setAnimation(Animation::XP_GAIN);
                    while (m_animator->animationPlaying() && !m_menu->shouldClose())
                    {
                        m_menu->renderMenu();
                        m_animator->playAnimation();
                        m_animator->updateRenderer();
                    }

                    m_battleData.playerLevel = "Lv" + std::to_string(m_playerDisplayPokemon[m_xpRecords[m_opponentPokemonIndex].at(i)].getLevel() + 1);
                }

                levelPokemon(m_xpRecords[m_opponentPokemonIndex].at(i));
                evolvePokemon(m_xpRecords[m_opponentPokemonIndex].at(i));
                teachMove(m_xpRecords[m_opponentPokemonIndex].at(i));
                m_playerTestPokemon[m_xpRecords[m_opponentPokemonIndex].at(i)] = m_playerDisplayPokemon[m_xpRecords[m_opponentPokemonIndex].at(i)];
            }
        }
    }
    m_xpRecords[m_opponentPokemonIndex].clear();
}

void OldBattleSimulator::levelPokemon(int index)
{
    //TODO: Get Leveling Pokemon Name, Level and stats
    PokemonStats statIncrease = m_playerDisplayPokemon[index].levelUp();
    PokemonStats stats = m_playerDisplayPokemon[index].getStats();

    m_battleData.pokemonStatName = m_playerDisplayPokemon[index].getName();
    m_battleData.pokemonStatLevel = "Lv" + std::to_string(m_playerDisplayPokemon[index].getLevel());

    m_battleData.pokemonStatDifference = SharedString{ std::to_string(statIncrease.hp), std::to_string(statIncrease.attack), std::to_string(statIncrease.defense), std::to_string(statIncrease.spAttack),
                                                    std::to_string(statIncrease.spDefense), std::to_string(statIncrease.speed)};
    m_battleData.pokemonStatValue = SharedString{ std::to_string(stats.hp), std::to_string(stats.attack), std::to_string(stats.defense), std::to_string(stats.spAttack),
                                                    std::to_string(stats.spDefense), std::to_string(stats.speed) };


    m_menu->setOverlay(MenuOverlay::LEVEL_UP_STAT_CHANGE);

    float count = 0.0f;
    float target = 0.5f;

    while (count < target && !m_menu->shouldClose())
    {
        count += m_timer->getDelta();
        m_menu->renderMenu();
        m_animator->updateRenderer();
    }

    while (true && !m_menu->shouldClose())
    {
        if (m_input->anyButtonPressed())
            break;

        m_menu->renderMenu();
        m_animator->updateRenderer();
    }

    count = 0.0f;

    m_menu->setOverlay(MenuOverlay::LEVEL_UP_STAT_VALUE);

    while (count < target && !m_menu->shouldClose())
    {
        count += m_timer->getDelta();
        m_menu->renderMenu();
        m_animator->updateRenderer();
    }

    while (true && !m_menu->shouldClose())
    {
        if (m_input->anyButtonPressed())
            break;

        m_menu->renderMenu();
        m_animator->updateRenderer();
    }
}

void OldBattleSimulator::evolvePokemon(int index)
{
    if (m_playerDisplayPokemon[index].readyToEvolve())
        m_playerDisplayPokemon[index].evolve();
}

void OldBattleSimulator::teachMove(int index)
{
    bool moveSwapped = false;
    int newMove = m_playerDisplayPokemon[index].readyToLearnMove();
    if (newMove == NONE)
        return;

    if (m_playerDisplayPokemon[index].getMoveset().move1 == NONE)
    {
        m_playerDisplayPokemon[index].learnMove(MOVE_ONE, newMove, getAttackFromID(newMove)->getPP());
        moveSwapped = true;
    }
    else if (m_playerDisplayPokemon[index].getMoveset().move2 == NONE)
    {
        m_playerDisplayPokemon[index].learnMove(MOVE_TWO, newMove, getAttackFromID(newMove)->getPP());
        moveSwapped = true;
    }
    else if (m_playerDisplayPokemon[index].getMoveset().move3 == NONE)
    {
        m_playerDisplayPokemon[index].learnMove(MOVE_THREE, newMove, getAttackFromID(newMove)->getPP());
        moveSwapped = true;
    }
    else if (m_playerDisplayPokemon[index].getMoveset().move4 == NONE)
    {
        m_playerDisplayPokemon[index].learnMove(MOVE_FOUR, newMove, getAttackFromID(newMove)->getPP());
        moveSwapped = true;
    }

    if (moveSwapped)
    {
        if (index == m_displayPokemonIndex)
        {
            m_p1moveset = m_playerDisplayPokemon[index].getMoveset();
            updatePlayerAttacks();
        }
        return;
    }

    int option = 0;
    logger->log(LogLevel::DEBUG, "Replacing move", "teachMove", "OldBattleSimulator");
    std::cout << "Do you want to replace a move?\n1) Yes\n2) No\n" << std::endl;
    std::cin >> option;
    std::cin.clear();

    if (option == 2)
        return;

    option = NONE;

    m_menu->setRequestedData(&option);
    m_menu->setOverlay(MenuOverlay::ATTACK_SELECT);
    m_menu->preRun();
    while (option == NONE && !m_menu->shouldClose())
    {
        onUpdate();
        m_menu->run();
        if (m_menu->leaveRequested())
        {
            m_menu->clearRequestedData();
            return;
        }
    }
    m_menu->clearRequestedData();
    m_menu->postRun();

    if (!m_menu->leaveRequested())
    {
        m_playerDisplayPokemon[index].learnMove(option, newMove, getAttackFromID(newMove)->getPP());
        logger->log(LogLevel::DEBUG, "pokemon has learned new move id: " + std::to_string(newMove), "teachMove", "OldBattleSimulator");
        std::cout << "Pokemon has learned " << getAttackFromID(newMove)->getName() << std::endl;
        system("pause");
        std::cin >> option;
        std::cin.clear();
    }
}

void OldBattleSimulator::displayFaintMessage(SelectedUser user)
{


    if (user == SelectedUser::AI)
    {
        if (m_npt == nullptr)
        {
            renderDialogue("The wild " + m_opponentDisplayPokemon[m_opponentPokemonIndex].getName(), "has fainted", true);
        }
        else
        {
            renderDialogue("The foes " + m_opponentDisplayPokemon[m_opponentPokemonIndex].getName(), "has fainted", true);
        }
    }
    else
    {
        renderDialogue(m_playerDisplayPokemon[m_displayPokemonIndex].getName(), "has fainted", true);
    }


}

void OldBattleSimulator::reducePP(SelectedUser attacker, int move)
{
    if (move == NONE || move == MOVE_FIVE)
        return;

    switch (move)
    {
    case MOVE_ONE:
        if (attacker == SelectedUser::PLAYER)
        {
            m_p1moveset.move1pp -= 1;
            updatePP(attacker);
        }
        else
        {
            Moveset aiMoves = m_opponentDisplayPokemon[m_opponentPokemonIndex].getMoveset();
            aiMoves.move1pp -= 1;

            m_opponentDisplayPokemon[m_opponentPokemonIndex].setMoveset(aiMoves);
            updatePP(attacker);
        }
        break;
    case MOVE_TWO:
        if (attacker == SelectedUser::PLAYER)
        {
            m_p1moveset.move2pp -= 1;
            updatePP(attacker);
        }
        else
        {
            Moveset aiMoves = m_opponentDisplayPokemon[m_opponentPokemonIndex].getMoveset();
            aiMoves.move2pp -= 1;

            m_opponentDisplayPokemon[m_opponentPokemonIndex].setMoveset(aiMoves);
            updatePP(attacker);
        }
        break;
    case MOVE_THREE:
        if (attacker == SelectedUser::PLAYER)
        {
                m_p1moveset.move3pp -= 1;
                updatePP(attacker);
        }
        else
        {
            Moveset aiMoves = m_opponentDisplayPokemon[m_opponentPokemonIndex].getMoveset();
            aiMoves.move3pp -= 1;

            m_opponentDisplayPokemon[m_opponentPokemonIndex].setMoveset(aiMoves);
            updatePP(attacker);
        }
        break;
    case MOVE_FOUR:
        if (attacker == SelectedUser::PLAYER)
        {
                m_p1moveset.move4pp -= 1;
                updatePP(attacker);
        }
        else
        {
                Moveset aiMoves = m_opponentDisplayPokemon[m_opponentPokemonIndex].getMoveset();
                aiMoves.move4pp -= 1;

                m_opponentDisplayPokemon[m_opponentPokemonIndex].setMoveset(aiMoves);
                updatePP(attacker);
        }
        break;
    default:
        logger->log(LogLevel::CRITICAL, "error reducing PP", "reducePP", "OldBattleSimulator");
        logger->reportCriticalError(ErrorCodes::FAILED_PP_REDUCTION);
        break;
    }

    if (attacker == SelectedUser::PLAYER)
        updatePlayerAttacks();
}

void OldBattleSimulator::updatePP(SelectedUser user)
{
    if (user == SelectedUser::PLAYER)
    {
        m_playerDisplayPokemon[m_displayPokemonIndex].setMoveset(m_p1moveset);
        m_playerTestPokemon[m_displayPokemonIndex].setMoveset(m_p1moveset);
        updatePlayerAttacks();
    }
    else
    {
        m_opponentTestPokemon[m_opponentPokemonIndex].setMoveset(m_opponentDisplayPokemon[m_opponentPokemonIndex].getMoveset());
    }
}

void OldBattleSimulator::updatePlayerAttacks()
{
    m_playerAttacks.string1 = getAttackFromID(m_p1moveset.move1)->getName() + "   " + std::to_string(m_p1moveset.move1pp) + ":" + std::to_string(getAttackFromID(m_p1moveset.move1)->getPP());
    m_playerAttacks.string2 = getAttackFromID(m_p1moveset.move2)->getName() + "   " + std::to_string(m_p1moveset.move2pp) + ":" + std::to_string(getAttackFromID(m_p1moveset.move2)->getPP());
    m_playerAttacks.string3 = getAttackFromID(m_p1moveset.move3)->getName() + "   " + std::to_string(m_p1moveset.move3pp) + ":" + std::to_string(getAttackFromID(m_p1moveset.move3)->getPP());
    m_playerAttacks.string4 = getAttackFromID(m_p1moveset.move4)->getName() + "   " + std::to_string(m_p1moveset.move4pp) + ":" + std::to_string(getAttackFromID(m_p1moveset.move4)->getPP());
}

void OldBattleSimulator::renderDialogue(std::string topLine, std::string bottomLine, bool awaitClick)
{
    m_dialogueRenderer->setDialogue(topLine, bottomLine, awaitClick, true);

    while (m_dialogueRenderer->rendereringDialogue() && !m_menu->shouldClose())
    {
        m_dialogueRenderer->renderDialogue();
        m_animator->updateRenderer();
    }
}

void OldBattleSimulator::resetMenu()
{
    //TODO: Attack, Items, Pokemon all need to be set back to 0 index. So that we arent starting on the wrong move. Same with the main menu. We want it to start on attack
    m_hoverIndex = -1;
    m_menu->setCanLeave(true);
    m_menu->clearScenes();
    m_menu->setscene(MenuScene::BATTLE);
    m_menu->setOverlay(MenuOverlay::BATTLE_OPTIONS);
    m_menuCommand = SimulationCommand{};
}

void OldBattleSimulator::adjustPokemonDisplay(SelectedUser user)
{
    if (user == SelectedUser::PLAYER)
    {
        m_playerPokemonData.dynamicImage = pokemonBackTexture(m_playerDisplayPokemon[m_playerPokemonIndex].getSpecies().name);
        //battleData.playerTexture = pokemonBackTexture(m_playerDisplayPokemon[m_playerPokemonIndex].getSpecies().name);
        m_battleData.playerName = m_playerDisplayPokemon[m_playerPokemonIndex].getName();
        m_battleData.maxHP = std::to_string(m_playerDisplayPokemon[m_playerPokemonIndex].getStats().hp);
        m_battleData.playerLevel = "Lv" + std::to_string(m_playerDisplayPokemon[m_playerPokemonIndex].getLevel());

        m_battleData.botLine = m_playerDisplayPokemon[m_playerPokemonIndex].getName() + " do";

        adjustHealthPercentage(user);
        adjustXPPercentage();
    }
    else
    {
        m_opponentPokemonData.dynamicImage = pokemonFrontTexture(m_opponentTestPokemon[m_opponentPokemonIndex].getSpecies().name);
        //battleData.opponentTexture = pokemonFrontTexture(m_opponentTestPokemon[m_opponentPokemonIndex].getSpecies().name);
        m_battleData.opponentName = m_opponentTestPokemon[m_opponentPokemonIndex].getName();
        m_battleData.opponentLevel = "Lv" + std::to_string(m_opponentTestPokemon[m_opponentPokemonIndex].getLevel());
        adjustHealthPercentage(user);
    }
}

void OldBattleSimulator::adjustHealthPercentage(SelectedUser user)
{
    float maxPlayPercent = 23.9f;
    float maxOppPercent = 17.4f;

    if (user == SelectedUser::PLAYER)
    {
        m_battleData.playerCurHPPercent = maxPlayPercent * ((float)m_playerDisplayPokemon[m_displayPokemonIndex].getCurHealth() / (float)m_playerDisplayPokemon[m_displayPokemonIndex].getStats().hp);
        m_battleData.currentHP = std::to_string(m_playerDisplayPokemon[m_playerPokemonIndex].getCurHealth());
    }
    else
    {
        m_battleData.opponentCurHPPercent = maxOppPercent * ((float)m_opponentDisplayPokemon[m_opponentPokemonIndex].getCurHealth() / (float)m_opponentDisplayPokemon[m_opponentPokemonIndex].getStats().hp);
    }
}

void OldBattleSimulator::adjustXPPercentage()
{
    float maxPercent = 37.9f;
    m_battleData.playerXPPercent = maxPercent * ((float)m_playerDisplayPokemon[m_displayPokemonIndex].getCurXP() / (float)m_playerDisplayPokemon[m_displayPokemonIndex].getXPNeeded());
}

bool OldBattleSimulator::validItemSelection(int selection)
{
    if (selection == 0 && m_playerBattleItems.itemName.string1 == "NONE")
        return false;
    else if (selection == 1 && m_playerBattleItems.itemName.string1 == "NONE")
        return false;
    else if (selection == 2 && m_playerBattleItems.itemName.string2 == "NONE")
        return false;
    else if (selection == 3 && m_playerBattleItems.itemName.string3 == "NONE")
        return false;
    else if (selection == 4 && m_playerBattleItems.itemName.string4 == "NONE")
        return false;
    else if (selection == 5 && m_playerBattleItems.itemName.string5 == "NONE")
        return false;

    return true;
}

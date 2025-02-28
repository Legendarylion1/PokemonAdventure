#include "BattleDataSimulator.h"

BattleDataSimulator::BattleDataSimulator()
{
}

void BattleDataSimulator::setup(Trainer* trainer, Menu* menu, Renderer* renderer, DialogueRenderer* dialogueRenderer, AnimationStream* animator, BattleMenuGraphics* battleMenuGraphics, Timer* timer, int* playerPokemonIndex, int* opponentPokemonIndex)
{
    m_trainer = trainer;
    m_menu = menu;
    m_renderer = renderer;
    m_dialogueRenderer = dialogueRenderer;
    m_animator = animator;
    m_battleMenuGraphics = battleMenuGraphics;
    m_playerPokemonIndex = playerPokemonIndex;
    m_opponentPokemonIndex = opponentPokemonIndex;
    m_timer = timer;
}

void BattleDataSimulator::setOpponent(NPT* npt)
{
    m_npt = npt;
    m_wildPokemon = nullptr;
}

void BattleDataSimulator::setOpponent(Pokemon* pokemon)
{
    m_npt = nullptr;
    m_wildPokemon = pokemon;
}

void BattleDataSimulator::runSimulation(std::vector<SimulationCommand> commands)
{
    if (commands.size() == 0)
        return;

    setupPokemon();

    for (const SimulationCommand& command : commands)
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
}

void BattleDataSimulator::simulateAttack(SimulationCommand command)
{

    if (attackMissed(command))
    {
        //std::cout << command.attackData.message << std::endl;

        renderDialogue(command.attackData.message, "", true);
        return;
    }
    
    if (command.attackData.message.size() > 0)
        renderDialogue(command.attackData.message, "", true);

    //TODO: Put attack animation here. Maybe blend the take damage animations. IDK just yet. Research this

    if (command.attackData.damage > 0)
    {
        if (command.commander == SelectedUser::PLAYER)
            pokemonTakeDamageAnimation(SelectedUser::AI);
        else
            pokemonTakeDamageAnimation(SelectedUser::PLAYER);
    }

    if (command.commander == SelectedUser::PLAYER)
        dripDamage(SelectedUser::AI, command.attackData.damage);
    else
        dripDamage(SelectedUser::PLAYER, command.attackData.damage);


    if (command.attackData.effectiveness == EffectiveStatus::NOT_VERY)
    {
        //std::cout << "It was not very effective" << std::endl;
        renderDialogue("It was not", "very effective", true);
    }
    else if (command.attackData.effectiveness == EffectiveStatus::SUPER)
    {
        //std::cout << "It was super effective!" << std::endl;
        renderDialogue("It was", "super effective", true);
    }

    if (command.attackData.crit)
    {
        //std::cout << "It was a critical hit" << std::endl;
        renderDialogue("It was a", "critical hit", true);
    }
}

void BattleDataSimulator::simulatePokemon(SimulationCommand command)
{
    if (command.commander == SelectedUser::PLAYER)
    {
        //TODO: Swap return text and send out text
        //TODO: Animation between

        withdrawPlayerPokemon();

        *m_playerPokemonIndex = command.selection1;
        sendOutPlayerPokemon();
        m_menu->reset(MenuOverlay::ATTACK_SELECT);
        
    }
    else
    {
        *m_opponentPokemonIndex = command.selection1;

        m_battleMenuGraphics->updatePokemonDisplay(SelectedUser::AI);
    }

    setupPokemon();
}

void BattleDataSimulator::simulateItem(SimulationCommand command)
{
    if (command.itemData.pokeballData.isPokeball)
    {
        throwPokeball(command);
    }
    else
    {
        dripHeal(command.commander, command.itemData.healAmount);

        renderDialogue(command.itemData.message, "", true);
    }

    //TODO: Implement status cure
}

void BattleDataSimulator::simulateFlee(SimulationCommand command)
{
    if (command.selection1 == (int)true)
    {
        logger->log(LogLevel::DEBUG, "Flee was successful", "simulateFlee", "OldBattleSimulator");
        renderDialogue("Flee was successful", "", true);
        return;
    }

    if (m_npt != nullptr)
        renderDialogue("You can't flee a", "trainer battle", true);
    else
        renderDialogue("Flee was unsuccessful", "", true);
}

void BattleDataSimulator::simulateStatus(SimulationCommand command)
{

    if (command.statusData.curedStatus != StatusID::NO_STATUS)
    {
        if (command.commander == SelectedUser::PLAYER)
        {
            if (getStatusFromID(command.statusData.curedStatus)->getData().type == StatusType::MAJOR)
            {
                m_playerPokemon->removeMajorStatus();
                m_battleMenuGraphics->updatePokemonDisplay(command.commander);
            }
            else
                m_playerPokemon->removeMinorStatus(command.statusData.curedStatus);

            
        }
        else
        {
            if (getStatusFromID(command.statusData.curedStatus)->getData().type == StatusType::MAJOR)
            {
                m_opponentPokemon->removeMajorStatus();
                m_battleMenuGraphics->updatePokemonDisplay(command.commander);
            }
            else
                m_opponentPokemon->removeMinorStatus(command.statusData.curedStatus);
        }


    }

    if (command.statusData.message.size() != 0)
    {
        //std::cout << command.statusData.message << std::endl;
        renderDialogue(command.statusData.message, "", true);
    }

    StatusID id = command.statusData.statusGiven;

    if (id != StatusID::NO_STATUS)
    {

        if (command.statusData.recipient == SelectedUser::PLAYER)
        {
            if (getStatusFromID(id)->getData().type == StatusType::MAJOR)
            {
                //TODO: Simulate Major Status Application With Animation
                m_playerPokemon->applyMajorStatus(id, getStatusFromID(id)->getData().isBlocker);
                m_battleMenuGraphics->updatePokemonDisplay(command.commander);
            }
            else
                m_playerPokemon->applyMinorStatus(id, getStatusFromID(id)->getData().isBlocker, getStatusFromID(id)->getData().isEvasive, getStatusFromID(id)->getData().forcedAttackID);
        
            
        }
        else
        {
            if (getStatusFromID(id)->getData().type == StatusType::MAJOR)
            {
                //TODO: Simulate Major Status Application
                m_opponentPokemon->applyMajorStatus(id, getStatusFromID(id)->getData().isBlocker);
                m_battleMenuGraphics->updatePokemonDisplay(command.commander);
            }
            else
                m_opponentPokemon->applyMinorStatus(id, getStatusFromID(id)->getData().isBlocker, getStatusFromID(id)->getData().isEvasive, getStatusFromID(id)->getData().forcedAttackID);
        
        }
    }

    if (command.commander == SelectedUser::PLAYER && m_playerPokemon->getCurHealth() != 0)
        dripDamage(command.commander, command.statusData.damage);
    else if (command.commander == SelectedUser::AI && m_opponentPokemon->getCurHealth() != 0)
        dripDamage(command.commander, command.statusData.damage);
}

void BattleDataSimulator::simulateStat(SimulationCommand command)
{
    if (command.statData.recipient == SelectedUser::PLAYER)
        m_playerPokemon->addBattleStats(command.statData.stats);
    else if (command.statData.recipient == SelectedUser::AI)
    {
        m_opponentPokemon->addBattleStats(command.statData.stats);
    }
    else
    {
        logger->log(LogLevel::CRITICAL, "Unknown Selected User", "simulateStat", "OldBattleSimulator");
        logger->reportCriticalError(ErrorCodes::UNHANDLED_ENUM);
    }

    std::cout << command.statData.message << std::endl;
    renderDialogue(command.statData.message, "", true);
}

bool BattleDataSimulator::attackMissed(SimulationCommand command)
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

void BattleDataSimulator::dripDamage(SelectedUser pokemonToDamage, int value)
{
    float dripCount = 0;

    if (pokemonToDamage == SelectedUser::PLAYER)
    {
        
        for (int i = 0; i < value; i++)
        {
            m_playerPokemon->adjustCurHealth(-1);
            m_battleMenuGraphics->updateHealthPercentage(pokemonToDamage);
           manageDripRate(m_damageDripRate);
        }

        if (m_playerPokemon->getCurHealth() == 0)
            faintPokemon(pokemonToDamage);
    }
    else
    {
        for (int i = 0; i < value; i++)
        {
            m_opponentPokemon->adjustCurHealth(-1);
            m_battleMenuGraphics->updateHealthPercentage(pokemonToDamage);
            manageDripRate(m_damageDripRate);
        }
        
        if (m_opponentPokemon->getCurHealth() == 0)
            faintPokemon(pokemonToDamage);
    }
   
}

void BattleDataSimulator::dripHeal(SelectedUser pokemonToHeal, int value)
{
    if (pokemonToHeal == SelectedUser::PLAYER)
    {
        for (int i = 0; i < value; i++)
        {
            m_playerPokemon->adjustCurHealth(1);
            m_battleMenuGraphics->updateHealthPercentage(pokemonToHeal);
            manageDripRate(m_healDripRate);
        }
    }
    else
    {
        for (int i = 0; i < value; i++)
        {
            m_opponentPokemon->adjustCurHealth(1);
            m_battleMenuGraphics->updateHealthPercentage(pokemonToHeal);
            manageDripRate(m_healDripRate);
        }
    }
}

void BattleDataSimulator::renderDialogue(std::string topLine, std::string bottomLine, bool awaitClick)
{
    m_dialogueRenderer->setDialogue(topLine, bottomLine, awaitClick, true);

    while (m_dialogueRenderer->rendereringDialogue())
    {
        if (m_menu->shouldClose())
            break;

        m_dialogueRenderer->renderDialogue();
        m_animator->updateRenderer();
    }
}

void BattleDataSimulator::throwPokeball(SimulationCommand command)
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

    while (m_animator->animationPlaying() && m_animator->getFrameCount() != frameToStop)
    {
        if (m_menu->shouldClose())
            break;

        //TODO: Add add pause for music
        //TODO: Shrink pokemon into pokeball
        BattleAnimations::wildPokemonIntoPokeball(m_animator->getFrameCount(), m_battleMenuGraphics->getOpponentRenderData());

        m_menu->renderMenu();
        m_animator->stream();
        m_animator->updateRenderer();
    }

    m_animator->stopAnimation();

    if (m_animator->getFrameCount() == frameToStop)
    {
        m_animator->setAnimation(escapeAnimation);
        while (m_animator->animationPlaying())
        {
            if (m_menu->shouldClose())
                break;

            BattleAnimations::wildPokemonEscapePokeball(m_animator->getFrameCount(), m_battleMenuGraphics->getOpponentRenderData());
            m_menu->renderMenu();
            m_animator->stream();
            m_animator->updateRenderer();
            //TODO: Expand pokemon animation
        }
        m_animator->stopAnimation();
    }

    for (int i = 0; i < command.itemData.pokeballData.shakes; i++)
    {
        //std::cout << "Pokeball Shook " << i + 1 << " time(s)" << std::endl;  //TODO: Add s for multiples
        //renderDialogue("Pokeball Shook", std::to_string(i + 1) + " time", false);
    }

    if (command.itemData.pokeballData.caught)
    {
        //std::cout << "Pokemon was caught!!!!\n";
        renderDialogue("The Wild " + m_opponentPokemon->getName(), " was caught", true);

        //system("pause");
    }
    else
    {
        logger->log(LogLevel::DEBUG, "The Wild " + m_opponentPokemon->getName() + " has escaped", "simulateItem", "OldBattleSimulator");
        //std::cout << "The Wild " << m_opponentPokemon->getName() << " has escaped" << std::endl;
        renderDialogue("The Wild " + m_opponentPokemon->getName(), "has escaped", false);

        //system("pause");
        //TODO: Consider pause in text after text is displayed. Research this
    }
}

void BattleDataSimulator::withdrawPlayerPokemon()
{
    for (int i = 0; i < 15; i++)
    {
        float count = 0.0f;
        float target = 0.1f;

        while (count < target)
        {
            if (m_menu->shouldClose())
                break;

            BattleAnimations::playerPokemonWithdraw(i, m_battleMenuGraphics->getPlayerRenderData());

            m_menu->renderMenu();
            m_animator->updateRenderer();
            count += m_timer->getDelta();
        }
    }
}

void BattleDataSimulator::sendOutPlayerPokemon()
{
    m_battleMenuGraphics->updatePokemonDisplay(SelectedUser::PLAYER);

    for (int i = 0; i < 16; i++)
    {
        float count = 0.0f;
        float target = 0.1f;

        while (count < target)
        {
            if (m_menu->shouldClose())
                break;

            BattleAnimations::sendOutPlayerPokemon(i, m_battleMenuGraphics->getPlayerRenderData());

            m_menu->renderMenu();
            m_animator->updateRenderer();
            count += m_timer->getDelta();
        }
    }
}

void BattleDataSimulator::pokemonTakeDamageAnimation(SelectedUser user)
{
    if (user == SelectedUser::PLAYER)
    {
        for (int i = 0; i < 9; i++)
        {
            float count = 0.0f;
            float target = 0.05f;

            while (count < target)
            {
                if (m_menu->shouldClose())
                    break;

                BattleAnimations::playerPokemonTakeDamage(i, m_battleMenuGraphics->getPlayerRenderData());

                m_menu->renderMenu();
                m_animator->updateRenderer();
                count += m_timer->getDelta();
            }
        }

    }
    else
    {
        for (int i = 0; i < 9; i++)
        {
            float count = 0.0f;
            float target = 0.05f;

            while (count < target)
            {
                if (m_menu->shouldClose())
                    break;

                BattleAnimations::opponentPokemonTakeDamage(i, m_battleMenuGraphics->getOpponentRenderData());

                m_menu->renderMenu();
                m_animator->updateRenderer();
                count += m_timer->getDelta();
            }
        }
    }
}

void BattleDataSimulator::faintPokemon(SelectedUser user)
{
    if (user == SelectedUser::PLAYER)
    {

        for (int i = 0; i < 15; i++)
        {

            float count = 0.0f;
            float target = 0.1f;

            while (count < target)
            {
                if (m_menu->shouldClose())
                    break;

                BattleAnimations::playerPokemonFaint(i, m_battleMenuGraphics->getPlayerRenderData());

                m_menu->renderMenu();
                m_animator->updateRenderer();
                count += m_timer->getDelta();
            }

        }
    }
    else
    {
        for (int i = 0; i < 15; i++)
        {

            float count = 0.0f;
            float target = 0.1f;

            while (count < target)
            {
                if (m_menu->shouldClose())
                    break;

                BattleAnimations::opponentPokemonFaint(i, m_battleMenuGraphics->getOpponentRenderData());
                m_menu->renderMenu();
                m_animator->updateRenderer();
                count += m_timer->getDelta();
            }

        }
    }
}

void BattleDataSimulator::manageDripRate(float dripRate)
{
    float dripCount = 0;
    float rate = dripRate;

    while (dripCount < rate)
    {
        if (m_menu->shouldClose())
            break;

        m_menu->renderMenu();
        m_animator->updateRenderer();
        dripCount += m_timer->getDelta();
    }
}

void BattleDataSimulator::setupPokemon()
{
    m_menu->setscene(MenuScene::BATTLE);
    m_menu->setOverlay(MenuOverlay::NONE);

    m_playerPokemon = &m_trainer->getRoster()[*m_playerPokemonIndex];

    m_opponentPokemon = m_wildPokemon;

    if (m_npt != nullptr)
        m_opponentPokemon = &m_npt->getRoster()[*m_opponentPokemonIndex];
}

void BattleDataSimulator::onUpdate()
{
    m_menu->renderMenu();
    m_animator->updateRenderer();
}

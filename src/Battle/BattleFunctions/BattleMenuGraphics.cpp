#include "BattleMenuGraphics.h"

void BattleMenuGraphics::setup(Trainer* trainer, Menu* menu, int* playerPokemonIndex, int* opponentPokemonIndex, RosterDisplayData* rosterData)
{
	m_trainer = trainer;
	m_menu = menu;

	m_playerPokemonIndex = playerPokemonIndex;
	m_opponentPokemonIndex = opponentPokemonIndex;

    m_rosterData = rosterData;

    m_playerPokemonData.deleteWithScene = false;
    m_opponentPokemonData.deleteWithScene = false;

	//m_menu->setupBattleData(&m_playerMoves, nullptr, m_rosterData, &m_playerBattleItems, &m_battleData, &m_playerPokemonData, &m_opponentPokemonData, &m_learnMoveData);      //TODO: REMOVE
    MenuSetup::setupBattleData(menu, &m_playerMoves, nullptr, m_rosterData, &m_playerBattleItems, &m_battleData, &m_playerPokemonData, &m_opponentPokemonData, &m_learnMoveData);
}

void BattleMenuGraphics::setOpponent(NPT* npt)
{
	m_npt = npt;
    m_wildPokemon = nullptr;

    m_playerPokemonData = { 25.5f, (253.5f / 563.0f) * 100.0f, 20.0f * (9.0f / 16.0f), 20.0f };
    m_opponentPokemonData = { 74.4f, (443.0f / 563.0f) * 100.0f, 10.0f, 10.0f * (16.0f / 9.0f) };
}

void BattleMenuGraphics::setOpponent(Pokemon* pokemon)
{
	m_npt = nullptr;
	m_wildPokemon = pokemon;
                                    
    m_playerPokemonData = { 25.5f, (253.5f / 563.0f) * 100.0f, 20.0f * (9.0f / 16.0f), 20.0f};
    m_opponentPokemonData = { 74.4f, (443.0f / 563.0f) * 100.0f, 10.0f, 10.0f * (16.0f / 9.0f)};
}

void BattleMenuGraphics::updateAllGraphics(int itemWindowDisposition)
{
	updateMoves();
	updateItemList(itemWindowDisposition);
	updateRosterList();
	updatePokemonStats();

    updatePokemonDisplay(SelectedUser::PLAYER);
    updatePokemonDisplay(SelectedUser::AI);
    updateHealthPercentage(SelectedUser::PLAYER);
    updateHealthPercentage(SelectedUser::AI);
    updateXPPercentage();
}

void BattleMenuGraphics::updateMoves()
{
	Moveset p1Moveset = m_trainer->getRoster()[*m_playerPokemonIndex].getMoveset();

	m_playerMoves.string1 = getAttackFromID(p1Moveset.move1)->getName() + "   " + std::to_string(p1Moveset.move1pp) + ":" + std::to_string(getAttackFromID(p1Moveset.move1)->getPP());
	m_playerMoves.string2 = getAttackFromID(p1Moveset.move2)->getName() + "   " + std::to_string(p1Moveset.move2pp) + ":" + std::to_string(getAttackFromID(p1Moveset.move2)->getPP());
	m_playerMoves.string3 = getAttackFromID(p1Moveset.move3)->getName() + "   " + std::to_string(p1Moveset.move3pp) + ":" + std::to_string(getAttackFromID(p1Moveset.move3)->getPP());
	m_playerMoves.string4 = getAttackFromID(p1Moveset.move4)->getName() + "   " + std::to_string(p1Moveset.move4pp) + ":" + std::to_string(getAttackFromID(p1Moveset.move4)->getPP());
}

void BattleMenuGraphics::updateItemList(int itemWindowDisposition)
{
    int count = 0;
    int indexCount = 0;

    for (auto i = m_trainer->getItemStorage()->getBattleItems()->begin(); i != m_trainer->getItemStorage()->getBattleItems()->end(); i++)
    {
        if (indexCount != itemWindowDisposition)
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
            m_playerBattleItems.itemTexture.string1 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
            break;
        case 1:
            formatRosterData(&m_playerBattleItems.itemName.string2, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string2 = "x" + std::to_string(i->second);
            m_playerBattleItems.itemTexture.string2 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
            break;
        case 2:
            formatRosterData(&m_playerBattleItems.itemName.string3, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string3 = "x" + std::to_string(i->second);
            m_playerBattleItems.itemTexture.string3 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
            break;
        case 3:
            formatRosterData(&m_playerBattleItems.itemName.string4, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string4 = "x" + std::to_string(i->second);
            m_playerBattleItems.itemTexture.string4 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
            break;
        case 4:
            formatRosterData(&m_playerBattleItems.itemName.string5, getItemFromID(i->first)->getName());
            m_playerBattleItems.itemAmount.string5 = "x" + std::to_string(i->second);
            m_playerBattleItems.itemTexture.string5 = g_itemTextureLocations[getItemFromID(i->first)->getID()];
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
            m_playerBattleItems.itemTexture.string1 = "";
            break;
        case 1:
            formatRosterData(&m_playerBattleItems.itemName.string2, "NONE");
            m_playerBattleItems.itemAmount.string2 = "";
            m_playerBattleItems.itemTexture.string2 = "";
            break;
        case 2:
            formatRosterData(&m_playerBattleItems.itemName.string3, "NONE");
            m_playerBattleItems.itemAmount.string3 = "";
            m_playerBattleItems.itemTexture.string3 = "";
            break;
        case 3:
            formatRosterData(&m_playerBattleItems.itemName.string4, "NONE");
            m_playerBattleItems.itemAmount.string4 = "";
            m_playerBattleItems.itemTexture.string4 = "";
            break;
        case 4:
            formatRosterData(&m_playerBattleItems.itemName.string5, "NONE");
            m_playerBattleItems.itemAmount.string5 = "";
            m_playerBattleItems.itemTexture.string5 = "";
            break;
        }
    }
}

void BattleMenuGraphics::updateRosterList()
{
	updateDisplayPokemon(m_trainer, m_rosterData);
}

void BattleMenuGraphics::updatePokemonStats()
{
	updateDisplayPokemonStats(&m_prevoiusRosterHoverIndex, m_trainer, m_menu->getButtonIndex(), m_rosterData);
}

void BattleMenuGraphics::updateLevelUpStats(std::string name, std::string level, SharedString statDifference, SharedString statValue)
{
    m_battleData.pokemonStatName = name;
    m_battleData.pokemonStatLevel = level;
    m_battleData.pokemonStatDifference = statDifference;
    m_battleData.pokemonStatValue = statValue;
}

void BattleMenuGraphics::updatePokemonDisplay(SelectedUser user)
{
    if (user == SelectedUser::PLAYER)
    {
        Pokemon playerPokemon = m_trainer->getRoster()[*m_playerPokemonIndex];

        m_playerPokemonData.dynamicImage = pokemonBackTexture(playerPokemon.getSpecies().name);
        m_battleData.playerName = playerPokemon.getName();
        m_battleData.maxHP = std::to_string(playerPokemon.getStats().hp);
        m_battleData.playerLevel = "Lv" + std::to_string(playerPokemon.getLevel());

        m_battleData.botLine = playerPokemon.getName() + " do"; //TODO: See if this is used

        m_battleData.playerMajorStatusTexture = "";
        if (playerPokemon.getMajorStatus()->id != StatusID::NO_STATUS)
            m_battleData.playerMajorStatusTexture = g_majorStatusTextureLocations[playerPokemon.getMajorStatus()->id];

        updateHealthPercentage(user);
        updateXPPercentage();
    }
    else
    {
        Pokemon opponentPokemon;

        if (m_wildPokemon != nullptr) 
            opponentPokemon = *m_wildPokemon;
        else
            opponentPokemon = m_npt->getRoster()[*m_opponentPokemonIndex];

        m_opponentPokemonData.dynamicImage = pokemonFrontTexture(opponentPokemon.getSpecies().name);
        m_battleData.opponentName = opponentPokemon.getName();
        m_battleData.opponentLevel = "Lv" + std::to_string(opponentPokemon.getLevel());

        m_battleData.opponentMajorStatusTexture = "";
        if (opponentPokemon.getMajorStatus()->id != StatusID::NO_STATUS)
            m_battleData.opponentMajorStatusTexture = g_majorStatusTextureLocations[opponentPokemon.getMajorStatus()->id];

        updateHealthPercentage(user);
    }
}

void BattleMenuGraphics::updateHealthPercentage(SelectedUser user)
{
    float maxPlayPercent = 23.9f;
    float maxOppPercent = 17.4f;

    if (user == SelectedUser::PLAYER)
    {
        Pokemon playerPokemon = m_trainer->getRoster()[*m_playerPokemonIndex];

        m_battleData.playerCurHPPercent = maxPlayPercent * ((float)playerPokemon.getCurHealth() / (float)playerPokemon.getStats().hp);
        m_battleData.currentHP = std::to_string(playerPokemon.getCurHealth());
    }
    else
    {
        Pokemon opponentPokemon;

        if (m_wildPokemon != nullptr)
            opponentPokemon = *m_wildPokemon;
        else
            opponentPokemon = m_npt->getRoster()[*m_opponentPokemonIndex];

        if (m_npt != nullptr)
            opponentPokemon = m_npt->getRoster()[*m_opponentPokemonIndex];

        m_battleData.opponentCurHPPercent = maxOppPercent * ((float)opponentPokemon.getCurHealth() / (float)opponentPokemon.getStats().hp);
    }
}

void BattleMenuGraphics::updateXPPercentage()
{
    float maxPercent = 37.9f;
    Pokemon playerPokemon = m_trainer->getRoster()[*m_playerPokemonIndex];

    m_battleData.playerXPPercent = maxPercent * ((float)playerPokemon.getCurXP() / (float)playerPokemon.getXPNeeded());
}

void BattleMenuGraphics::updateLearnMoveScene(int pokemonIndex, int hoverIndex, int newAttackID)
{
    if (hoverIndex == m_prevoiusLearnMoveHoverIndex)
        return;

    m_prevoiusLearnMoveHoverIndex = hoverIndex;
    Moveset moveset = m_trainer->getRoster()[pokemonIndex].getMoveset();
    int displayAttackIndex = NONE;

    m_learnMoveData.pokemonName = m_trainer->getRoster()[pokemonIndex].getName();
    m_learnMoveData.pokemonType1TextureLocation = g_typeTextureLocations[m_trainer->getRoster()[pokemonIndex].getSpecies().type1];
    m_learnMoveData.pokemonType2TextureLocation = g_typeTextureLocations[m_trainer->getRoster()[pokemonIndex].getSpecies().type2];
    m_learnMoveData.pokemonImageTextureLocation = pokemonFrontTexture(m_trainer->getRoster()[pokemonIndex].getSpecies().name);

    formatMoveStringData(&m_learnMoveData.move1, moveset.move1, moveset.move1pp);
    formatMoveStringData(&m_learnMoveData.move2, moveset.move2, moveset.move2pp);
    formatMoveStringData(&m_learnMoveData.move3, moveset.move3, moveset.move3pp);
    formatMoveStringData(&m_learnMoveData.move4, moveset.move4, moveset.move4pp);
    formatMoveStringData(&m_learnMoveData.newMove, newAttackID, getAttackFromID(newAttackID)->getPP());

    m_learnMoveData.move1OutlineVisiblity = false;
    m_learnMoveData.move2OutlineVisiblity = false;
    m_learnMoveData.move3OutlineVisiblity = false;
    m_learnMoveData.move4OutlineVisiblity = false;
    m_learnMoveData.newMoveOutlineVisiblity = false;

    switch (hoverIndex)
    {
    case 0:
        displayAttackIndex = moveset.move1;
        m_learnMoveData.move1OutlineVisiblity = true;
        break;
    case 1:
        displayAttackIndex = moveset.move2;
        m_learnMoveData.move2OutlineVisiblity = true;
        break;
    case 2:
        displayAttackIndex = moveset.move3;
        m_learnMoveData.move3OutlineVisiblity = true;
        break;
    case 3:
        displayAttackIndex = moveset.move4;
        m_learnMoveData.move4OutlineVisiblity = true;
        break;
    case 4:
        displayAttackIndex = newAttackID;
        m_learnMoveData.newMoveOutlineVisiblity = true;
        break;
    default:
        break;
    }

    Attack* displayAttack = getAttackFromID(displayAttackIndex);

    m_learnMoveData.power = std::to_string(displayAttack->getPower());
    m_learnMoveData.accuracy = std::to_string(displayAttack->getAccuracy());
    m_learnMoveData.description = displayAttack->getDescription();
}

void BattleMenuGraphics::formatMoveStringData(MoveStringData* moveData, int attackID, int currentPP)
{
    Attack* attack = nullptr;
    MoveStringData* move = nullptr;

    attack = getAttackFromID(attackID);
    move = moveData;
    move->currentPP = std::to_string(currentPP);

    if (attack->getName() != getAttackFromID(NONE)->getName())
    {
        move->moveName = attack->getName();
        move->maxPP = std::to_string(attack->getPP());
        move->moveTypeTextureLocation = g_typeTextureLocations[attack->getType()];
    }
    else
    {
        move->moveName = "NONE";
        move->currentPP = "0";
        move->maxPP = "NONE";
        move->moveTypeTextureLocation = "";
    }
}


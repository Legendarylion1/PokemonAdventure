#include "PokeMart.h"

PokeMart::PokeMart(MapHandler* handler, Trainer* player, Menu* menu, bool buyBattleItems)
{
	m_mapHandler = handler;
	m_player = player;
	m_menu = menu;

	setupItems(handler->getPrevSection(), buyBattleItems);

	//menu->setupBuyItems(&m_data);		//TODO: REMOVE
	MenuSetup::setupBuyItems(menu, &m_data);
}

PokeMart::~PokeMart()
{
	m_menu->remove(MenuScene::BUY_ITEMS);
}

void PokeMart::run(Renderer* renderer)
{

	m_menu->setRequestedData(&m_selection);
	m_menu->setscene(MenuScene::BUY_ITEMS);
	m_menu->setCanLeave(false);
	m_menu->preRun();
	m_menu->setButtonIndex(1);

	updateHoverIndex();
	updateShopItems();
	updatePlayerBalance();

	while (true)
	{
		if (m_menu->shouldClose())
			break;

		m_mapHandler->onUpdate();
		m_player->onUpdate(renderer);
		m_menu->run();

		if (m_menu->leaveRequested())
			break;

		updateHoverIndex();

		if (m_selection != NONE)
		{
			if (m_selection == arrowDirections::UP)
				decreaseWindow();
			else if (m_selection == arrowDirections::DOWN)
				increaseWindow();
			else
				purchaseItem();

			m_selection = NONE;

		}
	}

	m_menu->clearRequestedData();
	m_menu->clearScenes();
	m_menu->postRun();
}

void PokeMart::setupItems(SectionID mapID, bool battleItems)
{
	if (battleItems)
		setupBattleItems(mapID);
	else
		setupWorldItems(mapID);
}

void PokeMart::setupBattleItems(SectionID mapID)
{
	switch (mapID)
	{
	default:
		m_items.push_back(ItemID::POKEBALL);
		m_items.push_back(ItemID::GREATBALL);
		m_items.push_back(ItemID::ULTRABALL);
		m_items.push_back(ItemID::MASTERBALL);
		m_items.push_back(ItemID::SMALL_POTION);
		m_items.push_back(ItemID::MEDIUM_POTION);
		m_items.push_back(ItemID::LARGE_POTION);
		break;
	}
}

void PokeMart::setupWorldItems(SectionID mapID)
{
	switch (mapID)
	{
	default:
		m_items.push_back(ItemID::ROID_JUICE);
		break;
	}
}

void PokeMart::updateHoverIndex()
{
	int menuIndex = m_menu->getButtonIndex();
	if (menuIndex == m_hoverIndex)
		return;

	m_hoverIndex = menuIndex;

	std::string suffix = std::to_string(m_hoverIndex) + ".png";

	m_data.background = "Images/Backgrounds/overlays/buyMenu/buyMenu_" + suffix;
}

void PokeMart::updateShopItems()
{
	int count = 0;
	int indexCount = 0;

	for (int i = 0; i < m_items.size(); i++)
	{
		if (indexCount != m_windowShift)
		{
			indexCount++;
			continue;
		}
		if (count == 6)
			break;

		switch (count)
		{
		case 0:
			m_data.itemName.string1 = getItemFromID(m_items.at(i))->getName();
			m_data.itemCost.string1 = "$" + std::to_string(getItemFromID(m_items.at(i))->getCost());
			m_data.itemTexture.string1 = g_itemTextureLocations[getItemFromID(m_items.at(i))->getID()];
			break;
		case 1:
			m_data.itemName.string2 = getItemFromID(m_items.at(i))->getName();
			m_data.itemCost.string2 = "$" + std::to_string(getItemFromID(m_items.at(i))->getCost());
			m_data.itemTexture.string2 = g_itemTextureLocations[getItemFromID(m_items.at(i))->getID()];
			break;
		case 2:
			m_data.itemName.string3 = getItemFromID(m_items.at(i))->getName();
			m_data.itemCost.string3 = "$" + std::to_string(getItemFromID(m_items.at(i))->getCost());
			m_data.itemTexture.string3 = g_itemTextureLocations[getItemFromID(m_items.at(i))->getID()];
			break;
		case 3:
			m_data.itemName.string4 = getItemFromID(m_items.at(i))->getName();
			m_data.itemCost.string4 = "$" + std::to_string(getItemFromID(m_items.at(i))->getCost());
			m_data.itemTexture.string4 = g_itemTextureLocations[getItemFromID(m_items.at(i))->getID()];
			break;
		case 4:
			m_data.itemName.string5 = getItemFromID(m_items.at(i))->getName();
			m_data.itemCost.string5 = "$" + std::to_string(getItemFromID(m_items.at(i))->getCost());
			m_data.itemTexture.string5 = g_itemTextureLocations[getItemFromID(m_items.at(i))->getID()];
			break;
		case 5:
			m_data.itemName.string6 = getItemFromID(m_items.at(i))->getName();
			m_data.itemCost.string6 = "$" + std::to_string(getItemFromID(m_items.at(i))->getCost());
			m_data.itemTexture.string6 = g_itemTextureLocations[getItemFromID(m_items.at(i))->getID()];
			break;
		}

		count++;
	}

	for (int i = count; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			m_data.itemName.string1 = "";
			m_data.itemCost.string1 = "";
			m_data.itemTexture.string1 = "";
			break;
		case 1:
			m_data.itemName.string2 = "";
			m_data.itemCost.string2 = "";
			m_data.itemTexture.string2 = "";
			break;
		case 2:
			m_data.itemName.string3 = "";
			m_data.itemCost.string3 = "";
			m_data.itemTexture.string3 = "";
			break;
		case 3:
			m_data.itemName.string4 = "";
			m_data.itemCost.string4 = "";
			m_data.itemTexture.string4 = "";
			break;
		case 4:
			m_data.itemName.string5 = "";
			m_data.itemCost.string5 = "";
			m_data.itemTexture.string5 = "";
			break;
		case 5:
			m_data.itemName.string6 = "";
			m_data.itemCost.string6 = "";
			m_data.itemTexture.string6 = "";
			break;
		}
	}
}

void PokeMart::updatePlayerBalance()
{
	m_data.playerBalance = "$" + std::to_string(m_player->getBalance());
}

void PokeMart::increaseWindow()
{
	if (m_windowShift + 1 + 6 <= m_items.size())
	{
		m_windowShift++;
		updateShopItems();
	}
}

void PokeMart::decreaseWindow()
{
	if (m_windowShift <= 0)
		return;

	m_windowShift--;
	updateShopItems();
}

void PokeMart::purchaseItem()
{
	ItemID item = m_items.at(m_selection + m_windowShift);

	if (m_player->getBalance() < getItemFromID(item)->getCost())
		return;

	m_player->addItem(item);
	m_player->reduceMoney(getItemFromID(item)->getCost());
	updatePlayerBalance();
}

#pragma once
#include "../../GlobalData/globalIDs.h"
#include "../../Menu/Menu.h"
#include "../../Menu/MenuFunction/MenuSetup.h"
#include "../../Characters/Trainer/Trainer.h"
#include "../../Map/MapHandler.h"
#include <tuple>

class PokeMart
{
public:
	PokeMart(MapHandler* handler, Trainer* player, Menu* menu, bool buyBattleItems);
	~PokeMart();

	void run(Renderer* renderer);
private:

	void setupItems(SectionID mapID, bool battleItems);
	void setupBattleItems(SectionID mapID);
	void setupWorldItems(SectionID mapID);

	void updateHoverIndex();
	void updateShopItems();
	void updatePlayerBalance();

	void increaseWindow();
	void decreaseWindow();

	void purchaseItem();

	MapHandler* m_mapHandler;
	Trainer* m_player;
	Menu* m_menu;

	BuyItemData m_data;

	std::vector<ItemID> m_items;

	bool m_purchaseBattleItems = false;
	
	int m_windowShift = 0;
	int m_hoverIndex = -1;
	int m_selection = NONE;
};
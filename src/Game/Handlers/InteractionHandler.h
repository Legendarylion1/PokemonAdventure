#pragma once

#include "../../Map/MapHandler.h"
#include "../../Menu/Menu.h"
#include "../Interactions/PC.h"
#include "../../Battle/Battle.h"
#include "../Interactions/PokeMart.h"
#include "../../Menu/MenuFunction/MenuSetup.h"

class InteractionHandler
{
public:
	InteractionHandler() {};

	void setup(Trainer* player, MapHandler* mapHandler, Menu* menu, PC* pc, Battle* battleSimulator, DialogueRenderer* dialogueRenderer, Renderer* renderer);

	void evaluateInteraction();
private:

	void nurseInteraction();
	void buyItems(bool buyBattleItems);
	void aiInteraction(Coordinate aiPosition);

private:

	void resetPlayerPokemonData();
	void flashPokeballs();
	void changeImageNumber(std::string* textureLocation, int newNumber);
	bool nurseShouldHeal();

	void updateShopItems();
	void purchaseItem(int index);

	void turnAIToPlayer(NPT* npt);
	void renderDialogue(std::string topLine, std::string botLine, std::string speakerName, bool awaitClick, int* requestedData = nullptr, std::string topOption = "", std::string bottomOption = "");

private:

	Menu* m_menu = nullptr;
	Trainer* m_player = nullptr;
	MapHandler* m_mapHandler = nullptr;
	PC* m_pc = nullptr;
	Battle* m_battleSimulator = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	Renderer* m_renderer = nullptr;

	SharedString m_availableItems;
	NurseHealData m_nursePokeballData;
	std::string m_playerBalance;

private:
	std::string m_nurseName = "Nurse";
};
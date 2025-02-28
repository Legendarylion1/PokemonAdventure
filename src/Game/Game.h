#pragma once

#include "Handlers/EncounterHandler.h"
#include "../Characters/CharacterMover.h"
#include "Handlers/InteractionHandler.h"
#include "Handlers/PauseHandler.h"
#include "Handlers/StartupHandler.h"
#include "Interactions/Story.h"
#include "../Battle/OldBattleSimulator.h"
#include "../Map/MapHandler.h"
#include "Input/InputData.h"
#include "../Menu/menuData.h"
#include "../Characters/Trainer/Trainer.h"
#include "Input/Input.h"
#include "Interactions/PC.h"
#include "../Menu/Menu.h"
#include "../Battle/Battle.h"
#include "Pokedex/Pokedex.h"

class Game
{
public:

	Game();

	void run();

private:
	void startUp();

	void onUpdate();

	void handleInputEvents();

	void saveAndExit();

 
	Renderer m_renderer;
	Timer m_timer;

	Trainer m_player;
	Pokedex m_pokedex;
	CharacterMover m_characterMover;
	Input m_input;
	Menu m_menu;
	PC m_pc;

	Story m_cutScene;
	StartupHandler startupHandler;			//TODO: I want this to be deleted after startup
	Battle m_battlesimulator;
	InteractionHandler m_interactionHandler;
	EncounterHandler m_encounterHandler;
	MapHandler m_mapHandler;
	PauseHandler m_pauseHandler;
	DialogueRenderer m_dialogueRenderer;
	DataManager m_dataManager;
	OldAnimator m_animator;
	AnimationStream m_animationStream;

	InputVariables m_inputVariables;

	RosterDisplayData m_rosterData{};
};
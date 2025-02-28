#pragma once
#include "../../ExternalData/DataManager.h"
#include "../../Graphics/DialogueRenderer.h"
#include <Windows.h>
#include "../Timer.h"
#include "../../Graphics/Animator.h"
#include "../../Menu/MenuFunction/MenuSetup.h"

class StartupHandler
{
public:
	StartupHandler() {};
	StartupHandler(Trainer* player, DataManager* dataManager, Menu* menu, Timer* timer, Input* input, DialogueRenderer* dialogueRenderer, OldAnimator* animator, AnimationStream* newAnimator);

	void run();
private:

	void playIntro();
	void getSetupData();

	bool deleteFile(int* selection);
	void playNewGameSequence();

	void formatSave(HeaderSave save, SharedString* string, bool* visible);

	void playProfessorMessage();
	
	bool m_newGame = false;

	bool m_showMaleIcon = true;
	bool m_showFemaleIcon = false;

	Trainer* m_player = nullptr;
	DataManager* m_dataManager = nullptr;
	DialogueRenderer* m_dialogueRenderer = nullptr;
	OldAnimator* m_animator = nullptr;
	AnimationStream* m_newAnimator = nullptr;
	Menu* m_menu = nullptr;
	Timer* m_timer = nullptr;
	Input* m_input = nullptr;
};
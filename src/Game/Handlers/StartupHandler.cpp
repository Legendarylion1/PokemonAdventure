#include "StartupHandler.h"

const unsigned int OLD_ANIMATOR = 0;
const unsigned int NEW_ANIMATOR = 1;
const unsigned int ANIMATOR = NEW_ANIMATOR;

StartupHandler::StartupHandler(Trainer* player, DataManager* dataManager, Menu* menu, Timer* timer, Input* input, DialogueRenderer* dialogueRenderer, OldAnimator* animator, AnimationStream* newAnimator)
{
	m_player = player;
	m_dataManager = dataManager;
	m_menu = menu;
	m_timer = timer;
	m_input = input;
	m_dialogueRenderer = dialogueRenderer;
	m_animator = animator;
	m_newAnimator = newAnimator;
}

void StartupHandler::run()
{
	playIntro();

	getSetupData();

	playNewGameSequence();

	m_menu->setscene(MenuScene::NONE);
	//TODO: Skip Setup Data for first time sign on. Use file 2 for default
}

void StartupHandler::playIntro()
{
	m_timer->resetTimer();

	bool studioVisible = false;
	bool pressAnyButton = false;

	// Intro Links
	{
		MenuSetup::setupIntroData(m_menu, &studioVisible, &pressAnyButton, &m_showMaleIcon, &m_showFemaleIcon);	//TODO: Remove Studio Visible
		m_menu->setCanLeave(false);
		m_menu->preRun();
		m_menu->setscene(MenuScene::INTRO_LINKS);
		
		float count = 0.0f;
		float target = 3.0f;

		if (ANIMATOR == OLD_ANIMATOR)
		{
			m_animator->loadAnimations({ Animation::LEGENDARY_STUDIO, Animation::FADE_IN, Animation::FADE_OUT, Animation::LEGENDARY_POKEMON });

			std::cout << "Pre While Loop" << std::endl;

			while (count < target || !m_animator->loadingComplete())
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_animator->updateRenderer();
				count += m_timer->getDelta();
			}

			std::cout << "Count: " << count << std::endl;
		}
		else
		{
			while (count < target)
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_newAnimator->updateRenderer();
				count += m_timer->getDelta();
			}
		}
	}

	// Fade out from animation
	{
		if (ANIMATOR == NEW_ANIMATOR)
		{
			{
				m_newAnimator->setAnimation(Animation::FADE_OUT);

				while (m_newAnimator->animationPlaying())
				{
					if (m_menu->shouldClose())
						break;

					m_menu->renderMenu();
					m_newAnimator->stream(true);
					//m_animator->updateRenderer();
					//m_newAnimator->updateRenderer();
				}

				m_newAnimator->stopAnimation();
			}
		}
		else
		{
			m_animator->setAnimation(Animation::FADE_OUT);
		
			while (m_animator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_animator->playAnimation();
				m_animator->updateRenderer();
			}
		}
	}
	

	// Fade Into studio
	{
		if (ANIMATOR == NEW_ANIMATOR)
		{
			m_menu->setscene(MenuScene::INTRO_STUDIO);
			m_newAnimator->setAnimation(Animation::FADE_IN);

			while (m_newAnimator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_newAnimator->stream(true);
				//m_newAnimator->updateRenderer();
			}

			m_newAnimator->stopAnimation();
		}
		else
		
		{
			m_menu->setscene(MenuScene::INTRO_STUDIO);
			m_animator->setAnimation(Animation::FADE_IN);
		
			while (m_animator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_animator->playAnimation();
				m_animator->updateRenderer();
			}
		}
	}
	
	
	// Studio Animation
	{
		if (ANIMATOR == NEW_ANIMATOR)
		{
			m_newAnimator->setAnimation(Animation::LEGENDARY_STUDIO);

			while (m_newAnimator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				//m_menu->renderMenu();
				m_newAnimator->stream(true);
				//m_newAnimator->updateRenderer();
			}
			m_newAnimator->stopAnimation();
		}
		else
		{
			std::cout << "Pre set Animation" << std::endl;
		
			m_animator->setAnimation(Animation::LEGENDARY_STUDIO);
		
			while (m_animator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				m_animator->playAnimation();
				m_animator->updateRenderer();
			}
		}
	}
	

	// Fade Out from Studio Animation
	{
		if (ANIMATOR == NEW_ANIMATOR)
		{
			m_menu->setscene(MenuScene::INTRO_STUDIO_CROWN);
			m_newAnimator->setAnimation(Animation::FADE_OUT);

			while (m_newAnimator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_newAnimator->stream(true);
			}

			m_newAnimator->stopAnimation();
		}
		else
		{
			m_menu->setscene(MenuScene::INTRO_STUDIO_CROWN);
			m_animator->setAnimation(Animation::FADE_OUT);
		
			while (m_animator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_animator->playAnimation();
				m_animator->updateRenderer();
			}
		}
	}
	

	// Fade into Legendary display
	{
		if (ANIMATOR == NEW_ANIMATOR)
		{
			m_menu->setscene(MenuScene::INTRO_LEGENDARY);
			m_newAnimator->setAnimation(Animation::FADE_IN);

			while (m_newAnimator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_newAnimator->stream(true);
			}

			m_newAnimator->stopAnimation();
		}
		else
		{
			m_menu->setscene(MenuScene::INTRO_LEGENDARY);
			m_animator->setAnimation(Animation::FADE_IN);

			while (m_animator->animationPlaying())
			{
				if (m_menu->shouldClose())
					break;

				m_menu->renderMenu();
				m_animator->playAnimation();
				m_animator->updateRenderer();
			}
		}
		
	}

	//Frame 17 press true

	// Legendary Display
	{
		if (ANIMATOR == NEW_ANIMATOR)
		{
			m_menu->setscene(MenuScene::INTRO_PRESS_ANY_BUTTON);
			m_newAnimator->setAnimation(Animation::LEGENDARY_POKEMON, true);

			while (!m_menu->shouldClose())
			{
				if (!pressAnyButton && m_newAnimator->getFrameCount() > 17)
					pressAnyButton = true;

				if (pressAnyButton && m_input->anyButtonPressed())
					break;

				m_newAnimator->stream(false);
				m_menu->renderMenu();
				m_newAnimator->updateRenderer();
			}

			m_newAnimator->stopAnimation();

		}
		else
		{
			m_menu->setscene(MenuScene::INTRO_PRESS_ANY_BUTTON);
			m_animator->setAnimation(Animation::LEGENDARY_POKEMON, true);

			while (!m_menu->shouldClose())
			{
				if (!pressAnyButton && m_animator->getFrameCount() > 17)
					pressAnyButton = true;

				if (pressAnyButton && m_input->anyButtonPressed())
					break;

				m_animator->playAnimation();
				m_menu->renderMenu();
				m_animator->updateRenderer();

			}
		}

	}

	if (ANIMATOR == OLD_ANIMATOR)
	{
		m_animator->unloadAnimations({ Animation::LEGENDARY_STUDIO, Animation::FADE_IN, Animation::FADE_OUT, Animation::LEGENDARY_POKEMON });
		//TODO: Load these as items when they are in the players bag. Unload when they arent. Loading it here for testing purposes
		// Player Moves and item animations need to be loaded before they are used. Im not sure how to do that besides pre loading everything
		m_animator->loadAnimations({ Animation::THROW_POKEBALL, Animation::THROW_GREATBALL, Animation::THROW_ULTRABALL, Animation::THROW_MASTERBALL, Animation::ESCAPE_POKEBALL, Animation::ESCAPE_GREATBALL, Animation::ESCAPE_ULTRABALL, Animation::ESCAPE_MASTERBALL, Animation::XP_GAIN, Animation::XP_LEVEL_UP_UI });
	}

	m_menu->postRun();
	m_menu->setCanLeave(true);
}

void StartupHandler::getSetupData()
{
	SharedString* startupHeader1 = new SharedString;
	SharedString* startupHeader2 = new SharedString;	//TODO: No need to have these as pointers lol
	SharedString* startupHeader3 = new SharedString;

	bool* header1Visible = new bool;
	bool* header2Visible = new bool;
	bool* header3Visible = new bool;

	*header1Visible = true;
	*header2Visible = true;
	*header3Visible = true;

	MenuSetup::setupStartupData(m_menu, startupHeader1, startupHeader2, startupHeader3, header1Visible, header2Visible, header3Visible);
	//m_menu->setupStartupData(startupHeader1, startupHeader2, startupHeader3, header1Visible, header2Visible, header3Visible);		//TODO: REMOVE

	int selection = NONE;
	m_menu->setCanLeave(false);
	m_menu->setscene(MenuScene::STARTUP_SCENE);
	m_menu->setRequestedData(&selection);



	HeaderSave save1 = m_dataManager->loadHeader(FileNumber::FILE_ONE);
	HeaderSave save2 = m_dataManager->loadHeader(FileNumber::FILE_TWO);
	HeaderSave save3 = m_dataManager->loadHeader(FileNumber::FILE_THREE);


	formatSave(save1, startupHeader1, header1Visible);
	formatSave(save2, startupHeader2, header2Visible);
	formatSave(save3, startupHeader3, header3Visible);

	if (save1.playerName == "New Game")
		*header1Visible = false;
	if (save2.playerName == "New Game")
		*header2Visible = false;
	if (save3.playerName == "New Game")
		*header3Visible = false;

	if (*header1Visible == false && *header2Visible == false && *header3Visible == false)
	{
		//TODO: These dont need to be heap allocated anymore lol. Revert at some point
		//Also this entire funtion is ugly. Clean it up
		m_dataManager->setFile(FileNumber::FILE_TWO);

		delete startupHeader1;
		delete startupHeader2;
		delete startupHeader3;

		delete header1Visible;
		delete header2Visible;
		delete header3Visible;

		m_newGame = true;
		return;
	}

	m_menu->preRun();
	while (!m_menu->shouldClose())
	{
		//system("CLS");
		m_menu->run();

		if (selection == NONE)
			continue;

		if (selection == 3)
		{
			if (deleteFile(&selection))
			{
				m_dataManager->deleteSave(FileNumber::FILE_ONE);
				selection = NONE;
				*header1Visible = false;
				formatSave(save1, startupHeader1, header1Visible);
				m_menu->reset(MenuScene::STARTUP_SCENE);
			}
		}
		else if (selection == 4)
		{
			if (deleteFile(&selection))
			{
				m_dataManager->deleteSave(FileNumber::FILE_TWO);
				selection = NONE;
				*header2Visible = false;
				formatSave(save2, startupHeader2, header2Visible);
				m_menu->reset(MenuScene::STARTUP_SCENE);
			}
		}
		else if (selection == 5)
		{
			if (deleteFile(&selection))
			{
				m_dataManager->deleteSave(FileNumber::FILE_THREE);
				*header3Visible = false;
				formatSave(save3, startupHeader3, header3Visible);
				m_menu->reset(MenuScene::STARTUP_SCENE);
			}
		}
		else
		{
			break;
		}
		
		selection = NONE;
	}

	if (selection == 0)
		m_dataManager->setFile(FileNumber::FILE_ONE);
	else if (selection == 1)
		m_dataManager->setFile(FileNumber::FILE_TWO);
	else if (selection == 2)
		m_dataManager->setFile(FileNumber::FILE_THREE);

	m_menu->clearRequestedData();
	m_menu->postRun();

	if (!m_menu->shouldClose())
	{
		if (selection == 0 && startupHeader1->string1 == "New Game")
		{
			m_newGame = true;
			m_dataManager->loadNewGame();
		}
		else if (selection == 1 && startupHeader2->string1 == "New Game")
		{
			m_newGame = true;
			m_dataManager->loadNewGame();
		}
		else if (selection == 2 && startupHeader3->string1 == "New Game")
		{
			m_newGame = true;
			m_dataManager->loadNewGame();
		}
		else
			m_dataManager->loadGame();
	}

	delete startupHeader1;
	delete startupHeader2;
	delete startupHeader3;

	delete header1Visible;
	delete header2Visible;
	delete header3Visible;
}

bool StartupHandler::deleteFile(int* selection)
{
	*selection = NONE;

	while (!m_menu->shouldClose())
	{
		m_menu->run();

		if (*selection == NONE)
			continue;

		if (*selection == 0)
		{
			*selection = NONE;
			return true;
		}
		else
		{
			*selection = NONE;
			return false;
		}
	}

	return false;
}

void StartupHandler::playNewGameSequence()
{
	if (!m_newGame)
		return;

	playProfessorMessage();

	bool isMale = MenuFunction::getPlayerGenderIsMale(m_menu);

	if (!isMale)
	{
		m_showFemaleIcon = true;
		m_showMaleIcon = false;
		m_player->setCharacterID(CharacterID::PLAYER_FEMALE_TRAINER);
	}

	std::string playerName = MenuFunction::keyboard(m_menu, MenuScene::SET_PLAYER_NAME);

	m_menu->setCanLeave(true);

	m_player->setName(playerName);

	m_dataManager->loadNewGame();
	
}

void StartupHandler::formatSave(HeaderSave save, SharedString* string, bool* visible)
{
	string->string1 = save.playerName;

	if (*visible == false)
	{
		string->string1 = "New Game";
		string->string2 = "";
		string->string3 = "";
		string->string4 = "";
		return;
	}

	if (save.playerName == "New Game")
	{
		*visible = false;
		return;
	}

	string->string2 = save.playTime;
	string->string3 = "Pokemon Found: " + std::to_string(save.pokedexFound);	//TODO: Add a pokedex
	string->string4 = "Badges: " + std::to_string(save.badgesObtained);
}

void StartupHandler::playProfessorMessage()
{
	int selection = NONE;

	m_menu->setRequestedData(&selection);
	m_menu->setCanLeave(false);
	m_menu->setscene(MenuScene::PROFESSOR_M);
	m_menu->preRun();

	m_dialogueRenderer->setDialogue("Test Prof Dialogue", "Lets See", true);
	while (m_dialogueRenderer->rendereringDialogue())
	{
		if (m_menu->shouldClose())
			break;

		m_dialogueRenderer->renderDialogue();
		m_animator->updateRenderer();
	}

	m_menu->clearRequestedData();
	m_menu->postRun();
	m_menu->setCanLeave(true);
}

#include "Game.h"

Game::Game()
{
	//PRINT("1");
	m_player = Trainer("Torin", CharacterID::PLAYER_MALE_TRAINER);
	
	//PRINT("2");
	m_menu = Menu(&m_input);

	//PRINT("3");
	m_mapHandler = MapHandler(&m_player, &m_renderer);

	//PRINT("4");
	m_characterMover = CharacterMover(&m_mapHandler, &m_timer);

	//PRINT("5");
	m_input = Input(&m_inputVariables);

	//PRINT("6");
	m_renderer.init(&m_player.position.coords, &m_timer);

	//PRINT("7");
	m_characterMover.setTileSize(m_renderer.getTileSize());

	//TODO: Clean up
	//PRINT("8");
	m_input.setup(m_renderer.getWindow(), m_pauseHandler.getPauseSettingData());

	//PRINT("9");
	m_menu.setup(&m_inputVariables, &m_renderer, &m_timer);

	//PRINT("10");
	m_pc.setup(&m_player, &m_menu);

	//PRINT("11");
	m_pokedex.setup(&m_menu);

	//PRINT("12");
	m_dataManager.setup(&m_player, &m_pc, &m_mapHandler, &m_input, &m_renderer, &m_timer, &m_characterMover, &m_pokedex, &m_dialogueRenderer, &m_cutScene);

	//PRINT("13");
	m_battlesimulator.setup(&m_player, &m_pokedex, &m_menu, &m_rosterData, &m_dialogueRenderer, &m_animationStream, &m_renderer, &m_input, &m_timer);

	//PRINT("14");
	m_encounterHandler.setup(&m_battlesimulator, &m_mapHandler, &m_player, &m_pc, &m_menu, &m_characterMover, &m_rosterData, &m_dialogueRenderer, &m_animationStream, &m_renderer, &m_input, &m_timer);

	//PRINT("15");
	m_interactionHandler.setup(&m_player, &m_mapHandler, &m_menu, &m_pc, &m_battlesimulator, &m_dialogueRenderer, &m_renderer);

	//PRINT("16");
	m_pauseHandler.setup(&m_menu, &m_player, &m_input, &m_dataManager, &m_renderer, &m_characterMover, &m_timer, &m_rosterData, &m_pokedex, &m_dialogueRenderer, &m_mapHandler);

	//PRINT("17");
	m_dialogueRenderer.setup(&m_menu, &m_input, &m_timer, &m_renderer);	//TODO: Remove Timer From classes that dont need it
	//m_mapHandler.setup();

	//PRINT("18");
	m_animator.setup(&m_renderer, &m_timer);

	//PRINT("19");
	m_animationStream.setup(&m_renderer, &m_timer);

	//PRINT("20");
	m_cutScene = Story(&m_mapHandler, &m_characterMover, &m_player, &m_renderer, &m_dialogueRenderer, &m_menu, &m_battlesimulator, &m_pokedex);	//Needs to be initialized after map npts are
}

void Game::run()
{
	startUp();

	if (m_renderer.shouldClose())
		return;

	while (!m_renderer.shouldClose())
	{
		onUpdate();
	}

	saveAndExit();
}

void Game::startUp()
{
	StartupHandler startupHandler = StartupHandler(&m_player, &m_dataManager, &m_menu, &m_timer, &m_input, &m_dialogueRenderer, &m_animator, &m_animationStream);
	startupHandler.run();

	m_timer.resetTimer();
	m_timer.countPlay(true);
}

void Game::onUpdate()
{
	handleInputEvents();
	m_input.onUpdate();
	


	m_mapHandler.onUpdate();
	m_characterMover.onUpdate();
	m_encounterHandler.onUpdate();
	m_player.onUpdate(&m_renderer);
	m_cutScene.onUpdate();

	m_renderer.onUpdate();
	m_dataManager.autoSave();
}

void Game::handleInputEvents()
{
	if (m_inputVariables.up)
	{
		m_characterMover.moveCharacter(&m_player, Direction::UP);
	}
	if (m_inputVariables.down)
	{
		m_characterMover.moveCharacter(&m_player, Direction::DOWN);
	}
	if (m_inputVariables.left)
	{
		m_characterMover.moveCharacter(&m_player, Direction::LEFT);
	}
	if (m_inputVariables.right)
	{
		m_characterMover.moveCharacter(&m_player, Direction::RIGHT);
	}
	if (m_inputVariables.interact)
	{
		m_interactionHandler.evaluateInteraction();
	}
	if (m_inputVariables.pause)
	{
		m_pauseHandler.run(m_cutScene.getCurrentScene());
	}

	m_player.setSprinting(m_inputVariables.sprint);
}

void Game::saveAndExit()
{
	if (m_battlesimulator.inBattle() || !m_dataManager.fileLoaded())
		return;

	glfwSetWindowShouldClose(m_renderer.getWindow(), GLFW_FALSE);
	glfwSetWindowShouldClose(m_renderer.getSharedWindow(), GLFW_FALSE);

	MenuSetup::setupSaveAndExit(&m_menu);
	
	int selection = NONE;
	
	m_menu.setRequestedData(&selection);
	
	m_menu.setscene(MenuScene::NONE);
	m_menu.setOverlay(MenuOverlay::SAVE_BEFORE_EXIT);
	m_menu.setCanLeave(false);
	
	m_menu.preRun();
	while (!glfwWindowShouldClose(m_renderer.getSharedWindow()) && !glfwWindowShouldClose(m_renderer.getWindow()))
	{
		m_mapHandler.onUpdate();
		m_menu.run();
	
		if (selection == NONE)
			continue;
		else
			break;
	}
	m_menu.postRun();
	m_menu.clearRequestedData();
	
	glfwSetWindowShouldClose(m_renderer.getWindow(), GLFW_TRUE);
	glfwSetWindowShouldClose(m_renderer.getSharedWindow(), GLFW_TRUE);

	if (selection == NONE || selection == (int)false)
		return;
	
	m_dataManager.saveGame();
}

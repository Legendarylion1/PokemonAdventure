#include "Menu.h"
#include <iostream>

Menu::~Menu()
{
	for (auto scene = m_scenes.begin(); scene != m_scenes.end(); scene++)
	{
		//scene->second.freeMemory();
	}
	logger->log(LogLevel::INFO, "Scene Memory Freed", "~Menu", "Menu");
}

void Menu::add(MenuScene sceneID, Scene scene)
{
	if (m_scenes.find(sceneID) != m_scenes.end())
		return;

	m_scenes[sceneID] = scene;
}

void Menu::add(MenuOverlay overlayID, Overlay overlay)
{
	if (m_overlays.find(overlayID) != m_overlays.end())
		return;

	m_overlays[overlayID] = overlay;
}

void Menu::remove(MenuScene scene)
{
	if (m_scenes.find(scene) == m_scenes.end())
		return;

	m_scenes[scene].freeMemory();
	m_scenes.erase(scene);
}

void Menu::remove(MenuOverlay overlay)
{
	if (m_overlays.find(overlay) == m_overlays.end())
		return;

	m_overlays[overlay].freeMemory();
	m_overlays.erase(overlay);
}

Scene* Menu::modify(MenuScene sceneID)
{
	if (m_scenes.find(sceneID) == m_scenes.end())
		return nullptr;

	return &m_scenes[sceneID];
}

Overlay* Menu::modify(MenuOverlay overlayID)
{
	if (m_overlays.find(overlayID) == m_overlays.end())
		return nullptr;

	return &m_overlays[overlayID];
}

void Menu::setscene(MenuScene scene)
{
	m_renderer->clearCache();
	m_currentScene = scene;
	m_renderer->loadBackground(m_scenes[m_currentScene].getBackgroundPath());
}

void Menu::setOverlay(MenuOverlay overlay)
{
	m_currentOverlay = overlay;
	m_overlays[m_currentOverlay].reset();
}

void Menu::setButtonIndex(int index)
{
	if (m_currentOverlay != MenuOverlay::NONE)
	{
		m_overlays[m_currentOverlay].setButtonIndex(index);
	}
	else if (m_currentScene != MenuScene::NONE)
	{
		m_scenes[m_currentScene].setButtonIndex(index);
	}
}

void Menu::sleep(float seconds)
{
	onUpdate();

	float count = 0.0f;
	float target = seconds;

	while (count < target)
	{
		if (shouldClose())
			break;

		onUpdate();
		count += m_timer->getDelta();
	}
}

int Menu::getButtonIndex()
{
	if (m_currentOverlay != MenuOverlay::NONE)
		return m_overlays[m_currentOverlay].getButtonIndex();

	if (m_currentScene != MenuScene::NONE)
		return m_scenes[m_currentScene].getButtonIndex();
	return -1;
}

void Menu::run()
{
	onUpdate();
	handleInputs();
}

void Menu::handleInputs()
{
	if (m_inputVariables->up)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			m_scenes[m_currentScene].goUp();
		else
			m_overlays[m_currentOverlay].goUp();
	}

	if (m_inputVariables->down)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			m_scenes[m_currentScene].goDown();
		else
			m_overlays[m_currentOverlay].goDown();
	}

	if (m_inputVariables->left)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			m_scenes[m_currentScene].goLeft();
		else
			m_overlays[m_currentOverlay].goLeft();
	}

	if (m_inputVariables->right)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			m_scenes[m_currentScene].goRight();
		else
			m_overlays[m_currentOverlay].goRight();
	}

	if (m_inputVariables->interact)
	{
		if (m_currentOverlay == MenuOverlay::NONE)
			handleSelection(m_scenes[m_currentScene].getSelection());
		else
			handleSelection(m_overlays[m_currentOverlay].getSelection());
	}

	if (m_inputVariables->back)
		handleLeave();
}

void Menu::onUpdate()
{
	m_leaveRequested = false;

	renderMenu();

	m_renderer->onUpdate();
	m_input->onUpdate();
}

void Menu::renderMenu()
{
	if (m_currentScene != MenuScene::NONE)
		m_scenes[m_currentScene].onUpdate();

	if (m_currentOverlay != MenuOverlay::NONE)
		m_overlays[m_currentOverlay].onUpdate();
}

bool Menu::handleSelection(Button* button)
{
	logger->log(LogLevel::INFO, "Button Selected", "handleSelection", "Menu");

	if (button == nullptr)
		return false;

	if (m_currentOverlay == MenuOverlay::NONE)
	{
		switch (m_currentScene)
		{
		case MenuScene::BATTLE_ROSTER:
		case MenuScene::BATTLE_ITEMS:
		case MenuScene::USE_PC:
		case MenuScene::PAUSE_MENU:
		case MenuScene::PAUSE_ROSTER:
		case MenuScene::PAUSE_SETTINGS:
		case MenuScene::PAUSE_BAG:
		case MenuScene::STARTUP_SCENE:
		default:
			*m_requestedData = button->data;
			logger->log(LogLevel::ERROR, "Selected button has not been programmed for data", "handleSelection", "Menu");
			break;
		}
	}
	else
	{
		switch (m_currentOverlay)
		{
		case MenuOverlay::DELETE_CONFIRMATION:
		case MenuOverlay::RESOLUTION_SELECTION:
		case MenuOverlay::CHANGE_INPUT:
			m_overlays[m_currentOverlay].reset();
			m_currentOverlay = MenuOverlay::NONE;
		case MenuOverlay::ON_SCREEN_KEYBOARD:
		case MenuOverlay::BATTLE_OPTIONS:
		case MenuOverlay::ATTACK_SELECT:
		default:
			if (m_requestedData != nullptr)
				*m_requestedData = button->data;
			break;
		}
	}

	// Switch Scene
	if (button->scene != MenuScene::NONE)
	{
		m_previousScreens.push_back(m_currentScene);
		setscene(button->scene);

		logger->log(LogLevel::INFO, "Switching Scene", "handleSelection", "Menu");
	}

	// Switch Overlay
	//if (button->overlay != MenuOverlay::NONE)
	setOverlay(button->overlay);

	return false;	//TODO: Make void function
}

bool Menu::handleLeave()	//TODO: Also a void function
{
	m_leaveRequested = true;
	logger->log(LogLevel::INFO, "Leave Requested", "handleLeave", "Menu");

	if (m_currentOverlay != MenuOverlay::NONE && m_canLeave)
	{
		m_currentOverlay = MenuOverlay::NONE;
		return true;
	}

	if (m_currentOverlay == MenuOverlay::NONE && m_canLeave && m_scenes[m_currentScene].getReturnOverlay() != MenuOverlay::NONE)
		m_currentOverlay = m_scenes[m_currentScene].getReturnOverlay();

	if (m_previousScreens.size() == 0 || !m_canLeave)
		return true;
	

	if (m_previousScreens.size() != 0)
	{
		setscene(m_previousScreens.at(m_previousScreens.size() - 1));
		m_previousScreens.pop_back();
		logger->log(LogLevel::DEBUG, "Switching to previous screen", "handleLeave", "Menu");
	}

	return false;
}

#pragma once

#include "Scene.h"
#include "menuData.h"
#include "../GlobalData/helperFunctions.h"
#include <unordered_map>
#include "../Game/Input/Input.h"

/*
							Menu
							----

Buttons
	- Buttons Link to screens
	- Buttons Manipulate data
	- Buttons can close Menu
	- We remember previous button in the case of a one to many relationship
	- Buttons link to other buttons
	- Buttons highlight themselves if hovered

Screens
	- Screens are a collection of buttons
	- Screens may have a background
	- Screens get stored in vector
	- If a button isnt selected but the user wants to go to a previous screen then we pop screens
	- If there is no previous screen then we can close the menu
	- Maybe have an option for no menu close without button press

Overlay
	- Overlays are like the screens
	- Overlays display over the current screen
	- No overlays on overlays. Menu screens should be designed so that we do not need overlays on overlays
	- Overlays are also comprised of buttons
	- Back pressed on an overlay closes the overlay and keeps the screen beneath
*/

namespace arrowDirections
{
	const static int UP = -2;
	const static int DOWN = -3;
	const static int LEFT = -4;
	const static int RIGHT = -5;
}

class Menu
{
public:
	Menu(){};
	Menu(Input* input):m_input(input) {};
	~Menu();

	void setup(InputVariables* inputVariables, Renderer* renderer, Timer* timer) {
		m_inputVariables = inputVariables;
		m_renderer = renderer;
		m_timer = timer;
	};

	void add(MenuScene sceneID, Scene scene);
	void add(MenuOverlay overlayID, Overlay overlay);

	void remove(MenuScene scene);
	void remove(MenuOverlay overlay);

	Scene* modify(MenuScene sceneID);
	Overlay* modify(MenuOverlay overlayID);

	void reset(MenuScene scene) { m_scenes[scene].reset(); };
	void reset(MenuOverlay overlay) { m_overlays[overlay].reset(); };

public:
	Renderer* getRenderer() { return m_renderer; }

	void setscene(MenuScene scene);
	void setOverlay(MenuOverlay overlay);
	void setCanLeave(bool canLeave) { m_canLeave = canLeave; };
	void setRequestedData(int* data) { m_requestedData = data; };
	void setOverlayBackground(MenuOverlay overlay, ImageRenderData* data) { m_overlays[overlay].setOverlayBackground(data); };
	void setButtonIndex(int index);
		
	void clearRequestedData() { m_requestedData = nullptr; };
	void clearScenes() { m_previousScreens.clear(); };

	bool leaveRequested() { return m_leaveRequested; };
	void sleep(float seconds);											//TODO: Adjust all sleep users
	bool anyButtonPressed() { return m_input->anyButtonPressed(); };	//TODO: Adjust all input users
	float getDeltaTime() { return m_timer->getDelta(); };				//TODO: Adjust all timer users
	
	int getButtonIndex();
	MenuScene getCurrentScene() { return m_currentScene; };
	Resolution getResolution() { return m_renderer->getResolution(); };

	bool shouldClose() { return m_renderer->shouldClose(); }
	void preRun() { m_input->setCanHoldInput(false); };
	void run();
	void handleInputs();
	void postRun() { m_input->setCanHoldInput(true); };

	void onUpdate();
	void renderMenu();

private:

	bool handleSelection(Button* button);
	bool handleLeave();

private:
	InputVariables* m_inputVariables = nullptr;
	Renderer* m_renderer = nullptr;
	Input* m_input = nullptr;
	Timer* m_timer = nullptr;

private:
	bool m_canLeave = false;
	int* m_requestedData = nullptr;
	bool m_leaveRequested = false;

	MenuScene m_currentScene = MenuScene::NONE;
	MenuOverlay m_currentOverlay = MenuOverlay::NONE;

	std::vector<MenuScene> m_previousScreens;
	std::unordered_map<MenuScene, Scene> m_scenes;
	std::unordered_map<MenuOverlay, Overlay> m_overlays;
};
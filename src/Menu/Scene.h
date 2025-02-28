#pragma once
#include "../Battle/SimulationCommands.h"
#include <string>
#include <vector>
#include "../Graphics/Renderer.h"

struct Button
{
	std::string text;
	std::string* dynamic_text = nullptr;
	int index;
	int data = NONE;

	Button* up = nullptr;
	Button* down = nullptr;
	Button* left = nullptr;
	Button* right = nullptr;

	bool goBackOnUp = false;
	bool goBackOnDown = false;
	bool goBackOnLeft = false;
	bool goBackOnRight = false;

	bool* active = nullptr;

	MenuScene scene = MenuScene::NONE;
	MenuOverlay overlay = MenuOverlay::NONE;

	ButtonRenderData renderData;
	ButtonRenderData* dynamicRenderData = nullptr;

	bool deleteWithScene = true;
};

struct ButtonTemplate	//TODO: Remove this and all references. The idea was to have dynamic buttons for reuse. For example if two options in the settings menu had a popup with the same data they could use the same overlay with a button template
{
	std::string text;
	int data;

	Direction spawnDirection = Direction::DOWN;
	float spawnPercentOffset = 0.0f;
	int spawnButtonOffset = 0;

	float widthPercentage = 0.0f;
	float heightPercentage = 0.0f;

	int upLinkIndex = -1;
	int downLinkIndex = -1;
	int leftLinkIndex = -1;
	int rightLinkIndex = -1;

	Color buttonColor = Color::RED;
};

struct TextBox
{
	std::string text;
	std::string* dynamic_text = nullptr;

	bool* visible = nullptr;

	TextBoxRenderData renderData;
	TextBoxRenderData* dynamicRenderData = nullptr;

	bool deleteWithScene = true;
};

class Scene
{
public:
	Scene() {};
	Scene(Renderer* renderer): m_renderer(renderer) {};

	void setText(std::string text) { m_text = text; }; //TODO: Remove
	void setBackgroundPath(std::string text) { m_backgroundPath = text; };
	void setReturnOverlay(MenuOverlay overlay) { m_returnOverlay = overlay; };
	void setButtonIndex(int index) { m_currentButtonIndex = index; };
	virtual void freeMemory();	//TODO: Improve
	void reset();

	void goUp();
	void goDown();
	void goLeft();
	void goRight();

	Button* getSelection();
	MenuOverlay getReturnOverlay() { return m_returnOverlay; };

	void addButton(Button* button);
	void addTextBox(TextBox* textBox) { m_textBoxes.push_back(textBox); };
	void addImage(ImageRenderData* image) { m_images.push_back(image); };
	void addDynamicImage(DynamicImageRenderData* image) { m_dynamicImages.push_back(image); };
	void addRectangle(RectangleRenderData* rect) { m_rectangles.push_back(rect); };
	void addPolygon(PolygonData* data) { m_polygons.push_back(data); };

	void deleteButton(int index);

	int getButtonIndex() { return m_currentButtonIndex; };
	std::string getBackgroundPath() { return m_backgroundPath; };
	Renderer* getRenderer() { return m_renderer; };

	virtual void onUpdate(bool renderBackground = true);

private:
	bool buttonActive(Button* button);
	bool textBoxVisible(TextBox* textBox);

	void swapButton(int index, Direction swapDirection);
	void goBack();


private:
	Renderer* m_renderer = nullptr;
	std::string m_text;
	std::string m_backgroundPath = "Images/Backgrounds/transparent.png";
	MenuOverlay m_returnOverlay = MenuOverlay::NONE;

	int m_currentButtonIndex = 0;
	int m_previousButtonIndex = NONE;

	std::vector<Button*> m_buttons;
	std::vector<TextBox*> m_textBoxes;
	std::vector<ImageRenderData*> m_images;
	std::vector<RectangleRenderData*> m_rectangles;
	std::vector<DynamicImageRenderData*> m_dynamicImages;
	std::vector<PolygonData*> m_polygons;
};

class Overlay : public Scene
{
public:
	Overlay() : Scene() {};
	Overlay(Renderer* renderer) : Scene(renderer) {};

	void addButtonTemplate(ButtonTemplate buttonTemplate) { m_buttonTemplates.push_back(buttonTemplate); };
	void setOverlayBackground(ImageRenderData* background);
	void setupButtons(Button* button);
	void onUpdate();
	void freeMemory();
private:

	void clearDynamicButtons();
	std::vector<Button*> setupButtonLocations(Button* button);
	void linkDynamicButtons(std::vector<Button*> addedButtons);
	void buildRenderData(Button* button, ButtonTemplate buttonTemplate);

	std::vector<ButtonTemplate> m_buttonTemplates;
	std::vector<unsigned int> m_buttonIndexes;
	ImageRenderData* m_overlayBackground = nullptr;
};
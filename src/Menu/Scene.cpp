#include "Scene.h"
#include <iostream>		//Temporary

void Scene::freeMemory()
{
	for (int i = m_buttons.size() - 1; i >= 0; i--)
	{
		if (m_buttons.at(i)->deleteWithScene)
			delete m_buttons.at(i);
	}
	
	for (int i = m_textBoxes.size() - 1; i >= 0; i--)
	{
		if (m_textBoxes.at(i)->deleteWithScene)
			delete m_textBoxes.at(i);
	}

	for (int i = m_images.size() - 1; i >= 0; i--)
	{
		if (m_images.at(i)->deleteWithScene)
			delete m_images.at(i);
	}

	for (int i = m_rectangles.size() - 1; i >= 0; i--)
	{
		if (m_rectangles.at(i)->deleteWithScene)
			delete m_rectangles.at(i);
	}

	for (int i = m_dynamicImages.size() - 1; i >= 0; i--)
	{
		if (m_dynamicImages.at(i)->deleteWithScene)
			delete m_dynamicImages.at(i);
	}

	m_buttons.clear();
	m_textBoxes.clear();
	m_images.clear();
	m_rectangles.clear();
	m_dynamicImages.clear();
}

void Scene::reset()
{
	m_currentButtonIndex = 0;
	m_previousButtonIndex = NONE;
}

void Scene::goUp()
{
	if (m_buttons.size() == 0)
		return;

	if (buttonActive(m_buttons.at(m_currentButtonIndex)->up))
		swapButton(m_buttons.at(m_currentButtonIndex)->up->index, Direction::UP);
	else if (m_buttons.at(m_currentButtonIndex)->goBackOnUp)
		goBack();
}

void Scene::goDown()
{
	if (m_buttons.size() == 0)
		return;

	if (buttonActive(m_buttons.at(m_currentButtonIndex)->down))
		swapButton(m_buttons.at(m_currentButtonIndex)->down->index, Direction::DOWN);
	else if (m_buttons.at(m_currentButtonIndex)->goBackOnDown)
		goBack();
}

void Scene::goLeft()
{
	if (m_buttons.size() == 0)
		return;

	if (buttonActive(m_buttons.at(m_currentButtonIndex)->left))
		swapButton(m_buttons.at(m_currentButtonIndex)->left->index, Direction::LEFT);
	else if (m_buttons.at(m_currentButtonIndex)->goBackOnLeft)
		goBack();
}

void Scene::goRight()
{
	if (m_buttons.size() == 0)
		return;

	if (buttonActive(m_buttons.at(m_currentButtonIndex)->right))
		swapButton(m_buttons.at(m_currentButtonIndex)->right->index, Direction::RIGHT);
	else if (m_buttons.at(m_currentButtonIndex)->goBackOnRight)
		goBack();
}

Button* Scene::getSelection()
{
	if (m_buttons.size() == 0)
		return nullptr;

	return m_buttons.at(m_currentButtonIndex);
}

void Scene::addButton(Button* button)
{

	button->index = (int)m_buttons.size();
	m_buttons.push_back(button);
}

void Scene::deleteButton(int index)
{
	delete m_buttons.at(index); 
	m_buttons.erase(m_buttons.begin() + index);
}

void Scene::onUpdate(bool renderBackground)
{
	//std::cout << m_text << std::endl;

	if (renderBackground)
		m_renderer->renderBackground();

	for (Button* button : m_buttons)
	{
		if (!buttonActive(button))
			continue;

		if (button->renderData.visible != nullptr && *button->renderData.visible == false)
			continue;

		std::string text = button->text;

		if (button->dynamic_text != nullptr)
			text = *button->dynamic_text;

		ButtonRenderData renderData = button->renderData;
		if (button->dynamicRenderData != nullptr)
			renderData = *button->dynamicRenderData;

		m_renderer->renderButton(renderData, text, button->index == m_currentButtonIndex);
	}

	for (ImageRenderData* image : m_images)
	{
		if (image->visible == nullptr || *image->visible == true)
			m_renderer->renderImage(*image);
	}

	for (DynamicImageRenderData* image : m_dynamicImages)
		m_renderer->renderDynamicImage(*image);

	for (RectangleRenderData* rect : m_rectangles)
		m_renderer->renderRectangle(*rect);

	for (PolygonData* data : m_polygons)
		m_renderer->renderPolygon(*data);

	for (TextBox* textBox : m_textBoxes)
	{
		if (!textBoxVisible(textBox))
			continue;

		std::string text = textBox->text;

		if (textBox->dynamic_text != nullptr)
			text = *textBox->dynamic_text;

		TextBoxRenderData renderData = textBox->renderData;
		if (textBox->dynamicRenderData != nullptr)
			renderData = *textBox->dynamicRenderData;

		m_renderer->renderTextBox(renderData, text);
	}

	if (m_buttons.size() == 0)
		return;
}

bool Scene::buttonActive(Button* button)
{
	if (button == nullptr)
		return false;

	if (button->active == nullptr)
		return true;

	if (*button->active == false)
		return false;

	return true;
}

bool Scene::textBoxVisible(TextBox* textBox)
{
	if (textBox == nullptr)
		return false;

	if (textBox->visible == nullptr)
		return true;

	if (*textBox->visible == false)
		return false;

	return true;
}

void Scene::swapButton(int index, Direction swapDirection)
{

	switch (swapDirection)
	{
	case UP:
		if(m_buttons.at(index)->goBackOnDown == true)
			m_previousButtonIndex = m_currentButtonIndex;
		break;
	case DOWN:
		if(m_buttons.at(index)->goBackOnUp == true)
			m_previousButtonIndex = m_currentButtonIndex;
		break;
	case LEFT:
		if(m_buttons.at(index)->goBackOnRight == true)
		m_previousButtonIndex = m_currentButtonIndex;
		break;
	case RIGHT:
		if(m_buttons.at(index)->goBackOnLeft == true)
			m_previousButtonIndex = m_currentButtonIndex;
		break;
	default:
		break;
	}
	
	m_currentButtonIndex = index;
}

void Scene::goBack()
{
	if (m_previousButtonIndex != NONE && buttonActive(m_buttons.at(m_previousButtonIndex)))
		swapButton(m_previousButtonIndex, Direction(5));
}

void Overlay::setOverlayBackground(ImageRenderData* background)
{
	if (m_overlayBackground != nullptr)
		delete m_overlayBackground;

	m_overlayBackground = background;
}

void Overlay::setupButtons(Button* button)
{
	clearDynamicButtons();

	linkDynamicButtons(setupButtonLocations(button));
}

void Overlay::onUpdate()
{
	if (m_overlayBackground != nullptr)
		getRenderer()->renderImage(*m_overlayBackground);

	Scene::onUpdate(false);
}

void Overlay::freeMemory()
{
	if (m_overlayBackground != nullptr && m_overlayBackground->deleteWithScene)
		delete m_overlayBackground;

	Scene::freeMemory();
}

void Overlay::clearDynamicButtons()
{
	for (int i = m_buttonIndexes.size() - 1; i >= 0; i--)
	{
		deleteButton(m_buttonIndexes.at(i));
	}
}

std::vector<Button*> Overlay::setupButtonLocations(Button* button)
{
	std::vector<Button*> addedButtons;


	for (ButtonTemplate buttonTemplate : m_buttonTemplates)
	{
		Button* dynamicButton = new Button();

		dynamicButton->text = buttonTemplate.text;
		dynamicButton->data = buttonTemplate.data;

		buildRenderData(dynamicButton, buttonTemplate);

		addButton(dynamicButton);
		m_buttonIndexes.push_back(dynamicButton->index);
	}


	return addedButtons;
}

void Overlay::linkDynamicButtons(std::vector<Button*> addedButtons)
{
	int count = 0;
	for (ButtonTemplate buttonTemplate : m_buttonTemplates)
	{

		Button* currentButton = addedButtons.at(count);

		if (buttonTemplate.upLinkIndex != -1)
			currentButton->up = addedButtons.at(buttonTemplate.upLinkIndex);
		if (buttonTemplate.downLinkIndex != -1)
			currentButton->down = addedButtons.at(buttonTemplate.downLinkIndex);
		if (buttonTemplate.leftLinkIndex != -1)
			currentButton->left = addedButtons.at(buttonTemplate.leftLinkIndex);
		if (buttonTemplate.rightLinkIndex != -1)
			currentButton->right = addedButtons.at(buttonTemplate.rightLinkIndex);

		count++;
	}
}

void Overlay::buildRenderData(Button* button, ButtonTemplate buttonTemplate)
{
	ButtonRenderData renderData;

	if (buttonTemplate.spawnDirection == Direction::UP)
	{
		renderData.percentageX = button->renderData.percentageX;
		renderData.percentageY = button->renderData.percentageY + (button->renderData.heightPercent / 2.0f) + (buttonTemplate.heightPercentage / 2.0f) + (buttonTemplate.heightPercentage * buttonTemplate.spawnButtonOffset) + buttonTemplate.spawnPercentOffset;
	}
	else if (buttonTemplate.spawnDirection == Direction::DOWN)
	{
		renderData.percentageX = button->renderData.percentageX;
		renderData.percentageY = button->renderData.percentageY - (button->renderData.heightPercent / 2.0f) - (buttonTemplate.heightPercentage / 2.0f) - (buttonTemplate.heightPercentage * buttonTemplate.spawnButtonOffset) - buttonTemplate.spawnPercentOffset;
	}
	else if (buttonTemplate.spawnDirection == Direction::LEFT)
	{
		renderData.percentageX = button->renderData.percentageX - (button->renderData.widthPercent / 2.0f) - (buttonTemplate.widthPercentage / 2.0f) - (buttonTemplate.widthPercentage * buttonTemplate.spawnButtonOffset) - buttonTemplate.spawnPercentOffset;;
		renderData.percentageY = button->renderData.percentageY;
	}
	else
	{
		renderData.percentageX = button->renderData.percentageX + (button->renderData.widthPercent / 2.0f) + (buttonTemplate.widthPercentage / 2.0f) + (buttonTemplate.widthPercentage * buttonTemplate.spawnButtonOffset) + buttonTemplate.spawnPercentOffset;;
		renderData.percentageY = button->renderData.percentageY;
	}


	renderData.widthPercent = buttonTemplate.widthPercentage;
	renderData.heightPercent = buttonTemplate.heightPercentage;
	renderData.color = buttonTemplate.buttonColor;

	button->renderData = renderData;
}
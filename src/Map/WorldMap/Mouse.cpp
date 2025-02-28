#include "Mouse.h"

UserMouse::UserMouse(Input* input): 
	m_input(input), m_inputVariables(input->getInputVaraibles())
{
	input->setCanHoldInput(true);

	float size = 3.0f;

	float widthPercent = size / 9.0f;
	float heightPercent = size / 16.0f;

	m_position.screenX = 50.0f;
	m_position.screenY = 50.0f;

	m_renderData = ImageRenderData{m_position.screenX, m_position.screenY, widthPercent, heightPercent, "Images/Backgrounds/overlays/whiteSquare.png"};
}

UserMouse::~UserMouse()
{
	m_input->setCanHoldInput(false);
}

void UserMouse::move(float deltaTime)
{
	//TODO: Normalize movement

	m_input->onUpdate();

	float screenPercentSpeed = 15.0f;

	if (m_inputVariables->up)
	{
		m_position.screenY += screenPercentSpeed * deltaTime;
	}
	if (m_inputVariables->down)
	{
		m_position.screenY -= screenPercentSpeed * deltaTime;
	}
	if (m_inputVariables->left)
	{
		m_position.screenX -= screenPercentSpeed * deltaTime;
	}
	if (m_inputVariables->right)
	{
		m_position.screenX += screenPercentSpeed * deltaTime;
	}

	updateRenderData();
}

void UserMouse::setPosition(float xPercent, float yPercent)
{
	m_position.screenX = xPercent;
	m_position.screenY = yPercent;

	updateRenderData();
}

void UserMouse::updateRenderData()
{
	m_renderData.percentageX = m_position.screenX;
	m_renderData.percentageY = m_position.screenY;
}

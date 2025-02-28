#pragma once
#include "../../Graphics/PositionalData.h"
#include "../../Game/Input/Input.h"

class UserMouse
{
public:

	UserMouse(Input* input);
	~UserMouse();

	void move(float deltaTime);

	void setPosition(float xPercent, float yPercent);

	Coordinate getPosition() { return m_position; }

	ImageRenderData getRenderData() { return m_renderData; }

private:

	void updateRenderData();

private:

	Input* m_input = nullptr;
	InputVariables* m_inputVariables = nullptr;

	Coordinate m_position;
	ImageRenderData m_renderData;
};
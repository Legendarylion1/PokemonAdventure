#include "MapPath.h"

InteractiveRectangle::InteractiveRectangle(float centerX, float centerY, Color color, float size)
{
	// TODO: Make squares inherantly bigger
	// Squares are centered

	m_widthPercent = size * 9.0f;
	float heightPercent = size * 16.0f;

	m_renderData.bottomLeftXPercentage = centerX - (m_widthPercent / 2.0f);
	m_renderData.bottomLeftYPercentage = centerY - (heightPercent / 2.0f);

	m_renderData.heightPercent = heightPercent;
	m_renderData.widthPercent = &m_widthPercent;
	m_renderData.color = color;

	m_renderData.deleteWithScene = false;
}

InteractiveRectangle::InteractiveRectangle(float centerX, float centerY, Color color, float width, float height)
{
	m_widthPercent = width;
	float heightPercent = height;
	
	m_renderData.bottomLeftXPercentage = centerX - (m_widthPercent / 2.0f);
	m_renderData.bottomLeftYPercentage = centerY - (heightPercent / 2.0f);

	m_renderData.heightPercent = heightPercent;
	m_renderData.widthPercent = &m_widthPercent;
	m_renderData.color = color;

	m_renderData.deleteWithScene = false;
}

InteractiveRectangle::~InteractiveRectangle()
{
}

void InteractiveRectangle::toggleHover()
{
	float hoverSizeIncrease = 0.2f;
	float widthPercent = hoverSizeIncrease * 9.0f;
	float heightPercent = hoverSizeIncrease * 16.0f;

	if (m_hovered == true)
	{
		m_renderData.bottomLeftXPercentage += (widthPercent / 2.0f);
		m_renderData.bottomLeftYPercentage += (heightPercent / 2.0f);

		m_renderData.heightPercent -= heightPercent;
		m_widthPercent -= widthPercent;
		m_renderData.widthPercent = &m_widthPercent;
	}
	else
	{
		m_renderData.bottomLeftXPercentage -= (widthPercent / 2.0f);
		m_renderData.bottomLeftYPercentage -= (heightPercent / 2.0f);

		m_renderData.heightPercent += heightPercent;
		m_widthPercent += widthPercent;
		m_renderData.widthPercent = &m_widthPercent;
	}

	m_hovered = !m_hovered;
}

bool InteractiveRectangle::doesIntersect(float xPercent, float yPercent)
{
	if (xPercent <= m_renderData.bottomLeftXPercentage + *m_renderData.widthPercent && m_renderData.bottomLeftXPercentage <= xPercent )
	{
		if (yPercent <= m_renderData.bottomLeftYPercentage + m_renderData.heightPercent && m_renderData.bottomLeftYPercentage <= yPercent)
		{
			return true;
		}
	}
	return false;
}

RectangleRenderData InteractiveRectangle::getRenderData()
{
	return m_renderData;
}

std::vector<RectangleRenderData> BasePath::getRenderData()
{
	std::vector<RectangleRenderData> data;

	for (int i = 0; i < m_rectangles.size(); i++)
	{
		data.push_back(m_rectangles.at(i).getRenderData());
	}

	return data;
}

bool BasePath::doesIntersect(float xPercent, float yPercent)
{
	for (int i = 0; i < m_rectangles.size(); i++)
	{
		if (m_rectangles.at(i).doesIntersect(xPercent, yPercent))
			return true;
	}

	return false;
}

void BasePath::toggleHover()
{
	for (int i = 0; i < m_rectangles.size(); i++)
	{
		m_rectangles.at(i).toggleHover();
	}
}

Coordinate BasePath::getCenterPercent()
{
	if (m_rectangles.size() == 0)
		return Coordinate(0,0,50.0f,50.0f);

	Coordinate center;

	RectangleRenderData data = m_rectangles.at(0).getRenderData();

	center.screenX = data.bottomLeftXPercentage + (*data.widthPercent / 2.0f);
	center.screenY = data.bottomLeftYPercentage + (data.heightPercent / 2.0f);

	return center;
}

#pragma once

#include "../../Graphics/PositionalData.h"

class InteractiveRectangle
{
public:
	InteractiveRectangle(float centerX, float centerY, Color color, float size);
	InteractiveRectangle(float centerX, float centerY, Color color, float width, float height);
	~InteractiveRectangle();

	void toggleHover();
	bool doesIntersect(float xPercent, float yPercent);

	RectangleRenderData getRenderData();

private:
	RectangleRenderData m_renderData;

	bool m_hovered = false;
	float m_widthPercent = 0.0f;
};

class BasePath
{
public:
	BasePath(){}
	BasePath(std::string pathName, int linkedSectionID) : m_pathName(pathName), m_id(linkedSectionID) {}
	
	void addRectangle(InteractiveRectangle rectangle) { m_rectangles.push_back(rectangle); }

	std::vector<RectangleRenderData> getRenderData();

	bool doesIntersect(float xPercent, float yPercent);

	void toggleHover();

	int getSectionID() { return m_id; }
	std::string getPathName() { return m_pathName; }

	Coordinate getCenterPercent();

private:
	std::vector<InteractiveRectangle> m_rectangles;

	std::string m_pathName;
	int m_id;
};
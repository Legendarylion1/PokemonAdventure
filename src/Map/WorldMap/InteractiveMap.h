#pragma once

#include "MapPath.h"
#include "../../Graphics/Renderer.h"
#include "Mouse.h"

//TODO: Get map subsection from maphandler

class InteractiveMap
{
public:
	InteractiveMap(Renderer* renderer, Input* input, MapSubSectionID startingSection);
	~InteractiveMap();

	int run(MapSubSectionID id);
private:

	void setMousePosition(MapSubSectionID id, UserMouse* mouse);

	void updatePaths(UserMouse* mouse);
	void updateHighlightedPath();
	void onUpdate(UserMouse* mouse);

	Renderer* m_renderer = nullptr;
	Input* m_input = nullptr;

	ImageRenderData m_background = ImageRenderData{50.0f, 50.0f, 50.0f, 50.0f, "Images/Backgrounds/regionMap.png"};

	int m_pathHoverIndex = -1;

	std::vector<BasePath> m_paths;
};
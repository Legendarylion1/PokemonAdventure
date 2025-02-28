#include "InteractiveMap.h"

InteractiveMap::InteractiveMap(Renderer* renderer, Input* input, MapSubSectionID startingSection):
	m_renderer(renderer), m_input(input)
{
	//176,99 size
}

InteractiveMap::~InteractiveMap()
{
	m_renderer->clearCache();
}

int InteractiveMap::run(MapSubSectionID id)
{	
	// Route Paths
	{
		Color routeColor = Color::BLUE;
		float routeOffset = 0.8f;

		float depthH = (2.0f / 176.0f) * 100.0f;
		float depthV = (2.0f / 99.0f) * 100.0f;

		BasePath route1 = BasePath("Route 1", (int)MapSubSectionID::ROUTE_1);
		route1.addRectangle(InteractiveRectangle((54.0f / 176.0f) * 100.0f, ((99.0f - 82.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (9.8f / 99.0f) * 100.0f));
		m_paths.push_back(route1);

		BasePath route2 = BasePath("Route 2", (int)MapSubSectionID::ROUTE_2);
		route2.addRectangle(InteractiveRectangle((54.0f / 176.0f) * 100.0f, ((99.0f - 62.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (9.8f / 99.0f) * 100.0f));
		m_paths.push_back(route2);

		BasePath route3 = BasePath("Route 3", (int)MapSubSectionID::ROUTE_3);
		route3.addRectangle(InteractiveRectangle((44.0f / 176.0f) * 100.0f, ((99.0f - 52.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (10.0f / 176.0f) * 100.0f, depthV));
		m_paths.push_back(route3);

		BasePath route4 = BasePath("Route 4", (int)MapSubSectionID::ROUTE_4);
		route4.addRectangle(InteractiveRectangle((34.0f / 176.0f) * 100.0f, ((99.0f - 42.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (9.8f / 99.0f) * 100.0f));
		route4.addRectangle(InteractiveRectangle((41.0f / 176.0f) * 100.0f, ((99.0f - 38.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (16.0f / 176.0f) * 100.0f, depthV));
		route4.addRectangle(InteractiveRectangle((48.0f / 176.0f) * 100.0f, ((99.0f - 36.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (5.8f / 99.0f) * 100.0f));
		m_paths.push_back(route4);

		BasePath route5 = BasePath("Route 5", (int)MapSubSectionID::ROUTE_5);
		route5.addRectangle(InteractiveRectangle((62.0f / 176.0f) * 100.0f, ((99.0f - 36.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (5.8f / 99.0f) * 100.0f));
		route5.addRectangle(InteractiveRectangle((71.5f / 176.0f) * 100.0f, ((99.0f - 38.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (21.0f / 176.0f) * 100.0f, depthV));
		route5.addRectangle(InteractiveRectangle((81.0f / 176.0f) * 100.0f, ((99.0f - 35.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (7.8f / 99.0f) * 100.0f));
		route5.addRectangle(InteractiveRectangle((84.5f / 176.0f) * 100.0f, ((99.0f - 32.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (9.0f / 176.0f) * 100.0f, depthV));
		m_paths.push_back(route5);

		BasePath route6 = BasePath("Route 6", (int)MapSubSectionID::ROUTE_6);
		route6.addRectangle(InteractiveRectangle((94.0f / 176.0f) * 100.0f, ((99.0f - 42.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (9.8f / 99.0f) * 100.0f));
		m_paths.push_back(route6);

		BasePath route7 = BasePath("Route 7", (int)MapSubSectionID::ROUTE_7);
		route7.addRectangle(InteractiveRectangle((84.0f / 176.0f) * 100.0f, ((99.0f - 52.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (10.0f / 176.0f) * 100.0f, depthV));
		m_paths.push_back(route7);

		BasePath route8 = BasePath("Route 8", (int)MapSubSectionID::ROUTE_8);
		route8.addRectangle(InteractiveRectangle((94.0f / 176.0f) * 100.0f, ((99.0f - 19.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (15.8f / 99.0f) * 100.0f));
		route8.addRectangle(InteractiveRectangle((101.0f / 176.0f) * 100.0f, ((99.0f - 12.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (16.0f / 176.0f) * 100.0f, depthV));
		m_paths.push_back(route8);

		BasePath route9 = BasePath("Route 9", (int)MapSubSectionID::ROUTE_9);
		route9.addRectangle(InteractiveRectangle((114.0f / 176.0f) * 100.0f, ((99.0f - 22.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (9.8f / 99.0f) * 100.0f));
		m_paths.push_back(route9);

		BasePath route10 = BasePath("Route 10", (int)MapSubSectionID::ROUTE_10);
		route10.addRectangle(InteractiveRectangle((114.0f / 176.0f) * 100.0f, ((99.0f - 42.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (9.8f / 99.0f) * 100.0f));
		m_paths.push_back(route10);

		BasePath route11 = BasePath("Route 11", (int)MapSubSectionID::ROUTE_11);
		route11.addRectangle(InteractiveRectangle((104.0f / 176.0f) * 100.0f, ((99.0f - 42.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (22.0f / 176.0f) * 100.0f, depthV));
		m_paths.push_back(route11);

		BasePath route12 = BasePath("Route 12", (int)MapSubSectionID::ROUTE_12);
		route12.addRectangle(InteractiveRectangle((94.0f / 176.0f) * 100.0f, ((99.0f - 64.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (13.8f / 99.0f) * 100.0f));
		m_paths.push_back(route12);

		BasePath route13 = BasePath("Route 13", (int)MapSubSectionID::ROUTE_13);
		route13.addRectangle(InteractiveRectangle((101.0f / 176.0f) * 100.0f, ((99.0f - 72.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (16.0f / 176.0f) * 100.0f, depthV + 0.2f));
		m_paths.push_back(route13);

		BasePath route14 = BasePath("Route 14", (int)MapSubSectionID::ROUTE_14);
		route14.addRectangle(InteractiveRectangle((94.0f / 176.0f) * 100.0f, ((99.0f - 78.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (9.8f / 99.0f) * 100.0f));
		route14.addRectangle(InteractiveRectangle((87.0f / 176.0f) * 100.0f, ((99.0f - 82.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (16.0f / 176.0f) * 100.0f, depthV));
		m_paths.push_back(route14);

		BasePath route15 = BasePath("Route 15", (int)MapSubSectionID::ROUTE_15);
		route15.addRectangle(InteractiveRectangle((114.0f / 176.0f) * 100.0f, ((99.0f - 62.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (9.8f / 99.0f) * 100.0f));
		m_paths.push_back(route15);

		BasePath route16 = BasePath("Route 16", (int)MapSubSectionID::ROUTE_16);
		route16.addRectangle(InteractiveRectangle((129.5f / 176.0f) * 100.0f, ((99.0f - 72.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (21.0f / 176.0f) * 100.0f, depthV));
		route16.addRectangle(InteractiveRectangle((139.0f / 176.0f) * 100.0f, ((99.0f - 62.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (21.8f / 99.0f) * 100.0f));
		m_paths.push_back(route16);

		BasePath route17 = BasePath("Route 17", (int)MapSubSectionID::ROUTE_17);
		route17.addRectangle(InteractiveRectangle((67.0f / 176.0f) * 100.0f, ((99.0f - 72.0f + routeOffset) / 99.0f) * 100.0f, routeColor, (16.0f / 176.0f) * 100.0f, depthV));
		route17.addRectangle(InteractiveRectangle((74.0f / 176.0f) * 100.0f, ((99.0f - 74.0f + routeOffset) / 99.0f) * 100.0f, routeColor, depthH, (5.8f / 99.0f) * 100.0f));
		m_paths.push_back(route17);
	}

	// Town Paths
	{
		float squareOffset = 0.7f;
		float townSize = ((10.0f / 176.0f) / 9.0) * 100.0f;

		BasePath homeVillage = BasePath("Home Village", (int)MapSubSectionID::HOME_VILLAGE);
		homeVillage.addRectangle(InteractiveRectangle((54.0f / 176.0f) * 100.0f, ((99.0f - 92.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(homeVillage);

		BasePath townOne = BasePath("Town One", (int)MapSubSectionID::TOWN_1);
		townOne.addRectangle(InteractiveRectangle((54.0f / 176.0f) * 100.0f, ((99.0f - 72.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townOne);

		BasePath townTwo = BasePath("Town Two", (int)MapSubSectionID::TOWN_2);
		townTwo.addRectangle(InteractiveRectangle((54.0f / 176.0f) * 100.0f, ((99.0f - 52.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townTwo);

		BasePath townThree = BasePath("Town Three", (int)MapSubSectionID::TOWN_3);
		townThree.addRectangle(InteractiveRectangle((34.0f / 176.0f) * 100.0f, ((99.0f - 52.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townThree);

		BasePath townFour = BasePath("Town Four", (int)MapSubSectionID::TOWN_4);
		townFour.addRectangle(InteractiveRectangle((55.0f / 176.0f) * 100.0f, ((99.0f - 28.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, (20.0f / 176.0f) * 100.0f, (10.0f / 99.0f) * 100.0f));
		m_paths.push_back(townFour);

		BasePath townFive = BasePath("Town Five", (int)MapSubSectionID::TOWN_5);
		townFive.addRectangle(InteractiveRectangle((94.0f / 176.0f) * 100.0f, ((99.0f - 32.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townFive);

		BasePath townSix = BasePath("Town Six", (int)MapSubSectionID::TOWN_6);
		townSix.addRectangle(InteractiveRectangle((94.0f / 176.0f) * 100.0f, ((99.0f - 52.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townSix);

		BasePath townSeven = BasePath("Town Seven", (int)MapSubSectionID::TOWN_7);
		townSeven.addRectangle(InteractiveRectangle((74.0f / 176.0f) * 100.0f, ((99.0f - 52.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townSeven);

		BasePath townEight = BasePath("Town Eight", (int)MapSubSectionID::TOWN_8);
		townEight.addRectangle(InteractiveRectangle((114.0f / 176.0f) * 100.0f, ((99.0f - 12.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townEight);

		BasePath townNine = BasePath("Town Nine", (int)MapSubSectionID::TOWN_9);
		townNine.addRectangle(InteractiveRectangle((114.0f / 176.0f) * 100.0f, ((99.0f - 32.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townNine);

		BasePath townTen = BasePath("Town Ten", (int)MapSubSectionID::TOWN_10);
		townTen.addRectangle(InteractiveRectangle((114.0f / 176.0f) * 100.0f, ((99.0f - 52.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townTen);

		BasePath townEleven = BasePath("Town Eleven", (int)MapSubSectionID::TOWN_11);
		townEleven.addRectangle(InteractiveRectangle((114.0f / 176.0f) * 100.0f, ((99.0f - 72.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townEleven);

		BasePath townTwelve = BasePath("Town Twelve", (int)MapSubSectionID::TOWN_12);
		townTwelve.addRectangle(InteractiveRectangle((74.0f / 176.0f) * 100.0f, ((99.0f - 82.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, townSize));
		m_paths.push_back(townTwelve);

		BasePath eliteFour = BasePath("Elite Four", (int)MapSubSectionID::ELITE_FOUR);
		eliteFour.addRectangle(InteractiveRectangle((139.0f / 176.0f) * 100.0f, ((99.0f - 41.0f + squareOffset) / 99.0f) * 100.0f, Color::RED, (20.0f / 176.0f) * 100.0f, (20.0f / 99.0f) * 100.0f));
		m_paths.push_back(eliteFour);
	}

	m_renderer->clearCache();

	UserMouse mouse = UserMouse(m_input);

	setMousePosition(id, &mouse);

	while (!m_input->getInputVaraibles()->back && !m_renderer->shouldClose())
	{
		mouse.move(m_renderer->getDeltaTime());
		updatePaths(&mouse);
		onUpdate(&mouse);
	}

	return -1; //TODO: Return selected section
}

void InteractiveMap::setMousePosition(MapSubSectionID id, UserMouse* mouse)
{
	for (BasePath path : m_paths)
	{
		if (path.getSectionID() != (int)id)
			continue;

		Coordinate center = path.getCenterPercent();

		mouse->setPosition(center.screenX, center.screenY);
		return;
	}
}

void InteractiveMap::updatePaths(UserMouse* mouse)
{
	for (int i = 0; i < m_paths.size(); i++)
	{
		if (!m_paths.at(i).doesIntersect(mouse->getPosition().screenX, mouse->getPosition().screenY))
			continue;

		if (i == m_pathHoverIndex)
			return;

		if (m_pathHoverIndex != -1)
			m_paths.at(m_pathHoverIndex).toggleHover();

		m_paths.at(i).toggleHover();

		m_pathHoverIndex = i;
		return;
	}

	if (m_pathHoverIndex != -1)
		m_paths.at(m_pathHoverIndex).toggleHover();

	m_pathHoverIndex = -1;
}

void InteractiveMap::updateHighlightedPath()
{
	if (m_pathHoverIndex == -1)
		return;

	float percentageX = 1.0f;
	float percentageY = 95.0f;
	float fontPercentage = 2.5f;

	float xPos = m_renderer->getResolution().x * (percentageX / 100.0f);
	float yPos = m_renderer->getResolution().y * (percentageY / 100.0f);

	unsigned int fontSize = (unsigned int)(m_renderer->getResolution().x * (fontPercentage / 100.0f));

	m_renderer->renderText(m_paths[m_pathHoverIndex].getPathName(), xPos, yPos, fontSize, Alignment::LEFT_ALIGN, Color::BLACK);
}

void InteractiveMap::onUpdate(UserMouse* mouse)
{
	m_renderer->renderImage(m_background);

	for (BasePath path : m_paths)
	{
		for (RectangleRenderData data : path.getRenderData())
		{
			m_renderer->renderRectangle(data);
		}
	}

	m_renderer->renderImage(mouse->getRenderData());

	updateHighlightedPath();

	m_renderer->onUpdate();
}

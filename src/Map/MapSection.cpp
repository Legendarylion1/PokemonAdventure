#include "MapSection.h"

MapSection::MapSection(Renderer* renderer, SectionID id, bool indoorSection)
{
	m_renderer = renderer;
	m_indoorSection = indoorSection;
	setID(id);
}

void MapSection::onUpdate()
{

	//for (std::string row : m_map)
	//{
	//	for (int i = 0; i < row.size(); i++)
	//	{
	//		std::cout << row.at(i) << ",";
	//	}
	//	std::cout << "\n";
	//}
	m_renderer->renderMap();

	for (NPT* ai : m_npt)
	{
		//std::cout << "AI \"" << ai->getName() << "\" is at (" << ai->position.coords.xTile << "," << ai->position.coords.yTile << ")" << std::endl;
		ai->onUpdate(m_renderer);
	}
}

void MapSection::setMap(std::vector<std::string> map)
{

	std::vector<std::string> reversedMap;

	for (int i = map.size() - 1; i >= 0; i--)
	{
		reversedMap.push_back(map.at(i));
	}

	m_map = reversedMap; 
}

void MapSection::setPokemonLevelCaps(int min, int max)
{
	m_pokemonMinLevel = min;
	m_pokemonMaxLevel = max;
}

void MapSection::addPokemonSpawn(PokemonSpawn pokemonSpawn)
{
	//TODO: Add error checking
	m_pokemonSpawns.push_back(pokemonSpawn);
}

void MapSection::linkSection(Coordinate coord, SectionID id, Coordinate playerSpawn)
{
	if (m_linkedSections.count(coord) == 0)
	{
		m_linkedSections[coord] = id;
		m_playerSpawn[coord] = playerSpawn;
	}
	else
	{
		logger->log(LogLevel::CRITICAL, "Linked Section has already been added", "linkSection", "MapSection");
		logger->reportCriticalError(ErrorCodes::INVALID_ELEMENT);
	}
}

void MapSection::resetAIPositions()
{
	m_reservedCoords.clear();

	for (NPT* ai : m_npt)
	{
		ai->position = ai->getOriginalPosition();
	}
}

void MapSection::loadMap(CharacterID trainerID)
{
	m_renderer->unloadCharacters();
	m_renderer->loadMap(m_id, m_map.at(0).size(), m_map.size());
	loadCharacters(trainerID);
}

void MapSection::loadCharacters(CharacterID trainerID)
{
	std::vector<CharacterID> ids = {trainerID};

	for (NPT* npt : m_npt)
		ids.push_back(npt->getID());

	m_renderer->loadCharacterTextures(ids);
}

void MapSection::unloadCharacters()
{

}

void MapSection::addSubsection(std::tuple<Range, MapSubSectionID> subsection)
{
	m_subSections.push_back(subsection);
}

char MapSection::getMapTile(Coordinate coord)
{
	if (coord.xTile < 0 || coord.yTile < 0 || (size_t)coord.xTile >= m_map.at(0).size() || (size_t)coord.yTile > m_map.size())
		return '#';

	for (Coordinate reservedCoord : m_reservedCoords)
	{
		if (reservedCoord == coord)
			return '#';
	}

	for (NPT* ai : m_npt)
	{
		if (coord == ai->position.coords)
			return 'A';
	}

	return m_map.at(coord.yTile).at(coord.xTile);
}

NPT* MapSection::getAI(Coordinate position)
{
	for (NPT* ai : m_npt)
	{
		if (ai->position.coords == position)
			return ai;
	}

	return nullptr;
}

std::vector<NPT*> MapSection::getScriptedAI()
{
	std::vector<NPT*> selectedNPT;

	for (NPT* ai : m_npt)
	{
		if (ai->position == ai->getOriginalPosition() && outOfHundred(100) && ai->getMovingStatus() == MovingStatus::STOPPED)
			selectedNPT.push_back(ai);
	}

	return selectedNPT;
}

MapSubSectionID MapSection::getSubsection(Coordinate playerPosition)
{
	if (m_subSections.size() == 0)
		return MapSubSectionID::HOME_VILLAGE;

	for (int i = 0; i < m_subSections.size(); i++)
	{
		if (std::get<0>(m_subSections.at(i)).inRange(playerPosition))
			return std::get<1>(m_subSections.at(i));
	}

	return MapSubSectionID::HOME_VILLAGE;
}

void MapSection::removeCoordinate(Coordinate coord)
{
	int count = 0;
	for (Coordinate reservedCoord : m_reservedCoords)
	{
		if (reservedCoord == coord)
		{
			m_reservedCoords.erase(m_reservedCoords.begin() + count);
			return;
		}
		count++;
	}
}

void MapSection::removeAllNPT()
{
	for (int i = m_npt.size() - 1; i >= 0; i--)
	{
		delete m_npt.at(i);
	}

	m_npt.clear();
}

void MapSection::removeNPTOnCutscene(CutSceneID id)
{
	int nptCount = m_npt.size();

	for (int i = nptCount - 1; i >= 0; i--)
	{
		if ((int)m_npt.at(i)->getCutsceneRemovalID() <= (int)id)
			m_npt.erase(m_npt.begin() + i);
	}
}

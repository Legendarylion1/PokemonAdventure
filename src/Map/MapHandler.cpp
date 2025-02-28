#include "MapHandler.h"

MapHandler::MapHandler(Trainer* trainer, Renderer* renderer)
{
	m_trainer = trainer;
	
	// TODO: Map Sections should be created when they are entered and destroyed on exit
	// This will take up lots of storage with more npts and pokemon being added
	// Please Fix :)
	
	createPokemonCenter(renderer);
	createPokemart(renderer);
	createHomeVillageRoute1(renderer);
	createFirstTownRoute2(renderer);
	createStartHouseBaseFloor(renderer);
	createStartHouseUpstairsRoom(renderer);
	createProfLab(renderer);
}

void MapHandler::onUpdate()
{
	//TODO: Display When we switch subsections
	// Only when we switch subsections outdoors.

	swapSections();
	m_mapSections[m_currentSection].onUpdate();
	//m_trainer->printLocation();
}

void MapHandler::respawnAfterWhiteOut()
{
	m_currentSection = m_respawnPoint.mainSection;
	m_previousSection = m_respawnPoint.prevSection;

	m_trainer->position.coords = m_respawnPoint.currentSectionSpawn;
	m_trainer->position.direction = Direction::DOWN;

	m_previousSectionSpawn = m_respawnPoint.prevSectionSpawn;

	fullRestoreTrainerAfterRespawn();

	m_mapSections[m_currentSection].resetAIPositions();
	m_mapSections[m_currentSection].loadMap(m_trainer->getID());
}

std::string MapHandler::save()
{
	return std::to_string((int)m_currentSection) 
		+ "," + std::to_string((int)m_previousSection) 
		+ "," + std::to_string(m_previousSectionSpawn.xTile) 
		+ "," + std::to_string(m_previousSectionSpawn.yTile) 
		+ "," + std::to_string(m_autoSave)
		+ "," + std::to_string((int)m_respawnPoint.mainSection)
		+ "," + std::to_string((int)m_respawnPoint.prevSection)
		+ "," + std::to_string(m_respawnPoint.currentSectionSpawn.xTile)
		+ "," + std::to_string(m_respawnPoint.currentSectionSpawn.yTile)
		+ "," + std::to_string(m_respawnPoint.prevSectionSpawn.xTile)
		+ "," + std::to_string(m_respawnPoint.prevSectionSpawn.yTile);
}

void MapHandler::load(std::vector<std::string> data)
{
	m_currentSection = SectionID(std::stoi(data.at(0)));
	m_previousSection = SectionID(std::stoi(data.at(1)));
	m_previousSectionSpawn.xTile = std::stoi(data.at(2));
	m_previousSectionSpawn.yTile = std::stoi(data.at(3));
	m_autoSave = std::stoi(data.at(4));

	m_respawnPoint.mainSection = SectionID(std::stoi(data.at(5)));
	m_respawnPoint.prevSection = SectionID(std::stoi(data.at(6)));
	m_respawnPoint.currentSectionSpawn.xTile = std::stoi(data.at(7));
	m_respawnPoint.currentSectionSpawn.yTile = std::stoi(data.at(8));
	m_respawnPoint.prevSectionSpawn.xTile = std::stoi(data.at(9));
	m_respawnPoint.prevSectionSpawn.yTile = std::stoi(data.at(10));
	
	m_mapSections[m_currentSection].resetAIPositions();
	m_mapSections[m_currentSection].loadMap(m_trainer->getID());
}

void MapHandler::loadNewGame()
{
	m_mapSections[m_currentSection].loadMap(m_trainer->getID());

}

bool MapHandler::shouldAutoSave()
{
	if (!m_autoSave)
		return false;

	if (getSwappedSections())
		return true;

	return false;
}

MapSubSectionID MapHandler::getSubsection()
{
	if (m_mapSections[m_currentSection].isIndoorSection())
		return m_lastOutdoorSubsection;

	return m_mapSections[m_currentSection].getSubsection(m_trainer->position.coords);
}

void MapHandler::addMapSection(MapSection section)
{
	if (m_mapSections.count(section.getID()) == 0)
		m_mapSections[section.getID()] = section;
	else
	{
		logger->log(LogLevel::CRITICAL, "Map Section has already been added", "addMapSection", "MapHandler");
		logger->reportCriticalError(ErrorCodes::INVALID_ELEMENT);
	}
}

void MapHandler::removeNPTOnCutscene(CutSceneID id)
{
	for (auto section = m_mapSections.begin(); section != m_mapSections.end(); section++)
	{
		section->second.removeNPTOnCutscene(id);
	}
}

void MapHandler::swapSections()
{
	m_swappedSections = false;

	if (m_mapSections[m_currentSection].getMapTile(m_trainer->position.coords) != 'L')
		return;

	m_swappedSections = true;

	// TODO: Add direction to player spawn
	Coordinate playerSpawn = m_mapSections[m_currentSection].getPlayerSpawn(m_trainer->position.coords);
	SectionID linkedSection = m_mapSections[m_currentSection].getLinkedSection(m_trainer->position.coords);

	if (linkedSection == SectionID::PREVIOUS_SECTION)
	{
		m_currentSection = m_previousSection;
		m_trainer->position.coords = m_previousSectionSpawn;

		m_mapSections[m_currentSection].resetAIPositions();
		m_mapSections[m_currentSection].loadMap(m_trainer->getID());
		return;
	}
	else if (m_mapSections[linkedSection].isIndoorSection() && !m_mapSections[m_currentSection].isIndoorSection())	//Indoor to Indoor Section Check
	{
		m_previousSection = m_currentSection;
		m_previousSectionSpawn = m_trainer->position.coords;
		m_lastOutdoorSubsection = m_mapSections[m_currentSection].getSubsection(m_trainer->position.coords);

		switch (m_trainer->position.direction)
		{
		case Direction::UP:
			m_previousSectionSpawn.yTile--;
			break;
		case Direction::DOWN:
			m_previousSectionSpawn.yTile++;
			break;
		case Direction::LEFT:
			m_previousSectionSpawn.xTile++;
			break;
		case Direction::RIGHT:
			m_previousSectionSpawn.xTile--;
			break;
		}
	}

	m_currentSection = linkedSection;
	m_trainer->position.coords = playerSpawn;

	setRespawnPoint();

	m_mapSections[m_currentSection].resetAIPositions();
	m_mapSections[m_currentSection].loadMap(m_trainer->getID());
}

void MapHandler::setRespawnPoint()
{
	if (m_mapSections[m_currentSection].getWhiteoutRespawnPoint() == Coordinate{ -1,-1 })
		return;

	m_respawnPoint = PlayerRespawn{ m_currentSection, m_previousSection, m_mapSections[m_currentSection].getWhiteoutRespawnPoint(), m_previousSectionSpawn };
}

void MapHandler::fullRestoreTrainerAfterRespawn()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_trainer->getRoster()[i].getLevel() == 0)
			continue;

		m_trainer->getRoster()[i].fullRestore();

		Moveset moves = m_trainer->getRoster()[i].getMoveset();

		if (moves.move1 != NONE)
			moves.move1pp = getAttackFromID(moves.move1)->getPP();

		if (moves.move2 != NONE)
			moves.move2pp = getAttackFromID(moves.move2)->getPP();

		if (moves.move3 != NONE)
			moves.move3pp = getAttackFromID(moves.move3)->getPP();

		if (moves.move4 != NONE)
			moves.move4pp = getAttackFromID(moves.move4)->getPP();

		m_trainer->getRoster()[i].setMoveset(moves);
	}
}

bool MapHandler::isValidCharacterPosition(Coordinate coords)
{
	char tile = m_mapSections[m_currentSection].getMapTile(coords);

	switch (tile)
	{
	case '#':
	case 'I':
	case 'W':
	case 'N':
	case 'P':
	case 'C':
	case 'A':
		return false;
	default:
		return true;
	}


	//Add all of the checks for the tile. If it is the player AI and everything
}

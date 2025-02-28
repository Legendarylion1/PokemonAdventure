#pragma once
#include "MapSection.h"

struct PlayerRespawn
{
	SectionID mainSection = SectionID::START_HOUSE_ROOM;
	SectionID prevSection = SectionID::START_HOUSE_ROOM;
	Coordinate currentSectionSpawn = Coordinate{4, 3};
	Coordinate prevSectionSpawn = Coordinate{ 4, 3 };
};

class MapHandler
{
public:
	MapHandler() {};
	MapHandler(Trainer* trainer, Renderer* renderer);

	void onUpdate();

	void respawnAfterWhiteOut();

	std::string save();
	void load(std::vector<std::string> data);

	void loadNewGame();

	//void setup() { m_mapSections[m_currentSection].loadMap(); };	//TODO: Consider Removing

	bool shouldAutoSave();

	void toggleFasterText()
	{
		if (m_autoSave)
			m_autoSave = false;
		else
			m_autoSave = true;
	}

	void adjustPauseDisplay(std::string* autoSave)
	{
		if (m_autoSave)
			*autoSave = "ON";
		else
			*autoSave = "OFF";
	}

	bool isValidCharacterPosition(Coordinate coords);
	char getPlayerTile() { return  m_mapSections[m_currentSection].getMapTile(m_trainer->position.coords); };
	char getTile(Coordinate coord) { return m_mapSections[m_currentSection].getMapTile(coord); };
	SectionID getCurrentSection() { return m_currentSection; }
	SectionID getPrevSection() { return m_previousSection; }
	bool getSwappedSections() { return m_swappedSections; }
	MapSubSectionID getSubsection();

public:
	void addMapSection(MapSection section);

	std::vector<PokemonSpawn> getPokemonSpawns() { return m_mapSections[m_currentSection].getPokemonSpawns(); };
	int getPokemonMinLevel() { return m_mapSections[m_currentSection].getPokemonMinLevel(); };
	int getPokemonMaxLevel() { return m_mapSections[m_currentSection].getPokemonMaxLevel(); };

	NPT* getAI(Coordinate aiPosition) { return m_mapSections[m_currentSection].getAI(aiPosition); };
	NPT* getAI(int index) { return m_mapSections[m_currentSection].getAI(index); };
	NPT* getAI(SectionID id, int index) { return m_mapSections[id].getAI(index); };
	std::vector<NPT*> getAllAI() { return m_mapSections[m_currentSection].getAllAI(); };
	std::vector<NPT*> getScriptedAI() { return m_mapSections[m_currentSection].getScriptedAI(); };

	void reserveCoordinate(Coordinate coord) { m_mapSections[m_currentSection].reserveCoordinate(coord); };
	void removeCoordinate(Coordinate coord) { m_mapSections[m_currentSection].removeCoordinate(coord); };

	void removeNPTOnCutscene(CutSceneID id);

private:
	void swapSections();
	void setRespawnPoint();

	void fullRestoreTrainerAfterRespawn();

private:

	void createPokemonCenter(Renderer* renderer);
	void createPokemart(Renderer* renderer);
	void createHomeVillageRoute1(Renderer* renderer);
	void createFirstTownRoute2(Renderer* renderer);
	void createStartHouseBaseFloor(Renderer* renderer);
	void createStartHouseUpstairsRoom(Renderer* renderer);
	void createProfLab(Renderer* renderer);

private:
	Trainer* m_trainer = nullptr;

	SectionID m_currentSection = SectionID::START_HOUSE_ROOM;
	SectionID m_previousSection = SectionID::START_HOUSE_ROOM;
	Coordinate m_previousSectionSpawn;

	PlayerRespawn m_respawnPoint;
	MapSubSectionID m_lastOutdoorSubsection = MapSubSectionID::HOME_VILLAGE;

	std::unordered_map<SectionID, MapSection> m_mapSections;

	bool m_swappedSections = false;
	bool m_autoSave = true;
};
#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "../Characters/Trainer/NPT.h"
#include "../Characters/Pokemon/Pokemon.h"

struct PokemonSpawn
{
	Rarity rarity;
	PokemonID pokemon;
};

struct Range
{
	int bottomLeftX;
	int bottomLeftY;
	int topRightX;
	int topRightY;

	bool inRange(Coordinate coord)
	{
		if (coord.xTile >= bottomLeftX && coord.xTile <= topRightX)
		{
			if (coord.yTile >= bottomLeftY && coord.yTile <= topRightY)
			{
				return true;
			}
		}
		return false;
	}
};

class MapSection
{
public:
	MapSection() {};
	MapSection(Renderer* renderer, SectionID id, bool embeddedSection = false);

	void setID(SectionID id) { m_id = id; };
	SectionID getID() { return m_id; };

	void onUpdate();

	bool isIndoorSection() { return m_indoorSection; };

	void setMap(std::vector<std::string> map);
	void setPokemonLevelCaps(int min, int max);
	void setWhiteoutRespawnPoint(Coordinate coordinate) { m_whiteoutRespawnPoint = coordinate; }
	void addPokemonSpawn(PokemonSpawn pokemonSpawn);
	void linkSection(Coordinate coord, SectionID id, Coordinate playerSpawn = {NONE, NONE});
	void resetAIPositions();
	void loadMap(CharacterID trainerID);
	void loadCharacters(CharacterID trainerID);
	void unloadCharacters();
	void addSubsection(std::tuple<Range, MapSubSectionID> subsection);

	char getMapTile(Coordinate coord);
	std::vector<PokemonSpawn> getPokemonSpawns() { return m_pokemonSpawns; };
	int getPokemonMinLevel() { return m_pokemonMinLevel; };
	int getPokemonMaxLevel() { return m_pokemonMaxLevel; };
	Coordinate getPlayerSpawn(Coordinate coord) { return m_playerSpawn[coord]; };
	Coordinate getWhiteoutRespawnPoint() { return m_whiteoutRespawnPoint; }
	SectionID getLinkedSection(Coordinate coord) { return m_linkedSections[coord]; };
	NPT* getAI(Coordinate position);
	NPT* getAI(int index) { return m_npt.at(index); };
	std::vector<NPT*> getAllAI() { return m_npt; };
	std::vector<NPT*> getScriptedAI();
	MapSubSectionID getSubsection(Coordinate playerPosition);

public:
	void addNPT(NPT* npt) { m_npt.push_back(npt); };

	void reserveCoordinate(Coordinate coord) { m_reservedCoords.push_back(coord); };
	void removeCoordinate(Coordinate coord);

	void removeAllNPT();
	void removeNPTOnCutscene(CutSceneID id);
private:
	Renderer* m_renderer = nullptr;
	SectionID m_id = SectionID::HOME_VILLAGE_ROUTE_1;

	bool m_indoorSection = false;

	int m_pokemonMinLevel = 1;
	int m_pokemonMaxLevel = 1;

	std::vector<PokemonSpawn> m_pokemonSpawns;
	std::vector<std::string> m_map;
	std::vector<Coordinate> m_reservedCoords;
	std::vector<NPT*> m_npt;
	std::vector<std::tuple<Range, MapSubSectionID>> m_subSections;

	Coordinate m_whiteoutRespawnPoint = Coordinate{ -1,-1 };

	std::unordered_map<Coordinate, SectionID, CoordinateHashFunction> m_linkedSections;
	std::unordered_map<Coordinate, Coordinate, CoordinateHashFunction> m_playerSpawn;
};
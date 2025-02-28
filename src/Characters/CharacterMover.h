#pragma once

#include "../Characters/Trainer/NPT.h"
#include "../Map/MapHandler.h"
#include <tuple>

class CharacterMover
{
public:

	CharacterMover() {};
	CharacterMover(MapHandler* mapHandler, Timer* timer):m_mapHandler(mapHandler), m_timer(timer) {};

	void onUpdate();
	void setTileSize(float tileSize) { m_tileSize = tileSize; };

	bool moveCharacter(Trainer* character, Direction direction);
	bool turnCharacter(Trainer* character, Direction direction);
	void addScriptedAI(NPT* npt){ 
		m_scriptCharacters.push_back(std::make_tuple(npt, 0)); 
	};

	void setPriorityOnly(bool value) { m_priorityOnly = value; };
	bool priorityQueueEmpty() { return m_priorityCharacters.size() == 0; };


private:
	void clearQueues();
	void getScriptedAI();
	void addCharacterDirection(Trainer* character, InstructionType type, Direction direction);

	void moveCharacters();
	void movePriorityCharacters();
	void moveScriptCharacters();

	void removeCharacters(std::vector<int> indexes);
	void removePriorityCharacters(std::vector<int> indexes);

private:

	bool moveUp(Trainer* character);
	bool moveDown(Trainer* character);
	bool moveLeft(Trainer* character);
	bool moveRight(Trainer* character);

	void animateMove(Trainer* character);

	bool turnUp(Trainer* character);
	bool turnDown(Trainer* character);
	bool turnLeft(Trainer* character);
	bool turnRight(Trainer* character);

	void animateTurn(Trainer* character, Direction direction);
	

	MapHandler* m_mapHandler = nullptr;
	Timer* m_timer = nullptr;

	bool m_priorityOnly = false;

	std::vector<std::tuple<Trainer*, CharacterMoveDirections >> m_characters;
	std::vector<std::tuple<Trainer*, CharacterMoveDirections>> m_priorityCharacters;
	std::vector<std::tuple<NPT*, int>> m_scriptCharacters;

private:
	float m_tileSize = 200;
	float m_movementSpeed = 2.0f;
	float m_turnSpeed = 6.0f;
	float m_sprintIncrease = 1.5f;
};
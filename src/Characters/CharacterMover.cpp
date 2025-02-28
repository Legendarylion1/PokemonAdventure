#include "CharacterMover.h"

void CharacterMover::onUpdate()
{
	if (m_mapHandler->getSwappedSections())
		clearQueues();

	getScriptedAI();

	if (!m_priorityOnly)
	{
		moveScriptCharacters();
		moveCharacters();
	}
	else
		movePriorityCharacters();
}

bool CharacterMover::moveCharacter(Trainer* character, Direction direction)
{
	if (character->getMovingStatus() == MovingStatus::MOVING)
		return false;

	if (character->position.direction != direction)
	{
		turnCharacter(character, direction);
		return false;
	}

	Coordinate reserveCoordinate;

	switch (direction)
	{
	case Direction::UP:
		reserveCoordinate = { character->position.coords.xTile,character->position.coords.yTile + 1 };
		break;
	case Direction::DOWN:
		reserveCoordinate = { character->position.coords.xTile,character->position.coords.yTile - 1 };
		break;
	case Direction::LEFT:
		reserveCoordinate = { character->position.coords.xTile - 1,character->position.coords.yTile };
		break;
	case Direction::RIGHT:
		reserveCoordinate = { character->position.coords.xTile + 1,character->position.coords.yTile };
		break;
	}

	if (!m_mapHandler->isValidCharacterPosition(reserveCoordinate))
		return false;

	m_mapHandler->reserveCoordinate(reserveCoordinate);
	addCharacterDirection(character, InstructionType::MOVE, direction);
	return true;
}

bool CharacterMover::turnCharacter(Trainer* character, Direction direction)
{
	if (character->position.direction == direction)
		return false;

	addCharacterDirection(character, InstructionType::TURN, direction);
	return true;
}

void CharacterMover::clearQueues()
{
	//TODO: Make sure to set their screen pos to 0

	for (int i = m_characters.size() - 1; i >= 0; i--)
	{
		std::get<0>(m_characters.at(i))->setMovingStatus(MovingStatus::STOPPED);
		std::get<0>(m_characters.at(i))->position.coords.screenX = 0;
		std::get<0>(m_characters.at(i))->position.coords.screenY = 0;
		std::get<0>(m_characters.at(i))->position.turnCount = 0;

		m_characters.erase(m_characters.begin() + i);
	}

	for (int i = m_priorityCharacters.size() - 1; i >= 0; i--)
	{
		std::get<0>(m_priorityCharacters.at(i))->setMovingStatus(MovingStatus::STOPPED);

		std::get<0>(m_priorityCharacters.at(i))->position.coords.screenX;
		std::get<0>(m_priorityCharacters.at(i))->position.coords.screenY;
		std::get<0>(m_priorityCharacters.at(i))->position.turnCount = 0;

		m_priorityCharacters.erase(m_priorityCharacters.begin() + i);
	}

	m_scriptCharacters.clear();
}

void CharacterMover::getScriptedAI()
{
	for (NPT* npt : m_mapHandler->getScriptedAI())
		addScriptedAI(npt);
}

void CharacterMover::addCharacterDirection(Trainer* character, InstructionType type, Direction direction)
{
	character->setMovingStatus(MovingStatus::MOVING);

	CharacterMoveDirections directions = { type, direction };

	if (!m_priorityOnly)
	{
		m_characters.push_back( std::make_tuple( character, directions));
	}
	else
	{
		m_priorityCharacters.push_back(std::make_tuple(character, directions));
	}
	
}

void CharacterMover::moveCharacters()
{
	std::vector<int> removeIndexes;
	
	for (size_t i = 0; i < m_characters.size(); i++)
	{
		if (std::get<1>(m_characters.at(i)).type == InstructionType::MOVE)
		{

			switch (std::get<1>(m_characters.at(i)).direction)
			{
			case Direction::UP:
				if (moveUp(std::get<0>(m_characters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::DOWN:
				if (moveDown(std::get<0>(m_characters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::LEFT:
				if(moveLeft(std::get<0>(m_characters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::RIGHT:
				if(moveRight(std::get<0>(m_characters.at(i))))
					removeIndexes.push_back(i);
				break;
			}
		}
		else
		{
			switch (std::get<1>(m_characters.at(i)).direction)
			{
			case Direction::UP:
				if(turnUp(std::get<0>(m_characters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::DOWN:
				if(turnDown(std::get<0>(m_characters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::LEFT:
				if(turnLeft(std::get<0>(m_characters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::RIGHT:
				if(turnRight(std::get<0>(m_characters.at(i))))
					removeIndexes.push_back(i);
				break;
			}
		}
		
	}

	removeCharacters(removeIndexes);
}

void CharacterMover::movePriorityCharacters()
{
	std::vector<int> removeIndexes;

	for (size_t i = 0; i < m_priorityCharacters.size(); i++)
	{
		if (std::get<1>(m_priorityCharacters.at(i)).type == InstructionType::MOVE)
		{

			switch (std::get<1>(m_priorityCharacters.at(i)).direction)
			{
			case Direction::UP:
				if (moveUp(std::get<0>(m_priorityCharacters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::DOWN:
				if (moveDown(std::get<0>(m_priorityCharacters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::LEFT:
				if (moveLeft(std::get<0>(m_priorityCharacters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::RIGHT:
				if (moveRight(std::get<0>(m_priorityCharacters.at(i))))
					removeIndexes.push_back(i);
				break;
			}
		}
		else
		{
			switch (std::get<1>(m_priorityCharacters.at(i)).direction)
			{
			case Direction::UP:
				if (turnUp(std::get<0>(m_priorityCharacters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::DOWN:
				if (turnDown(std::get<0>(m_priorityCharacters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::LEFT:
				if (turnLeft(std::get<0>(m_priorityCharacters.at(i))))
					removeIndexes.push_back(i);
				break;
			case Direction::RIGHT:
				if (turnRight(std::get<0>(m_priorityCharacters.at(i))))
					removeIndexes.push_back(i);
				break;
			}
		}

	}

	removePriorityCharacters(removeIndexes);
}

void CharacterMover::moveScriptCharacters()
{
	std::vector<int> removeIndexes;

	for (size_t i = 0; i < m_scriptCharacters.size(); i++)
	{

		if (!std::get<0>(m_scriptCharacters.at(i))->wantsToMove())
		{
			removeIndexes.push_back(i);
			continue;
		}

		if (std::get<0>(m_scriptCharacters.at(i))->getMovingStatus() == MovingStatus::MOVING)
			continue;

		if (std::get<0>(m_scriptCharacters.at(i))->getScript().size() == std::get<1>(m_scriptCharacters.at(i)))
		{
			removeIndexes.push_back(i);
			continue;
		}

		//std::get<0>(m_scriptCharacters.at(i))->setMovingStatus(MovingStatus::MOVING);
		//m_characters.push_back(std::make_tuple(std::get<0>(m_scriptCharacters.at(i)), std::get<0>(m_scriptCharacters.at(i))->getScript().at(std::get<1>(m_scriptCharacters.at(i)))));

		CharacterMoveDirections instruction = std::get<0>(m_scriptCharacters.at(i))->getScript().at(std::get<1>(m_scriptCharacters.at(i)));

		
		if (instruction.type == InstructionType::MOVE && moveCharacter(std::get<0>(m_scriptCharacters.at(i)), instruction.direction))
			std::get<1>(m_scriptCharacters.at(i))++;
		else if (instruction.type == InstructionType::TURN && turnCharacter(std::get<0>(m_scriptCharacters.at(i)), instruction.direction))
			std::get<1>(m_scriptCharacters.at(i))++;
	}

	for (int i = removeIndexes.size() - 1; i >= 0; i--)
		m_scriptCharacters.erase(m_scriptCharacters.begin() + removeIndexes.at(i));
}

void CharacterMover::removeCharacters(std::vector<int> indexes)
{
	for (int i = indexes.size() - 1; i >= 0; i--)
	{
		std::get<0>(m_characters.at(indexes.at(i)))->setMovingStatus(MovingStatus::STOPPED);

		m_mapHandler->removeCoordinate(std::get<0>(m_characters.at(indexes.at(i)))->position.coords);

		m_characters.erase(m_characters.begin() + indexes.at(i));
	}
}

void CharacterMover::removePriorityCharacters(std::vector<int> indexes)
{

	for (int i = indexes.size() - 1; i >= 0; i--)
	{
		std::get<0>(m_priorityCharacters.at(indexes.at(i)))->setMovingStatus(MovingStatus::STOPPED);

		m_mapHandler->removeCoordinate(std::get<0>(m_priorityCharacters.at(indexes.at(i)))->position.coords);

		m_priorityCharacters.erase(m_priorityCharacters.begin() + indexes.at(i));
	}

}

bool CharacterMover::moveUp(Trainer* character)
{
	float movementIncrease = 1.0f;

	if (character->getIsSprinting())
		movementIncrease = m_sprintIncrease;

	if (abs(character->position.coords.screenY) + (m_tileSize * m_timer->getDelta() * m_movementSpeed * movementIncrease) >= m_tileSize)
	{
		character->position.coords.yTile += 1;
		character->position.coords.screenY = 0.0f;
		return true;
	}

	character->position.coords.screenY += (m_tileSize * m_timer->getDelta() * m_movementSpeed * movementIncrease);
	animateMove(character);

	return false;
}

bool CharacterMover::moveDown(Trainer* character)
{
	float movementIncrease = 1.0f;

	if (character->getIsSprinting())
		movementIncrease = m_sprintIncrease;

	if (abs(character->position.coords.screenY) + (m_tileSize * m_timer->getDelta() * m_movementSpeed * movementIncrease) >= m_tileSize)
	{
		character->position.coords.yTile -= 1;
		character->position.coords.screenY = 0.0f;
		return true;
	}

	character->position.coords.screenY -= (m_tileSize * m_timer->getDelta() * m_movementSpeed * movementIncrease);
	animateMove(character);

	return false;
}

bool CharacterMover::moveLeft(Trainer* character)
{
	float movementIncrease = 1.0f;

	if (character->getIsSprinting())
		movementIncrease = m_sprintIncrease;

	if (abs(character->position.coords.screenX) + (m_tileSize * m_timer->getDelta() * m_movementSpeed * movementIncrease) >= m_tileSize)
	{
		character->position.coords.xTile -= 1;
		character->position.coords.screenX = 0.0f;
		return true;
	}

	character->position.coords.screenX -= (m_tileSize * m_timer->getDelta() * m_movementSpeed * movementIncrease);
	animateMove(character);

	return false;
}

bool CharacterMover::moveRight(Trainer* character)
{
	float movementIncrease = 1.0f;

	if (character->getIsSprinting())
		movementIncrease = m_sprintIncrease;

	if (abs(character->position.coords.screenX) + (m_tileSize * m_timer->getDelta() * m_movementSpeed * movementIncrease) >= m_tileSize)
	{
		character->position.coords.xTile += 1;
		character->position.coords.screenX = 0.0f;
		return true;
	}

	character->position.coords.screenX += (m_tileSize * m_timer->getDelta() * m_movementSpeed * movementIncrease);
	animateMove(character);

	return false;
}

void CharacterMover::animateMove(Trainer* character)
{
	if (character->position.spriteState == SpriteState::IDLE && (abs(character->position.coords.screenX) > m_tileSize * (2.0f / 3.0f) || abs(character->position.coords.screenY) > m_tileSize * (2.0f / 3.0f)))
		return;

	if (character->position.spriteState != SpriteState::IDLE && (abs(character->position.coords.screenX) > m_tileSize * (2.0f / 3.0f) || abs(character->position.coords.screenY) > m_tileSize * (2.0f / 3.0f)))
	{
		character->position.spriteState = SpriteState::IDLE;
	}
	else if (character->position.spriteState == SpriteState::IDLE && (abs(character->position.coords.screenX) > m_tileSize * (1.0f / 3.0f) || abs(character->position.coords.screenY) > m_tileSize * (1.0f / 3.0f)))
	{

		SpriteState last = character->getLastStep();

		if (last == SpriteState::STEP1)
		{
			character->setLastStep(SpriteState::STEP2);
			character->position.spriteState = SpriteState::STEP2;
		}
		else
		{
			character->setLastStep(SpriteState::STEP1);
			character->position.spriteState = SpriteState::STEP1;
		}
	}
}

bool CharacterMover::turnUp(Trainer* character)
{
	float movementIncrease = 1.0f;

	if (character->getIsSprinting())
		movementIncrease = m_sprintIncrease;

	if (abs(character->position.turnCount) + (m_tileSize * m_timer->getDelta() * m_turnSpeed * movementIncrease) >= m_tileSize)
	{
		character->position.turnCount = 0.0f;
		character->position.direction = Direction::UP;
		return true;
	}

	character->position.turnCount -= (m_tileSize * m_timer->getDelta() * m_turnSpeed * movementIncrease);

	animateTurn(character, Direction::UP);
	return false;
}

bool CharacterMover::turnDown(Trainer* character)
{
	float movementIncrease = 1.0f;

	if (character->getIsSprinting())
		movementIncrease = m_sprintIncrease;

	if (abs(character->position.turnCount) + (m_tileSize * m_timer->getDelta() * m_turnSpeed * movementIncrease) >= m_tileSize)
	{
		character->position.turnCount = 0.0f;
		character->position.direction = Direction::DOWN;
		return true;
	}

	character->position.turnCount -= (m_tileSize * m_timer->getDelta() * m_turnSpeed * movementIncrease);

	animateTurn(character, Direction::DOWN);
	return false;
}

bool CharacterMover::turnLeft(Trainer* character)
{
	float movementIncrease = 1.0f;

	if (character->getIsSprinting())
		movementIncrease = m_sprintIncrease;

	if (abs(character->position.turnCount) + (m_tileSize * m_timer->getDelta() * m_turnSpeed * movementIncrease) >= m_tileSize)
	{
		character->position.turnCount = 0.0f;
		character->position.direction = Direction::LEFT;
		return true;
	}

	character->position.turnCount -= (m_tileSize * m_timer->getDelta() * m_turnSpeed * movementIncrease);

	animateTurn(character, Direction::LEFT);
	return false;
}

bool CharacterMover::turnRight(Trainer* character)
{
	float movementIncrease = 1.0f;

	if (character->getIsSprinting())
		movementIncrease = m_sprintIncrease;

	if (abs(character->position.turnCount) + (m_tileSize * m_timer->getDelta() * m_turnSpeed * movementIncrease) >= m_tileSize)
	{
		character->position.turnCount = 0.0f;
		character->position.direction = Direction::RIGHT;
		return true;
	}

	character->position.turnCount -= (m_tileSize * m_timer->getDelta() * m_turnSpeed * movementIncrease);

	animateTurn(character, Direction::RIGHT);
	return false;
}

void CharacterMover::animateTurn(Trainer* character, Direction direction)
{
	if (character->position.direction == direction)
		return;

	if (abs(character->position.turnCount) >= m_tileSize / 2.0f)
		character->position.direction = direction;
}

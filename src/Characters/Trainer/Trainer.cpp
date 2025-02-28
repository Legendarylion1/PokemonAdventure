#include "Trainer.h"

Trainer::Trainer(std::string name, CharacterID id)
{
	m_name = name;
	m_id = id;
}

void Trainer::onUpdate(Renderer* renderer)
{
	renderer->renderCharacter(position, m_id);
}

void Trainer::load(TrainerSave save)
{
	m_name = save.name;
	m_money = save.money;
	m_badges = save.badgeCount;
	position.coords.xTile = save.x;
	position.coords.yTile = save.y;
	position.direction = Direction(save.direction);
	m_id = (CharacterID)save.characterID;
}

bool Trainer::unableToBattle()
{

	for (int i = 0; i < 6; i++)
	{
		if (m_roster[i].getCurHealth() > 0)
			return false;
	}

	return true;
}

void Trainer::setPokemon(int index, Pokemon pokemon)
{
	m_roster[index] = pokemon;
}

Pokemon Trainer::getPokemon(int index)
{
	return m_roster[index];
}

ItemStorage* Trainer::getItemStorage()
{
	return &m_itemStorage;
}

void Trainer::addItem(ItemID item)
{
	m_itemStorage.addItem(item);
}

void Trainer::removeItem(ItemID item)
{
	m_itemStorage.removeItem(item);
}

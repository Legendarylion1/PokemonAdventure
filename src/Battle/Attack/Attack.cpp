#include "Attack.h"

// Initialize static members
AttackSingleton* AttackSingleton::instancePtr = nullptr;
std::mutex AttackSingleton::mtx;

Attack* AttackSingleton::m_attack = nullptr;
int AttackSingleton::m_currentID = -2;

Attack* AttackSingleton::getAttack(int id)
{
	if (id == m_currentID)
		return m_attack;

	if (m_attack != nullptr)
		delete m_attack;

	switch (AttackID(id))
	{
	case AttackID::STRUGGLE:
		m_attack = new Attack("Struggle", Type::NORMAL, PowerType::PHYSICAL, 5, 1, 0, 100, "");
		break;
	case AttackID::HYPERFANG:
		m_attack = new HyperFang("Hyper Fang", Type::GRASS, PowerType::PHYSICAL, 80, 10, 30, 100, "Attacker strikes with a strong bite!");
		break;
	case AttackID::EMBER:
		m_attack = new Ember("Ember", Type::FIRE, PowerType::SPECIAL, 5, 10, 0, 80, "Throws fire at the opponent setting them ablaze!");
		break;
	case AttackID::BONERUSH:
		m_attack = new BoneRush("BoneRush", Type::WATER, PowerType::PHYSICAL, 10, 10, 10, 50, "Up to 5 strong bones are thrown at the opponent");
		break;
	case AttackID::TORPID_PUNCH:
		m_attack = new TorpidPunch("Torpid Punch", Type::GRASS, PowerType::PHYSICAL, 5, 10, 50, 50, "A carefully placed punch is thrown at the oppoenet. They are more likely to go to sleep the lower their hp");
		break;
	case AttackID::GET_PUMPED:
		m_attack = new GetPumped("Get Pumped", Type::NONE, PowerType::PHYSICAL, 0, 10, 0, 100, "The user gets excited to fight raising their attack sharply");
		break;
	case AttackID::LONG_JAB:
		m_attack = new LongJab("Long Jab", Type::WATER, PowerType::PHYSICAL, 20, 10, 0, 100, "A jab is thrown for a far distance with a chance to flinch its target");
		break;
	case AttackID::DIG:
		m_attack = new Dig("Dig", Type::FIRE, PowerType::SPECIAL, 20, 5, 0, 95, "The user burrows underground before striking up at the opponent the next turn");
		break;
	case AttackID::SPLASH:
		m_attack = new Attack("Splash", Type::WATER, PowerType::PHYSICAL, 15, 10, 0, 100, "The user flails in water causing all excess to damage other pokemon");
		break;
	case AttackID::LEAF_SMACK:
		m_attack = new Attack("Leaf Smack", Type::WATER, PowerType::PHYSICAL, 15, 10, 0, 100, "The user smacks their opponent with a leaf");
		break;
	default:
		m_attack = new Attack("NONE", Type::NONE, PowerType::PHYSICAL, 0, 0, 0, 0, "");
	}

	m_currentID = id;
	return m_attack;
}
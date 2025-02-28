#pragma once
#include <string>
#include "../GlobalData/globalIDs.h"
#include "../Menu/menuData.h"

const static std::string comma = ",";

struct HeaderSave
{
	std::string playerName;
	std::string playTime;
	int pokedexFound;
	int badgesObtained;
	bool fasterText;
	int cutscene;

	operator std::string const()
	{
		return playerName + comma + playTime + comma + std::to_string(pokedexFound) + comma + std::to_string(badgesObtained) + comma + std::to_string(fasterText) + comma + std::to_string(cutscene) + "\n";
	}
};

struct PokemonSave
{
	std::string name;
	PokemonID species;

	int level;
	int currentHealth;
	int currentXP;

	// Stats
	int hpIv, attackIv, defenseIv, speedIv, specialIv;
	int hpEv, attackEv, defenseEv, spattackEv, spDefenseEv, speedEv, evasionEv, accuracyEv;

	// Move Data
	int move1, move2, move3, move4;
	int move1pp, move2pp, move3pp, move4pp;

	// Status Condition Tracker
	int statusID, turnCount, forcedAttack;
	bool isBlocker, isEvasive;

	operator std::string const()
	{
		return name + comma + std::to_string(species) + comma + std::to_string(level) + comma + std::to_string(currentHealth)
			+ comma + std::to_string(currentXP) + comma + std::to_string(hpIv) + comma + std::to_string(attackIv)
			+ comma + std::to_string(defenseIv) + comma + std::to_string(speedIv) + comma + std::to_string(specialIv)
			+ comma + std::to_string(hpEv) + comma + std::to_string(attackEv) + comma + std::to_string(defenseEv)
			+ comma + std::to_string(spattackEv) + comma + std::to_string(spDefenseEv) + comma + std::to_string(speedEv)
			+ comma + std::to_string(evasionEv) + comma + std::to_string(accuracyEv) + comma + std::to_string(move1)
			+ comma + std::to_string(move2) + comma + std::to_string(move3) + comma + std::to_string(move4)
			+ comma + std::to_string(move1pp) + comma + std::to_string(move2pp) + comma + std::to_string(move3pp)
			+ comma + std::to_string(move4pp) + comma + std::to_string(statusID) + comma + std::to_string(turnCount)
			+ comma + std::to_string(isBlocker) + comma + std::to_string(isEvasive) + comma + std::to_string(forcedAttack) + "\n";
	}
};

struct TrainerSave
{
	std::string name;
	int money;
	int x;
	int y;
	int direction;
	int badgeCount;
	int characterID;

	operator std::string const()
	{
		return name + comma + std::to_string(money) + comma + std::to_string(x) + comma + std::to_string(y) + comma + std::to_string(direction) + comma + std::to_string(badgeCount) + comma + std::to_string(characterID) + "\n";
	}
};

struct InputKeySave
{
	std::string main = "";
	std::string alt = "";

	operator std::string const()
	{
		return main + comma + alt + comma;
	}
};

struct InputSave
{
	InputKeySave keyboardUp;
	InputKeySave keyboardDown;
	InputKeySave keyboardLeft;
	InputKeySave keyboardRight;
	InputKeySave keyboardSelect;
	InputKeySave keyboardPause;
	InputKeySave keyboardBack;
	InputKeySave keyboardSprint;

	InputKeySave controllerUp;
	InputKeySave controllerDown;
	InputKeySave controllerLeft;
	InputKeySave controllerRight;
	InputKeySave controllerSelect;
	InputKeySave controllerPause;
	InputKeySave controllerBack;
	InputKeySave controllerSprint;

	operator std::string const()
	{
		return	(std::string)keyboardUp + (std::string)keyboardDown + (std::string)keyboardLeft + (std::string)keyboardRight + (std::string)keyboardSelect + (std::string)keyboardPause + (std::string)keyboardBack + (std::string)keyboardSprint +
			(std::string)controllerUp + (std::string)controllerDown + (std::string)controllerLeft + (std::string)controllerRight + (std::string)controllerSelect + (std::string)controllerPause + (std::string)controllerBack + (std::string)controllerSprint + "\n";
	}
};

struct RendererSave
{
	int resolution;
	bool fullscreen;
	bool showFPS;

	operator std::string const()
	{
		return std::to_string(resolution) + comma + std::to_string(fullscreen) + comma + std::to_string(showFPS) + "\n";
	}
};

struct ItemSave
{
	int itemID;
	int quantity;

	operator std::string const()
	{
		return std::to_string(itemID) + comma + std::to_string(quantity) + "\n";
	}
};
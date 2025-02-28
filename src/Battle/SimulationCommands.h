#pragma once
#include "../GlobalData/globalIDs.h"
#include "../Characters/Pokemon/Pokemon.h"
#include <string>

enum SimulationType
{
	ATTACK_SELECTED,
	POKEMON_SELECTED,
	ITEM_SELECTED,
	FLEE_SELECTED,
	ATTACK,
	POKEMON,
	ITEM,
	FLEE,
	STATUS,
	STAT
};

enum class SelectedUser
{
	PLAYER,
	AI,
	BOTH
};

enum MoveSelection
{
	MOVE_ONE,
	MOVE_TWO,
	MOVE_THREE,
	MOVE_FOUR,
	MOVE_FIVE
};

enum class EffectiveStatus
{
	NOT_VERY,
	EFFECTIVE,
	SUPER
};


struct PokeballCommand
{
	bool isPokeball = false;	//TODO: Check usages for removal
	int shakes = 0;
	bool caught = false;
};

//		What does an item need to convey
// Need to select pokemon				- Not all items are for use on pokemon
// SAVE THIS SPACE FOR ITEMS THAT DONT EFFECT POKEMON
// Healing to be done					- How much to heal for
// Status to clear						- Status cleared. Multiple status cleared can be sent as multiple commands
// Did Revive							- Whether or not a pokemon has been revived
struct ItemCommand
{
	ItemID id;
	PokeballCommand pokeballData;
	PokemonStats statsToBoost;
	bool selectPokemon;
	bool revive;
	int healAmount;
	std::string message;
};

struct AttackCommand
{
	int damage;
	bool crit;
	EffectiveStatus effectiveness = EffectiveStatus::EFFECTIVE;
	StatusID statusGiven = StatusID::NO_STATUS;
	std::string message;
};

struct StatusCommand
{
	SelectedUser recipient;
	int damage = 0;
	StatusID statusGiven = StatusID::NO_STATUS;
	StatusID curedStatus = StatusID::NO_STATUS;
	std::string message;
};

struct StatCommand
{
	SelectedUser recipient;
	PokemonStats stats;
	std::string message;
};

//		General Command Needs
// Player or opponent issuing command
// Selection 1		- Item, Pokemon, or Move
// Selection 2		- Pokemon
struct SimulationCommand
{
	SimulationType type;
	SelectedUser commander;
	int selection1 = NONE;
	int selection2 = NONE;
	ItemCommand itemData;
	AttackCommand attackData;
	StatusCommand statusData;
	StatCommand statData;
};
#pragma once

#include <string>
#include "../Graphics/PositionalData.h"

//		Data Needed
//	
// Pokemon Roster
//	- Name
//	- HP formatted
//	- XP formatted
// 
// Move Data
// 
//	

struct SharedString
{
	std::string string1;
	std::string string2;
	std::string string3;
	std::string string4;
	std::string string5;
	std::string string6;
};

struct SharedBool
{
	bool bool1 = false;
	bool bool2 = false;
	bool bool3 = false;
	bool bool4 = false;
	bool bool5 = false;
	bool bool6 = false;
};

struct DialogueRendererData
{
	std::string speakerName;

	std::string topLine;
	std::string bottomLine;

	std::string topButtonOption;
	std::string bottomButtonOption;

	ButtonRenderData topButtonRenderData;
	ButtonRenderData bottomButtonRenderData;

	bool nextArrowVisible = false;
	ImageRenderData nextArrow;

	PolygonData nameOutline;

	bool buttonActiveStatus = false;
};

struct PokemonStringData
{
	std::string name;
	std::string level;
	std::string health;
	std::string Type1;
	std::string Type2;
	std::string attack;
	std::string defense;
	std::string spAttack;
	std::string spDefense;
	std::string speed;

	std::string move1;
	std::string move2;
	std::string move3;
	std::string move4;
};

struct BattlePokemonData
{
	std::string playerTexture;
	std::string opponentTexture;

	std::string playerName;
	std::string opponentName;

	std::string playerLevel;
	std::string opponentLevel;

	std::string playerMajorStatusTexture;
	std::string opponentMajorStatusTexture;

	std::string currentHP;
	std::string maxHP;

	std::string botLine;


	std::string pokemonStatName;
	std::string pokemonStatLevel;
	SharedString pokemonStatDifference;
	SharedString pokemonStatValue;

	float playerCurHPPercent = 50.0f;
	float opponentCurHPPercent = 50.0f;

	float playerXPPercent = 50.0f;
};

struct MoveStringData
{
	std::string moveName;
	std::string currentPP;
	std::string maxPP;
	std::string moveTypeTextureLocation;	//TODO: Rename to move type
};

struct PokemonStatsData
{
	std::string level;
	std::string health;
	std::string attack;
	std::string defense;
	std::string spAttack;
	std::string spDefense;
	std::string speed;
};

struct PausePokemonData
{
	float hpPercent;

	std::string name;
	std::string level;
	std::string health;
	std::string attack;
	std::string defense;
	std::string spAttack;
	std::string spDefense;
	std::string speed;

	std::string type1;
	std::string type2;

	MoveStringData move1;
	MoveStringData move2;
	MoveStringData move3;
	MoveStringData move4;

	std::string majorStatusTexture;
};

struct LearnMoveData
{
	MoveStringData move1;
	MoveStringData move2;
	MoveStringData move3;
	MoveStringData move4;

	MoveStringData newMove;

	std::string power;
	std::string accuracy;
	std::string description;

	std::string pokemonName;
	std::string pokemonType1TextureLocation;
	std::string pokemonType2TextureLocation;
	std::string pokemonImageTextureLocation;

	bool buttonVisibility = false;

	bool move1OutlineVisiblity = false;
	bool move2OutlineVisiblity = false;
	bool move3OutlineVisiblity = false;
	bool move4OutlineVisiblity = false;
	bool newMoveOutlineVisiblity = false;
};

struct PauseControlData
{
	std::string UpMain;
	std::string UpAlt;

	std::string DownMain;
	std::string DownAlt;

	std::string LeftMain;
	std::string LeftAlt;

	std::string RightMain;
	std::string RightAlt;

	std::string SelectMain;
	std::string SelectAlt;

	std::string BackMain;
	std::string BackAlt;

	std::string PauseMain;
	std::string PauseAlt;

	std::string SprintMain;
	std::string SprintAlt;
};

struct TrainerBadgeData
{
	bool fireBadgeVisibility = false;
	bool flyingBadgeVisibility = false;
	bool grassBadgeVisibility = false;
	bool iceBadgeVisibility = false;
	bool normalBadgeVisibility = false;
	bool rockBadgeVisibility = false;
	bool waterBadgeVisibility = false;
	bool dragonBadgeVisibility = false;
};

struct PauseMenuData
{
	std::string playTime;
	std::string playerBalance;

	TrainerBadgeData badgeData;

	bool pokedexHighlight = false;
	bool mapHighlight = false;

	bool pokedexHighlightVisible = false;
	bool mapHighlightVisible = false;
	bool buttonVisibility = false;

	bool mapButtonUsable = true;
	bool pokedexButtonUsable = true;
};

struct PauseSettingsData
{
	PauseControlData keyboardData;
	PauseControlData controllerData;

	std::string resolution;
	std::string fullscreen;
	std::string showFps;
	std::string autoSave;
	std::string fasterText;
};

struct RosterPokemonData
{
	std::string name;
	std::string pokemonTexture;
	std::string hp;
	std::string level;
	std::string majorStatusTexture;
};

struct RosterDisplayData
{
	RosterPokemonData pokemon1;
	RosterPokemonData pokemon2;
	RosterPokemonData pokemon3;
	RosterPokemonData pokemon4;
	RosterPokemonData pokemon5;
	RosterPokemonData pokemon6;

	PausePokemonData pausePokemonData;
};

struct ItemDisplayData
{
	SharedString itemName;
	SharedString itemAmount;
	SharedString itemTexture;
};

struct AlphabetStringData
{
	SharedString a_f = { "a","b","c","d","e","f" };
	SharedString g_l = { "g","h","i","j","k","l" };
	SharedString m_r = { "m","n","o","p","q","r" };
	SharedString s_x = { "s","t","u","v","w","x" };
	SharedString y_z = { "y","z"};
};

struct DynamicTextBoxData
{
	//TODO: Create TextBoxRenderData* in textbox. We can get rid of this
	float percentageX = 0.0f;
	float percentageY = 0.0f;

	float fontSizePercentage = 0.0f;
	Color color = Color::BLACK;
	Alignment alignment = Alignment::CENTER_ALIGN;
};

struct PokedexSelectedPokemonData
{
	std::string pokemonName;
	std::string pokemonNumber;
	std::string pokemonHeight;
	std::string pokemonWight;
	std::string pokemonDescription;

	DynamicImageRenderData pokemonImage = DynamicImageRenderData{ (260.0f/ 1000.0f) * 100.0f, (393.0f / 563.0f) * 100.0f, 9.0f, 16.0f};
	DynamicImageRenderData pokemonType1 = DynamicImageRenderData{ (260.0f / 1000.0f) * 100.0f, 90.0f, 5.0f, 2.5f};
	DynamicImageRenderData pokemonType2 = DynamicImageRenderData{ (360.0f / 1000.0f) * 100.0f, 90.0f, 5.0f, 2.5f};
};

struct TextBoxData
{
	std::string value;
	TextBoxRenderData renderData;
};

struct PokedexScrollButton
{
	TextBoxData pokemonName;
	TextBoxData pokemonNumber;

	ButtonRenderData buttonRenderData;
	DynamicImageRenderData buttonImage;
	DynamicImageRenderData pokemonCaughtImage;
};

struct PokedexDisplayData
{
	PokedexSelectedPokemonData pokemonSelectedData;

	std::string pokemonSeen;
	std::string pokemonCaught;

	DynamicImageRenderData newPokemonImage = DynamicImageRenderData{ (655.0f / 1000.0f) * 100.0f, (384.0f / 563.0f) * 100.0f, 9.0f / 1.3f, 16.0f / 1.3f };

	DynamicImageRenderData sortArrow = DynamicImageRenderData{ (880.0f / 1000.0f) * 100.0f, (313.0f / 563.0f) * 100.0f, 9.0f / 10.0f, 16.0f / 10.0f};
	DynamicImageRenderData selectionHighlight = DynamicImageRenderData{ 0.0f, 0.0f, 0.0f, 0.0f};

	bool sortButtonsVisible = false;

	PokedexScrollButton button1;
	PokedexScrollButton button2;
	PokedexScrollButton button3;
	PokedexScrollButton button4;
	PokedexScrollButton button5;
	PokedexScrollButton button6;
	PokedexScrollButton button7;
};

struct NurseHealData
{
	SharedString textures;
	SharedBool visibility;
};

struct PCData
{
	SharedString pcTextures0;
	SharedString pcTextures1;
	SharedString pcTextures2;
	SharedString pcTextures3;
	SharedString pcTextures4;
	SharedString pcTextures5;
	SharedString trainerRosterTextures;

	ImageRenderData movePokemonHighlightData;
	ImageRenderData overlayBackgroundLocation;

	ButtonRenderData moveButtonData;
	ButtonRenderData summaryButtonData;
	ButtonRenderData renameButtonData;
	ButtonRenderData deleteButtonData;

	std::string freePokemonMessage;
	std::string selectedPokemonTexture;
};

struct SummaryData
{
	PokemonStatsData statsData;

	LearnMoveData moveData;

	PolygonData evStatContainerOutline = { 18, {},{} };
	PolygonData evStatContainer = { 18, {}, {} };
	PolygonData evStatGraph = { 18, {}, {} };

	ImageRenderData type1;
	ImageRenderData type2;

	TextBoxData hpStatGraphData;
	TextBoxData attackStatGraphData;
	TextBoxData defenseStatGraphData;
	TextBoxData speedStatGraphData;
	TextBoxData spDefStatGraphData;
	TextBoxData spAttackStatGraphData;
};

struct AcquireItemData
{
	std::string itemName;
	std::string itemLocation;

	std::string comments;
	std::string buttonText = "OK";
};

struct SelectProfPokemonData
{
	bool buttonsVisible = false;

	bool leftPokemonVisible = true;
	bool centerPokemonVisible = true;
	bool rightPokemonVisible = true;

	bool dialogueVisible = false;

	std::string backgroundPath;

	std::string pokemonName;
	std::string pokemonImage;
	std::string pokemonDescription;

	std::string leftPokemonImage;
	std::string rightPokemonImage;

	std::string frameImageLeft;
	std::string frameImageRight;
	std::string frameImageCenter;
	std::string pokeball;

	std::string topLine;
	std::string botLine;
};

struct BuyItemData
{
	std::string playerBalance;
	std::string background;

	SharedString itemName;
	SharedString itemCost;
	SharedString itemTexture;

	bool buttonVisibility = false;
};

static void swapAlphabetData(AlphabetStringData* data)
{
	if (data->a_f.string1 == "a")
	{
		data->a_f = { "A","B","C","D","E","F" };
		data->g_l = { "G","H","I","J","K","L" };
		data->m_r = { "M","N","O","P","Q","R" };
		data->s_x = { "S","T","U","V","W","X" };
		data->y_z = { "Y","Z" };
	}
	else
	{
		data->a_f = { "a","b","c","d","e","f" };
		data->g_l = { "g","h","i","j","k","l" };
		data->m_r = { "m","n","o","p","q","r" };
		data->s_x = { "s","t","u","v","w","x" };
		data->y_z = { "y","z" };
	}
}

static char getKeyboardCharacter(AlphabetStringData* stringData, int keySelection)
{
	// a-z = 1-26
	// colon = 27
	// apostrophe = 28
	// 1-0 = 29-38

	int lower = 1;
	if (stringData->a_f.string1 != "a")
		lower = 0;

	if (keySelection == 27)
		return ':';
	else if (keySelection == 28)
		return '\'';
	else if (keySelection == 38)
		return '0';
	else if (keySelection >= 29)
		return '0' + (keySelection - 28);
	else
		return char(64 + keySelection + (lower * 32));
}

//Handles name of pokemon
static void formatRosterData(std::string* value, std::string data)
{
	*value = data;
}

//Handles XP and PP
static void formatRosterData(std::string* value, int data1, int data2)
{

}
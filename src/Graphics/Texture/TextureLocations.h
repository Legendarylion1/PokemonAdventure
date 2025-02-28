#pragma once

#include <unordered_map>

#include "../../GlobalData/globalIDs.h"
#include "Texture.h"

enum class MenuScene
{
	NONE,
	STARTUP_SCENE,
	BATTLE,
	BUY_ITEMS,
	USE_PC,
	PAUSE_MENU,
	PAUSE_ROSTER,
	PAUSE_SETTINGS,
	PAUSE_BAG,
	INTRO_LINKS,
	INTRO_LEGENDARY,
	INTRO_STUDIO,
	INTRO_STUDIO_CROWN,
	INTRO_PRESS_ANY_BUTTON,
	BATTLE_ROSTER,
	BATTLE_ITEMS,
	SET_PLAYER_NAME,
	PROFESSOR_M,
	LEARN_MOVE,
	EVOLUTION,
	POKEDEX,
	NEW_POKEMON,
	RENAME_POKEMON,
	POKEMON_SUMMARY,
	SELECT_PLAYER_GENDER
};

enum class MenuOverlay
{
	NONE,
	ON_SCREEN_KEYBOARD,
	DELETE_CONFIRMATION,
	DIALOGUE,
	BATTLE_OPTIONS,
	ATTACK_SELECT,
	ITEM_SELECT,
	BATTLE_CHAT,
	IMAGE_FRAME,
	RESOLUTION_SELECTION,
	CHANGE_INPUT,
	LEVEL_UP_STAT_CHANGE,
	LEVEL_UP_STAT_VALUE,
	SWAP_POKEMON_QUESTION,
	MOVE_OUTLINE,
	LEARN_MOVE,
	POKEDEX_OUTLINE,
	MAP_OUTLINE,
	POKEDEX_NOT_CAUGHT,
	POKEDEX_CAUGHT,
	POKEDEX_UP_ARROW,
	POKEDEX_DOWN_ARROW,
	POKEDEX_HIGHLIGHT_SORT,
	POKEDEX_HIGHLIGHT_BUTTON,
	NURSE_POKEBALL,
	NURSE_GREATBALL,
	NURSE_ULTRABALL,
	NURSE_MASTERBALL,
	PC_SELECTION,
	FREE_POKEMON_CONFIRMATION,
	SAVE_COMPLETE,
	SAVE_BEFORE_EXIT,
	MALE_GENDER_ICON,
	FEMALE_GENDER_ICON,
	SELECT_PLAYER_GENDER_MALE,
	SELECT_PLAYER_GENDER_FEMALE,
	PAUSE_MAP_IMAGE,
	PAUSE_POKEDEX_IMAGE,
	PLAYER_ACQUIRE_ITEM,
	SELECT_POKEMON_FROM_PROFESSOR,
	IMAGE_FRAME_HIGHLIGHT,
	DIALOGUE_DOWN_ARROW,
	ROSTER_OPTIONS
};

// TODO: Make these into functions so that they arent just global data in the stack

static std::unordered_map<CharacterID, std::string> g_CharacterTextureLocations = {
	{CharacterID::PLAYER_MALE_TRAINER, "Images/Characters/male_player.png"},
	{CharacterID::PLAYER_FEMALE_TRAINER, "Images/Characters/female_player.png"},
	{CharacterID::MOM, "Images/Characters/Mom.png"},
	{CharacterID::FIRST_TRAINER, "Images/Characters/aiSprite.png"},
	{CharacterID::SECURITY_OFFICER, "Images/Characters/security_officer.png"},
	{CharacterID::PROFESSOR, "Images/Characters/professor.png"},
};

static std::unordered_map<SectionID, std::string> g_MapTextureLocations = {
	{SectionID::HOME_VILLAGE_ROUTE_1, "Images/Maps/HVRoute1.png"},
	{SectionID::POKE_MART, "Images/Maps/PokeMart.png"},
	{SectionID::POKE_CENTER, "Images/Maps/PokeCenter.png"},
	{SectionID::FIRST_TOWN_ROUTE_2, "Images/Maps/first_town_route_2.png"},
	{SectionID::START_HOUSE_BASE_FLOOR, "Images/Maps/startHouseBaseFloor.png"},
	{SectionID::START_HOUSE_ROOM, "Images/Maps/startHouseRoom.png"},
	{SectionID::PROFESSOR_LAB, "Images/Maps/profLab.png"},
};

static std::unordered_map<Type, std::string> g_typeTextureLocations = {
	{Type::NONE, ""},
	{Type::NORMAL, "Images/Pokemon/Typing/normalType.png"},
	{Type::FIRE, "Images/Pokemon/Typing/fireType.png"},
	{Type::WATER, "Images/Pokemon/Typing/waterType.png"},
	{Type::GRASS, "Images/Pokemon/Typing/grassType.png"},
	{Type::ELECTRIC, "Images/Pokemon/Typing/electricType.png"},
	{Type::ICE, "Images/Pokemon/Typing/iceType.png"},
	{Type::FIGHTING, "Images/Pokemon/Typing/fightingType.png"},
	{Type::POISON, "Images/Pokemon/Typing/poisonType.png"},
	{Type::GROUND, "Images/Pokemon/Typing/groundType.png"},
	{Type::FLYING, "Images/Pokemon/Typing/flyingType.png"},
	{Type::PSYCHIC, "Images/Pokemon/Typing/psychicType.png"},
	{Type::BUG, "Images/Pokemon/Typing/bugType.png"},
	{Type::ROCK, "Images/Pokemon/Typing/rockType.png"},
	{Type::GHOST, "Images/Pokemon/Typing/ghostType.png"},
	{Type::DRAGON, "Images/Pokemon/Typing/dragonType.png"},
	{Type::DARK, "Images/Pokemon/Typing/darkType.png"},
	{Type::STEEL, "Images/Pokemon/Typing/steelType.png"},
	{Type::FAIRY, "Images/Pokemon/Typing/fairyType.png"}
};

static std::unordered_map<StatusID, std::string> g_majorStatusTextureLocations =
{
	{StatusID::NO_STATUS, ""},
	{StatusID::BURN, "Images/Pokemon/Status/burned.png"},
	{StatusID::SLEEP, "Images/Pokemon/Status/sleep.png"},
	{StatusID::POISON, "Images/Pokemon/Status/posioned.png"},
	{StatusID::PARALYSIS, "Images/Pokemon/Status/paralyzed.png"},
	{StatusID::FREEZE, "Images/Pokemon/Status/frozen.png"},
};

static std::unordered_map<MenuScene, std::string> g_sceneTextureLocations = {
	{MenuScene::SET_PLAYER_NAME, "Images/Backgrounds/Scenes/set_player_name.png" },
	{MenuScene::STARTUP_SCENE, "Images/Backgrounds/Scenes/selectSave.png" },
	{MenuScene::PROFESSOR_M, "Images/Backgrounds/Scenes/professorM.png" },
	{MenuScene::BATTLE, "Images/Backgrounds/Scenes/battleUI.png" },
	{MenuScene::PAUSE_ROSTER, "Images/Backgrounds/Scenes/pokemonRoster.png" },
	{MenuScene::INTRO_LINKS, "Images/Backgrounds/Scenes/intro_links.png"},
	{MenuScene::INTRO_LEGENDARY, "Images/Backgrounds/Scenes/aganiteIntro.png"},
	{MenuScene::INTRO_STUDIO, "Images/Backgrounds/Scenes/LegendaryStudio.png"},
	{MenuScene::INTRO_STUDIO_CROWN, "Images/Backgrounds/Scenes/LegendaryStudioCrown.png"},
	{MenuScene::PAUSE_MENU, "Images/Backgrounds/Scenes/pauseMenu.png" },
	{MenuScene::PAUSE_SETTINGS, "Images/Backgrounds/Scenes/settings.png" },
	{MenuScene::BATTLE_ITEMS, "Images/Backgrounds/Scenes/battle_items.png" },
	{MenuScene::LEARN_MOVE, "Images/Backgrounds/Scenes/learnMove.png" },
	{MenuScene::EVOLUTION, "Images/Backgrounds/Scenes/evolution.png" },
	{MenuScene::POKEDEX, "Images/Backgrounds/Scenes/pokedexMenu.png" },
	{MenuScene::NEW_POKEMON, "Images/Backgrounds/Scenes/newPokemon.png" },
	{MenuScene::USE_PC, "Images/Backgrounds/Scenes/pc.png" },
	{MenuScene::POKEMON_SUMMARY, "Images/Backgrounds/Scenes/pokemonSummary.png" },
};

static std::unordered_map<MenuOverlay, std::string> g_overlayTextureLocations ={
	{MenuOverlay::DELETE_CONFIRMATION, "Images/Backgrounds/overlays/deleteConfirmation.png"},
	{MenuOverlay::DIALOGUE, "Images/Backgrounds/overlays/normalChat.png"},
	{MenuOverlay::BATTLE_CHAT, "Images/Backgrounds/overlays/battleChat.png"},
	{MenuOverlay::IMAGE_FRAME, "Images/Backgrounds/overlays/imageFrame.png"},
	{MenuOverlay::LEVEL_UP_STAT_CHANGE, "Images/Backgrounds/overlays/levelUp.png"},
	{MenuOverlay::LEVEL_UP_STAT_VALUE, "Images/Backgrounds/overlays/levelUp.png"},
	{MenuOverlay::MOVE_OUTLINE, "Images/Backgrounds/overlays/moveOutline.png"},
	{MenuOverlay::POKEDEX_OUTLINE, "Images/Backgrounds/overlays/pokedexOverlay.png"},
	{MenuOverlay::MAP_OUTLINE, "Images/Backgrounds/overlays/mapOverlay.png"},
	{MenuOverlay::POKEDEX_CAUGHT, "Images/Backgrounds/overlays/pokedexCaught.png"},
	{MenuOverlay::POKEDEX_NOT_CAUGHT, "Images/Backgrounds/overlays/pokedexNotCaught.png"},
	{MenuOverlay::POKEDEX_UP_ARROW, "Images/Backgrounds/overlays/pokedexUpArrow.png"},
	{MenuOverlay::POKEDEX_DOWN_ARROW, "Images/Backgrounds/overlays/pokedexDownArrow.png"},
	{MenuOverlay::POKEDEX_HIGHLIGHT_SORT, "Images/Backgrounds/overlays/pokedexHighlightSort.png"},
	{MenuOverlay::POKEDEX_HIGHLIGHT_BUTTON, "Images/Backgrounds/overlays/pokedexHighlightButton.png"},
	{MenuOverlay::NURSE_POKEBALL, "Images/Backgrounds/overlays/nursePokeball_0.png"},
	{MenuOverlay::NURSE_GREATBALL, "Images/Backgrounds/overlays/nurseGreatball_0.png"},
	{MenuOverlay::NURSE_ULTRABALL, "Images/Backgrounds/overlays/nurseUltraball_0.png"},
	{MenuOverlay::NURSE_MASTERBALL, "Images/Backgrounds/overlays/nurseMasterball_0.png"},
	{MenuOverlay::MALE_GENDER_ICON, "Images/Backgrounds/overlays/boy_symbol.png"},
	{MenuOverlay::FEMALE_GENDER_ICON, "Images/Backgrounds/overlays/girl_symbol.png"},
	{MenuOverlay::SELECT_PLAYER_GENDER_FEMALE, "Images/Backgrounds/overlays/boy_girl_selection_girl_highlight.png"},
	{MenuOverlay::SELECT_PLAYER_GENDER_MALE, "Images/Backgrounds/overlays/boy_girl_selection_boy_highlight.png"},
	{MenuOverlay::PAUSE_MAP_IMAGE, "Images/Backgrounds/overlays/mapImage.png"},
	{MenuOverlay::PAUSE_POKEDEX_IMAGE, "Images/Backgrounds/overlays/pokedexImage.png"},
	{MenuOverlay::IMAGE_FRAME_HIGHLIGHT, "Images/Backgrounds/overlays/imageFrameHighlight.png"},
	{MenuOverlay::DIALOGUE_DOWN_ARROW, "Images/Backgrounds/overlays/dialogueDownArrow.png"},
};

static std::unordered_map<ItemID, std::string> g_itemTextureLocations = {
	{ItemID::SMALL_POTION, "Images/Items/potion.png"},
	{ItemID::MEDIUM_POTION, "Images/Items/superPotion.png"},
	{ItemID::LARGE_POTION, "Images/Items/hyperPotion.png"},
	{ItemID::POKEBALL, "Images/Items/pokeball.png"},
	{ItemID::GREATBALL, "Images/Items/greatball.png"},
	{ItemID::ULTRABALL, "Images/Items/ultraball.png"},
	{ItemID::MASTERBALL, "Images/Items/masterball.png"},
	{ItemID::ROID_JUICE, "Images/Items/potion.png"},
};

static std::string pokemonFrontTexture(std::string pokemonName)
{
	return "Images/Pokemon/" + pokemonName + "_Front.png";
}

static std::string pokemonBackTexture(std::string pokemonName)
{
	return "Images/Pokemon/" + pokemonName + "_Back.png";
}
#pragma once

#include "../../Characters/CharacterMover.h"
#include "../../Graphics/DialogueRenderer.h"
#include "../../Menu/MenuFunction/MenuFunction.h"
#include "../Pokedex/Pokedex.h"

#include <thread>
#include <chrono>

struct Artifact
{
	std::string artifactName;
	std::string artifactPath;
	std::vector<std::string> comments;
};

struct BattleData
{
	std::vector<Pokemon> opponentPokemon;
	bool mustWin = true;
};

/// <summary>
/// 
/// Usage Note.
///	Instruction Type Move: adds the movement to the queue
///	Instruction Type Play: begins the movement on screen
/// 
/// </summary>
struct CutsceneInstruction
{
	Trainer* character = nullptr;
	InstructionType type = InstructionType::PLAY;
	Direction direction = Direction::UP;
	Dialogue dialogue = Dialogue{"",""};
	Coordinate coord = Coordinate{};
	Artifact artifact;
	BattleData battleData;
	int index = 0;

	void (*menuFunction)(MapHandler* mapHandler, Trainer* trainer, Menu* menu, Renderer* renderer, Pokedex* pokedex) = nullptr;

	CutsceneInstruction() {}

	CutsceneInstruction(Trainer* person, InstructionType insType, Direction dir) :
		character(person), type(insType), direction(dir) {}

	CutsceneInstruction(Dialogue text) :
		type(InstructionType::DIALOGUE), dialogue(text) {}

	CutsceneInstruction(InstructionType instruction):
		type(InstructionType::PLAY) {}

	CutsceneInstruction(Trainer* person, InstructionType instruction, Direction dir, Coordinate coordinate):
		character(person), type(instruction), direction(dir), coord(coordinate) {}

	CutsceneInstruction(InstructionType instruction, Artifact artifactData):
		type(instruction), artifact(artifactData) {}

	CutsceneInstruction(InstructionType instruction, void (*function)(MapHandler* mapHandler, Trainer* trainer, Menu* menu, Renderer* renderer, Pokedex* pokedex)):
		type(instruction), menuFunction(function) {}

	CutsceneInstruction(Trainer* opponent, InstructionType instruction, BattleData data) :
		character(opponent), type(instruction), battleData(data) {}

	CutsceneInstruction(Trainer* personToHeal, InstructionType instruction, int pokemonIndex):
		character(personToHeal), type(instruction), index(pokemonIndex) {}
};

namespace StoryBoard
{
	static PokemonID fireStarter = PokemonID::Fitty;
	static PokemonID waterStarter = PokemonID::Bery;
	static PokemonID grassStarter = PokemonID::Baroot;

	namespace Variant
	{
		static std::vector<CutsceneInstruction> meetFriendAndTellToGoToProf_variant_0(MapHandler* mapHandler, Trainer* player, int variant)
		{
			std::string gender = "he";
			if (player->getID() != CharacterID::PLAYER_MALE_TRAINER)
				gender = "she";

			int MOM = 0;
			int RIVAL = 1;

			std::vector<CutsceneInstruction> instructions =
			{
				{player, InstructionType::TURN, Direction::LEFT},
				{InstructionType::PLAY},

				{Dialogue{"There " + gender + " is!", "" ,mapHandler->getAI(RIVAL)->getName()}},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::RIGHT},
				{mapHandler->getAI(MOM), InstructionType::TURN, Direction::RIGHT},
				{InstructionType::PLAY},
				
				{mapHandler->getAI(MOM), InstructionType::MOVE, Direction::RIGHT},
				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::RIGHT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::RIGHT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::UP},
				{InstructionType::PLAY},
				
				{player, InstructionType::TURN, Direction::DOWN},
				{InstructionType::PLAY},
				{Dialogue{"I can't believe you weren't","down here already", mapHandler->getAI(RIVAL)->getName()}},
				{Dialogue{"I couldn't even sleep last","night I was so excited", mapHandler->getAI(RIVAL)->getName()}},

				{player, InstructionType::TURN, Direction::LEFT},
				{InstructionType::PLAY},
				{Dialogue{"Now that you are 13 you can","finally be a trainer", mapHandler->getAI(MOM)->getName()}},

				{player, InstructionType::TURN, Direction::DOWN},
				{InstructionType::PLAY},
				{Dialogue{"Come on let's get to the","professor already!", mapHandler->getAI(RIVAL)->getName()}},

				{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::SET_POSITION, Direction::DOWN, {-30,-30}},

				{player, InstructionType::TURN, Direction::LEFT},
				{InstructionType::PLAY},

				{Dialogue{"Well you better get going","", mapHandler->getAI(MOM)->getName()}},
				{Dialogue{"Head to the profs house along","the stone path", mapHandler->getAI(MOM)->getName()}},
				{Dialogue{"Have fun I love you","", mapHandler->getAI(MOM)->getName()}},
			};

			return instructions;
		}

		static std::vector<CutsceneInstruction> meetFriendAndTellToGoToProf_variant_1(MapHandler* mapHandler, Trainer* player, int variant)
		{
			std::string gender = "he";
			if (player->getID() != CharacterID::PLAYER_MALE_TRAINER)
				gender = "she";

			int MOM = 0;
			int RIVAL = 1;

			std::vector<CutsceneInstruction> instructions =
			{
				{player, InstructionType::TURN, Direction::LEFT},
				{InstructionType::PLAY},

				{Dialogue{"There " + gender + " is!", "", mapHandler->getAI(RIVAL)->getName()}},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::RIGHT},
				{mapHandler->getAI(MOM), InstructionType::TURN, Direction::RIGHT},
				{InstructionType::PLAY},

				{mapHandler->getAI(MOM), InstructionType::MOVE, Direction::RIGHT},
				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::RIGHT},
				{InstructionType::PLAY},

				{mapHandler->getAI(MOM), InstructionType::MOVE, Direction::RIGHT},
				{InstructionType::PLAY},

				{mapHandler->getAI(MOM), InstructionType::TURN, Direction::DOWN},
				{InstructionType::PLAY},

				{Dialogue{"I can't believe you weren't","down here already", mapHandler->getAI(RIVAL)->getName()}},
				{Dialogue{"I couldn't even sleep last","night I was so excited", mapHandler->getAI(RIVAL)->getName()}},

				{player, InstructionType::TURN, Direction::UP},
				{InstructionType::PLAY},
				{Dialogue{"Now that you are 13 you can","finally be a trainer", mapHandler->getAI(MOM)->getName()}},

				{player, InstructionType::TURN, Direction::LEFT},
				{InstructionType::PLAY},
				{Dialogue{"Come on let's get to the","professor already!", mapHandler->getAI(RIVAL)->getName()}},

				{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
				{InstructionType::PLAY},

				{mapHandler->getAI(RIVAL), InstructionType::SET_POSITION, Direction::DOWN, {-30,-30}},

				{player, InstructionType::TURN, Direction::UP},
				{InstructionType::PLAY},

				{Dialogue{"Well you better get going","", mapHandler->getAI(MOM)->getName()}},
				{Dialogue{"Head to the profs house along","the stone path", mapHandler->getAI(MOM)->getName()}},
				{Dialogue{"Have fun I love you","", mapHandler->getAI(MOM)->getName()}},
			};

			return instructions;
		}
	}

	namespace MockFunctions
	{
		static void dialogue(MapHandler* mapHandler, Trainer* trainer, Menu* menu, Renderer* renderer, SelectProfPokemonData* data, std::string topLine = "", std::string botLine = "", bool fasterText = false, std::string speakerName = "")
		{
			data->topLine = "";
			data->botLine = "";

			menu->setCanLeave(false);
			menu->setOverlay(MenuOverlay::SELECT_POKEMON_FROM_PROFESSOR);

			mapHandler->onUpdate();
			trainer->onUpdate(renderer);
			menu->onUpdate();

			data->dialogueVisible = true;

			int count = 0;
			float textSpeed = 10;
			float textSpeedIncrease = 10;

			if (fasterText)
				textSpeed += textSpeedIncrease;
			
			// Dialogue Renderer Code
			{
				while (!menu->shouldClose() && (data->topLine.size() != topLine.size() || data->botLine.size() != botLine.size()))
				{
					// Top Line
					if (data->topLine.size() != topLine.size())
					{
						if (count >= 100)
						{
							data->topLine += topLine.at(data->topLine.size());
							count = 0;
						}
					}
					else if (data->botLine.size() != botLine.size())  // Bot Line
					{
						if (count >= 100)
						{
							data->botLine += botLine.at(data->botLine.size());
							count = 0;
						}
					}

					count += (int)(200 * menu->getDeltaTime() * textSpeed);

					mapHandler->onUpdate();
					trainer->onUpdate(renderer);
					menu->onUpdate();
				}

				while (!menu->anyButtonPressed() && !menu->shouldClose())
				{
					mapHandler->onUpdate();
					trainer->onUpdate(renderer);
					menu->onUpdate();
				}
			}

			menu->setOverlay(MenuOverlay::NONE);
			data->dialogueVisible = false;
		}
	}

	namespace StoryGraphics
	{
		static void displayFirstPokemon(MapHandler* mapHandler, Trainer* trainer, Menu* menu, Renderer* renderer, Pokedex* pokedex)
		{
			int selection = NONE;

			SelectProfPokemonData data;

			data.backgroundPath = g_overlayTextureLocations[MenuOverlay::DIALOGUE];
			data.pokemonName = getSpeciesFromID(PokemonID::Baroot).name;
			data.pokemonDescription = "The Grass Pokemon";

			data.leftPokemonImage = pokemonFrontTexture(getSpeciesFromID(fireStarter).name);
			data.pokemonImage = pokemonFrontTexture(getSpeciesFromID(grassStarter).name);
			data.rightPokemonImage = pokemonFrontTexture(getSpeciesFromID(waterStarter).name);

			data.frameImageLeft = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];
			data.frameImageCenter = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME_HIGHLIGHT];
			data.frameImageRight = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];

			data.pokeball = g_overlayTextureLocations[MenuOverlay::NURSE_POKEBALL];

			MenuSetup::setupProfTablePokemonSelection(menu, &data);
			//menu->setupProfTablePokemonSelection(&data);		//TODO: REMOVE
			menu->setRequestedData(&selection);

			menu->setCanLeave(false);
			menu->setOverlay(MenuOverlay::SELECT_POKEMON_FROM_PROFESSOR);
			menu->preRun();


			// Get Player Selection

			int hoverIndex = menu->getButtonIndex();

			{
				data.frameImageLeft = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];
				data.frameImageRight = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];
				data.frameImageCenter = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];

				if (hoverIndex == 0)
					data.frameImageCenter = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME_HIGHLIGHT];
				else if (hoverIndex == 1)
					data.frameImageLeft = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME_HIGHLIGHT];
				else
					data.frameImageRight = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME_HIGHLIGHT];
			}

			mapHandler->onUpdate();
			trainer->onUpdate(renderer);

			while (!menu->shouldClose())
			{
				menu->run();

				if (menu->getButtonIndex() != hoverIndex)
				{
					hoverIndex = menu->getButtonIndex();

					data.frameImageLeft = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];
					data.frameImageRight = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];
					data.frameImageCenter = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];

					if (hoverIndex == 0)
						data.frameImageCenter = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME_HIGHLIGHT];
					else if (hoverIndex == 1)
						data.frameImageLeft = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME_HIGHLIGHT];
					else
						data.frameImageRight = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME_HIGHLIGHT];
				}

				if (selection != NONE)
					break;

				mapHandler->onUpdate();
				trainer->onUpdate(renderer);
			}

			data.frameImageLeft = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];
			data.frameImageRight = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];
			data.frameImageCenter = g_overlayTextureLocations[MenuOverlay::IMAGE_FRAME];

			menu->postRun();

			PokemonID id = grassStarter;

			if (selection == 1)
			{
				id = fireStarter;
				data.leftPokemonVisible = false;
			}
			else if (selection == 2)
			{
				id = waterStarter;
				data.rightPokemonVisible = false;
			}
			else
				data.centerPokemonVisible = false;

			// Get the pokemon
			Pokemon selectedPokemon = Pokemon(getSpeciesFromID(id), 5);

			// Give the moves PP
			Moveset oppMoves = selectedPokemon.getMoveset();
			oppMoves.move1pp = getAttackFromID(oppMoves.move1)->getPP();
			oppMoves.move2pp = getAttackFromID(oppMoves.move2)->getPP();
			oppMoves.move3pp = getAttackFromID(oppMoves.move3)->getPP();
			oppMoves.move4pp = getAttackFromID(oppMoves.move4)->getPP();
			selectedPokemon.setMoveset(oppMoves);
			
			trainer->setPokemon(0, selectedPokemon);

			pokedex->spotPokemon(waterStarter);
			pokedex->spotPokemon(grassStarter);
			pokedex->spotPokemon(fireStarter);
			pokedex->obtainPokemon(id);

			mapHandler->onUpdate();
			trainer->onUpdate(renderer);
			menu->onUpdate();


			// Let Rival selects counter

			// Dialogue. Ill take this one
			//TODO: Need to know whether or not faster dialogue is on
			//TODO: Allow player to rename pokemon
			//			- We have menu function for this
			MockFunctions::dialogue(mapHandler, trainer, menu, renderer, &data, "YES! I really wanted this one", "", false, mapHandler->getAI(0)->getName());

			
			if (id == grassStarter)
			{
				data.leftPokemonVisible = false;
			}
			else if (id == fireStarter)
			{
				data.rightPokemonVisible = false;
			}
			else
			{
				data.centerPokemonVisible = false;
			}



			MockFunctions::dialogue(mapHandler, trainer, menu, renderer, &data, "Good choices Ill put this one back", "", false, mapHandler->getAI(0)->getName());

			menu->remove(MenuOverlay::SELECT_POKEMON_FROM_PROFESSOR);

			trainer->addItem(ItemID::POKEBALL);
			trainer->addItem(ItemID::POKEBALL);
			trainer->addItem(ItemID::POKEBALL);
			trainer->addItem(ItemID::POKEBALL);
			trainer->addItem(ItemID::POKEBALL);
		}
	}

	static std::vector<CutsceneInstruction> momCallsDownstairs(MapHandler* mapHandler, Trainer* player, int variant, Pokedex* pokedex)
	{
		std::vector<CutsceneInstruction> instructions =
		{
			{Dialogue{player->getName() + " come downstairs" , "your friend is here", "Mom"}}
		};

		return instructions;
	}

	static std::vector<CutsceneInstruction> meetFriendAndTellToGoToProf(MapHandler* mapHandler, Trainer* player, int variant, Pokedex* pokedex)
	{
		if (variant == 0)
			return Variant::meetFriendAndTellToGoToProf_variant_0(mapHandler, player, variant);
		else
			return Variant::meetFriendAndTellToGoToProf_variant_1(mapHandler, player, variant);
	}

	static std::vector<CutsceneInstruction> recieveMapFromMom(MapHandler* mapHandler, Trainer* player, int variant, Pokedex* pokedex)
	{

		int stepsLeft = mapHandler->getAI(0)->position.coords.xTile - player->position.coords.xTile;
		int stepsDown = mapHandler->getAI(0)->position.coords.yTile - player->position.coords.yTile - 1;

		std::vector<CutsceneInstruction> instructions =
		{
			{Dialogue{"WAIT!!!", "", mapHandler->getAI(0)->getName()}},
			{mapHandler->getAI(0), InstructionType::TURN, Direction::LEFT},
			{player, InstructionType::TURN, Direction::UP},
			{InstructionType::PLAY}
		};

		for (int i = 0; i < stepsLeft; i++)
		{
			instructions.push_back({ mapHandler->getAI(0), InstructionType::MOVE, Direction::LEFT });
			instructions.push_back({ InstructionType::PLAY });
		}

		instructions.push_back({ mapHandler->getAI(0), InstructionType::TURN, Direction::DOWN });
		instructions.push_back({ InstructionType::PLAY });

		for (int i = 0; i < stepsDown; i++)
		{
			instructions.push_back({ mapHandler->getAI(0), InstructionType::MOVE, Direction::DOWN });
			instructions.push_back({ InstructionType::PLAY });
		}

		instructions.push_back({ Dialogue{ "You almost forgot this", "", mapHandler->getAI(0)->getName()}});

		instructions.push_back({ InstructionType::ACQUIRE_ITEM, Artifact{"Map", g_overlayTextureLocations[MenuOverlay::PAUSE_MAP_IMAGE]} });

		instructions.push_back({ Dialogue{ "Now you can use the map to", "find your way back home", mapHandler->getAI(0)->getName()}});
		instructions.push_back({ Dialogue{ "Okay sorry go have fun", "I love you!!!", mapHandler->getAI(0)->getName()}});

		return instructions;
	}

	static std::vector<CutsceneInstruction> enterProfessorLab(MapHandler* mapHandler, Trainer* player, int variant, Pokedex* pokedex)
	{
		// Prof is 2 above
		// Prof will walk down

		// Take them up top
		// Give presents for their birthday
		// 2 pokdexes
		// grab pokemon from vault thing
		// Everyone walks to table
		// Pick pokemon that you want
		// pokemon added to pokedex and roster
		// Talk some more

		int PROF = 0;
		int RIVAL = 1;

		std::vector<CutsceneInstruction> instructions =
		{
			{Dialogue{"Hey " + player->getName() + "!", "", mapHandler->getAI(RIVAL)->getName()}},
			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::DOWN},
			{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::DOWN},
			{InstructionType::PLAY },

			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::DOWN},
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
			{InstructionType::PLAY },

			{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::RIGHT},
			{InstructionType::PLAY },

			{Dialogue{"Happy Birthday!!", "", mapHandler->getAI(PROF)->getName()}},
			{Dialogue{"I was just telling " + mapHandler->getAI(RIVAL)->getName() + " that I", "have some presents for you both", mapHandler->getAI(PROF)->getName()}},

			{Dialogue{"Why don't you both follow me into the" , "lab", mapHandler->getAI(PROF)->getName()}},

			{mapHandler->getAI(PROF), InstructionType::TURN, Direction::UP},
			{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::UP},
			{InstructionType::PLAY },

			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::UP},
			{InstructionType::PLAY},

			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::UP},
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP},
			{player, InstructionType::MOVE, Direction::UP},
			{InstructionType::PLAY},

			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::UP},
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP},
			{player, InstructionType::MOVE, Direction::UP},
			{InstructionType::PLAY},

			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::UP},
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP},
			{player, InstructionType::MOVE, Direction::UP},
			{InstructionType::PLAY},

			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::UP},
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP},
			{player, InstructionType::MOVE, Direction::UP},
			{InstructionType::PLAY},

			{mapHandler->getAI(PROF), InstructionType::TURN, Direction::DOWN},
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP},
			{player, InstructionType::MOVE, Direction::UP},
			{InstructionType::PLAY},

			{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::RIGHT},
			{InstructionType::PLAY},

			{Dialogue{"It has been no secret to the", "entire town that you two,", mapHandler->getAI(PROF)->getName()}},
			{Dialogue{"want to become strong trainers.", "", mapHandler->getAI(PROF)->getName()}},

			{Dialogue{"In order to be strong trainers," , "you need strong pokemon", mapHandler->getAI(PROF)->getName()}},
			{Dialogue{"Here is a pokedex that will help" , "you learn about all of the pokemon", mapHandler->getAI(PROF)->getName()}},
			{InstructionType::ACQUIRE_ITEM, Artifact{"Pokedex", g_overlayTextureLocations[MenuOverlay::PAUSE_POKEDEX_IMAGE]}},


			{mapHandler->getAI(PROF), InstructionType::TURN, Direction::LEFT},
			{InstructionType::PLAY},

			{Dialogue{"Heres one for you too", "", mapHandler->getAI(PROF)->getName()}},

			{mapHandler->getAI(PROF), InstructionType::TURN, Direction::DOWN},
			{InstructionType::PLAY},

			{Dialogue{"As you encounter pokemon, the" , "pokedex will fill with information", mapHandler->getAI(PROF)->getName()}},
			{Dialogue{"Try to catch all of them and" , "fill the entire pokedex!!!", mapHandler->getAI(PROF)->getName()}},
			
			{mapHandler->getAI(PROF), InstructionType::TURN, Direction::DOWN},
			{InstructionType::PLAY},

			{Dialogue{"If you want to catch a pokemon" , "you are going to need one first", mapHandler->getAI(PROF)->getName()}},
			{Dialogue{"Wait at the table while I" , "grab them", mapHandler->getAI(PROF)->getName()}},

			{mapHandler->getAI(PROF), InstructionType::TURN, Direction::LEFT},
			{InstructionType::PLAY},

			{Dialogue{"WOW THANKS PROFESSOR!!!" , "BEST BIRTHDAY EVER", mapHandler->getAI(RIVAL)->getName()}},
			{Dialogue{"Of course", "" , mapHandler->getAI(PROF)->getName()}},

			{mapHandler->getAI(PROF), InstructionType::TURN, Direction::UP},
			{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::DOWN},
			{InstructionType::PLAY},

			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::UP},
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
			{InstructionType::PLAY},

			{mapHandler->getAI(PROF), InstructionType::MOVE, Direction::UP},
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN},
			{InstructionType::PLAY},

			
			{mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::LEFT},
			{player, InstructionType::TURN, Direction::DOWN},
			{InstructionType::PLAY},

			
			{mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT},
			{player, InstructionType::MOVE, Direction::DOWN},
			{InstructionType::PLAY},

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::LEFT },
			{ player, InstructionType::TURN, Direction::LEFT },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::LEFT },
			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::UP },
			{ player, InstructionType::MOVE, Direction::LEFT },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::LEFT },
			{ player, InstructionType::MOVE, Direction::LEFT },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::LEFT },
			{ player, InstructionType::MOVE, Direction::LEFT },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::DOWN },
			{ player, InstructionType::TURN, Direction::UP },
			{ InstructionType::PLAY },

			{ Dialogue{"You can each pick one pokemon", "", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"Thanks Professor", "", mapHandler->getAI(RIVAL)->getName()}},

			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::RIGHT },
			{ player, InstructionType::TURN, Direction::LEFT },
			{ InstructionType::PLAY },

			{ Dialogue{"Hey " + player->getName() + " which pokemon do you want", "", mapHandler->getAI(RIVAL)->getName()}},
			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::UP },
			{ player, InstructionType::TURN, Direction::UP },
			{ InstructionType::PLAY },

			{InstructionType::PLAY_OVERLAY, StoryGraphics::displayFirstPokemon},

			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::RIGHT },
			{ player, InstructionType::TURN, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::RIGHT },
			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::RIGHT },
			{ player, InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::DOWN },
			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::RIGHT },
			{ player, InstructionType::TURN, Direction::RIGHT },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::DOWN },
			{ player, InstructionType::MOVE, Direction::RIGHT },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::DOWN },
			{ player, InstructionType::TURN, Direction::UP },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },


			// Prof Gives Pokeballs
			{ Dialogue{"Laslty you two will need some" , "pokeballs to catch pokemon", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"Heres 5 for you", "", mapHandler->getAI(PROF)->getName()}},
			{ InstructionType::ACQUIRE_ITEM, Artifact{"Pokeballs", g_overlayTextureLocations[MenuOverlay::NURSE_POKEBALL]}},
			
			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::LEFT },
			{ InstructionType::PLAY },
			{ Dialogue{"And 5 for you", "", mapHandler->getAI(PROF)->getName()}},

			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::DOWN },
			{ InstructionType::PLAY },
			{ Dialogue{"When you see a wild pokemon", "You can throw one of these", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"The pokeball has a chance to", "catch the pokemon for you", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"It doesnt always work so you", "may need to buy stronger pokeballs", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"With these tools you can", "become the strongest trainers!!!", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"Good luck on your journeys", "", mapHandler->getAI(PROF)->getName()}},

			// Rival Asks for battle
			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::RIGHT },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::RIGHT },
			{ InstructionType::PLAY },
			
			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::UP },
			{ player, InstructionType::TURN, Direction::DOWN },
			{ InstructionType::PLAY },

			{ Dialogue{"Hey " + player->getName() + " lets battle!!!", "", mapHandler->getAI(RIVAL)->getName()}},

			// Send them outside
			{ Dialogue{"WAIIIIT!!!!! ", "", mapHandler->getAI(PROF)->getName()}},
			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::RIGHT},
			{ InstructionType::PLAY },
			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::RIGHT },
			{ InstructionType::PLAY },
			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::DOWN},
			{ InstructionType::PLAY },
			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },
			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },


			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::LEFT },
			{ InstructionType::PLAY },
			{ mapHandler->getAI(PROF), InstructionType::MOVE, Direction::LEFT },
			{ InstructionType::PLAY },
			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::DOWN},
			{ InstructionType::PLAY },

			{ Dialogue{"Your pokemon may be small", "but they are very strong", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"Take this fight outside", "", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"Sorry Professor","", mapHandler->getAI(RIVAL)->getName()}},
			{ Dialogue{player->getName() + " I'll be waiting for you", "at the village exit", mapHandler->getAI(RIVAL)->getName()}},

			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(PROF), InstructionType::TURN, Direction::UP },
			{ InstructionType::PLAY },

			{ Dialogue{"Go on and become a great trainer", "", mapHandler->getAI(PROF)->getName()}},
			{ Dialogue{"When you come back I'll check to see", "how many pokemon you've caught!", mapHandler->getAI(PROF)->getName()}},
		};

		return instructions;

	}

	static std::vector<CutsceneInstruction> firstRivalFight(MapHandler* mapHandler, Trainer* player, int variant, Pokedex* pokedex)
	{
		int RIVAL = 0;

		mapHandler->getAI(RIVAL)->position.coords.xTile = player->position.coords.xTile;

		Pokemon opponentPokemon;
		int index = -1;

		// Get opponent Pokemon
		for (int i = 0; i < 6; i++)
		{
			if (player->getRoster()[i].getLevel() != 0)
			{
				if (player->getRoster()[i].getSpecies().name == getSpeciesFromID(fireStarter).name)
					opponentPokemon = Pokemon(getSpeciesFromID(waterStarter), 5);
				else if (player->getRoster()[i].getSpecies().name == getSpeciesFromID(waterStarter).name)
					opponentPokemon = Pokemon(getSpeciesFromID(grassStarter), 5);
				else
					opponentPokemon = Pokemon(getSpeciesFromID(fireStarter), 5);

				index = i;
				break;
			}
		}

		// Give Opponent Pokemon Their PP
		{
			Moveset oppMoves = opponentPokemon.getMoveset();
			oppMoves.move1pp = getAttackFromID(oppMoves.move1)->getPP();
			oppMoves.move2pp = getAttackFromID(oppMoves.move2)->getPP();
			oppMoves.move3pp = getAttackFromID(oppMoves.move3)->getPP();
			oppMoves.move4pp = getAttackFromID(oppMoves.move4)->getPP();
			opponentPokemon.setMoveset(oppMoves);
		}

		std::vector<CutsceneInstruction> instructions =
		{
			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::DOWN },
			{ InstructionType::PLAY },

			{ Dialogue{"Okay lets test out our new pokemon!!!!", "", mapHandler->getAI(RIVAL)->getName()}},
			{ mapHandler->getAI(RIVAL), InstructionType::BATTLE, BattleData{{opponentPokemon}, false}},
			{ Dialogue{"Wow What a battle", "", mapHandler->getAI(RIVAL)->getName()}},
			{ Dialogue{"Here I have some potions to heal our", "pokemon.", mapHandler->getAI(RIVAL)->getName()}},
			{ player, InstructionType::HEAL_POKEMON, index},
			{ Dialogue{"Im going to go ahead to fight the", "gym leader!", mapHandler->getAI(RIVAL)->getName()}},
			{ Dialogue{"Im sure Ill see you soon.", "", mapHandler->getAI(RIVAL)->getName()}},
			{ Dialogue{"Find some strong pokemon and we can", "fight again!", mapHandler->getAI(RIVAL)->getName()}},
			{ Dialogue{"Okay Im off bye!!", "", mapHandler->getAI(RIVAL)->getName()}},
			{ mapHandler->getAI(RIVAL), InstructionType::TURN, Direction::UP },
			{ InstructionType::PLAY },
			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP },
			{ InstructionType::PLAY },
			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP },
			{ InstructionType::PLAY },
			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP },
			{ InstructionType::PLAY },
			{ mapHandler->getAI(RIVAL), InstructionType::MOVE, Direction::UP },
			{ InstructionType::PLAY },
		};

		return instructions;
	}
}

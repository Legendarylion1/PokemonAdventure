#include "DataManager.h"
#include <fstream>

void DataManager::setup(Trainer* player, PC* pc, MapHandler* mapHandler, Input* input, Renderer* renderer, Timer* timer, CharacterMover* characterMover, Pokedex* pokedex, DialogueRenderer* dialogueRenderer, Story* story)
{
	m_player = player;
	m_pc = pc;
	m_mapHandler = mapHandler;
	m_input = input;
	m_renderer = renderer;
	m_timer = timer;
	m_characterMover = characterMover;
	m_itemStorage = m_player->getItemStorage();
	m_pokedex = pokedex;
	m_dialogueRenderer = dialogueRenderer;
	m_story = story;
}

void DataManager::saveGame()
{
	//TODO: Encrypt and come up with a checksum
	std::ofstream saveFile(m_fileLocation[m_file]);

	if (!saveFile.is_open())
		return;	//TODO: Handle
	
	saveHeader(&saveFile);
	saveInput(&saveFile);
	saveTrainer(&saveFile);
	saveItems(&saveFile);
	saveRoster(&saveFile);
	savePC(&saveFile);
	saveRenderer(&saveFile);
	savePokedex(&saveFile);
	saveMap(&saveFile);
	
	saveFile.close();
}

void DataManager::loadGame()
{
	std::string data;

	std::ifstream saveFile(m_fileLocation[m_file]);

	std::string loadState;

	char delimeter = ',';

	while (getline(saveFile, data)) {

		if (data == MAIN_HEADER)
		{
			loadState = MAIN_HEADER;
			continue;
		}
		else if (data == INPUT_HEADER)
		{
			loadState = INPUT_HEADER;
			continue;
		}
		else if (data == TRAINER_HEADER)
		{
			loadState = TRAINER_HEADER;
			continue;
		}
		else if (data == ROSTER_HEADER)
		{
			loadState = ROSTER_HEADER;
			continue;
		}
		else if (data == PC_HEADER)
		{
			loadState = PC_HEADER;
			continue;
		}
		else if (data == RENDERER_HEADER)
		{
			loadState = RENDERER_HEADER;
			continue;
		}
		else if (data == ITEM_HEADER)
		{
			loadState = ITEM_HEADER;
			continue;
		}
		else if (data == POKEDEX_HEADER)
		{
			loadState = POKEDEX_HEADER;
			continue;
		}
		else if (data == MAP_HEADER)
		{
			loadState = MAP_HEADER;
			continue;
		}


		if (loadState == MAIN_HEADER)
			loadHeader(splitString(data, delimeter));
		else if (loadState == INPUT_HEADER)
			loadInput(splitString(data, delimeter));
		else if (loadState == TRAINER_HEADER)
			loadTrainer(splitString(data, delimeter));
		else if (loadState == ROSTER_HEADER)
			loadRoster(splitString(data, delimeter));
		else if (loadState == PC_HEADER)
			loadPC(splitString(data, delimeter));
		else if (loadState == RENDERER_HEADER)
			loadRenderer(splitString(data, delimeter));
		else if (loadState == ITEM_HEADER)
			loadItem(splitString(data, delimeter));
		else if (loadState == POKEDEX_HEADER)
			loadPokedex(splitString(data, delimeter));
		else if (loadState == MAP_HEADER)
			loadMap(splitString(data, delimeter));
	}

	saveFile.close();
}

void DataManager::autoSave()
{
	if (!m_mapHandler->shouldAutoSave())
		return;

	saveGame();	//TODO: Probably display saving icon. Saving happens so fast tho so idk if its needed
}

void DataManager::loadNewGame()
{

	m_player->position.coords.xTile = 4;
	m_player->position.coords.yTile = 3;
	m_player->position.direction = Direction::DOWN;

	m_mapHandler->loadNewGame();
	loadNewInput();
	loadNewRenderer();

	m_timer->setPlayTime(0);
}

void DataManager::deleteSave(FileNumber fileNumber)
{
	remove(m_fileLocation[fileNumber].c_str());
}

HeaderSave DataManager::loadHeader(FileNumber fileNumber)
{
	HeaderSave headerData;

	std::string lineData;

	std::ifstream saveFile(m_fileLocation[fileNumber]);

	if (!saveFile.is_open())
	{
		saveFile.close();
		headerData.playerName = "New Game";
		return headerData;
	}

	int count = 0;
	try
	{
		while (getline(saveFile, lineData)) {

			if (count == 0)
			{
				count++;
				continue;
			}

			saveFile.close();

			std::vector<std::string> splitData = splitString(lineData, ',');

			headerData.playerName = splitData.at(0);
			headerData.playTime = m_timer->formatTime(std::stoi(splitData.at(1)));
			headerData.pokedexFound = std::stoi(splitData.at(2));
			headerData.badgesObtained = std::stoi(splitData.at(3));
			
			return headerData;
		}
	}
	catch (...)
	{
		saveFile.close();
		headerData.playerName = "New Game";
		return headerData;
	}
}

void DataManager::saveHeader(std::ofstream* file)
{
	HeaderSave headerSave;

	headerSave.playerName = m_player->getName();
	headerSave.playTime = std::to_string(m_timer->getPlayTime());	
	headerSave.pokedexFound = 3; //TODO: Add this stat
	headerSave.badgesObtained = m_player->getBadgeCount();
	headerSave.fasterText = m_dialogueRenderer->getFasterText();
	headerSave.cutscene = m_story->getCurrentScene();

	*file << MAIN_HEADER + "\n";
	*file << std::string(headerSave);
}

void DataManager::saveInput(std::ofstream* file)
{
	*file << INPUT_HEADER + "\n";
	*file << std::string(InputSave(*m_input));
}

void DataManager::saveTrainer(std::ofstream* file)
{
	*file << TRAINER_HEADER + "\n";
	*file << std::string(TrainerSave(*m_player));
}

void DataManager::saveRoster(std::ofstream* file)
{
	*file << ROSTER_HEADER + "\n";

	for (int i = 0; i < 6; i++)
	{
		*file << std::to_string(i) << "," << std::string(PokemonSave(m_player->getPokemon(i)));
	}
}

void DataManager::savePC(std::ofstream* file)
{
	*file << PC_HEADER + "\n";

	for (int box = 0; box < NUMBER_OF_BOXES; box++)
	{
		for (int pokemonIndex = 0; pokemonIndex < POKEMON_IN_BOX; pokemonIndex++)
		{
			if (m_pc->getPokemon(box, pokemonIndex).getLevel() == 0)
				continue;

			*file << std::to_string(box) << comma << std::to_string(pokemonIndex) << comma
			<< std::string(PokemonSave(m_pc->getPokemon(box, pokemonIndex)));
		}
	}
}

void DataManager::saveRenderer(std::ofstream* file)
{
	*file << RENDERER_HEADER + "\n";
	*file << std::string(RendererSave(*m_renderer));

}

void DataManager::saveItems(std::ofstream* file)
{
	*file << ITEM_HEADER + "\n";

	for (auto item = m_itemStorage->getAllItems()->begin(); item != m_itemStorage->getAllItems()->end(); item++)
	{
		*file << std::string(ItemSave{ item->first, item->second });
	}
}

void DataManager::savePokedex(std::ofstream* file)
{
	*file << POKEDEX_HEADER + "\n";
	*file << m_pokedex->save() << std::endl;
}

void DataManager::saveMap(std::ofstream* file)
{
	*file << MAP_HEADER + "\n";
	*file << m_mapHandler->save() << std::endl;
}

void DataManager::loadHeader(std::vector<std::string> data)
{
	m_timer->setPlayTime(std::stoi(data.at(1)));
	m_dialogueRenderer->setFasterText((std::stoi(data.at(4))));
	m_story->setCutSceneID(std::stoi(data.at(5)));
}

void DataManager::loadInput(std::vector<std::string> data)
{
	InputSave inputSave{};
	
	inputSave.keyboardUp.main		= data.at(0);
	inputSave.keyboardUp.alt		= data.at(1);
	inputSave.keyboardDown.main		= data.at(2);
	inputSave.keyboardDown.alt		= data.at(3);
	inputSave.keyboardLeft.main		= data.at(4);
	inputSave.keyboardLeft.alt		= data.at(5);
	inputSave.keyboardRight.main	= data.at(6);
	inputSave.keyboardRight.alt		= data.at(7);
	inputSave.keyboardSelect.main	= data.at(8);
	inputSave.keyboardSelect.alt	= data.at(9);
	inputSave.keyboardPause.main	= data.at(10);
	inputSave.keyboardPause.alt		= data.at(11);
	inputSave.keyboardBack.main		= data.at(12);
	inputSave.keyboardBack.alt		= data.at(13);
	inputSave.keyboardSprint.main	= data.at(14);
	inputSave.keyboardSprint.alt	= data.at(15);
	inputSave.controllerUp.main		= data.at(16);
	inputSave.controllerUp.alt		= data.at(17);
	inputSave.controllerDown.main	= data.at(18);
	inputSave.controllerDown.alt	= data.at(19);
	inputSave.controllerLeft.main	= data.at(20);
	inputSave.controllerLeft.alt	= data.at(21);
	inputSave.controllerRight.main	= data.at(22);
	inputSave.controllerRight.alt	= data.at(23);
	inputSave.controllerSelect.main = data.at(24);
	inputSave.controllerSelect.alt	= data.at(25);
	inputSave.controllerPause.main	= data.at(26);
	inputSave.controllerPause.alt	= data.at(27);
	inputSave.controllerBack.main	= data.at(28);
	inputSave.controllerBack.alt	= data.at(29);
	inputSave.controllerSprint.main = data.at(30);
	inputSave.controllerSprint.alt	= data.at(31);
	
	m_input->load(inputSave);
}

void DataManager::loadTrainer(std::vector<std::string> data)
{
	TrainerSave trainerSave{};

	trainerSave.name = data.at(0);
	trainerSave.money = std::stoi(data.at(1));
	trainerSave.x = std::stoi(data.at(2));
	trainerSave.y = std::stoi(data.at(3));
	trainerSave.direction = std::stoi(data.at(4));
	trainerSave.badgeCount = std::stoi(data.at(5));
	trainerSave.characterID = std::stoi(data.at(6));	//TODO: Change to the save data

	m_player->load(trainerSave);
}

void DataManager::loadRoster(std::vector<std::string> data)
{
	PokemonSave pokemonSave{};
	Pokemon savedPokemon;

	int rosterPosition = std::stoi(data.at(0));

	pokemonSave.name = data.at(1);
	pokemonSave.species = PokemonID(std::stoi(data.at(2)));
	pokemonSave.level = std::stoi(data.at(3));
	pokemonSave.currentHealth = std::stoi(data.at(4));
	pokemonSave.currentXP = std::stoi(data.at(5));
	pokemonSave.hpIv = std::stoi(data.at(6));
	pokemonSave.attackIv = std::stoi(data.at(7));
	pokemonSave.defenseIv = std::stoi(data.at(8));
	pokemonSave.speedIv = std::stoi(data.at(9));
	pokemonSave.specialIv = std::stoi(data.at(10));
	pokemonSave.hpEv = std::stoi(data.at(11));
	pokemonSave.attackEv = std::stoi(data.at(12));
	pokemonSave.defenseEv = std::stoi(data.at(13));
	pokemonSave.spattackEv = std::stoi(data.at(14));
	pokemonSave.spDefenseEv = std::stoi(data.at(15));
	pokemonSave.speedEv = std::stoi(data.at(16));
	pokemonSave.evasionEv = std::stoi(data.at(17));
	pokemonSave.accuracyEv = std::stoi(data.at(18));
	pokemonSave.move1 = std::stoi(data.at(19));
	pokemonSave.move2 = std::stoi(data.at(20));
	pokemonSave.move3 = std::stoi(data.at(21));
	pokemonSave.move4 = std::stoi(data.at(22));
	pokemonSave.move1pp = std::stoi(data.at(23));
	pokemonSave.move2pp = std::stoi(data.at(24));
	pokemonSave.move3pp = std::stoi(data.at(25));
	pokemonSave.move4pp = std::stoi(data.at(26));

	pokemonSave.statusID = std::stoi(data.at(27));
	pokemonSave.turnCount = std::stoi(data.at(28));
	pokemonSave.isBlocker = (bool)std::stoi(data.at(29));
	pokemonSave.isEvasive = (bool)std::stoi(data.at(30));
	pokemonSave.forcedAttack = std::stoi(data.at(31));

	savedPokemon.load(pokemonSave);
	m_player->setPokemon(rosterPosition, savedPokemon);
}

void DataManager::loadPC(std::vector<std::string> data)
{
	PokemonSave pokemonSave{};
	Pokemon savedPokemon;

	int boxNumber = std::stoi(data.at(0));
	int boxIndex = std::stoi(data.at(1));

	pokemonSave.name = data.at(2);
	pokemonSave.species = PokemonID(std::stoi(data.at(3)));
	pokemonSave.level = std::stoi(data.at(4));
	pokemonSave.currentHealth = std::stoi(data.at(5));
	pokemonSave.currentXP = std::stoi(data.at(6));
	pokemonSave.hpIv = std::stoi(data.at(7));
	pokemonSave.attackIv = std::stoi(data.at(8));
	pokemonSave.defenseIv = std::stoi(data.at(9));
	pokemonSave.speedIv = std::stoi(data.at(10));
	pokemonSave.specialIv = std::stoi(data.at(11));
	pokemonSave.hpEv = std::stoi(data.at(12));
	pokemonSave.attackEv = std::stoi(data.at(13));
	pokemonSave.defenseEv = std::stoi(data.at(14));
	pokemonSave.spattackEv = std::stoi(data.at(15));
	pokemonSave.spDefenseEv = std::stoi(data.at(16));
	pokemonSave.speedEv = std::stoi(data.at(17));
	pokemonSave.evasionEv = std::stoi(data.at(18));
	pokemonSave.accuracyEv = std::stoi(data.at(19));
	pokemonSave.move1 = std::stoi(data.at(20));
	pokemonSave.move2 = std::stoi(data.at(21));
	pokemonSave.move3 = std::stoi(data.at(22));
	pokemonSave.move4 = std::stoi(data.at(23));
	pokemonSave.move1pp = std::stoi(data.at(24));
	pokemonSave.move2pp = std::stoi(data.at(25));
	pokemonSave.move3pp = std::stoi(data.at(26));
	pokemonSave.move4pp = std::stoi(data.at(27));

	pokemonSave.statusID = std::stoi(data.at(28));
	pokemonSave.turnCount = std::stoi(data.at(29));
	pokemonSave.isBlocker = (bool)std::stoi(data.at(30));
	pokemonSave.isEvasive = (bool)std::stoi(data.at(31));
	pokemonSave.forcedAttack = std::stoi(data.at(32));

	savedPokemon.load(pokemonSave);
	m_pc->setPokemon(boxNumber, boxIndex, savedPokemon);
}

void DataManager::loadRenderer(std::vector<std::string> data)
{
	RendererSave rendererSave{};

	rendererSave.resolution = std::stoi(data.at(0));
	rendererSave.fullscreen = std::stoi(data.at(1));
	rendererSave.showFPS = std::stoi(data.at(2));

	m_renderer->load(rendererSave);
	m_characterMover->setTileSize(m_renderer->getTileSize());
}

void DataManager::loadItem(std::vector<std::string> data)
{
	for (int i = 0; i < std::stoi(data.at(1)); i++)
		m_player->getItemStorage()->addItem(ItemID(std::stoi(data.at(0))));
}

void DataManager::loadPokedex(std::vector<std::string> data)
{
	m_pokedex->load(data);
}

void DataManager::loadMap(std::vector<std::string> data)
{
	m_mapHandler->load(data);
}

void DataManager::loadNewInput()
{
	InputSave inputSave{};

	inputSave.keyboardUp.main = keyBinds::w;
	inputSave.keyboardDown.main = keyBinds::s;
	inputSave.keyboardLeft.main = keyBinds::a;
	inputSave.keyboardRight.main = keyBinds::d;
	inputSave.keyboardSelect.main = keyBinds::e;
	inputSave.keyboardBack.main = keyBinds::q;
	inputSave.keyboardPause.main = keyBinds::p;
	inputSave.keyboardSprint.main = keyBinds::left_shift;

	inputSave.controllerUp.main = keyBinds::gamepad_dpad_up;
	inputSave.controllerDown.main = keyBinds::gamepad_dpad_down;
	inputSave.controllerLeft.main = keyBinds::gamepad_dpad_left;
	inputSave.controllerRight.main = keyBinds::gamepad_dpad_right;
	inputSave.controllerSelect.main = keyBinds::gamepad_a;
	inputSave.controllerBack.main = keyBinds::gamepad_b;
	inputSave.controllerPause.main = keyBinds::gamepad_start;
	inputSave.controllerSprint.main = keyBinds::gamepad_y;

	m_input->load(inputSave);
}

void DataManager::loadNewRenderer()
{
	m_renderer->loadNewGame();
	m_characterMover->setTileSize(m_renderer->getTileSize());
}

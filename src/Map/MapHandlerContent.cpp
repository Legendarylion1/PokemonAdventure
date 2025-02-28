#include "MapHandler.h"

///		~ DRAWING MAP ~
/// # -	Boundary
/// R - Return
/// N - Nurse
/// P - PokeCenter
/// C - PC
/// S - PokeMart
/// I - Buy Battle Items
/// W - Buy World Items
/// G - Grass
/// A - AI
/// L - Linked Section
/// U - Story
/// 
///			Jump not implemented yet
/// V - Jump Down
/// ^ - Jump Up
/// > - Jump Right
/// < - Jump Left
///		~ DRAWING MAP ~
/// 
/// NOTE: Maps start at 0,0 in the bottom left

// NOTE: If memory becomes a problem we can store the maps in files for loading

void MapHandler::createPokemonCenter(Renderer* renderer)
{
	MapSection linkedMapSectionTest = MapSection(renderer, SectionID::POKE_CENTER, true);
	std::vector<std::string> pokecenter = {
		"##############",
		"##############",
		"####     ##C##",
		"####     #   #",
		"#  ####N##   #",
		"#            #",
		"#####     ####",
		"#####     ####",
		"#####     ####",
		"#    LLL     #"
	};

	linkedMapSectionTest.setMap(pokecenter);

	linkedMapSectionTest.linkSection({ 5,0 }, SectionID::PREVIOUS_SECTION);
	linkedMapSectionTest.linkSection({ 6,0 }, SectionID::PREVIOUS_SECTION);
	linkedMapSectionTest.linkSection({ 7,0 }, SectionID::PREVIOUS_SECTION);

	addMapSection(linkedMapSectionTest);
}

void MapHandler::createPokemart(Renderer* renderer)
{
	MapSection pokemartSection = MapSection(renderer, SectionID::POKE_MART, true);

	std::vector<std::string> pokemart = {
		"##############",
		"##############",
		"## #     #####",
		"## #     #  ##",
		"#  ##I##W#  ##",
		"#           ##",
		"# ##     ## ##",
		"# ##     ## ##",
		"# ##     ## ##",
		"#    LLL     #"
	};

	pokemartSection.setMap(pokemart);

	pokemartSection.linkSection({ 5,0 }, SectionID::PREVIOUS_SECTION);
	pokemartSection.linkSection({ 6,0 }, SectionID::PREVIOUS_SECTION);
	pokemartSection.linkSection({ 7,0 }, SectionID::PREVIOUS_SECTION);

	addMapSection(pokemartSection);
}

void MapHandler::createHomeVillageRoute1(Renderer* renderer)
{
	MapSection mapSection = MapSection(renderer, SectionID::HOME_VILLAGE_ROUTE_1);
	std::vector<std::string> map = {
		"###################################",
		"###################################",
		"###################################",
		"###################################",
		"###############LLL#################",
		"##############     ################",
		"########                    #######",
		"########              GGGGG #######",
		"########              GGGGG #######",
		"########                    #######",
		"########        ##########  #######",
		"######## ########GGG  GGG##########",
		"######## ########GGG   GG##########",
		"######## ########        ##########",
		"######## ########        ##########",
		"######## ###########  #############",
		"########           #        #######",
		"########                    #######",
		"########                    #######",
		"########                    #######",
		"########GGG                 #######",
		"########GGG##               #######",
		"########GGG##             GG#######",
		"########GGG##             GG#######",
		"########GGG##             GG#######",
		"########GGG##             GG#######",
		"########GGG##             GG#######",
		"########GGG##          GGGGG#######",
		"########GGG##          GGGGG#######",
		"########GGG##          GGGGG#######",
		"#############          GGGGG#######",
		"#############          GGGGG#######",
		"########               GGGGG#######",
		"########               GGGGG#######",
		"########               GGGGG#######",
		"########               GGGGG#######",
		"########               GGGGG#######",
		"########                    #######",
		"########                    #######",
		"###############   #################",
		"###############   #################",
		"###############   #################",
		"###############   #################",
		"       #      #UUU##        ##     ",
		"       #                ### #      ",
		"     ###                ### #      ",
		"     ##########         ### #      ",
		"       ########   #     #L# #      ",
		"       ########             #      ",
		"       #    #               ###    ",
		"       #                    ###    ",
		"       #                    ###    ",
		"       #                ##  ###    ",
		"       #          #####     #      ",
		"     ###  #####   #####     #      ",
		"     ###  #####   #############    ",
		"       #  #####    #L# ########    ",
		"       #      #        ########    ",
		"       #              ##    ###    ",
		"     ### ##           ##    #      ",
		"     ### ##                 #      ",
		"     ###                    #      ",
		"     ###                    #      ",
		"       ######################      ",
		"            ##   ##     ##         ",
		"            ##   ##     ##         ",
		"            ##   ##     ##         ",
		"                                   ",
		"                                   ",
		"                                   "
	};

	mapSection.setMap(map);

	mapSection.addPokemonSpawn({ Rarity::COMMON, PokemonID::Baroot });
	mapSection.addPokemonSpawn({ Rarity::UNCOMMON, PokemonID::Bery });
	mapSection.addPokemonSpawn({ Rarity::RARE, PokemonID::Fitty });
	mapSection.setPokemonLevelCaps(1, 8);

	// Route 2
	mapSection.linkSection({15,65}, SectionID::FIRST_TOWN_ROUTE_2, { 15, 6 });
	mapSection.linkSection({16,65}, SectionID::FIRST_TOWN_ROUTE_2, { 15, 6 });
	mapSection.linkSection({17,65}, SectionID::FIRST_TOWN_ROUTE_2, { 15, 6 });

	// Player Home
	mapSection.linkSection({20,13}, SectionID::START_HOUSE_BASE_FLOOR, { 3, 1 });

	// Professor Lab
	mapSection.linkSection({25, 22}, SectionID::PROFESSOR_LAB, { 7, 1 });

	// NPT
	{
		//TODO: Get Rival Name
		CharacterID rivalID = m_trainer->getID();

		if (rivalID == CharacterID::PLAYER_MALE_TRAINER)
			rivalID = CharacterID::PLAYER_FEMALE_TRAINER;
		NPT* rival = new NPT("Rival", rivalID, 16, 31, Direction::DOWN);
		rival->setCutsceneRemovalID(CutSceneID(int(CutSceneID::FIRST_RIVAL_FIGHT) + 1));
		rival->giveMoney(60);

		// Story Guards
		// They block the user from leaving before getting their starter
		//16, 26 Center Guard 3 needed. one on either side
		NPT* guard1 = new NPT("Guard1", CharacterID::SECURITY_OFFICER, 15, 26, Direction::DOWN);
		NPT* guard2 = new NPT("Guard2", CharacterID::SECURITY_OFFICER, 16, 26, Direction::DOWN);
		NPT* guard3 = new NPT("Guard3", CharacterID::SECURITY_OFFICER, 17, 26, Direction::DOWN);

		guard1->setCutsceneRemovalID(CutSceneID(int(CutSceneID::ENTER_PROFESSOR_LAB) + 1));
		guard2->setCutsceneRemovalID(CutSceneID(int(CutSceneID::ENTER_PROFESSOR_LAB) + 1));
		guard3->setCutsceneRemovalID(CutSceneID(int(CutSceneID::ENTER_PROFESSOR_LAB) + 1));

		guard1->addNormalDialogue({ "Sorry kid you can't go past here", "There are some bandits attacking with pokemon" });
		guard1->addNormalDialogue({ "Dont worry were taking care of it", "I think I saw your friend run down the stone path" });

		guard2->addNormalDialogue({ "Sorry kid you can't go past here", "There are some bandits attacking with pokemon" });
		guard2->addNormalDialogue({ "Dont worry were taking care of it", "I think I saw your friend run down the stone path" });

		guard3->addNormalDialogue({ "Sorry kid you can't go past here", "There are some bandits attacking with pokemon" });
		guard3->addNormalDialogue({ "Dont worry were taking care of it", "I think I saw your friend run down the stone path" });

		mapSection.addNPT(rival);
		mapSection.addNPT(guard1);
		mapSection.addNPT(guard2);
		mapSection.addNPT(guard3);


		//NPT* testNPT = new NPT("Jake", CharacterID::FIRST_TRAINER, 27, 53, Direction::LEFT, 1000, 3);
		// 
		//testNPT->setPokemon(0, Pokemon(fitty, 8));
		//testNPT->setPokemon(1, Pokemon(bery, 6));
		// 
		//testNPT->addBattleDialogue({ "Im so excited", "Lets fight" });
		//testNPT->addNormalDialogue({ "That was a good fight", "I need to train more" });
		// 
		//testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::LEFT });
		//testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::LEFT });
		//testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::LEFT });
		//testNPT->addScriptInstruction({ InstructionType::TURN, Direction::RIGHT });
		//testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::RIGHT });
		//testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::RIGHT });
		//testNPT->addScriptInstruction({ InstructionType::MOVE, Direction::RIGHT });
		//testNPT->addScriptInstruction({ InstructionType::TURN, Direction::LEFT });
		// 
		//mapSection.addNPT(testNPT);
	}
	
	mapSection.addSubsection(std::make_tuple (Range{0, 0, 30, 26 }, MapSubSectionID::HOME_VILLAGE));
	mapSection.addSubsection(std::make_tuple (Range{0, 27, 30, 100 }, MapSubSectionID::ROUTE_1));

	addMapSection(mapSection);
}

void MapHandler::createFirstTownRoute2(Renderer* renderer)
{

	MapSection firstTownRoute2Section = MapSection(renderer, SectionID::FIRST_TOWN_ROUTE_2);
	std::vector<std::string> firstTownRoute2Layout = {
	"     #       #          #     ",
	"     #       #          #     ",
	"     #       #          #     ",
	"     #       #          #     ",
	"     #       #  #########     ",
	"     #       #  #########     ",
	"     #       #    GGGGGG#     ",
	"     #########    GGGGGG#     ",
	"     #    GGGG#######GGG#     ",
	"     #    GGGG#     #GGG#     ",
	"     #######GG#######GGG#     ",
	"     #     #GG#GGG###GGG#     ",
	"     ####  #GG#GGG###GGG#     ",
	"     #GG#  #GG#GGG GGGGG#     ",
	"     #GG#  #GG#GGG GGGGG#     ",
	"     #GG#  #GG#    GGGGG#     ",
	"     #GG#  #GG#####   ###     ",
	"     #GG####GG#####   # #     ",
	"     #GGGGGGGGGGGGG   # #     ",
	"     #GGGGGGGGGGGGG   # #     ",
	"     ####  ############ #     ",
	"     #  #  #            #     ",
	"     #  #  #            #     ",
	"     #  #  #  ########  #     ",
	"     #  #  #  #GG    #  #     ",
	"     #  #  #  #GG    #  #     ",
	"     #  #  #  #GG#####  #     ",
	"     #  #  ####GG#      #     ",
	"     #  #   GGGGG#      #     ",
	"     #  #   GGGGG#      #     ",
	"     #  ######GGG#      #     ",
	"     #       #GGG#      #     ",
	"     #       #GGG#      #     ",
	"     ##      #GGG#      #     ",
	"     # # #   #GGG###### #     ",
	"     # ## ####GGG##   ###     ",
	"     # ##   ##   #     ##     ",
	"     #                 ##     ",
	"     #########   ########     ",
	"     #####  ##   ###    #     ",
	"     #########   ### ## #     ",
	"     ##  ####    ### ## #     ",
	"     #   ####        ## #     ",
	"     #               ## #     ",
	"     #   ####           #     ",
	"     ########     ##### #     ",
	"     ########     ##### #     ",
	"     #            ##### #     ",
	"     # #####     ###LL# #     ",
	"     # #####            #     ",
	"     # #####            #     ",
	"     # ##LL# #          #     ",
	"     #  #          ######     ",
	"     #             #### #     ",
	"     #                  #     ",
	"     #########LLL########     ",
	"                              ",
	"                              ",
	"                              ",
	"                              ",
	"                              "
	};

	firstTownRoute2Section.setMap(firstTownRoute2Layout);

	//Previous Route 1
	firstTownRoute2Section.linkSection({14,5}, SectionID::HOME_VILLAGE_ROUTE_1, {16, 64});
	firstTownRoute2Section.linkSection({15,5}, SectionID::HOME_VILLAGE_ROUTE_1, {16, 64});
	firstTownRoute2Section.linkSection({16,5}, SectionID::HOME_VILLAGE_ROUTE_1, {16, 64});


	//Pokemon Center
	firstTownRoute2Section.linkSection({9,9}, SectionID::POKE_CENTER, {6, 1});
	firstTownRoute2Section.linkSection({10,9}, SectionID::POKE_CENTER, {6, 1});

	//Pokemart
	firstTownRoute2Section.linkSection({ 20,12 }, SectionID::POKE_MART, { 6, 1 });
	firstTownRoute2Section.linkSection({ 21,12 }, SectionID::POKE_MART, { 6, 1 });

	firstTownRoute2Section.addSubsection(std::make_tuple(Range{ 0,0,50,22 }, MapSubSectionID::TOWN_1));
	firstTownRoute2Section.addSubsection(std::make_tuple(Range{ 0,23, 50, 100 }, MapSubSectionID::ROUTE_2));

	addMapSection(firstTownRoute2Section);
}

void MapHandler::createStartHouseBaseFloor(Renderer* renderer)
{
	MapSection startHouseBaseFloorSection = MapSection(renderer, SectionID::START_HOUSE_BASE_FLOOR, true);

	std::vector<std::string> map =
	{
		"##############################",
		"##############################",
		"### # ## ######## ####     L##",
		"#        #     ##          ###",
		"##  #  # #     ##       ######",
		"##     # #      #       ######",
		"## ###   ##  ####          ###",
		"#        ##  ####       #    #",
		"#        ##             #    #",
		"#         U          # ##    #",
		"#         U          # ##    #",
		"#       ##   ###     # ##    #",
		"#       ### #####    # ##    #",
		"# UUU   ###  ###     #  # ## #",
		"#ULLLU  ###          #  # ## #",
	};

	startHouseBaseFloorSection.setMap(map);

	// Back to village
	startHouseBaseFloorSection.linkSection({ 2,0 }, SectionID::HOME_VILLAGE_ROUTE_1, {20, 12});
	startHouseBaseFloorSection.linkSection({ 3,0 }, SectionID::HOME_VILLAGE_ROUTE_1, {20, 12});
	startHouseBaseFloorSection.linkSection({ 4,0 }, SectionID::HOME_VILLAGE_ROUTE_1, {20, 12});

	// To Room
	startHouseBaseFloorSection.linkSection({ 27, 12}, SectionID::START_HOUSE_ROOM, {8,4});
	

	// NPT
	//NPT* mom = new NPT()

	NPT* mom = new NPT("Mom", CharacterID::MOM, 8, 5, Direction::DOWN);
	mom->addNormalDialogue({ "You are going to be the", "greatest. I believe in you!" });
	startHouseBaseFloorSection.addNPT(mom);


	CharacterID rivalID = m_trainer->getID();

	if (rivalID == CharacterID::PLAYER_MALE_TRAINER)
		rivalID = CharacterID::PLAYER_FEMALE_TRAINER;

	NPT* rival = new NPT("Rival", rivalID, 7, 4, Direction::RIGHT);	//TODO: Get Rival Name
	rival->setCutsceneRemovalID(CutSceneID::RECIEVE_MAP_FROM_MOM);
	startHouseBaseFloorSection.addNPT(rival);

	addMapSection(startHouseBaseFloorSection);
}

void MapHandler::createStartHouseUpstairsRoom(Renderer* renderer)
{
	MapSection startHouseUpstairsSection = MapSection(renderer, SectionID::START_HOUSE_ROOM, true);

	std::vector<std::string> map =
	{
		"##########",
		"##########",
		"#  ###   L",
		"#    U   #",
		"#    U   #",
		"#  # U   #",
		"###  U   #",
	};

	startHouseUpstairsSection.setMap(map);

	startHouseUpstairsSection.linkSection({ 9,4 }, SectionID::START_HOUSE_BASE_FLOOR, { 26, 12 });

	addMapSection(startHouseUpstairsSection);
}

void MapHandler::createProfLab(Renderer* renderer)
{
	MapSection profLabSection = MapSection(renderer, SectionID::PROFESSOR_LAB, true);
	
	std::vector<std::string> map = {
		"###############",
		"###############",
		"#  ##  ##   # #",
		"#       ##### #",
		"# ####        #",
		"# ####    ##  #",
		"#         ### #",
		"#           # #",
		"####    ##### #",
		"####    ##### #",
		"####   U      #",
		"####  LLL     #",
	};

	profLabSection.setMap(map);

	profLabSection.linkSection({ 6,0 }, SectionID::HOME_VILLAGE_ROUTE_1, {25,21});
	profLabSection.linkSection({ 7,0 }, SectionID::HOME_VILLAGE_ROUTE_1, {25,21});
	profLabSection.linkSection({ 8,0 }, SectionID::HOME_VILLAGE_ROUTE_1, {25,21});

	CharacterID rivalID = m_trainer->getID();

	if (rivalID == CharacterID::PLAYER_MALE_TRAINER)
		rivalID = CharacterID::PLAYER_FEMALE_TRAINER;

	NPT* professor = new NPT("Professor", CharacterID::PROFESSOR, 7, 4, Direction::DOWN);
	profLabSection.addNPT(professor);

	NPT* rival = new NPT("Rival", rivalID, 6, 3, Direction::RIGHT);	//TODO: Get Rival Name
	rival->setCutsceneRemovalID( CutSceneID(int(CutSceneID::ENTER_PROFESSOR_LAB) + 1));
	profLabSection.addNPT(rival);

	addMapSection(profLabSection);
}

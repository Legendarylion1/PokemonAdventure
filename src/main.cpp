#include "Game/Game.h"

///
///												UNOFFICIAL TODO LIST
///		NOTE: I tend to forget about this list because I have an updated list on my phone that I reference
/// 
///						~ BATTLE SIMULATOR ~
///		Do more research on what to do if we crit and its super effective. Should we say both. Should it just be one message?
/// 
///						~ GENERAL ~
/// 
///		Remove all duplicate references. Theres a lot of files being reference that dont need to be due to a lower file
///		Refactor Code for clarity
/// 
///						~ GRAPHICS ~
///		Animate Pokemon Swap
/// 
///						~ Map Section ~
///		Only create section when entering section. Saves space
///		Load and save AI Battle Status

int main()
{
	//Timer timer = Timer();
	//Renderer renderer = Renderer();
	//renderer.init(new Coordinate{ 0,0 }, &timer);
	//
	//AnimationStream animationStream = AnimationStream(&renderer, &timer);
	//
	//animationStream.setAnimation(Animation::LEGENDARY_POKEMON, true);
	//
	//while (!animationStream.animationReady()) {}
	//
	//while (animationStream.animationPlaying())
	//{
	//	animationStream.stream(true);
	//}
	//
	//animationStream.stopAnimation();

	srand(time(NULL));
	
	Game game;
	game.run();
	
	return 0;
}
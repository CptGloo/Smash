#include "catch.hpp"
#include "../../Smash/src/TextFile.h"
#include "../../Smash/src/Renderer.h"


TEST_CASE("Renderer setup with a TextFile", "[Renderer]")
{
	smash::Renderer renderer = smash::Renderer();
	smash::TextFile file = smash::TextFile("./res/test1.txt");
	renderer.setCurrentFile(&file);
	REQUIRE(renderer.getCurrentFile());
}

TEST_CASE("Renderer setup with the screen", "[Renderer]")
{
	smash::Renderer renderer = smash::Renderer();
	smash::Screen screen = smash::Screen(120, 40);
	renderer.setScreen(&screen);
	REQUIRE(renderer.getScreen());
}

//TEST_CASE("Renderer can create a ScreenRow from the active TextFile", "[Renderer]")
//{
//	smash::Renderer renderer = smash::Renderer();
//	smash::TextFile file = smash::TextFile("./res/test1.txt");
//	renderer.setCurrentFile(&file);
//	
//}
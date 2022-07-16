
#include "Ext.h"
#include "App.h"
#include "TextFile.h"
#include "Screen.h"


const int screenWidth = 120;			// Console Screen Size X (columns)
const int screenHeight = 40;			// Console Screen Size Y (rows)

int main(int argc, char** argv)
{
	smash::Screen screen = smash::Screen(screenWidth, screenHeight);
	smash::TextFile file;

	try
	{
		file = smash::TextFile("./res/example.txt");
	}
	catch (smash::TextFile::FileNotFound& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	};

	bool shouldQuit = false;
	float currentLine = 0.0f;

	while (!shouldQuit)
	{

		
		screen.clear();

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			currentLine += 0.05f;
		if (GetAsyncKeyState(VK_UP) & 0x8000)
			currentLine -= 0.05f;

		screen.display((int)currentLine, file);
		
		shouldQuit = GetAsyncKeyState(VK_LCONTROL) & 0x8000 && GetAsyncKeyState((unsigned short)'Q') & 0x8000;
	}

	return 0;
}





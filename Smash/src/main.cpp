
#include <iostream>
#include "App.h"
#include "TextFile.h"


const int screenWidth = 120;			// Console Screen Size X (columns)
const int screenHeight = 40;			// Console Screen Size Y (rows)

int main(int argc, char** argv)
{
	
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


	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;


	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD pos = { 3, 6 };
	//SetConsoleCursorPosition(hConsole, pos);
	//WriteConsole(hConsole, "Hello", 5, NULL, NULL);


	bool shouldQuit = false;

	while (!shouldQuit)
	{
		// clear screen
		for (int i = 0; i < screenWidth * screenHeight; i++)
		{
			screen[i] = '\0';
		}

		//if (GetAsyncKeyState((unsigned short)'A') & 0x8000)

		std::vector<std::string> screenRows;

		for (int i = 0; i < file.size(); i++)
		{
			std::string str;
			file.getLine(i, str);

			int tabCount = 0;
			for (int k = 0; k < str.size(); k++)
			{
				if (str[k] == '\t')
					tabCount++;
			}

			int rowNb = (str.size() + 3 * tabCount) / screenWidth;
			for (int n = 0; n < rowNb + 1; n++)
			{
				std::string temp;
				for (int j = 0; j < screenWidth; j++)
				{
					if (j >= str.size() - n * screenWidth)
					{
						break;
					}
					else
					{
						if (str[j + n * screenWidth] == '\t')
						{
							temp += "    ";
						}
						else
							temp += str[j + n * screenWidth];
					}
				}
				screenRows.push_back(std::string(temp));
			}
		}

		int n = min(screenRows.size(), screenHeight);

		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < screenRows[j].size(); i++)
			{
				screen[i + j * screenWidth] = screenRows[j][i];
			}
		}


		WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
		
		shouldQuit = GetAsyncKeyState(VK_LCONTROL) & 0x8000 && GetAsyncKeyState((unsigned short)'Q') & 0x8000;
	}



	return 0;



}





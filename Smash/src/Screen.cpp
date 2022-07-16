#include "Screen.h"
#include "TextFile.h"

namespace smash
{

	Screen::Screen(const int width, const int height)
		: screenWidth(width), screenHeight(height)
	{
		screen = new wchar_t[screenWidth * screenHeight];
		console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(console);
		bytesWritten = 0;

		for (int i = 0; i < screenWidth * screenHeight; i++)
		{
			screen[i] = '\0';
		}
	}

	Screen::~Screen()
	{
		delete screen;
	}
	void Screen::clear()
	{
		for (int i = 0; i < screenWidth * screenHeight; i++)
		{
			screen[i] = '\0';
		}
	}

	void Screen::display(int line, TextFile& file)
	{
		std::vector<std::string> screenRows;
		
		if (line < 0) line = 0;
		if (line >= file.size()) line = file.size() - 1;

		for (int i = line; i < file.size(); i++)
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


		WriteConsoleOutputCharacter(console, screen, screenWidth * screenHeight, { 0,0 }, &bytesWritten);
	}
}
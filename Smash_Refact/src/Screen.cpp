#include "Screen.h"
#include "TextFile.h"

namespace smash
{

	Screen::Screen(const int _width, const int _height)
		: width(_width), height(_height)
	{
		screen = new wchar_t[width * height];
		console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(console);
		bytesWritten = 0;

		for (int i = 0; i < width * height; i++)
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
		for (int i = 0; i < width * height; i++)
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

			int rowNb = (str.size() + 3 * tabCount) / width;
			for (int n = 0; n < rowNb + 1; n++)
			{
				std::string temp;
				for (int j = 0; j < width; j++)
				{
					if (j >= str.size() - n * width)
					{
						break;
					}
					else
					{
						if (str[j + n * width] == '\t')
						{
							temp += "    ";
						}
						else
							temp += str[j + n * width];
					}
				}
				screenRows.push_back(std::string(temp));
			}
		}

		int n = min(screenRows.size(), height);

		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < screenRows[j].size(); i++)
			{
				screen[i + j * width] = screenRows[j][i];
			}
		}


		WriteConsoleOutputCharacter(console, screen, width * height, { 0,0 }, &bytesWritten);
	}
}
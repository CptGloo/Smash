#include "Screen.h"

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
}
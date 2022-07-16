#ifndef SCREEN_H
#define SCREEN_H

#include "Ext.h"


namespace smash
{
	class Screen
	{
	private:
		const int screenWidth;
		const int screenHeight;
		wchar_t* screen;
		HANDLE console;
		DWORD bytesWritten;

	public:
		Screen(const int width, const int height);
		~Screen();
		void clear();
		void display(int line, class TextFile& file);
	};
}

#endif


// Some Code about cursor :
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//COORD pos = { 3, 6 };
//SetConsoleCursorPosition(hConsole, pos);
//WriteConsole(hConsole, "Hello", 5, NULL, NULL);


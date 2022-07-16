#ifndef SCREEN_H
#define SCREEN_H

#include "Ext.h"

namespace smash
{
	class Screen
	{
	private:
		const int width;
		const int height;
		wchar_t* screen;
		HANDLE console;
		DWORD bytesWritten;

	public:
		Screen(const int width, const int height);
		~Screen();
		int width() { return width; }
		int height() { return height; }
	};
}

#endif
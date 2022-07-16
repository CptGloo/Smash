#ifndef RENDERER_H
#define RENDERER_H

#include "Ext.h"
#include "Screen.h"
#include "ScreenRow.h"
#include "TextFile.h"

namespace smash
{
	class Renderer
	{
	private:
		Screen* screen;
		TextFile* currentFile;
		std::vector<ScreenRow> rows;

	public:
		Renderer();
		void setCurrentFile(TextFile* _file) { currentFile = _file; }
		TextFile* getCurrentFile() { return currentFile; }
		void setScreen(Screen* _screen) { screen = _screen; }
		Screen* getScreen() { return screen; }
	};
}




#endif

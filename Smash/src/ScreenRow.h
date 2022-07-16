#ifndef SCREEN_ROW_H
#define SCREEN_ROW_H

#include "Ext.h"

namespace smash
{
	class ScreenRow
	{
	private:
		int lineIndex;
		int rowIndex;
		std::string str;

	public:
		ScreenRow(int _lineIndex, int _rowIndex, std::string _str);
		int getLineIndex() { return lineIndex; }
		int getRowIndex() { return rowIndex; }
		void getStr(std::string& _str) { _str = str; }

	};
}

#endif

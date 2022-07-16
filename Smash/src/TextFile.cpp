#include "TextFile.h"

namespace smash
{
	TextFile::TextFile()
		: path("")
	{}

	TextFile::TextFile(const char* _path)
		: path (_path)
	{
		std::ifstream s;
		s.open(path.c_str());
		if (s)
		{
			std::string str;
			while (getline(s, str))
			{
				content.push_back(str);
			}
			s.close();
		}
		else throw FileNotFound(path);
	}

	TextFile::~TextFile()
	{}

	TextFile::TextFile(const TextFile& _file)
	{
		path = _file.path;
		content = _file.content;
	}

	void TextFile::save()
	{
		std::ofstream s;
		s.open(path.c_str());
		if (s)
		{
			for (int i = 0; i < content.size(); i++)
			{
				s << content[i] << "\n";
			}
			s.close();
		}
		else throw FileNotFound(path);
	}

	void TextFile::getLine(int i, std::string& str)
	{
		if (i < 0 || i >= content.size())
			throw IndexOutOfBound();
		else
		{
			str = content[i];
		}
	}

	void TextFile::replace(int i, std::string& str)
	{
		if (i < 0 || i >= content.size())
			throw IndexOutOfBound();
		else
		{
			content[i] = str;
		}
	}

	void TextFile::replace(int i, const char* c)
	{
		if (i < 0 || i >= content.size())
			throw IndexOutOfBound();
		else
		{
			content[i] = c;
		}
	}

	void TextFile::insert(int i, std::string& str)
	{
		if (i < 0 || i > content.size())
			throw IndexOutOfBound();
		else
		{
			std::vector<std::string>::iterator it;
			it = content.begin() + i;
			it = content.insert(it, std::string(str));
		}
	}

	void TextFile::insert(int i, const char* c)
	{
		if (i < 0 || i > content.size())
			throw IndexOutOfBound();
		else
		{
			std::vector<std::string>::iterator it;
			it = content.begin() + i;
			it = content.insert(it, std::string(c));
		}
	}

}
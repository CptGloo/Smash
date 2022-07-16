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

	int TextFile::size()
	{
		return content.size();
	}

	void TextFile::getLine(int i, std::string& str)
	{
		if (i < 0 || i >= content.size())
		{
			throw IndexOutOfBound();
		}
		else
		{
			str = content[i];
		}
	}
	void TextFile::edit(int i, const char* c)
	{
		if (i < 0 || i >= content.size())
		{
			throw IndexOutOfBound();
		}
		else
		{
			content[i] = c;
		}
	}
	void TextFile::edit(int i, std::string& str)
	{
		if (i < 0 || i >= content.size())
		{
			throw IndexOutOfBound();
		}
		else
		{
			content[i] = str;
		}
	}

	void TextFile::insert(int i, const char* c)
	{
		if (i < 0 || i > content.size())
		{
			throw IndexOutOfBound();
		}
		else
		{
			auto it = content.begin();
			content.insert(it, std::string(c));
		}
	}

	void TextFile::insert(int i, std::string& str)
	{
		if (i < 0 || i > content.size())
		{
			throw IndexOutOfBound();
		}
		else
		{
			auto it = content.begin();
			content.insert(it, std::string(str));
		}
	}
	void TextFile::erase(int i)
	{
		if (i < 0 || i >= content.size())
		{
			throw IndexOutOfBound();
		}
		else
		{
			auto it = content.begin();
			content.erase(it + i);
		}
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
}
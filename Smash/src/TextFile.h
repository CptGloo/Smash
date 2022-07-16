#ifndef TEXT_FILE_H
#define TEXT_FILE_H


#include "Ext.h"

namespace smash
{
	class TextFile
	{

	private:
		std::string path;
		std::vector<std::string> content;

	public:
		TextFile();
		TextFile(const char* _path);
		~TextFile();
		TextFile(const TextFile& _file);
		int size();
		void getLine(int i, std::string& str);
		void edit(int i, const char* c);
		void edit(int i, std::string& str);
		void insert(int i, const char* c);
		void insert(int i, std::string& str);
		void erase(int i);
		void save();

		class FileNotFound : public std::exception
		{
			std::string m_msg;
		public:

			FileNotFound(const std::string& path)
				: m_msg(std::string("File not found at ") + path + "\n")
			{}

			virtual const char* what() const throw()
			{
				return m_msg.c_str();
			}
		};

		class IndexOutOfBound : public std::exception
		{
		public:

			IndexOutOfBound()
			{}

			virtual const char* what() const throw()
			{
				return "Index passed was out of bound";
			}
		};
	};
}

#endif 


// EXAMPLE CODE
/*

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


	std::string str;
	for (int i = 0; i < file.size(); i++)
	{
		file.getLine(i, str);
		std::cout << str << std::endl;
	}

	std::cout << file.size() << std::endl;
	std::cout << std::endl << "Saving file" << std::endl << std::endl;

	file.insert(file.size(), "");

	try
	{
		file.save();
	}
	catch (smash::TextFile::FileNotFound& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	};

	smash::TextFile file2;

	try
	{
		file2 = smash::TextFile("./res/example.txt");
	}
	catch (smash::TextFile::FileNotFound& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	};

	for (int i = 0; i < file2.size(); i++)
	{
		file2.getLine(i, str);
		std::cout << str << std::endl;
	}

*/

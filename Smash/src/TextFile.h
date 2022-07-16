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

		void save();
		int size() { return content.size(); }
		
		// returns the array of character at a specific line	
		void getLine(int i, std::string& str);

		// replace a line in the content vector where i is the index	
		void replace(int i, std::string& str);
		void replace(int i, const char* c);

		// insert a line. the index can go from 0 to size().
		// if i = size() then the line is added at the end of the file.
		// if i = 0, the line is added at the top of the file.
		void insert(int i, std::string& str);
		void insert(int i, const char* c);

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
				return "Index is out of bound...";
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

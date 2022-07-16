#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../../Smash/src/TextFile.h"



TEST_CASE("TextFile FileNotFound exception throws if file is missing", "[TextFile]") 
{
    smash::TextFile file;
    REQUIRE_NOTHROW(file = smash::TextFile("./res/test1.txt"));
    smash::TextFile file2;
    REQUIRE_THROWS_AS(file2 = smash::TextFile("./res/tata.txt"), smash::TextFile::FileNotFound);
}

TEST_CASE("size() returns the number of lines in the file")
{
    smash::TextFile file = smash::TextFile("./res/test1.txt");
    REQUIRE(file.size() == 1);
    smash::TextFile file2 = smash::TextFile("./res/test2.txt");
    REQUIRE(file2.size() == 3);
}

TEST_CASE("TextFile getLine() gives access to the lines of the file", "[TextFile]")
{
    smash::TextFile file = smash::TextFile("./res/test1.txt");
    std::string str = "tititoto";
    std::string str2;
    file.getLine(0, str2);
    REQUIRE(str == str2);
}

TEST_CASE("Throws exception if index passed to getLine() is out of bound", "[TextFile]")
{
    smash::TextFile file = smash::TextFile("./res/test1.txt");
    std::string str;
    REQUIRE_THROWS_AS(file.getLine(-2, str), smash::TextFile::IndexOutOfBound);
    REQUIRE_NOTHROW(file.getLine(0, str));
    REQUIRE_THROWS_AS(file.getLine(1, str), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.getLine(100, str), smash::TextFile::IndexOutOfBound);
}

TEST_CASE("TextFile Can edit() a line", "[TextFile]")
{
    smash::TextFile file = smash::TextFile("./res/test2.txt");
    std::string str = "Bonjour";
    std::string str2 ;
    file.getLine(0, str2);
    REQUIRE(str == str2);

    std::string str3 = "Salut";
    file.edit(0, "Salut");
    file.getLine(0, str2);
    REQUIRE(str2 == str3);
}

TEST_CASE("TextFile throws exception if index passed in edit() is out of bound", "[TextFile]")
{
    smash::TextFile file = smash::TextFile("./res/test2.txt");
    REQUIRE_THROWS_AS(file.edit(-2, "Salut"), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.edit(100, "Salut"), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.edit(3, "Salut"), smash::TextFile::IndexOutOfBound);
    std::string str = "Salut";
    REQUIRE_THROWS_AS(file.edit(-2, str), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.edit(100, str), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.edit(3, str), smash::TextFile::IndexOutOfBound);
}

TEST_CASE("TextFile can insert() a new line in the file")
{
    smash::TextFile file = smash::TextFile("./res/test2.txt");
    std::string str = "Salut";
    int n = file.size();
    file.insert(0, "Salut");
    std::string str2;
    file.getLine(0, str2);
    REQUIRE(str == str2);
    REQUIRE(file.size() == n + 1);

    smash::TextFile file2 = smash::TextFile("./res/test2.txt");
    std::string str3 = "Salut";
    n = file2.size();
    file2.insert(0, str);
    REQUIRE(file.size() == n + 1);
    str2 = "";
    file2.getLine(0, str2);
    REQUIRE(str3 == str2);
}

TEST_CASE("TextFile throws exception if index passed in insert() is out of bound", "[TextFile]")
{
    smash::TextFile file = smash::TextFile("./res/test2.txt");
    REQUIRE_THROWS_AS(file.insert(-2, "Salut"), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.insert(100, "Salut"), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.insert(4, "Salut"), smash::TextFile::IndexOutOfBound);
    REQUIRE_NOTHROW(file.insert(3, "Salut"));

    smash::TextFile file2 = smash::TextFile("./res/test2.txt");
    std::string str = "Salut";
    REQUIRE_THROWS_AS(file2.insert(-2, str), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file2.insert(100, str), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file2.insert(4, str), smash::TextFile::IndexOutOfBound);
    REQUIRE_NOTHROW(file2.insert(3, str));
}

TEST_CASE("TextFile can erase() a line", "[TextFile]")
{
    smash::TextFile file = smash::TextFile("./res/test3.txt");
    std::string str;
    std::string str2;
    file.getLine(1, str2);
    file.erase(0);
    file.getLine(0, str);
    REQUIRE(str == str2);
    REQUIRE(file.size() == 2);
}

TEST_CASE("TextFile should throw when index passed to erase() is out of bound", "[TextFile]")
{
    smash::TextFile file = smash::TextFile("./res/test2.txt");
    REQUIRE_THROWS_AS(file.erase(-2), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.erase(100), smash::TextFile::IndexOutOfBound);
    REQUIRE_THROWS_AS(file.erase(3), smash::TextFile::IndexOutOfBound);
}

TEST_CASE("TextFile can save() the file on the drive", "[TextFile]")
{
    smash::TextFile file = smash::TextFile("./res/test3.txt");
    std::string str;
    std::string str2;
    int n = file.size();
    file.getLine(0, str);
    file.getLine(1, str2);
    file.erase(0);
    file.save();

    smash::TextFile file2 = smash::TextFile("./res/test3.txt");
    int n2 = file2.size();
    REQUIRE(n2 == n - 1);
    std::string str3;
    file2.getLine(0, str3);
    REQUIRE(str2 == str3);
    file2.insert(0, str);
    file2.save();

    smash::TextFile file3 = smash::TextFile("./res/test3.txt");
    int n3 = file3.size();
    REQUIRE(n3 == n2 + 1);
    std::string str4;
    std::string str5;
    file3.getLine(0, str4);
    REQUIRE(str4 == str);
    file3.getLine(1, str5);
    REQUIRE(str2 == str5);
}


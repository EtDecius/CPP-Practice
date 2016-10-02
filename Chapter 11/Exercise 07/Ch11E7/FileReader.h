// FileReader.h
// A very basic class to open a file, read from it then close.

#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>
#include <stdexcept>

class FileReader
{
public:
	FileReader(std::string filename);


private:
	std::ifstream fin;
	std::string filename;

};






#endif

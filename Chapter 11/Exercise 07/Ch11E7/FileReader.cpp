// FileReader.cpp
// Implements FileReader class


#include "FileReader.h"

FileReader::FileReader(std::string filename)
	: filename{ filename }
{
	fin.open(filename);
	if (!fin) throw std::runtime_error("FileReader() failed to open file " + filename);
}
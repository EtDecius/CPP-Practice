// Contraction_separator.h
// Class to convert English contractions into separate words
// Ex: can't -> cannot, don't -> do not
// Imports list of contractions from a file. File name must be supplied
// to contructor.
// Note: All characters converted into lowercase. Uppercase not preserved.

#ifndef CONTRACTION_SEPARATOR_H
#define CONTRACTION_SEPARATOR_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>

class Contraction_separator
{
public:
	Contraction_separator(const std::string filename); 
	std::string get_separated (const std::string input);
	bool is_contraction(const std::string input);

private:
	struct Contraction_pair
	{
		std::string contraction;
		std::string expanded;
	};
	void import_contraction_list(std::ifstream& fin);
	std::vector<Contraction_pair> lookup;
	std::string lowercase(const std::string& s);
};
#endif
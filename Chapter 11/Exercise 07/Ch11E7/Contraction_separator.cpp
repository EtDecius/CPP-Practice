// Contraction_separator.cpp
// Implementation of the Contraction_separator class

#include "Contraction_separator.h"

// public methods

Contraction_separator::Contraction_separator(const std::string filename)
{
	std::ifstream fin{ filename };
	if (!fin) throw std::runtime_error("Contraction_separator() failed to open file " + filename);
	import_contraction_list(fin);
}

// returns true if supplied string matches known contraction
bool Contraction_separator::is_contraction(const std::string input)
{
	std::string lc_input = lowercase(input);
	for (Contraction_pair& cp : lookup)
		if (cp.contraction == lc_input)
			return true;
	return false;
}

// returns two-word expanded form of supplied word
// if not contraction, return word unchanged
std::string Contraction_separator::get_separated(const std::string input)
{
	std::string lc_input = lowercase(input);
	for (Contraction_pair& cp : lookup)
		if (cp.contraction == lc_input)
			return cp.expanded;
	return input;  // no match found, return original
}

// private methods

// reads data from ifstream, converts to a Contraction_pair and stores it in vector
void Contraction_separator::import_contraction_list(std::ifstream& fin)
{
	std::string contract;
	std::string expand1, expand2;

	while (fin >> contract >> expand1 >> expand2)
	{
		Contraction_pair cp;
		cp.contraction = contract;
		cp.expanded = expand1 + " " + expand2;
		std::transform(cp.contraction.begin(), cp.contraction.end(), cp.contraction.begin(), ::tolower);
		lookup.push_back(cp);
	}
	if (fin.eof()) return;
	if (fin.bad()) throw std::runtime_error("import_contraction_list() bad file stream");
	if (fin.fail()) throw std::runtime_error("import_contraction_list() failed to import file");
}

// convert string to lowercase
std::string Contraction_separator::lowercase(const std::string& s)
{
	std::string copy = s;
	transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
	return copy;
}


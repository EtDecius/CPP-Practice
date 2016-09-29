// Roman_digit.cpp
// Implements Roman_digit class

#include "Roman_digit.h"

namespace Digit {


const vector<Roman_digit>& initialize_table()
{
	// lookup table to convert integer to Roman numeral and vice versa
	static const vector<Roman_digit>Roman_conversion_tbl = {
		Roman_digit("I", 1), Roman_digit("IV", 4),
		Roman_digit("V", 5), Roman_digit("IX", 9),
		Roman_digit("X", 10), Roman_digit("XL", 40),
		Roman_digit("L", 50), Roman_digit("XC", 90),
		Roman_digit("C", 100), Roman_digit("CD", 400),
		Roman_digit("D", 500), Roman_digit("CM", 900),
		Roman_digit("M", 1000)
	};
	return Roman_conversion_tbl;
}

// lookup Roman numeral, convert to integer
int symbol_to_value(std::string s)
{
	vector<Roman_digit>Roman_conversion_tbl = initialize_table();
	
	transform(s.begin(), s.end(), s.begin(), ::toupper);	// ensure uppcase
	for (Roman_digit rd : Roman_conversion_tbl)
		if (rd.symbol == s)
			return rd.value;
	error("symbol_to_value() invalid symbol ", s);
}

// convert char to std::string, then pass to std::string implementation
int symbol_to_value(char c)
{
//	cout << "called symbol_to_value(char)" << endl;
	string s = to_string(c);
	return symbol_to_value(s);

}

// lookup integer, convert to Roman numeral
std::string value_to_symbol(int n)
{

	vector<Roman_digit>Roman_conversion_tbl = initialize_table();
	for (Roman_digit rd : Roman_conversion_tbl)
		if (rd.value == n)
			return rd.symbol;
	error("value_to_symbol() no symbol found for value ", n);
}

// returns integer value of closest Roman numeral without going over
int nearest(int n)
{
	vector<Roman_digit>Roman_conversion_tbl = initialize_table();
	int near = Roman_conversion_tbl[Roman_conversion_tbl.size() - 1].value;	// default largest
	for (int i = 0; i < Roman_conversion_tbl.size(); ++i)	// check against all valid symbols 
		if (n >= Roman_conversion_tbl[i].value)				// found largest without going over
			near = Roman_conversion_tbl[i].value;
	return near;
}

} // end of namespace
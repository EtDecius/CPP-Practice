// Roman_digit.h
// Header file for Roman_digit class
// Roman_digit represents the symbol and value pair for a single Roman numeral
// ex: 10, "X"

#ifndef ROMAN_DIGIT_H
#define ROMAN_DIGIT_H

#include "../../../std_lib_facilities.h"

namespace Digit
{

// Roman numeral symbol, value pair
struct Roman_digit {
public:
	Roman_digit(std::string s, int v) : symbol{ s }, value{ v } {};
	std::string symbol;
	int value;

};

int symbol_to_value(std::string s);
int symbol_to_value(char c);
std::string value_to_symbol(int n);
int nearest(int n);

const vector<Roman_digit>& initialize_table();

} // end namespace

#endif
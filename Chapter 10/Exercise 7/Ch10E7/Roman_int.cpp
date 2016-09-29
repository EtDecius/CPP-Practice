// Roman_int.cpp
// Roman_int class implementation

#include "../../../std_lib_facilities.h"
#include "Roman_int.h"

// ------------------------------------------------------------------

// forward declaration for helper functions
std::string int_to_roman(int n);
int roman_to_int(std::string roman_number);
bool valid_roman_numeral(const std::string& s);

// default constructor
Roman_int::Roman_int()
{
	value = 1;
	numeral = int_to_roman(value);
}


// constructor
Roman_int::Roman_int(int n)
	: value{ n }
{
	if (value <= 0) error("Roman_int() invalid value ", value);
	numeral = int_to_roman(value);
}

// constructor
Roman_int::Roman_int(std::string s)
	: numeral{ s }
{
	transform(numeral.begin(), numeral.end(), numeral.begin(), ::toupper);	// ensure uppercase
	if (!valid_roman_numeral(numeral)) error("Roman_int() invalid Roman numeral ", numeral);
	value = roman_to_int(numeral);
}

Roman_int& Roman_int::operator=(const Roman_int& ri)
{
	if (this == &ri)
		return *this;
	
	value = ri.integer();
	numeral = ri.roman();
	return *this;
}

Roman_int& Roman_int::operator+=(const Roman_int& ri)
{
	value += ri.integer();
	numeral = int_to_roman(value);
	return *this;
}

Roman_int& Roman_int::operator-=(const Roman_int& ri)
{
	if (value - ri.integer() <= 0) 
		error("cannot subtract by a larger value " + numeral + " - " + ri.roman());
	value -= ri.integer();
	numeral = int_to_roman(value);
	return *this;
}

Roman_int& Roman_int::operator*=(const Roman_int& ri)
{
	value *= ri.integer();
	numeral = int_to_roman(value);
	return *this;
}

Roman_int& Roman_int::operator/=(const Roman_int& ri)
{
	if (value / ri.integer() <= 0)
		error("cannot divide by a larger value " + numeral + " / " + ri.roman());
	value /= ri.integer();
	numeral = int_to_roman(value);
	return *this;
}


ostream& operator<<(ostream& os, const Roman_int& ri)
{
	return os << ri.roman();
}

istream& operator >> (istream& is, Roman_int& ri)
{
	std::string input;
	if (!(is >> input)) return is;

	ri = Roman_int{ input };
	return is;
}


Roman_int operator+(const Roman_int& ri1, const Roman_int& ri2)
{
	return Roman_int{ ri1.integer() + ri2.integer() };
}

Roman_int operator-(const Roman_int& ri1, const Roman_int& ri2)
{
	int difference = ri1.integer() - ri2.integer();
	if (difference <= 0) error("cannot subtract by a larger value " + ri1.roman() + " - " + ri2.roman());
	return Roman_int{ difference };
}

Roman_int operator*(const Roman_int& ri1, const Roman_int& ri2)
{
	return Roman_int{ ri1.integer() & ri2.integer() };
}

Roman_int operator/(const Roman_int& ri1, const Roman_int& ri2)
{
	int quotient = ri1.integer() / ri2.integer();
	if (quotient <= 0) error("cannot divide by a larger value " + ri1.roman() + " / " + ri2.roman());
	return Roman_int{ quotient };
}

// ------------------------------------------------------------------
// Roman_int helper functions

// convert integer n into equivalent std::string of Roman numeral characters
std::string int_to_roman(int n)
{
	std::string roman_number;
	int to_process = n;			// initially full amount
	int near = 0;				// closest Roman numeral value without going over

	while (to_process > 0)
	{
		near = Digit::nearest(to_process);				// determine closest fit
		roman_number += Digit::value_to_symbol(near);	// append std::string that matches near value
		to_process -= near;						// subtract near from to_process
	}
	return roman_number;
}

bool is_subtractive_symbol(std::string s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	if (s == "I" || s == "X" || s == "C")
		return true;
	return false;
}

// maximum number of times symbol can appear sequentially (ex: III = 3, V = 1)
int max_chain(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	if (s == "I" || s == "X" || s == "C")
		return 3;
	if (s == "M")
		return (INT_MAX / 1000); // arbitrarily large number
	return 1;
}

int max_chain(char c)
{
	string s = to_string(c);
	return max_chain(s);
}

// verify Roman numerals listed largest to smallest (except subtractive symbols)
bool bad_order(const std::string& s)
{
	if (s.size() == 1) return false;	// not applicable for single element

	int prev_symb_val = 0;
	int curr_symb_val = 0;

	for (int i = 1; i < s.size(); ++i)
	{
		prev_symb_val = Digit::symbol_to_value(s[i - 1]);
		curr_symb_val = Digit::symbol_to_value(s[i]);

		if (curr_symb_val > prev_symb_val)
		{
			string prev_symb = to_string(s[i - 1]);		// convert to std::string for easy comparison
			if (!(is_subtractive_symbol(prev_symb)))	// not subractive, confirmed out of order
				return true;
			else									// handle subtractive symbols
			{
				string combined = to_string(s[i - 1]) + to_string(s[i]);  // combine subtractive
				if (i < 2 && s.size() >= 3)			// front of list, compare to following symbol
					if (Digit::symbol_to_value(combined) < Digit::symbol_to_value(s[i + 1]))
						return true;
				if (i >= 2)							// not front of list, compare prior symbols
					if (Digit::symbol_to_value(combined) > Digit::symbol_to_value(s[i - 2])) // 
						return true;
			}
		}
	}
	return false;
}

// handle case where subtractive symbol appears bfore and after middle symbol, and is lower value
// ex: 10 should be written as X, not IXI (9 + 1)
bool subtractive_negation(const string& s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		// only applies to symbols that can combine subtractively, stay in bounds
		if (is_subtractive_symbol(to_string(s[i])) && (i + 2) < s.size())
		{
			// numeral invalid if middle symbol greater value than matching outer symbols
			if (s[i] == s[i + 2] && Digit::symbol_to_value(s[i]) < Digit::symbol_to_value(s[i + 1]))
				return true;
		}
	}

	return false;
}

// detect characters repeated too many times
bool duplicate_symbols(const std::string& s)
{
	if (s.size() == 1) return false;	// not applicible for single element

	int seen = 1;
	char prev_char = s[0];
	for (int i = 1; i < s.size(); ++i)
	{
		prev_char = s[i - 1];
		if (s[i] == prev_char)
			++seen;
		else
			seen = 1;
		if (seen > max_chain(s[i]))
			return true;
	}
	return false;
}

// ensure Roman numeral adheres to formatting rules
// 1) symbol not sequenced more times than appropriate (I X C = 3, V L D = 1)
// 2) symbols listed in descending order, except for subtractions (ex: IX)
// 3) subtractions don't negate themselves (ex: IXI)
bool valid_roman_numeral(const std::string& s)
{
	if (s.size() == 0) cout << "vnr: size 0" << endl;	// temp code
	if (s.size() == 0) return false;

	if (duplicate_symbols(s)) cout << "dup_symb is true\n";
	if (bad_order(s)) cout << "bad_order is true\n";
	if (subtractive_negation(s)) cout << "sub_neg is true\n";

	


	if (duplicate_symbols(s) || bad_order(s) || subtractive_negation(s))
		return false;
	return true;
}

// convert Roman numeral std::string to integer value
// NOTE: does not verify valid Roman numeral format
// if used outside Roman_int constructor, call valid_roman_numeral() on std::string first to validate
int roman_to_int(std::string roman_number)
{
	
	if (roman_number.size() == 0) error("roman_to_int() no Roman numeral provided");
	
	int running_value = 0;
	string curr_symb;
	int curr_symb_val = 0;

	for (int i = 0; i < roman_number.size(); ++i)	// iterate through std::string
	{
		// for some reason, this isn't converting to a string
		curr_symb = to_string(roman_number[i]);		// convert to std::string for easier comparison
		
													// handle potential subtractive characters (ex: IX = X - I)
		if (is_subtractive_symbol(curr_symb) && i < roman_number.size() - 1)
		{
			// subractive if curr value < next value
			if (Digit::symbol_to_value(curr_symb) < Digit::symbol_to_value(roman_number[i + 1]))
			{
				curr_symb += roman_number[i + 1];	// combine symbols
				++i;								// two symbols were processed
			}
		}
		curr_symb_val = Digit::symbol_to_value(curr_symb); // value from lookup
		running_value += curr_symb_val;
	}
	return running_value;
}
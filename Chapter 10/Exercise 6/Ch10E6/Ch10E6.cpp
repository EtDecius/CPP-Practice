// Ch10E6.cpp
// Chapter 10, Exercise 6 (p.377)
// Write Roman_int class for holding Roman numerals.
// Provide << and >> functions, and functions to convert to/from an int.

#include "../../../std_lib_facilities.h"

// ------------------------------------------------------------------
// struct: Roman_digit
// Contains Roman numeral (as string) and it's integer value
// Valid digits stored in Roman_conversion_tbl data structure
// Note: "Subtractive" prefix numerals treated as single Roman_digit to simplify evaluation
//   Ex: IX = 10 - 1 = 9
// Use functions:
//	 symbol_to_value(string or char): convert Roman numeral -> int
//   value_to_symbol(int): convert int -> Roman numeral
//   nearest(int): greatest Roman numeral without going over

// Roman numeral symbol, value pair
struct Roman_digit {
public:
	Roman_digit(string s, int v) : symbol{ s }, value{ v } {};
	string symbol;
	int value;
};

// lookup table to convert integer to Roman numeral and vice versa
const vector<Roman_digit> Roman_conversion_tbl = {
	Roman_digit("I", 1), Roman_digit("IV", 4),
	Roman_digit("V", 5), Roman_digit("IX", 9),
	Roman_digit("X", 10), Roman_digit("XL", 40),
	Roman_digit("L", 50), Roman_digit("XC", 90),
	Roman_digit("C", 100), Roman_digit("CD", 400),
	Roman_digit("D", 500), Roman_digit("CM", 900),
	Roman_digit("M", 1000)
};

// lookup Roman numeral, convert to integer
int symbol_to_value(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);	// ensure uppcase
	for (Roman_digit rd : Roman_conversion_tbl)
		if (rd.symbol == s)
			return rd.value;
	error("symbol_to_value() invalid symbol ", s);
}

// convert char to string, then pass to string implementation
int symbol_to_value(char c)
{
	string s = to_string(c);
	return symbol_to_value(s);
}

// lookup integer, convert to Roman numeral
string value_to_symbol(int n)
{
	for (Roman_digit rd : Roman_conversion_tbl)
		if (rd.value == n)
			return rd.symbol;
	error("value_to_symbol() no symbol found for value ", n);
}

// returns integer value of closest Roman numeral without going over
int nearest(int n)
{
	int near = Roman_conversion_tbl[Roman_conversion_tbl.size() - 1].value;	// default largest
	for (int i = 0; i < Roman_conversion_tbl.size(); ++i)	// check against all valid symbols 
		if (n >= Roman_conversion_tbl[i].value)				// found largest without going over
			near = Roman_conversion_tbl[i].value;			
	return near;
}



// ------------------------------------------------------------------

// forward declaration for helper functions
string int_to_roman(int n);
int roman_to_int(string roman_number);
bool valid_roman_numeral(const string& s);

class Roman_int
{
public:
	Roman_int(int n);					// constructor given int
	Roman_int(string s);				// constructor given Roman numeral
	string roman() const { return numeral; }	// return value as Roman numeral
	int integer() const {	return value; }		// return value as integer

private:
	int value;
	string numeral;

};

// constructor
Roman_int::Roman_int(int n)
	: value{ n }
{
	if (value <= 0) error("Roman_int() invalid value ", value);
	numeral = int_to_roman(value);
}

// constructor
Roman_int::Roman_int(string s)
	: numeral{ s }
{
	transform(numeral.begin(), numeral.end(), numeral.begin(), ::toupper);	// ensure uppercase
	if (!valid_roman_numeral(numeral)) error("Roman_int() invalid Roman numeral ", numeral);
//	if (unified_valid_numeral_check(numeral)) error("Roman_int() invalid Roman numeral ", numeral);

	value = roman_to_int(numeral);
}

ostream& operator<<(ostream& os, const Roman_int& ri)
{
	return os << ri.roman();
}

istream& operator >> (istream& is, Roman_int& ri)
{
	string input;
	if (!(is >> input)) return is;

	ri = Roman_int{ input };
	return is;
}


// ------------------------------------------------------------------
// Roman_int helper functions

// convert integer n into equivalent string of Roman numeral characters
string int_to_roman(int n)
{
	string roman_number;	
	int to_process = n;			// initially full amount
	int near = 0;				// closest Roman numeral value without going over

	while (to_process > 0)
	{
		near = nearest(to_process);				// determine closest fit
		roman_number += value_to_symbol(near);	// append string that matches near value
		to_process -= near;						// subtract near from to_process
	}
	return roman_number;
}

bool is_subtractive_symbol(string s)
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
bool bad_order(const string& s)
{
	if (s.size() == 1) return false;	// not applicable for single element

	int prev_symb_val = 0;
	int curr_symb_val = 0;

	for (int i = 1; i < s.size(); ++i)
	{
		prev_symb_val = symbol_to_value(s[i - 1]);
		curr_symb_val = symbol_to_value(s[i]);

		if (curr_symb_val > prev_symb_val)
		{
			string prev_symb = to_string(s[i - 1]);		// convert to string for easy comparison
			if (!(is_subtractive_symbol(prev_symb)))	// not subractive, confirmed out of order
				return true;
			else									// handle subtractive symbols
			{
				string combined = to_string(s[i - 1]) + to_string(s[i]);  // combine subtractive
				if (i < 2 && s.size() >= 3)			// front of list, compare to following symbol
					if (symbol_to_value(combined) < symbol_to_value(s[i + 1]))
						return true;
				if (i >= 2)							// not front of list, compare prior symbols
					if (symbol_to_value(combined) > symbol_to_value(s[i - 2])) // 
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
			if (s[i] == s[i + 2] && symbol_to_value(s[i]) < symbol_to_value(s[i + 1])) 
				return true;
		}
	}
	return false;
}

// detect characters repeated too many times
bool duplicate_symbols(const string& s)
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
bool valid_roman_numeral(const string& s)
{
	if (s.size() == 0) return false;
	if (duplicate_symbols(s) || bad_order(s) || subtractive_negation(s))
		return false;
	return true;
}

// convert Roman numeral string to integer value
// NOTE: does not verify valid Roman numeral format
// if used outside Roman_int constructor, call valid_roman_numeral() on string first to validate
int roman_to_int(string roman_number)
{
	if (roman_number.size() == 0) error("roman_to_int() no Roman numeral provided");

	int running_value = 0;
	string curr_symb;
	int curr_symb_val = 0;

	for (int i = 0; i < roman_number.size(); ++i)	// iterate through string
	{
		curr_symb = to_string(roman_number[i]);		// convert to string for easier comparison

		// handle potential subtractive characters (ex: IX = X - I)
		if (is_subtractive_symbol(curr_symb) && i < roman_number.size() - 1)
		{
			// subractive if curr value < next value
			if (symbol_to_value(curr_symb) < symbol_to_value(roman_number[i + 1]))
			{
				curr_symb += roman_number[i + 1];	// combine symbols
				++i;								// two symbols were processed
			}
		}
		curr_symb_val = symbol_to_value(curr_symb); // value from lookup
		running_value += curr_symb_val;
	}
	return running_value;
}

int main()
try {
	
	cout << "Enter a roman numeral: ";
	string input;
	cin >> input;

	Roman_int test = { input };
	
	cout << "You entered " << test.roman() << ", which equals " << test.integer() << endl;



	return 0;
}
catch (runtime_error& e)
{
	cerr << "error: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}
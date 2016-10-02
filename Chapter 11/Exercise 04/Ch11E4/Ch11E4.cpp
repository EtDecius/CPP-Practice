// Ch11E4.cpp
// Chapter 11 , Exercise 4 (p.408)
// Write a program that prompts the user to enter several integers in any
// combination of octal, decimal or hexadecimal, using the 0 and 0x
// base suffixes; interprets the numbers correctly; and converts them
// to decimal form. Then your program should output the values in properly
// spaced columns.
//
// Notes:
//   - Does not handle negative numbers in any base. Don't use them!
//   - Does not handle overflow.
//   - Does not convert values. Uses iostream to display according to base.

#include "../../../std_lib_facilities.h"
#include <iomanip>

enum class base {
	oct, dec, hex
};

// stores a value and its number base
struct Int_base
{
	long value;
	base base_type; // oct, dec or hex
};

// returns true if every char in string is an acceptable
// value for its format or an identifier (ex: 0x for hex)
bool valid_number(const string& s, base b)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (b == base::oct)
		{
			if (s[i] < '0' || s[i] > '7')	// oct: [0,7]
				return false;
		}
		else if (b == base::dec)			// dec: [0, 9]
		{
			if (!isdigit(s[i]))
				return false;
		}
		else if (b == base::hex)			// hex: [0,f], X or x
		{
			if (!isxdigit(s[i]) && !(s[i] == 'x' || s[i] == 'X'))
				return false;
		}
	}
	return true;
}

// convert user input string to a valid dec/hex/oct integer
// Populate and return Int_base if string valid, else throws error
Int_base convert_to_int_base(const string& s)
{
	if (s.size() == 0) error("convert_to_int_base() cannot convert empty string");

	istringstream iss{ s };  // convert to stringstream for easier processing
	Int_base result;
	char next;

	iss.get(next);  // for oct/hex numbers, this eats leading 0
	if (!isdigit(next))  // must begin with numeric digit
		error("convert_to_int_base() invalid input: " + to_string(next));

	if (next != '0' || iss.rdbuf()->in_avail() == 0)  // no leading zero, it's a decimal value
	{
		iss.putback(next);  // is digit but not 0, puts back for read operation
		if (!valid_number(s, base::dec)) error("not valid decimal number");
		iss >> result.value;
		result.base_type = base::dec;
		return result;
	}

	iss.get(next);  // already got leading 0 above, now check for x
	if (next == 'x' || next == 'X')
	{   // note: don't need "0x" identifier
		if (!valid_number(s, base::hex)) error("not valid hexadecimal number");
		iss >> hex >> result.value;
		result.base_type = base::hex;
		return result;
	}
	else
	{
		// already got leading 0 above
		iss.putback(next);  // prior get() wasn't x, put it back for read operation
		if (!valid_number(s, base::oct)) error("Not valid octal number");
		iss >> oct >> result.value;
		result.base_type = base::oct;
		return result;
	}
	return result;
}

void show_prompt(int n)
{
	cout << "#" << n << ": ";
}

// sets cin flag to accept standard notation for non-decimal numbers
void enable_all_bases()
{
	cin.unsetf(ios::dec);
	cin.unsetf(ios::hex);	// 0x
	cin.unsetf(ios::oct);	// 0
}

// attempts to read and validate a dec/oct/hex number from user
// modifies param ib, returns true if input validated
bool read_number(Int_base& ib)
{
	string input;
	try
	{
		cin >> input;
		ib = convert_to_int_base(input);
	}
	catch (runtime_error& e)
	{
		cerr << "error: " << e.what() << '\n';
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	return true;
}

// requests user enter specified number of integers, rejects bad values
void get_user_input(vector<Int_base>& numbers, const int num_elements)
{
	enable_all_bases();  // permits hex (0x) and oct (0) prefix
	
	cout << "Enter " << num_elements << " numbers in decimal, octal or hexadecimal form:\n";
	for (int i = 0; i < num_elements; ++i)
	{
		Int_base ib;  // modified in read_number()
		bool successful_input = false;
		while (!successful_input)
		{
			show_prompt(i + 1);
			successful_input = read_number(ib); 
		}
		numbers.push_back(ib);  
	}
}

// aligned into padded columns unless value is 9+ digits including base identifier
void print_formatted_line(Int_base ib)
{
	if (ib.base_type == base::oct)
		cout << setw(8) << oct << ib.value << "  " << "octal\t\t" << "converts to " << dec << setw(8) << ib.value << " decimal\n";
	if (ib.base_type == base::dec)
		cout << setw(8) << dec << ib.value << "  " << "decimal\t" << "converts to " << dec << setw(8) << ib.value << " decimal\n";
	if (ib.base_type == base::hex)
		cout << setw(8) << hex << ib.value << "  " << "hexadecimal\t" << "converts to " << dec << setw(8) << ib.value << " decimal\n";
}

void print_formatted_values(const vector<Int_base>& numbers)
{
	cout << showbase;
	for (const Int_base& ib : numbers)
		print_formatted_line(ib);
}

int main()
try {
	vector<Int_base> numbers;
	int num_elements = 3;
	
	get_user_input(numbers, num_elements);
	print_formatted_values(numbers);
	
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
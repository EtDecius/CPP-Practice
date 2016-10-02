// Chapter11E14.cpp
// Chapter 11, Exercise 14 (p.408)
// Write a program that reads a text file and writes out how many characters
// of each character classification (11.6) are in the file.

#include "../../../std_lib_facilities.h"

// holds count for various character types
struct Char_type_counter
{
	unsigned int space = 0,		alpha = 0,		digit = 0,
				 hexdigit = 0,	uppercase = 0,	lowercase = 0,
				 alphanumeric = 0,	ctrl = 0,	punctuation = 0,
				 printable = 0,	graphic = 0;
};

// counts and categorizes each character in file
// chars may fit multiple categories
Char_type_counter count_characters(ifstream& fin)
{
	Char_type_counter char_count;
	
	char ch;
	while (fin.get(ch))
	{
		if (isspace(ch)) ++char_count.space;
		if (isalpha(ch)) ++char_count.alpha;
		if (isdigit(ch)) ++char_count.digit;
		if (isxdigit(ch)) ++char_count.hexdigit;
		if (isupper(ch)) ++char_count.uppercase;
		if (islower(ch)) ++char_count.lowercase;
		if (isalnum(ch)) ++char_count.alphanumeric;
		if (iscntrl(ch)) ++char_count.ctrl;
		if (ispunct(ch)) ++char_count.punctuation;
		if (isprint(ch)) ++char_count.printable;
		if (isgraph(ch)) ++char_count.graphic;
	}
	return char_count;
}

// print formatted characte counts
void print_char_values(const string& filename, const Char_type_counter& char_count)
{
	cout << "Summary of characters in file: " << filename << '\n';

	cout << "Whitespace:" << "\t\t\t" << char_count.space << '\n';
	cout << "Alphabetic:" << "\t\t\t" << char_count.alpha << '\n';
	cout << "Alphanumeric:" << "\t\t\t" << char_count.alphanumeric << '\n';
	cout << "Decimal Digit:" << "\t\t\t" << char_count.digit << '\n';
	cout << "Hexadecimal Digit:" << "\t\t" << char_count.hexdigit << '\n';
	cout << "Uppercase:" << "\t\t\t" << char_count.uppercase << '\n';
	cout << "Lowercase:" << "\t\t\t" << char_count.lowercase << '\n';
	cout << "Punctuation:" << "\t\t\t" << char_count.punctuation << '\n';
	cout << "Printable:" << "\t\t\t" << char_count.printable << '\n';
	cout << "Non-printable (control):" << "\t" << char_count.ctrl << '\n';
	cout << "Has Visual Representation:" << "\t" << char_count.graphic << '\n';
}

int main()
try {
	cout << "Character Type Counter v.01\n\n";  

	cout << "Enter file name: ";
	string filename;
	cin >> filename;

	ifstream fin{ filename };
	if (!fin) error("failed to open file ", filename);

	Char_type_counter char_count = count_characters(fin);

	print_char_values(filename, char_count);
	
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
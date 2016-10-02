// Ch11E5.cpp
// Chapter 11, Exercise 5 (p.408)
// Write a program that reads strings and for each string outputs the
// character classification of each character, as defined by the 
// character classifications presented in 11.6. Note that a character
// can have several classifications (ex: x is both a leter and an
// alphanumeric).
//
// Character classifications (11.6):
// isspace, isalpha, isdigit, isxdigit, isupper, islower, isalnumeric
// iscntrl, ispunct, isprint, isgraph

#include "../../../std_lib_facilities.h"

// print type(s) for each character in string
void classify_chars(const string& word)
{
	cout << "Full String: " << word << '\n';
	for (char c : word)
	{
		cout << c << ": ";
		if (isspace(c)) cout << "space ";
		if (isalpha(c)) cout << "alpha ";
		if (isdigit(c)) cout << "decimal digit ";
		if (isxdigit(c)) cout << "hex digit ";
		if (isupper(c)) cout << "uppercase ";
		if (islower(c)) cout << "lowercase ";
		if (isalnum(c)) cout << "alpha-numeric ";
		if (iscntrl(c)) cout << "control ";
		if (ispunct(c)) cout << "punctuation ";
		if (isprint(c)) cout << "printable ";
		if (isgraph(c)) cout << "has graphic";
		cout << "\n";
	}
	cout << '\n';
}

#include "../../../std_lib_facilities.h"

int main()
try {
	
	// test strings
	vector<string> phrases{
		"Hello Darkness, my old friend...",
		"For a good time, call 1 (900) 555-1234 oxoxoxo",
		"(>'-')> <('-'<) ^('-')^ v('-')v(>'-')> (^-^) ... Kirby",
		"ru w8 4 me 2 rite 4 rlz \t lolololol",
		"PLAY DOTA 2!"
	};

	for (const string& s : phrases)
		classify_chars(s);

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
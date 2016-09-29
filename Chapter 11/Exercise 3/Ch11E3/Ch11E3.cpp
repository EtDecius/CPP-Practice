// Ch11E3.cpp
// Chapter 11, Exercise 3 (p.408)
// Write a program that removes all vowels from a file ("disemvowels").

#include "../../../std_lib_facilities.h"

void welcome_screen()
{
	cout << "Ch 11, Ex 3: The Disemvoweler\n";
}

string get_filename()
{
	string fn;
	cout << "Enter file name: ";
	cin >> fn;
	return fn;
}

bool is_vowel(char c)
{
	c = tolower(c);

	switch (c)
	{
	case 'a': case 'e':	case 'i':
	case 'o': case 'u':	case 'y': 
		return true;
	default:
		return false;
	}
}

// stores file contents except for vowels
void parse_file(fstream& fio, vector<char>& content_no_vowels)
{
	char in;
	while (fio.get(in))
	{
		if (!is_vowel(in))
			content_no_vowels.push_back((char)in);
	}
}

// erase contents of file
void clear_file(fstream& fio, string filename)
{
	fio.close();
	fio.open(filename, ofstream::out|ofstream::trunc);
	if (!fio) error("clear_file() failed to clear file contents ", filename);
}

// print all characters stored in vector
void fill_file(fstream& fio, const vector<char>& content_no_vowels)
{
	for (char c : content_no_vowels)
		fio << c;
}

// removes vowel characters from file, leaves other characters intact
void remove_vowels(fstream& fio, string filename)
{
	vector<char> content_no_vowels;			// temporary storage for file contents
	parse_file(fio, content_no_vowels);		
	clear_file(fio, filename);
	
	if (fio) 
		fill_file(fio, content_no_vowels);	
	cout << "Operation complete. Vowels removed from " << filename << '\n';
}

int main()
try {
	welcome_screen();

	string filename = get_filename();
	fstream fio{ filename, fstream::in | fstream::out };
	if (!fio) error("unable to open file ", filename);
	
	remove_vowels(fio, filename);

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
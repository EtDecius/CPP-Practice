// Ch11E1.cpp
// Chapter 11, Exercise 1 (p.408)
// Write a program that reads a text file and converts its input
// to all lower case, producing a new file.

#include "../../../std_lib_facilities.h"

void convert_file_lowercase(ifstream& fin, ofstream& fout)
{
	char input;
	char output;
	while (fin.get(input))				// note: get() returns an int
		fout << (char) tolower(input);	// cast int to char before output

	if (fin.eof()) cout << "Operation complete.\n";
}

int main()
try {
	
	string in_file = "source.txt";
	ifstream fin{ in_file };
	if (!fin) error("failed to open file ", in_file);

	string out_file = "output.txt";
	ofstream fout{ out_file };
	if (!fout) error("failed to open file ", out_file);

	convert_file_lowercase(fin, fout);

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
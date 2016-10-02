// Ch11E15.cpp
// Chapter 11, Exercise 15 (p.409)
// Write a program that reads a file of whitespace-separated numbers and
// outputs a file of numbers using scientific formation and precision 8 in four
// fields of 20 characters per line.

#include "../../../std_lib_facilities.h"

int main()
try {
	cout << "Numbers from File to Scientific Notation v0.1\n\n";

	string filename = "sample.txt";
	ifstream fin{ filename };
	if (!fin) error("failed to open input file ", filename);

	string outfile = "output.txt";
	ofstream fout{ outfile };
	if (!fout) error("failed to open output file ", outfile);

	const int values_per_line = 4;
	int curr_per_line = 0;
	double input;
	fout << scientific << setprecision(8);
	while (fin >> input)
	{
		if (curr_per_line == values_per_line)
		{
			fout << '\n';
			curr_per_line = 0;
		}

		// printing to cout instead of fout for debugging
		fout << setw(20) << input;
		++curr_per_line;
	}

	cout << "Operation complete.\n";

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
// Ch10E11.cpp
// Chapter 10, Exercise 11 (p.378)
// Write a program that produces the sum of all integers in a text file.
// Text file will be white-space seperated but contains words, letters and symbols
// in addition to the ingegers.

#include "../../../std_lib_facilities.h"

int sum_ints_in_file(ifstream& fin)
{
	int sum = 0;

	char next;
	int number;
	string junk;
	while (fin)
	{
		next = fin.peek();
		if (isdigit(next))
		{
			fin >> number;
			sum += number;
		}
		else if (isspace(next))
			fin >> ws;
		else
			fin >> junk;
	}

	return sum;
}

int main()
try {

	string filename = "raw.txt";
	ifstream fin{ filename };
	if (!fin) error("failed to open file ", filename);

	int sum = sum_ints_in_file(fin);
	cout << "Sum: " << sum << '\n';

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
// Ch11E9.cpp
// Chapter 11, Exercise 9 (p.409)
// Split the binary I/O program from 11.3.2 into two: one program that
// converts an ordinary text file into binary and one program that reads
// binary and converts it to text. Test these programs by comparing a test
// file with what you get by converting it to binary and back.
//
// This program reads in a binary file, then prints contents to screen
// (as text).

#include "../../../std_lib_facilities.h"

int main()
try {
	// open an istream for binary input from a file
	cout << "Please enter input binary file name: ";
	string iname;
	cin >> iname;
	ifstream ifs{ iname, ios_base::binary };  // open in binary mode
	if (!ifs) error("can't open input file ", iname);

	vector<int> v;

	// read from binary file
	for (int x; ifs.read(as_bytes(x), sizeof(int));)
		v.push_back(x);
	if (ifs.eof())
		cout << "Reading binary file complete.\n";

	cout << "Printing loaded content:\n";
	for (int n : v)
		cout << (char(n));
	cout << '\n';

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
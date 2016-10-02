// Ch11E9b.cpp
// Chapter 11, Exercise 9 (p.409)
// Split the binary I/O program from 11.3.2 into two: one program that
// converts an ordinary text file into binary and one program that reads
// binary and converts it to text. Test these programs by comparing a test
// file with what you get by converting it to binary and back.
//
// This program reads text from a file, then writes it's content to
// a new binary file.

#include "../../../std_lib_facilities.h"

int main()
try {
	// open a file containing text
	cout << "Please enter text file name\n";
	string iname;
	cin >> iname;
	ifstream fin{ iname };
	if (!fin) error("can't open input file ", iname);

	vector<int> v;

	char n;
	while (fin.get(n))
		v.push_back(int(n));

	if (fin.eof()) cout << "Loading file " << iname << " complete.\n";

	// open an ostream for binary output to a file
	cout << "Please enter output file name\n";
	string oname;
	cin >> oname;
	ofstream ofs { oname, ios_base::binary };
	if (!ofs) error("can't open output file ", oname);

	for (int x : v)
		ofs.write(as_bytes(x), sizeof(int));
	cout << "Saving to binary file complete.\n";

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
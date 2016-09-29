// Ch10E8.cpp
// Chapter 10, Exercise 8 (p.378)
// Write a problem that concatenates the contents of two files
// and stores them in a third file

#include "../../../std_lib_facilities.h"

// open input file using supplied ifstream
bool open_file(ifstream& fin, const string& filename)
{
	fin.open(filename);
	if (!fin) error("open_file() failed to open ", filename);
	return true;
}

// open output file using supplied ofstream
bool open_file(ofstream& fout, const string& filename)
{
	fout.open(filename);
	if (!fout) error("open_file() failed to open ", filename);
	return true;
}

// copy contents from one file to another
void copy_file_contents(ifstream& fin, ofstream& out)
{
	string full_line;
	while (getline(fin, full_line))
		out << full_line << '\n';
	if (fin.eof()) return;
}


// copy contents from two input files into single output file
void append_file(const string& infile1, const string& infile2, const string& outfile)
{
	ifstream fin1;
	if (!open_file(fin1, infile1)) error("append_file() failed to open ", infile1);

	ifstream fin2;
	if (!open_file(fin2, infile2)) error("append_file() failed to open ", infile2);

	ofstream fout;
	if (!open_file(fout, outfile)) error("append_file() failed to open ", outfile);

	copy_file_contents(fin1, fout);
	copy_file_contents(fin2, fout);
}



int main()
try {
	string infile1,
		infile2,
		outfile;

	cout << "Enter input file #1 name: ";
	getline(cin, infile1);

	cout << "Enter input file #2 name: ";
	getline(cin, infile2);

	cout << "Enter output file name: ";
	getline(cin, outfile);

	append_file(infile1, infile2, outfile);

	return 0;
}
catch (runtime_error& e)
{
	cerr << "error:() " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}
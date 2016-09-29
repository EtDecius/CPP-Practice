// Ch10E9.cpp
// Chapter 10, Exercise 9 (p.378)
// Write a program that takes two files containing sorted
// white-space separated words and merges them, preserving order.
// Note: changed requirement to read per line rather than per whitespace

#include "../../../std_lib_facilities.h"

// simple buffer that stores up to one string
struct Input_buffer
{
	Input_buffer() : is_empty{ true } {};
	bool is_empty;
	string value;
};

// merges contents of two files line by line, preserving alphabetic order
// setup:	- ifstream objects must be initialized and associated to file beforehand
//			- each file should be sorted alphabetically by line beforehand
// use:		- use input_complete() in loop conditional to read entire file contents
// 			- use next() to get string from either file that comes first alphabetically
class Input_switch
{
public:
	Input_switch(ifstream& left_in, ifstream& right_in);
	bool input_complete();
	string next();

private:
	string get_least();
	string extract(Input_buffer& ib);
	void fill_buffer(ifstream& fin, Input_buffer& ib);

	const string stream_done = "~!~~Input Complete~#~~";
	ifstream& left_in;
	ifstream& right_in;
	Input_buffer left;
	Input_buffer right;
};

// ---------- Input_switch private functions ----------

// reads next line from file, stores in buffer. no changes if buffer full
void Input_switch::fill_buffer(ifstream& fin, Input_buffer& ib)
{
	if (fin.eof() && ib.is_empty)	// EOF reached, last line already processed
	{
		ib.value = stream_done;		// set to sentinel value
		ib.is_empty = false;		
	}
	else if (ib.is_empty)			
	{
		getline(fin, ib.value);
		ib.is_empty = false;
	}
}

// returns buffered string and empties buffer
string Input_switch::extract(Input_buffer& ib)
{
	ib.is_empty = true;
	return ib.value;
}

// returns string from either buffer that comes first alphabetically
string Input_switch::get_least()
{
	if (left.value <= right.value)
		return extract(left);
	else
		return extract(right);
}

// -----------------------------
// Input_switch public functions

// constructor: requires two ifstream objects that have been linked to files
Input_switch::Input_switch(ifstream& left, ifstream& right)
	: left_in{ left }, right_in{ right }
{
	if (!(left_in) || !(right_in)) error("Input_switch() failed to open stream");
}

// returns true when both files fully read
bool Input_switch::input_complete()
{
	return (left_in.eof() && right_in.eof());
}

// returns next line from either file that comes first alphabetically
string Input_switch::next()
{
	fill_buffer(left_in, left);
	fill_buffer(right_in, right);

	if (left.value == stream_done)
		return extract(right);
	else if (right.value == stream_done)
		return extract(left);
	else
		return get_least();
}
// ***************************************************

// open input file using supplied ifstream
void open_file(ifstream& fin, const string& filename)
{
	fin.open(filename);
	if (!fin) error("open_file() failed to open ", filename);
}

// combines content from two sorted files, retaining alphabetic order
// stores the sorted content in a vector of strings
void file_import_sorted(vector<string>& list, const string& file_left, const string& file_right)
{
	// open both files
	ifstream fin_left;
	open_file(fin_left, file_left);

	ifstream fin_right;
	open_file(fin_right, file_right);

	// get next alphabetical input from either file and add to list
	Input_switch is{ fin_left, fin_right };
	while (!(is.input_complete()))
		list.push_back(is.next());
}

void print_results(const vector<string>& list)
{
	for (const string& s : list)
		cout << s << '\n';
}


int main()
try {
	vector<string> list;
	string file1, file2;

	file1 = "onepiece.txt";
	file2 = "hunterxhunter.txt";

	file_import_sorted(list, file1, file2);
	print_results(list);
	cout << "Total lines: " << list.size() << '\n';
	
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
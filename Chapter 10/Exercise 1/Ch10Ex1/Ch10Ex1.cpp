// Ch10Ex1.cpp
// Chapter 10, Exercise 1 (p.377)
// Write program that sums all numbers in a file of 
// white-space separated integers.


#include "../../../std_lib_facilities.h"

void load_file_data(ifstream& fin, vector<int>& data)
{
	int input;
	while (fin >> input)
		data.push_back(input);

	if (fin.bad()) error("load_file_data() bad ifstream");
	if (fin.eof()) return;
	if (fin.fail())
	{
		// figure out why it failed and how to reset it
	}
}

void load_file(string filename, vector<int>& data)
{
	ifstream fin;
	fin.open(filename);
	if (!fin) error("load_data(): failed to open file ", filename);
	
	load_file_data(fin, data);
}


void print_data(vector<int>& data)
{
	for (int n : data)
		cout << n << ' ';
}

int sum_data(vector<int>& data)
{
	int sum = 0;
	for (int n : data)
		sum += n;
	return sum;
}


int main()
try {

	vector<int> data;
	string filename = "data.txt";
	load_file(filename, data);

	print_data(data);
	cout << '\n';
	int sum = sum_data(data);
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
// Ch11E16.cpp
// Chapter 11, Exercise 16 (p.409)
// Write a program to read a file of whitespace-separated numbers and
// output them in order (lowest value first), one value per line.
// Write a value only once, and if it occurs more than once write the
// count of it's occurences on it's line.

#include "../../../std_lib_facilities.h"
#include <map>

// reads values in from file; adds new or increments count for existing
void load_values(ifstream& fin, map<int, int>& values)
{
	int buffer;
	while (fin >> buffer)
	{
		if (values.count(buffer) == 0)  // 
			values.emplace(buffer,1);  // creates value,count pair and adds it
		else
		{
			auto it = values.find(buffer);
			it->second += 1;
		}
	}
}

// prints formatted list of values and their respective counts
void print_values(const map<int, int>& values)
{
	cout << setw(5) << "  Value" << setw(7) << "  Count" << '\n';
	for (auto it = values.begin(); it != values.end(); ++it)
		cout << setw(5) << it->first << setw(7) << it->second << '\n';
}

int main()
try {
	cout << "Number Counter v0.1\n\n";

	string filename;
	cout << "Enter file name: ";
	cin >> filename;

	ifstream fin{ filename };
	if (!fin) error("failed to open file ", filename);

	map<int, int> values;
	
	load_values(fin, values);
	print_values(values);

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
// Ch11E10.cpp
// Chapter 11, Exercise 10 (p.409)
// Write a function that returns a vector of whitespace-separated
// substrings from a string argument.

#include "../../../std_lib_facilities.h"

vector<string> split(const string& s)
{
	vector<string> substrings;
	istringstream iss{ s };
	string sub;

	while (iss >> sub)
		substrings.push_back(sub);

	return substrings;
}

int main()
try {
	string sample_sentence{
		"The man in black fled across the desert, and the gunslinger followed."
	};

	vector<string> test = split(sample_sentence);

	for (string& s : test)
		cout << s << '\n';
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
// Ch11E11.cpp
// Chapter 11, Exercise 11 (p.409)
// Write a function that returns a vector of whitespace-separated
// substrings from a string argument, where whitespace is defined
// as "ordinary whitespace" plus the characters in w

#include "../../../std_lib_facilities.h"

// true if character is whitespace or found in w parameter
// @param w: string of delimiters
bool is_delimiter(char c, const string& w)
{
	if (c == ' ') return true;
	for (const char& cc : w)
		if (c == cc)
			return true;
	return false;
}

// separate string into substringers using delimiters
// @param w: string of delimiters
vector<string> split(const string& s, const string& w)
{
	vector<string> vs;
	istringstream iss{ s };
	char ch;
	string sub;

	while (iss.get(ch))
	{
		if (!is_delimiter(ch, w))
			sub += ch;
		else if (!sub.empty())
		{
			vs.push_back(sub);
			sub.clear();
		}
	}
	return vs;
}

void print_vector(const vector<string>& vs)
{
	for (const string& s : vs)
		cout << s << ' ';
	cout << '\n';
}

int main()
try {
	string sample_sentence{
		"The man in black fled across the desert, and the gunslinger followed."
	};
	string sample_2{
		"The!man in black-fled-across the ,,desert, and the -  - gunslinger. followed..."
	};

	string delimiters{ ",.!-" };

	vector<string> test = split(sample_sentence, delimiters);
	print_vector(test);

	test = split(sample_2, delimiters);
	print_vector(test);

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
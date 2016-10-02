// Ch11E6.cpp
// Chapter 11, Exercise 6 (p.408)
// Write a program that replaces punctuation with whitespace. Don't
// modify characters within a pair of double quotes (").
// Consider the following as punctuation:
// . ; , ? - ' 

#include "../../../std_lib_facilities.h"

bool is_custom_punct(char c)
{
	static const vector<char> punct_list{
		'.', ';', ',', '?', '-', '\''
	};

	for (char cc : punct_list)
		if (cc == c)
			return true;
	return false;
}

// replaces specific punctuations characters in string with a whitespace
string clear_punctuation(const string& s)
{
	string result = s;
	bool supress = false;

	for (char& c : result)
	{
		if (c == '\"')
			supress = !supress;
		
		if (!supress)
		{
			if (is_custom_punct(c))
				c = ' ';
		}
	}
	return result;
}


int main()
try {
	// sample strings
	vector<string> samples{
		"Doctor Who? I don't know, man.",
		"Example sentence; says \" - don't use the as-if rule.\" so test it.",
		"This is a good C++ book, better than C-- by \"Some Guy!\"..."
	};

	string test;
	for (const string& s : samples)
	{
		test = clear_punctuation(s);
		cout << test << '\n';
	}
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

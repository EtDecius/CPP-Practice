// Ch11E2.cpp
// Chapter 11, Exercise 2 (p.408)
// Write a program that given a file name and a word outputs each line
// that contains that word together with the line number. Hint: getline().

// Note: Loop functions well, but implementation to discard non-alpha characters
// such as . , " ! etc. is hackish and similar to the overly specific example in 11.7.
// Better implementation would use the Punct_stream class described in chapter.

#include "../../../std_lib_facilities.h"

// compares char to list of unwanted, non-alpha characters
bool prune_char(const char& c)
{
	static const string clean_these_chars = "\".,:()?!-";
	for (char cc : clean_these_chars)
		if (c == cc)
			return true;
	return false;
}

// removes unwanted characters from string as specified in prune_char()
void prune_word(string& s)
{
	for (int i = 0; i < s.length(); ++i)
	{
		if (prune_char(s[i]))
		{
			s.erase(i, 1);
			--i;  // account for removed element
		}
	}
}

// returns true if line contains specified word at least once
// ignores common non-alpha symbols
bool word_found(const string& full_line, const string& word)
{
	string curr_word;
	istringstream iss{ full_line };

	while (iss >> curr_word)
	{
		prune_word(curr_word);	
		if (curr_word == word)
			return true;
	}
	return false;
}

// prints the line in a file whenever that line contains specified word
void find_word(ifstream& fin, const string& search_for)
{
	string full_line;
	int line_number = 1;
	int line_count = 0;

	// loop through each line of file and search for specified word
	while (getline(fin, full_line))
	{
		if (word_found(full_line, search_for))
		{
			cout << line_number << ": " << full_line << '\n';
			++line_count;
		}
		++line_number;
	}
	cout << "\n\"" << search_for << "\" found on " << line_count << " separate lines.\n\n";
}

int main()
try {
	string in_file = "input.txt";
	ifstream fin{ in_file };
	if (!fin) error("failed to open file ", in_file);

	const string end_program = "quit";
	string search_for;
	
	do 
	{
		cout << "Enter search word (quit to exit): ";
		cin >> search_for;

		// call function
		find_word(fin, search_for);
		
		// reset file back to beginning
		if (fin.eof())
		{
			fin.clear();
			fin.seekg(0, ios::beg);
		}
	} while (search_for != end_program);

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
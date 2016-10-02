// Ch11E7.cpp
// Chapter 11, Exercise 7 (p.409)
// Modify the program from the previous exercise so that it replaces
// don't with do not, can't with cannot, etc.; leaves hyphens within words
// intact (so that we get " do not use the as-if rule "); and converts
// all characters to lower case
//
// Modification breakdown:
// 1) make lowercase
// 2) replace contractions with two-word expanded form (don't -> do not)
// 3) replace punctuation with white space unless enclosed by double quotes
// 4) don't replace hyphen in middle of word, even if not in double quotes

#include "Contraction_separator.h"
#include "../../../std_lib_facilities.h"

bool is_custom_punct(char c)
{
	static const vector<char> punct_list{  // from exercise requirements
		'.', ';', ',', '?', '-', '\''
	};

	for (char cc : punct_list)
		if (cc == c)
			return true;
	return false;
}

// replaces specific punctuations characters with a whitespace
// no replacement if suppress is true
void clear_punctuation(char& c, bool suppress)
{
	if (!suppress)
	{
		if (is_custom_punct(c))
			c = ' ';
	}
}

void lowercase(char& c)
{
	c = tolower(c);
}


// handle special case for hyphen in middle of word
// replaces hyphen unless alpha character on both sides
void handle_hyphen(string& word, int loc, bool& suppress)
{
	if (loc == 0 || loc == word.size() - 1)  // first or last char, not inbetwen
		clear_punctuation(word[loc], suppress);
	else if (loc != 0 && loc != word.size() - 1) // middle char
	{
		// check if adjacent chars are alphabetic
		if (isalpha(word[loc - 1]) && isalpha(word[loc + 1]))
			return;
		else
			clear_punctuation(word[loc], suppress);
	}
}
	
// applies several rules from assignment to modify strings
// checks each character and modify if appropriate
void parse_word(Contraction_separator& cs, string& word, bool& suppress)
{
	const char toggle_suppress = '\"';
	if (word.size() == 0) return;

	for (int i = 0; i < word.size(); ++i)
	{
		lowercase(word[i]);					// set to lowercase
		if (word[i] == toggle_suppress)		// stop replacing chars when sentinel detected
			suppress = !suppress;
		if (word[i] == '\'')				// ' indicates possible contraction
			word = cs.get_separated(word);	// contraction found, replace before further changes
		if (word[i] == '-')					// check for hyphens in middle of word
			handle_hyphen(word, i, suppress);  
		else
			clear_punctuation(word[i], suppress);
	}
}

// convert string into a series of whitespace separated "words"
// parse each word per assignment criteria
std::string parse_input(Contraction_separator& cs, string& input)
{
	istringstream iss{ input };
	bool suppress = false;
	string curr;

	string output;
	while (iss >> curr)  // reads in white-space separated word
	{
		parse_word(cs, curr, suppress);
		output += curr + ' ';
	}
	if (iss.eof()) return output;
	if (iss.bad()) error("parse_input() bad istringstream");
	if (iss.fail()) error("parse_input() encountered issue");
}

int main()
try {

	string filename = "contractions.txt";
	Contraction_separator cs{ filename };  // separates contractions into two words

	// sample strings
	vector<string> samples{
		"Doctor Who? I don't know, man.",
		"Example sentence; says \" - don't use the as-if rule.\" so test it.",
		"This is a good C++ book, better than C-- by \"Some Guy!\"..."
	};

	// check output
	for (string& s : samples)
	{
		string output = parse_input(cs, s);
		cout << output << '\n';
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
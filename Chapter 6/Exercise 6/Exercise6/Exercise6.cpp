// Exercise6.cpp
// Chapter 6 Exercise (p.219)
// Write program that checks if a sentence adheres to the "English" grammar from Ch 6.4.1.
// Includes article "the" from Exercise 5.

#include "../../../std_lib_facilities.h"

class Word_stream
{
public:
	Word_stream();
	string get();
	void putback(string s);
private:
	bool full;
	string buffer;
};

// Word_stream class constructor
Word_stream::Word_stream()		
	:full(false), buffer("")	// initialization list
{
}

// Return next word
string Word_stream::get()
{
	if (full)					// Word stored in buffer
	{							
		full = false;			
		return buffer;			// return it
	}

	// define all words in grammar
	vector<string> dictionary;
	dictionary.push_back("and");	dictionary.push_back("or");		dictionary.push_back("but");
	dictionary.push_back("birds");	dictionary.push_back("fish");	dictionary.push_back("C++");
	dictionary.push_back("rules");	dictionary.push_back("fly");	dictionary.push_back("swim");
	dictionary.push_back("the");

	// define sentinels
	dictionary.push_back(".");		dictionary.push_back("q");

	string input = "";
	cin >> input;
	
	// verify word is in dictionary and return
	for (string s : dictionary)		
	{
		if (input == s)
			return s;
	}
	error("unrecognized word " + input);
}


void Word_stream::putback(string s)
{
	if (full) error("putback() into full buffer");
	buffer = s;
	full = true;
}

Word_stream w_stream;
string sentence();		// function prototype


// verify and return article
string article()
{
	string s = w_stream.get();
	if (s == "the")
		return s + " ";
	else
	{								
		w_stream.putback(s);		
		return "";
	}
}

// verify and append noun to phrase
string noun()
{
	string left = article();
	string s = w_stream.get();
	if (s == "birds" || s == "fish" || s == "C++")
		return left + s;
	else
		error("noun expected");
}

// verify and append verb to sentence
string verb()
{
	string left = noun();
	string s = w_stream.get();
	if (s == "rules" || s == "fly" || s == "swim")
	{
		left = left + " " + s;
		return left;
	}
	else
		error("verb expected");
}

// verify and append conjunction + another sentence
string w_conjunction()
{
	string s = w_stream.get();
	if (s == "and" || s == "or" || s == "but")
	{
		string right = sentence();
		return s + " " + right;
	}
	else
		error("conjunction expected");
}

// compose sentence per grammar rules
string sentence()
{
	string left = verb();

	// check for sentinel to determine if end of sentence
	string s = w_stream.get();
	if (s == ".")
	{
		w_stream.putback(s);		
		return left;
	}

	// sentence was not complete, proceed with conjunction
	w_stream.putback(s);
	string right = w_conjunction();
	left = left + " " + right;
	return left ;
}


int main()
{
	try
	{
		string input = "";
		string output = "";
		bool quit = false;
		while (!quit)
		{
			input = w_stream.get();
			if (input == "q")
				quit = true;
			else if (input == ".")
				cout << output << " <- valid\n";
			else
				w_stream.putback(input);
			output = sentence();
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
	}
}
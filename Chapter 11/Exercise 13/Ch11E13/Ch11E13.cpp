// Ch11E13.cpp
// Chapter 11, Exercise 13 (p.409)
// Reverse the order of words (defined as whitespace-separated strings) in a
// file. For example, "Norwegian Blue parrot" becomes "parrot Blue Norwegian".
// You are allowed to assume that all the strings from the file will fit into
// memory at once.
//
// Minor adjustment: handles text that contains punctuation as well as
// whitespaces.
// Ex: (Hello, world!) --> (!world ,Hello)
// Note: Does not correct hyphenated words on two lines
// Ex:  
//  anti-    -->  matter
//  matter        anti-

#include "../../../std_lib_facilities.h"
#include <stack>

void welcome()
{
	cout << "File Reverser v0.2\n\n";
}

// returns true if character commonly used as seperator in English sentences
bool is_punctuation(char c)
{
	switch (c)
	{
	case '.':	case ',':	case '!':
	case '?':	case ';':	case ':':
	case '\\':	case '/':	case '\"':
	case '[':	case ']':	case '{':
	case '}':	case '(':	case ')':
		return true;
	default:
		return false;
	}
}

// flip the direction for encapsulating punctuation
char reverse_punctuation(char c)
{
	switch (c)
	{
	case '[': return ']';
	case ']': return '[';
	case '{': return '}';
	case '}': return '{';
	case '(': return ')';
	case ')': return '(';
	default:
		return c;
	}
}

// read text from file and store in buffer
void read_from_file(fstream& fio, vector<char>& buffer)
{
	char in;
	while (fio.get(in))
		buffer.push_back(in);
}

void print_buffer(fstream& fio, stack<char>& substring)
{
	while (substring.size() != 0)
	{
		fio << substring.top();
		substring.pop();
	}
}

// print from buffer to file, preserving order of letters within words
void write_to_file(fstream& fio, vector<char>& buffer)
{
	char ch;
	stack<char> substring;  // use stack data structre to reverse letter order

	// print buffer contents from back to front
	for (int i = buffer.size() - 1; i >= 0; --i)
	{
		ch = buffer[i];
		if (is_punctuation(ch) || isspace(ch))
		{
			print_buffer(fio, substring);   // print whatever was in buffer
			fio << reverse_punctuation(ch); // then print punct/whitespace
		}
		else
			substring.push(ch);
	}
	print_buffer(fio, substring); 	// clear out any remaining data in buffer
}

// reverses order of words in file, but preserves order of characters
// within each word.
void reverse_file(const string& filename)
{
	fstream fio{ filename, ios_base::in};
	if (!fio) error("reverse_file() failed to open file ", filename);

	vector<char> buffer;

	read_from_file(fio, buffer);

	// clear file contents
	fio.close();
	fio.open(filename, ios_base::out | ios_base::trunc);
	if (!fio) error("reverse_file() failed to clear file ", filename);

	write_to_file(fio, buffer);
}

int main()
try {
	welcome();
	cout << "Enter file name: ";
	string filename;
	cin >> filename;

	reverse_file(filename);

	cout << "File reversal complete.\n";

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
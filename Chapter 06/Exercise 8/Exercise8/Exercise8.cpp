// Exercise8.cpp
// Chapter 6 exercise (p.219)
// Redo "Bulls and Cows" game from Ch 4 Ex 12 using four letters
// rather than 4 digits

#include "../../../std_lib_facilities.h"

// Return number of characters in which both value and position are correct
int bulls(vector<char>& guess, vector<char>& answer)
{
	if (guess.size() != answer.size())
		error("invalid argument for bulls()");

	int bull = 0;
	for (unsigned int i = 0; i < answer.size(); ++i)
	{
		if (guess[i] == answer[i])
			++bull;
	}
	return bull;
}

// Return number of digits in which value exists, but not in correct position
int cows(vector<char>& guess, vector<char>& answer)
{
	if (guess.size() != answer.size())
		error("invalid argument for cows()");

	int cow = 0;
	for (unsigned int i = 0; i < guess.size(); ++i)
	{
		for (unsigned int j = 0; j < answer.size(); ++j)
		{
			if (guess[i] == answer[j])
				++cow;
		}
	}
	cow -= bulls(guess, answer);
	return cow;
}

// Print all chars in vector
void print_list(vector<char>& v)
{
	for (char x : v)
		cout << x;
}

// Returns true if an character listed more than once
bool duplicates(vector<char>& v)
{
	bool duplicates = false;
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		for (unsigned int j = i + 1; j < v.size(); ++j)
		{
			if (v[i] == v[j])
			{
				duplicates = true;
				break;
			}
		}
	}
	return duplicates;
}

// Returns true if n found in vector
bool find_int(char c, vector<char>& answer)
{
	bool found = false;
	for (unsigned int i = 0; i < answer.size(); ++i)
	{
		if (c == answer[i])
			found = true;
	}
	return found;
}



int main()
{
	try
	{
		constexpr int num_letters = 4;				// set number of characters per puzzle
		while (true)								// game loop, continues forever until user quits
		{
			vector<char> answer;					// set of answers
			while (answer.size() < num_letters)		
			{
				char candidate = char(randint('a', 'z'));	// random char from a to z
				if (!find_int(candidate, answer))			// check for dupes, add if unique
					answer.push_back(candidate);
			}

			bool solved = false;
			while (!solved)
			{
				vector<char> guess;
				char input;
				cout << "Enter four-letter guess:\n";
				while (guess.size() < num_letters && cin >> input)	// read in user's guess
				{
					if (input < 'a' || input > 'z')					// validate character
						error("only letters a to z are valid");
					guess.push_back(input);
				}

				if (duplicates(guess) == true)								
					error("guess cannot contain duplicate letters");

				int bulls_count = bulls(guess, answer);				// calculate and report number of chars
				if (bulls_count == num_letters)						// that are correct and in posision
				{
					cout << "Correct! ";
					print_list(guess);
					cout << '\n';
					solved = true;
				}
				else
				{
					int cows_count = cows(guess, answer);			// calculate and report number of chars
					print_list(guess);								// that are correct but not in position
					cout << " : " << bulls_count << " bulls, ";
					cout << cows_count << " cows.\n";
				}
				guess.clear();										// reset guess
				cin.ignore(numeric_limits<streamsize>::max(), '\n');// reset cin
			}
			cout << "New puzzle created.\n";
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
}
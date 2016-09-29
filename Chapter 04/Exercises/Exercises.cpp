#include "..\..\std_lib_facilities.h"

// Simplistic calculator
void Exercise5()
{
	double first, second;
	char operation;

	while (cin >> first >> second >> operation)
	{
		switch (operation)
		{
		case ('+'):
			cout << "The sum of " << first << " and " << second << " is " << first + second << "\n";
			break;
		case ('-'):
			cout << "The difference of " << first << " and " << second << " is " << first - second << "\n";
			break;
		case ('*'):
			cout << "The product of " << first << " and " << second << " is " << first * second << "\n";
			break;
		case ('/'):
			cout << "The quotient of " << first << " and " << second << " is " << first / second << "\n";
			break;
		default:
			cout << "Unknown operation " << operation << "\n";
		}
	}
}

// Convert single digit numbers to words, and vice versa.
void Exercise6()
{
	vector<string> words;
	words.push_back("zero");
	words.push_back("one");
	words.push_back("two");
	words.push_back("three");
	words.push_back("four");
	words.push_back("five");
	words.push_back("six");
	words.push_back("seven");
	words.push_back("eight");
	words.push_back("nine");

	string input;

	while (cin >> input)
	{
		if (input.size() == 1)
		{
			int convert = stoi(input);
			cout << input << ": " << words.at(convert) << "\n";
		}
		else
		{
			for (unsigned int i = 0; i < words.size(); ++i)
			{
				if (input == words.at(i))
					cout << input << ": " << i << "\n";
			}
		}

	}
}

// Exercise7 support function
int stringToIntDigit(string input, vector<string> & words)
{
	int output;
	if (input.size() == 1)
		output = stoi(input);
	else
	{
		for (unsigned int i = 0; i < words.size(); ++i)
		{
			if (input == words.at(i))
				output = i;
		}
	}
	return output;
}

// Simplistic calculator, accepts single digits that are spelled out
void Exercise7()
{
	vector<string> words;
	words.push_back("zero");
	words.push_back("one");
	words.push_back("two");
	words.push_back("three");
	words.push_back("four");
	words.push_back("five");
	words.push_back("six");
	words.push_back("seven");
	words.push_back("eight");
	words.push_back("nine");
	
	string first, second;
	char operation;
	int convert_first, convert_second;

	while (cin >> first >> second >> operation)
	{
		convert_first = stringToIntDigit(first, words);
		convert_second = stringToIntDigit(second, words);

		switch (operation)
		{
		case ('+'):
			cout << "The sum of " << first << " and " << second << " is " << convert_first + convert_second << "\n";
			break;
		case ('-'):
			cout << "The difference of " << first << " and " << second << " is " << convert_first - convert_second << "\n";
			break;
		case ('*'):
			cout << "The product of " << first << " and " << second << " is " << convert_first * convert_second << "\n";
			break;
		case ('/'):
			cout << "The quotient of " << first << " and " << second << " is " << convert_first / convert_second << "\n";
			break;
		default:
			cout << "Unknown operation " << operation << "\n";
		}
	}
}

// Loop to double a value repeatedly
void Exercise8()
{
	int target;
	int sum = 0;
	int loop_counter = 0;
	int current = 0;

	cout << "Enter minimum amount of grain: ";
	cin >> target;

	while (sum < target)
	{
		++loop_counter;
		cout << "Square: " << loop_counter << "\t";
		if (loop_counter == 1)
			current = 1;
		else
			current *= 2;
		sum += current;
		cout << "added: " << current << "\t total: " << sum << "\n";
	}

	cout << sum << " grains of rice acquired after " << loop_counter << " squares.\n";
}

// Loop to double a value repeatedly, using types that can store more data
void Exercise9()
{
	long long curr = 0;
	long long sum = 0;
	
	for (int i = 1; i <= 64; ++i)
	{
		if (i == 1)
			curr = 1;
		else
			curr *= 2;
		sum += curr;

		cout << "Loop: " << i << " \tCurr: " << curr << " \t\tSum: " << sum << "\n";
	}
}

// A simple game of Rock Paper Scissors
void Exercise10()
{
	// Non-random AI script to play Rock Paper Scissors
	// stored as characters r, p, s respectively
	vector<char> ai;
	ai.push_back('r');	ai.push_back('s');	ai.push_back('r');	ai.push_back('p');
	ai.push_back('r');	ai.push_back('s');	ai.push_back('p');	ai.push_back('r');
	ai.push_back('r');	ai.push_back('s');	ai.push_back('s');	ai.push_back('r');
	ai.push_back('s');	ai.push_back('s');	ai.push_back('r');	ai.push_back('p');
	ai.push_back('s');	ai.push_back('p');	ai.push_back('r');	ai.push_back('r');
	ai.push_back('s');	ai.push_back('r');	ai.push_back('p');	ai.push_back('r');
	ai.push_back('s');	ai.push_back('p');	ai.push_back('r');	ai.push_back('s');
	ai.push_back('r');	ai.push_back('s');	ai.push_back('p');	ai.push_back('r');
	ai.push_back('r');	ai.push_back('p'); 	ai.push_back('s');	ai.push_back('r');
	ai.push_back('s');	ai.push_back('s');	ai.push_back('r');	ai.push_back('r');
	ai.push_back('p'); 	ai.push_back('s');	ai.push_back('s'); 	ai.push_back('p');

	int round = 0,
		win = 0,
		lose = 0,
		tie = 0;
	int max_rounds = ai.size();
	char player_input;
	char ai_input;

	cout << "Enter your play: (r)ock, (p)aper, (s)cissors: ";
	while (round < max_rounds && cin >> player_input)
	{
		ai_input = ai.at(round);
		switch (player_input)
		{
		case 'r':
			if (ai_input == 'r')
			{
				cout << "rock - rock\t tie\n";
				++tie;
			}
			else if (ai_input == 'p')
			{
				cout << "rock - paper\t loss\n";
				++lose;
			}
			else if (ai_input == 's')
			{
				cout << "rock - scissors\t win\n";
				++win;
			}
			break;
		case 'p':
			if (ai_input == 'r')
			{
				cout << "paper - rock\t win\n";
				++win;
			}
			else if (ai_input == 'p')
			{
				cout << "paper - paper\t tie\n";
				++tie;
			}
			else if (ai_input == 's')
			{
				cout << "paper - scissors\t loss\n";
				++lose;
			}
			break;
		case 's':
			if (ai_input == 'r')
			{
				cout << "scissor - rock\t loss\n";
				++lose;
			}
			else if (ai_input == 'p')
			{
				cout << "scissor - paper\t win\n";
				++win;
			}
			else if (ai_input == 's')
			{
				cout << "scissor - scissors\t tie\n";
				++tie;
			}
			break;
		default:			// invalid input, don't count round
			--round;
		}
		++round;
		cout << "Enter your play: (r)ock, (p)aper, (s)cissors: ";
	}

	cout << "\n\nAfter " << round << " rounds, your record is: \n";
	cout << win << " wins\t" << tie << " ties\t" << lose << " losses\n";

}

// Helper function for Exercises 11, 12 & 15
bool isPrime(int value, vector<int> & primes)
{
	bool prime = true;
	for (int x : primes)
	{
		if (value % x == 0)
		{
			prime = false;
			break;
		}
	}
	return prime;
}

// Find all prime numbers from 1 to 100
void Exercise11()
{
	vector<int> primes;
	primes.push_back(2);			// Set 2 as first prime number
	for (int i = 3; i <= 100; ++i)	// then check all numbers up to 100
	{
		if (isPrime(i, primes))		// When prime found...
			primes.push_back(i);	// add to list of primes
	}

	cout << "Prime numbers from 1 to 100:\n";
	for (int x : primes)
		cout << x << "\t";
	cout << endl;
}

// Find all prime numbers from 1 to inputed value
void Exercise12()
{
	cout << "Find all primes up to: ";
	int max;
	cin >> max;
	
	vector<int> primes;
	primes.push_back(2);			// Set 2 as first prime number
	for (int i = 3; i <= max; ++i)	// then check all numbers up to max
	{
		if (isPrime(i, primes))		// When prime found...
			primes.push_back(i);	// add to list of primes
	}

	cout << "Prime numbers from 1 to 100:\n";
	for (int x : primes)
		cout << x << "\t";
	cout << endl;
}

// Find all prime numbers from 1 to 100 using Sieve of Eratosthenes algorithm
void Exercise13()
{
	int max = 100;
	vector<bool> primes(max + 1);		// vector of all values from 0 to max
	for (unsigned int i = 0; i < primes.size(); ++i)
		primes.at(i) = true;

	for (unsigned int i = 2; i <= sqrt(max); ++i)
	{
		if (primes.at(i))
		{
			for (int j = i*i; j <= max; j += i)
				primes.at(j) = false;
		}
	}

	for (unsigned int i = 2; i < primes.size(); ++i)
	{
		if (primes.at(i))
			cout << i << '\t';
	}
	cout << endl;
}

// Find all prime numbers from 1 to inputed value using Sieve of Eratosthenes algorithm
void Exercise14()
{
	cout << "Find all primes up to: ";
	int max;
	cin >> max;

	vector<bool> primes(max + 1);		// vector of all values from 0 to max
	for (unsigned int i = 0; i < primes.size(); ++i)
		primes.at(i) = true;

	for (unsigned int i = 2; i <= sqrt(max); ++i)
	{
		if (primes.at(i))
		{
			for (int j = i*i; j <= max; j += i)
				primes.at(j) = false;
		}
	}

	for (unsigned int i = 2; i < primes.size(); ++i)
	{
		if (primes.at(i))
			cout << i << '\t';
	}
	cout << endl;
}

// Find the first N prime numbers
void Exercise15()
{
	cout << "How many prime numbers do you want?: ";
	unsigned int total;
	cin >> total;

	vector<int> primes;
	primes.push_back(2);

	for (unsigned int i = 3; primes.size() < total; ++i)
	{
		if (isPrime(i, primes))
			primes.push_back(i);
	}

	cout << "The first " << total << " primes are:\n";
	for (int x : primes)
		cout << x << "\t";
	cout << endl;
}

// Find the min, max and mode of a set of integers
void Exercise16()
{
	vector<int> data;
	int input;

	cout << "Enter a series of positive integers:\n";
	while (cin >> input)
		data.push_back(input);

	int min,
		max,
		mode_count = 0,
		mode_value;

	if (data.size() > 0)
	{
		min = max = mode_value = data.at(0);

		for (int x : data)
		{
			if (x < min)
				min = x;
			if (x > max)
				max = x;

			int count = 0;
			for (unsigned int i = 0; i < data.size(); ++i)
			{
				if (data.at(i) == x)
					++count;
			}
			if (count > mode_count)
			{
				mode_count = count;
				mode_value = x;
			}
		}
	}

	cout << "Minimum value: " << min << "\n"
		<< "Max value: " << max << "\n"
		<< "Mode: " << mode_value << " (repeated " << mode_count << " times)\n";
}

// Find min, max and mode of a set of strings
void Exercise17()
{
	vector<string> data;
	string input;

	cout << "Enter a series of positive integers:\n";
	while (cin >> input)
		data.push_back(input);

	string min,
		max,
		mode_value;
	int mode_count = 0;

	if (data.size() > 0)
	{
		min = max = mode_value = data.at(0);

		for (string s : data)
		{
			if (s < min)
				min = s;
			if (s > max)
				max = s;

			int count = 0;
			for (unsigned int i = 0; i < data.size(); ++i)
			{
				if (data.at(i) == s)
					++count;
			}
			if (count > mode_count)
			{
				mode_count = count;
				mode_value = s;
			}
		}
	}

	cout << "Minimum value: " << min << "\n"
		<< "Max value: " << max << "\n"
		<< "Mode: " << mode_value << " (repeated " << mode_count << " times)\n";

}

// Solve quadratic equation
void Exercise18()
{
	cout << "Quadratic Equation: 0 = ax^2 + bx + c\n"
		<< "Enter the values for a, b, and c:\n";
	double a, b, c,
		x1, x2;

	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "c = ";
	cin >> c;

	x1 = ((-1 * b) + sqrt(b*b - (4 * a * c))) / (2 * a);
	x2 = ((-1 * b) - sqrt(b*b - (4 * a * c))) / (2 * a);

	cout << "Solution: x = " << x1 << " and " << x2 << "\n";
}

// Read and display list of names and scores
void Exercise19()
{
	vector<string> names;
	vector<int> scores;

	string name_input;
	int score_input;
	bool duplicate = false;

	while (cin >> name_input >> score_input)
	{
		if (name_input == "NoName" && score_input == 0)
			break;

		// check for dupelicate names
		duplicate = false;
		for (string s : names)
		{
			if (s == name_input)
				duplicate = true;
		}		

		if (duplicate)
			cout << name_input << " already exists, score not added.\n";
		else
		{
			names.push_back(name_input);
			scores.push_back(score_input);
		}
	}

	// print all names and scores
	for (unsigned int i = 0; i < names.size(); ++i)
		cout << names.at(i) << ", " << scores.at(i) << "\n";
}

// Read and store a list of names and scores. Search by name to retrieve score.
void Exercise20()
{
	vector<string> names;
	vector<int> scores;

	string name_input;
	int score_input;
	bool exists = false;

	cout << "Enter name and score (Ex: Bob 25)\n"
		<< "Terminate input with NoName 0\n";
	while (cin >> name_input >> score_input)
	{
		if (name_input == "NoName" && score_input == 0)
			break;

		// check for dupelicate names
		exists = false;
		for (string s : names)
		{
			if (s == name_input)
				exists = true;
		}

		if (exists)
			cout << name_input << " already exists, score not added.\n";
		else
		{
			names.push_back(name_input);
			scores.push_back(score_input);
		}
	}

	cout << "Lookup via name: ";
	while (cin >> name_input)
	{
		exists = false;
		for (unsigned int i = 0; i < names.size(); ++i)
		{
			if (names.at(i) == name_input)
			{
				cout << names.at(i) << ", " << scores.at(i) << "\n";
				exists = true;
			}
		}

		if (!exists)
			cout << "Name not found: " << name_input << ".\n";
	}
}

// Read and store a list of names and scores. Search by score to retrieve names.
void Exercise21()
{
	vector<string> names;
	vector<int> scores;

	string name_input;
	int score_input;
	bool exists = false;

	cout << "Enter name and score (Ex: Bob 25)\n"
		<< "Terminate input with NoName 0\n";
	while (cin >> name_input >> score_input)
	{
		if (name_input == "NoName" && score_input == 0)
			break;

		// check for dupelicate names
		exists = false;
		for (string s : names)
		{
			if (s == name_input)
				exists = true;
		}

		if (exists)
			cout << name_input << " already exists, score not added.\n";
		else
		{
			names.push_back(name_input);
			scores.push_back(score_input);
		}
	}

	cout << "Lookup via score: ";
	while (cin >> score_input)
	{
		exists = false;
		for (unsigned int i = 0; i < scores.size(); ++i)
		{
			if (scores.at(i) == score_input)
			{
				cout << names.at(i) << ", " << scores.at(i) << "\n";
				exists = true;
			}
		}
		if (!exists)
			cout << "Name not found: " << name_input << ".\n";
	}
}


int main()
{
//	ExerciseX();
	return 0;
}
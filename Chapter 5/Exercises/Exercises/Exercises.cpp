// Exercises.cpp
// Chapter 5 Exercises (p.169)

#include "../../../std_lib_facilities.h"

// Helper function for Exercise 2 & 3
double ctok(double c)	// converts Celcius to Kelvin
{
	double k = c + 273.15;
	return k;
}

// Fix code to convert temp from Celcius to Kelvin
void Exercise2()
{
	double c = 0;			// declare input variable
	cin >> c;				// retrieve temperature to input variable
	double k = ctok(c);		// convert temperature

	cout << k << '\n';		// print out temperature
}

// Fix code to convert temp from Celcius to Kelvin, validate before calling ctok()
void Exercise3()
{
	try
	{
		constexpr double absolute_zero = -273.15; // absolute value in celcius

		double c = 0;			// declare input variable
		cin >> c;				// retrieve temperature to input variable
		if (c < absolute_zero)	// and validate
			error("bad call to ctok()");

		double k = ctok(c);		// convert temperature
		cout << k << '\n';		// print out temperature
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << '\n';
	}
	catch (...)
	{
		cerr << "unknown error\n";
	}
}

// Helper function for Exercise 4
double ctok2(double c)	// converts Celcius to Kelvin
{
	constexpr double absolute_zero = -273.15;	// absolute zero in C
	if (c < absolute_zero)						// validate argument
		error("bad argument for ctok2()");

	double k = c + 273.15;
	return k;
}

// Fix code to convert temp from Celcius to Kelvin, validate within ctok2()
void Exercise4()
{
	try
	{
		double c = 0;			// declare input variable
		cin >> c;				// retrieve temperature to input variable
		double k = ctok2(c);	// convert temperature
		cout << k << '\n';
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << '\n';
	}
	catch (...)
	{
		cerr << "unknown error\n";
	}
}

// Helper function for Exercise 5
double ktoc2(double k)
{
	constexpr double absolute_zero = 0.0;		// absolute zero in K
	if (k < absolute_zero)
		error("bad argument for ktoc2()");

	double c = k - 273.15;
	return c;
}

// Add to prior exercise so it can convert from Kelvin to Celcius
void Exercise5()
{
	try
	{
		cout << "Convert between Celcius and Kelvin.\n" 
			<< "Enter both temperature and unit (ex: 38.5 c)\n";
		double temp_value,
			temp_converted;
		char temp_unit;
		while (cin >> temp_value >> temp_unit)
		{
			switch (temp_unit) 
			{
			case ('c'):			// convert celcius to kelvin
			case ('C'):		
				temp_converted = ctok2(temp_value);
				cout << temp_value << " C = " << temp_converted << " K\n";
				break;
			case ('k'):			// convert kelvin to celcius
			case ('K'): 
				temp_converted = ktoc2(temp_value);
				cout << temp_value << " K = " << temp_converted << " C\n";
				break;
			default:
				cout << "Unknown unit " << temp_unit << '\n';
			}
		}
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << '\n';
	}
	catch (...)
	{
		cerr << "unkonwn error\n";
	}
}

// convert from Fahrenheit to Celcius
double ftoc(double f)
// argument not less than absolute zero
{
	constexpr double absolute_zero = -459.67;		// absolute zero in F
	if (f < absolute_zero)
		error("bad argument to ftoc()");

	double c = (f - 32) / 1.8;
	return c;
}

// convert Celcius to Fahrenheit
double ctof(double c)
// argument not less than absolute zero
{
	constexpr double absolute_zero = -273.15;	// absolute zero in C
	if (c < absolute_zero)
		error("bad argument for ctof()");

	double f = 1.8 * c + 32;
	return f;
}

// Convert temperature between Celcius and Fahrenheit
void Exercise6()
{
	try
	{
		cout << "Convert between Celcius and Fahrenheit.\n"
			<< "Enter both temperature and unit (ex: 38.5 c)\n";
		double temp_value,
			temp_converted;
		char temp_unit;
		while (cin >> temp_value >> temp_unit)
		{
			switch (temp_unit)
			{
			case ('c'):			// convert celcius to fahrenheit
			case ('C'):
				temp_converted = ctof(temp_value);
				cout << temp_value << " C = " << temp_converted << " F\n";
				break;
			case ('f'):			// convert fahrenheit to celcius
			case ('F'):
				temp_converted = ftoc(temp_value);
				cout << temp_value << " F = " << temp_converted << " C\n";
				break;
			default:
				cout << "Unknown unit " << temp_unit << '\n';
			}
		}
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << '\n';
	}
	catch (...)
	{
		cerr << "unkonwn error\n";
	}
}

// Helper function for Exercise 7
bool validate_coefficients(double a, double b, double c)
{
	bool is_valid = true;
	if (a == 0)					// a cannot be zero, would result in divide by zero
		is_valid = false;
	if (b*b - (4 * a * c) < 0)  // negative result leads to imaginary numbers
		is_valid = false;
	return is_valid;
}

// Solve quadratic equation. Report error if coefficients are invalid or result in imaginary numbers
void Exercise7()
{
	double a, b, c,		// coefficents
		x1,		// answers
		x2;		

	cout << "Quadratic Equations form: 0 = ax^2 + bx + c\n"
		<< "Enter each coefficient:\n";
	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;
	cout << "c = "; cin >> c;

	// x = ( -b +- sqrt( b^2 - 4ac) ) / 2a
	if (!validate_coefficients(a, b, c))
		cout << "Invalid coefficients: " << a << ", " << b << ", " << c << '\n';
	else
	{
		x1 = (-1 * b + sqrt(b*b - (4 * a * c))) / (2 * a);
		x2 = (-1 * b - sqrt(b*b - (4 * a * c))) / (2 * a);
		cout << "x = " << x1 << ", " << x2 << '\n';
	}
}

// Request a list of numbers and print sum for first N values.
void Exercise8()
{
	try
	{
		cout << "Enter the number of values to sum: ";
		unsigned int count = 0;
		cin >> count;

		cout << "Enter some integers (or | to stop):\n";
		vector<int> data;
		int input;
		while (cin >> input && input != '|')
			data.push_back(input);

		if (count > data.size())
			error("not enough values to sum\n");

		int sum = 0;
		for (unsigned int i = 0; i < count; ++i)
			sum += data.at(i);

		cout << "Sum of first " << count << " values: " << sum << '\n';
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << '\n';
	}
}

// Modify Exercise 8 to report error if sum can't be represented as an int
// Used Stroustrup method to detect overflow (if current sum < previous sum)
// Not fully reliable, possible to add a value that overflows it then add enough to still be bigger?
void Exercise9()
{
	try
	{
		cout << "Enter the number of values to sum: ";
		unsigned int count = 0;
		cin >> count;

		cout << "Enter some integers (or | to stop):\n";
		vector<int> data;
		int input;
		while (cin >> input && input != '|')
			data.push_back(input);

		if (count > data.size())
			error("not enough values to sum\n");

		int sum = 0;
		int prior_sum;
		for (unsigned int i = 0; i < count; ++i)
		{
			prior_sum = sum;
			sum += data.at(i);

			if (prior_sum > sum)
				error("sum too large for int");
		}

		cout << "Sum of first " << count << " values: " << sum << '\n';
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << '\n';
	}

}

// Skipped
void Exercise10()
{


}

// Print the first N values of Fibonacci series
// Integer overflow begins at element #47. Correct: 2971215073, calculated: -1323752223
void Exercise11()
{
	try 
	{
		cout << "How many Fibonacci numbers should be printed? ";
		int count;
		cin >> count;
		if (count < 0) error("Number must be positive.\n");
	
		// Sequence beginning
		int prev = 1,
			curr = 1,
			temp;

		cout << prev << ' ' << curr << ' ';

		for (int i = 2; i < count; i++)
		{
			temp = curr;
			curr += prev;
			prev = temp;
			cout << curr << ' ';
		}
		cout << '\n';
	}
	catch (exception e)
	{
		cerr << "error: " << e.what() << '\n';
	}
}

// Stroustrup version from http://stroustrup.com/Programming/Solutions/Ch5/e5-10.cpp
// Notes:
// This version uses the same logic to increment the current value
// It skips the initial 1 1 start
// It detects int overflow via while (n < m)
// Once m overflows, it becomes a megative so the condition is no longer true
// Then it prints the prior value as thie highest that fits into an int
void Exercise11a()
{
	try 
	{
		int n = 1;
		int m = 2;

		while (n < m)
		{
			cout << n << '\n';	
			int x = n + m;
			n = m;		// drop the lowest number
			m = x;		// add a new highest number
		}

		cout << "the largest Fibonacci number that fits in an int is " << n << '\n';
	
	}
	catch (runtime_error e)
	{
		cerr << e.what() << '\n';
	}

}

// Return number of digits in which both value and position are correct
// Support function for exercise 12 + 13
int bulls(vector<int>& guess, vector<int>& answer)
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
int cows(vector<int>& guess, vector<int>& answer)
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

// Separate a 4 digit number into it's component digits
// If only 3 digits provided, treat as though leading zero (ex: 123 -> 0123)
vector<int> separate_digits(int guess)
{
	if (guess < 100 || guess > 9999)
		error("guess must contain 4 digits");

	int n = 0;
	vector<int> v;
	
	v.push_back(guess / 1000);		// store thousands digit	x _ _ _
	
	if (guess < 1000)				// if guess begins with 0, pad thousands digit
		n = (guess + 1000) % 1000;	// so next % operation works properly
	
	n = guess % 1000;				// drop thousands digit		- _ _ _
	v.push_back(n / 100);			// store hundreds digit		- x _ _
	n = n % 100;					// drop hundreds digit		- - _ _
	v.push_back(n / 10);			// store tens digit			- - x _
	n = n % 10;						// drop tend digit			- - - _
	v.push_back(n);					// store ones digit			- - - x

	return v;
}

// Print all ints in vector
void print_list(vector<int>& v)
{
	for (int x : v)
		cout << x;
}

// Returns true if an integer listed more than once
bool duplicates(vector<int>& v)
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
bool find_int(int n, vector<int>& answer)
{
	bool found = false;
	for (unsigned int i = 0; i < answer.size(); ++i)
	{
		if (n == answer[i])
			found = true;
	}
	return found;
}

// Bulls and Cows number guessing game
void Exercise12()
{
	try
	{
		constexpr int num_digits = 4;	// set number of digits

		vector<int> answer;				// hard-code arbitrary answer
		answer.push_back(5);			
		answer.push_back(8);
		answer.push_back(2);
		answer.push_back(1);

		bool solved = false;
		while (!solved)
		{

			int i_guess;
			cout << "Enter four-digit guess: ";
			if (!(cin >> i_guess))
				error("guess can only contain integers");
			
			vector<int> guess;
			guess = separate_digits(i_guess);
			if (duplicates(guess))
				error("guess cannot contain duplicate digits");

			int bulls_count = bulls(guess, answer);
			if (bulls_count == num_digits)
			{
				cout << "Correct! ";
				print_list(guess);
				cout << '\n';
				solved = true;
			}
			else
			{
				int cows_count = cows(guess, answer);
				print_list(guess);
				cout << " : " << bulls_count << " bulls, ";
				cout << cows_count << " cows.\n";
			}
		}
	}
	catch (runtime_error& e)
	{
		cerr << "error: " << e.what() << '\n';
	}
	catch (...)
	{
		cerr << "error: unknown error\n";
	}
}

// Modify Exercise to generate random digits for the answer
// Note: seed_randint() does not exist in std_lib_facilities.h, so same
// puzzles each time game is loaded
void Exercise13()
{
	try
	{
		constexpr int num_digits = 4;	// set number of digits

		while (true)					// game loop, continues forever until user quits
		{
			vector<int> answer;			// set of answers
			while (answer.size() < num_digits)		// add digits randomly to answer
			{
				int candidate = randint(9);		
				if (!find_int(candidate, answer))	// check for dupes, add if unique
					answer.push_back(candidate);
			}

			bool solved = false;
			while (!solved)
			{
				int i_guess;
				cout << "Enter four-digit guess:\n";
				if (!(cin >> i_guess))
					error("guess can only contain integers");

				vector<int> guess;
				guess = separate_digits(i_guess);
				if (duplicates(guess))
					error("guess cannot contain duplicate digits");

				int bulls_count = bulls(guess, answer);
				if (bulls_count == num_digits)
				{
					cout << "Correct! ";
					print_list(guess);
					cout << '\n';
					solved = true;
				}
				else
				{
					int cows_count = cows(guess, answer);
					print_list(guess);
					cout << " : " << bulls_count << " bulls, ";
					cout << cows_count << " cows.\n";
				}
			}
			cout << "New puzzle created.\n";
		}
	}
	catch (runtime_error& e)
	{
		cerr << "error: " << e.what() << '\n';
	}
	catch (...)
	{
		cerr << "error: unknown error\n";
	}
}


bool alt_names(vector<string> day, string input)
{
	bool name_found = false;
	for (string s : day)
	{
		if (s == input)
			name_found = true;
	}
	return name_found;
}

// Helper function for Exercise 14
void print_days(string day, vector<int> values)
{
	int sum = 0;
	cout << day << "    \t";

	for (int x : values)		// sum values
		sum += x;

	cout << "Total: " << sum << '\t';

	for (int x : values)		// print values
		cout << x << ' ';
	cout << '\n';
}

// Read in Day-Total values and store in vectors
// Sum and print values for each day of the week
void Exercise14()
{
	try
	{
		vector<int> monday;
		vector<int> tuesday;
		vector<int> wednesday;
		vector<int> thursday;
		vector<int> friday;
		vector<int> saturday;
		vector<int> sunday;

		// Setup alternate spellings for days of the week
		// Manual added due to lack of vector initialization in MS Visual Studio
		vector<string> monday_strings;				
		monday_strings.push_back("Monday");	monday_strings.push_back("monday");
		monday_strings.push_back("Mon"); monday_strings.push_back("mon");

		vector<string> tuesday_strings;
		tuesday_strings.push_back("Tuesday"); tuesday_strings.push_back("tuesday");
		tuesday_strings.push_back("Tues"); tuesday_strings.push_back("tues");
		tuesday_strings.push_back("Tue"); tuesday_strings.push_back("tue");
		tuesday_strings.push_back("Tu"); tuesday_strings.push_back("tu");

		vector<string> wednesday_strings;
		wednesday_strings.push_back("Wednesday"); wednesday_strings.push_back("wednesday");
		wednesday_strings.push_back("Wed"); wednesday_strings.push_back("wed");

		vector<string> thursday_strings;
		thursday_strings.push_back("Thursday");	thursday_strings.push_back("thursday");
		thursday_strings.push_back("Thurs"); thursday_strings.push_back("thurs");
		thursday_strings.push_back("Thur");	thursday_strings.push_back("thur");
		thursday_strings.push_back("Thu"); thursday_strings.push_back("thu");
		thursday_strings.push_back("Th"); thursday_strings.push_back("th");

		vector<string> friday_strings;
		friday_strings.push_back("Friday");	friday_strings.push_back("friday");
		friday_strings.push_back("Fri"); friday_strings.push_back("fri");

		vector<string> saturday_strings;
		saturday_strings.push_back("Saturday");	saturday_strings.push_back("saturday");
		saturday_strings.push_back("Sat");	saturday_strings.push_back("sat");

		vector<string> sunday_strings;
		sunday_strings.push_back("Sunday"); sunday_strings.push_back("sunday");
		sunday_strings.push_back("Sun"); sunday_strings.push_back("sun");

		cout << "Enter Day and Value (ex: Monday 25):\n";

		string day_name = "";
		int day_value = 0;
		int rejected = 0;
		while (cin >> day_name >> day_value)
		{
			if (alt_names(monday_strings, day_name))
				monday.push_back(day_value);
			else if (alt_names(tuesday_strings, day_name))
				tuesday.push_back(day_value);
			else if (alt_names(wednesday_strings, day_name))
				wednesday.push_back(day_value);
			else if (alt_names(thursday_strings, day_name))
				thursday.push_back(day_value);
			else if (alt_names(friday_strings, day_name))
				friday.push_back(day_value);
			else if (alt_names(saturday_strings, day_name))
				saturday.push_back(day_value);
			else if (alt_names(sunday_strings, day_name))
				sunday.push_back(day_value);
			else
			{
				cout << "Invalid day: " << day_name << '\n';
				++rejected;
			}
		}

		// Print out total for each day
		print_days("Monday", monday);
		print_days("Tuesday", tuesday);
		print_days("Wednesday", wednesday);
		print_days("Thursday", thursday);
		print_days("Friday", friday);
		print_days("Saturday", saturday);
		print_days("Sunday", sunday);
		cout << '\n';
		cout << rejected << " value(s) rejected due to invalid day name.\n";

	}
	catch (runtime_error& e)
	{
		cerr << "error: " << e.what() << '\n';
	}
	catch (...)
	{
		cerr << "unknown error\n";
	}
}


int main()
{
	Exercise14();

	return 0;
}
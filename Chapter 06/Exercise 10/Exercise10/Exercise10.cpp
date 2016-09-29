// Exercise10.cpp
// Chapter 6 exercise (p.219)
// Calculate the number of permutations or combinations
// Mostly complete. Does not check for overflow on big numbers

#include "../../../std_lib_facilities.h"


// display prompt and read number input
int64_t input_number(string prompt)
{
	cout << prompt;			// print prompt
	int64_t in = 0;
	if (!(cin >> in))
		error("expected integer value");
	return in;
}

// display prompt and read char input
char input_perm_comb(string prompt)
{
	cout << prompt;			// print prompt
	char ch;
	cin >> ch;
	if (ch == 'p' || ch == 'c')
		return ch;
}

int64_t calc_permutations(int64_t n, int64_t k)
{
	int64_t perm = 1;
	for (int64_t i = n; i > n-k; --i)
		perm *= i;
	return perm;
}
int64_t factorial(int64_t n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return 1;
	return n * factorial(n - 1);
}


int main()
{
	try
	{
		cout << "Calculate number of Permutations and Combinations.\n\n";

		int64_t n = 1,
				k = 1;
		n = input_number("Enter total number of options: ");
		k = input_number("Enter number of choices: ");

		while (!(0 <= k && k <= n))
		{
			cout << "invalid: values must be >= 0, options >= choices.\n";
			n = input_number("Enter total number of options: ");
			k = input_number("Enter number of choices: ");
		}

		char selection = input_perm_comb("Select (p)ermutation or (c)ombination: ");
		while (selection != 'p' && selection != 'c')
		{
			cout << "invalid: enter p for permutation or c for combination.\n";
			selection = input_perm_comb("Select (p)ermutation or (c)ombination: ");
		}

		int64_t permutations = calc_permutations(n, k);

		switch (selection)
		{
		case 'p':
			cout << "P(" << n << "," << k << ") = " << permutations << '\n';
			break;
		case 'c':
			int64_t combinations = calc_permutations(n, k) / factorial(k);
			cout << "C(" << n << "," << k << ") = " << combinations << '\n';
			break;
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
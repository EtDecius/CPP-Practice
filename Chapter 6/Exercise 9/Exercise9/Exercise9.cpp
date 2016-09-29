// Exercise9.cpp
// Chapter 6 exercise (p.219)
// Write program that reads digits and composes them into integers


#include "../../../std_lib_facilities.h"

bool is_whitespace(char c)
{
	switch (c)	{
	case ' ': case '\t': case '\n':
	case '\v': case '\f': case '\r':
		return true;
	default:
		return false;
	}
}

// compose vector of char digits into a single int
int compose_ints(vector<char> v)
{
	int total = 0;
	int place_factor = 1;
	for (int i = v.size() -1 ; i >= 0; --i)
	{
		total += place_factor * (v[i] - '0');
		place_factor *= 10;
	}
	return total;
}

vector<string> digit_place_names(int num_digits)
{
	vector<string> v;
	if (num_digits > 13) error("set_place_names() cannot exceed trillions");

	switch (num_digits)
	{
	case 13:	v.push_back("trillions");
	case 12:	v.push_back("hundred billions");
	case 11:	v.push_back("ten billions");
	case 10:	v.push_back("billions");
	case 9:		v.push_back("hundred millions");
	case 8:		v.push_back("ten millions");
	case 7:		v.push_back("millions");
	case 6:		v.push_back("hundred thousands");
	case 5:		v.push_back("ten thousands");
	case 4:		v.push_back("thousands");
	case 3:		v.push_back("hundreds");
	case 2:		v.push_back("tens");
	case 1:		v.push_back("ones");
	default:	break;
	}
	return v;
}

int main()
{
	try {

		constexpr int max_size = 4;
		vector<char> list;
		char ch;

		// read in digits and add to list. ignore whitespaces
		cout << "Enter up to 4 digits on single line: ";
		while (cin.get(ch) && list.size() < max_size)
		{
			if (ch == '\n')
				break;
			if (is_whitespace(ch))
			{	// do not process spaces
			}
			else if (ch < '0' || ch > '9')
				cout << "invalid digit: " << ch << '\n';
			else
				list.push_back(ch);
		}

		// compose chars into a single int value
		int solution = compose_ints(list);
		cout << solution << " is ";

		// generate digit place names to match size list size, and print results
		vector<string> digit_place = digit_place_names(list.size());
		for (int i = 0; i < list.size(); ++i)
		{
			cout << list[i] << " " << digit_place[i];
			if (i != list.size() - 1)
				cout << " and ";
		}
		cout << '\n';
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
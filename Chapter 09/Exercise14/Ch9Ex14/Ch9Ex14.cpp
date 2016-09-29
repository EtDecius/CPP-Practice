// Ch9Ex14.cpp
// Chapter 9, Exercise 14 (p.341)
// Design and implement Money class to handle currency

#include "../../../std_lib_facilities.h"

// generic representation of money with a specified decimal precision
class Money {
public:
	Money(double n);	// convert to value with 
	double val();		// amount with rounding
	Money precise_val() const { return amount; }; // amount without rounding
private:
	static const int precision_digits = 4;	// number decimal places to calculate
	static const int display_digits = 2;	// number decimal places to display

	long amount;		// original amount scaled up to accomidate decimal precision
	int scale_factor;	// = 10 ^ precision_digits 
	int display_factor;	// decimal distance between precision and display, then scaled
	int round_factor;	// decimal place of rounding digit, then scaled

	long round();		// round to appropriate decimal place
};

// constructor
Money::Money(double n)
{
	if (display_digits > precision_digits) error("Money() cannot display more decimal places calculated");

	// scale original amount up to accomodate additional decimal precision
	scale_factor = pow(10, precision_digits);
	amount = n * scale_factor;

	// decimal location of rounding digit, scaled up for modulo use
	display_factor = pow(10, precision_digits - display_digits);
	round_factor = display_factor / 10;
}


// round down at 4, up at 5
long Money::round()
{
	int leftovers = amount % display_factor;		// amount to be rounded away
	int rounding_digit = leftovers / round_factor;	// leading digit of leftovers

	amount -= leftovers;
	if (rounding_digit >= 5)
		amount += display_factor;

	return amount;
}

// return value rounded to appropriate decimal place
double Money::val()
{
	double d = double(round()) / scale_factor;
	return d;
}

Money operator+(const Money& m1, const Money& m2)
{
	return Money{ m1.precise_val() + m2.precise_val() };
}


ostream& operator<<(ostream& os, Money m)
{
	return os << m.val();
}




int main()
try {
	double t1 = 1234.00;
	double t2 = 1.07830;
	double t3 = 500.0328;

	Money test1{ t1 };
	Money test2{ t2 };
	Money test3{ t3 };

	cout << t1 + t3 << endl;

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
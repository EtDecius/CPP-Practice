// Ch9ex123.cpp
// Chapter 9, Exercise 13 (p.340)
// Design and implement Rational number class
// Supports:
//		basic arithmetic: +  -  *  /
//		comparisons: ==  != 
//		iostream: <<  >>
//		converstion: to_double()
// Invoke via: Rational{ numerator, denominator };

#include "../../../std_lib_facilities.h"

// useful math functions
bool is_negative(int n) { return (n < 0) ? true : false; }

// from wikipedia.org: Binary_GCD_algorithm
int greatest_common_divisor(int u, int v)
{
	u = abs(u);
	v = abs(v);
	
	// termination cases
	if (u == v)	return u;
	if (u == 0) return u;
	if (v == 0) return v;

	// look for factors of 2
	if (~u & 1)	// u is even
	{
		if (v & 1)	// v is odd
			return greatest_common_divisor(u >> 1, v);
		else   // both are even
			return greatest_common_divisor(u >> 1, v >> 1) << 1;
	}

	if (~v & 1)		// u is odd, v is even
		return greatest_common_divisor(u, v >> 1);

	// reduce larger argument
	if (u > v)
		return greatest_common_divisor((u - v) >> 1, v);

	return greatest_common_divisor((v - u) >> 1, u);
}


// *****************************
// * class & member functions  *
// *****************************

class Rational
{
public:
	Rational(int numerator, int denominator);			// constructor
	int numerator() const { return top; }
	int denominator() const { return bottom; }
	void simplify();									// simpify terms, handle negative signs
	friend istream& operator >> (istream& is, Rational& r);

private:
	int top;
	int bottom;
};

// constructor
Rational::Rational(int numerator, int denominator)
	: top{ numerator }, bottom{ denominator }
{
	if (bottom == 0) error("Rational() denominator cannot be 0");
}

// reduce to lowest terms, handle negative symbols
void Rational::simplify()
{
	// let numerator carry negative symbol when appropriate
	if (is_negative(bottom))
	{							
		top *= -1;			// multiply by -1/-1
		bottom *= -1;		// to ensure bot is positive
	}

	// reduce to lowest terms
	int gcd = greatest_common_divisor(top, bottom);
	if (gcd > 1)			
	{
		top /= gcd;
		bottom /= gcd;
	}
}

// *****************************
// *     helper functions      *
// *****************************

// true if identical terms or reduce to same fraction
bool operator==(const Rational& left, const Rational& right)
{
	// check for matching values
	if (left.numerator() == right.numerator() &&
		left.denominator() == right.denominator())
		return true;

	// more involved check, create copies and simplify terms
	Rational l = left;
	l.simplify();

	Rational r = right;
	r.simplify();
	
	if (l.numerator() == r.numerator() &&
		l.denominator() == r.denominator())
		return true;

	return false;
}

bool operator!=(const Rational& left, const Rational& right)
{
	return !(left == right);
}

// add
Rational operator+(const Rational& left, const Rational& right)
{
	// formula: a/b + c/d = ad/bd + bc/bd = (ad + bc)/bd
	int num, denom;
	if (left.denominator() == right.denominator())    // shared denominator
	{
		
		num = left.numerator() + right.numerator();   
		denom = left.denominator();
	}
	else    // multiply to get common denominator, then add
	{
		num = (left.numerator() * right.denominator()) + (left.denominator() * right.numerator());
		denom = left.denominator() * right.denominator();
	}
	
	Rational r{ num,denom };
	r.simplify();
	return r;
}

// subtract
Rational operator-(const Rational& left, const Rational& right)
{
	// formula: a/b + c/d = ad/bd - bc/bd = (ad - bc)/bd
	int num, denom;
	if (left.denominator() == right.denominator())	// shared denominator
	{
		num = left.numerator() - right.numerator();
		denom = left.denominator();
	}
	else    // multiply to get common denominator, then subtract
	{
		num = (left.numerator() * right.denominator()) - (left.denominator() * right.numerator());
		denom = left.denominator() * right.denominator();
	}

	Rational r{ num, denom };
	r.simplify();
	return r;
}

// multiply
Rational operator*(const Rational& left, const Rational& right)
{
	// formula: a/b * c/d = ac/bd
	Rational r{ left.numerator() * right.numerator(),		// numerator
			    left.denominator() * right.denominator() };	// denominator
	r.simplify();
	return r;
}

// divide
Rational operator/(const Rational& left, const Rational& right)
{
	// formula: a/b / c/d = ad/bc
	Rational r{ left.numerator() * right.denominator(),		// numerator
				left.denominator() * right.numerator() };	// denominator
	r.simplify();
	return r;
}

// print to ostream
ostream& operator<<(ostream& os, const Rational& r)
{
	return os << r.numerator() << '/' << r.denominator();
}

// read istream input and create object
istream& operator>> (istream& is, Rational& r)
{
	int num, denom;
	char slash;
	is >> num >> slash >> denom;

	if (slash != '/') error(">> invalid symbol (expected / ): " + slash);
	r.top = num;
	r.bottom = denom;
	return is;
}

// convert fraction to decimal value
double to_double(Rational& r)
{
	return double(r.numerator()) / r.denominator();
}

int main()
try {
	Rational bb{ -4,5 };
	Rational cc{ 4,-5 };

	if (bb == cc)
		cout << "same\n";
	else
		cout << "not same\n";

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
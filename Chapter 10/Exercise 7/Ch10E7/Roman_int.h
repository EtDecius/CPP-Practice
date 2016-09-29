// Roman_int.h
// Roman_int class represents Roman Numerals

#ifndef _ROMAN_INT_H
#define _ROMAN_INT_H

#include <string>
#include "Roman_digit.h"

class Roman_int
{
public:
	Roman_int();
	Roman_int(int n);								// constructor given int
	Roman_int(std::string s);						// constructor given Roman numeral

	// operators
	Roman_int& operator=(const Roman_int& ri);		// assignment operator
	Roman_int& operator+=(const Roman_int& ri);
	Roman_int& operator-=(const Roman_int& ri);
	Roman_int& operator*=(const Roman_int& ri);
	Roman_int& operator/=(const Roman_int& ri);


	std::string roman() const { return numeral; }	// return value as Roman numeral
	int integer() const { return value; }			// return value as integer

private:
	int value;
	std::string numeral;
};

// overloaded operators
ostream& operator<<(ostream& os, const Roman_int& ri);
istream& operator>>(istream& is, Roman_int& ri);

Roman_int operator+(const Roman_int& ri1, const Roman_int& ri2);
Roman_int operator-(const Roman_int& ri1, const Roman_int& ri2);
Roman_int operator*(const Roman_int& ri1, const Roman_int& ri2);
Roman_int operator/(const Roman_int& ri1, const Roman_int& ri2);


#endif
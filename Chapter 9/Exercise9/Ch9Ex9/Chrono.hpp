// Chrono.hpp
// Implements Date class to represent calender dates
#pragma once

#include <iostream>
#include "../../../std_lib_facilities.h"

namespace Chrono {

	enum class Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date {
	public:
		class Invalid {};				// to throw as exception

		Date(int y, Month m, int d);	// check for valid date and initialize
		Date();							// default constructor
		// default copy operations are fine

		// nonmodifying operations
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }

		// modifying operations
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

	private:
		int y;
		Month m;
		int d;
	};

	int days_in_month(int y, Month m);		// number days per on month
	bool is_date(int y, Month m, int d);	// true for valid date
	bool leapyear(int y);					// true if y is leap year

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	std::ostream& operator<<(std::ostream& os, const Date& d);
	std::istream& operator>>(std::istream& is, Date& dd);


//	Day day_of_week(const Date& d);
//	Date next_Sunday(const Date& d);
//	Date next_weekday(const Date& d);

};
// Chrono.cpp
// Implementation for Date class to represent caldendar dates

#include "Chrono.hpp"

namespace Chrono {
	
	// forward declarations
	Month operator++(Month& m);

	// member function definitions

	Date::Date(int yy, Month mm, int dd)
		: y{ yy }, m{ mm }, d{ dd }
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date& default_date()
	{
		static Date dd{ 2001, Month::jan, 1 };
		return dd;
	}

	Date::Date()
		:y{ default_date().year() },
		m{ default_date().month() },
		d{ default_date().day() }
	{
	}

	// increase day by specified amount
	void Date::add_day(int n)
	{
		if (n < 0) error("add_day() cannot add negative days");

		while (d + n > days_in_month(y, m))		// when added days eclipse current month
		{
			n -= days_in_month(y, m);			// reduce remaining days
			if (m == Month::dec)
				++y;
			++m;
		}
		d += n;									// leftover days fit in month
	}

	// increase month by specified amount
	// note: truncate days to fit destination month (mar 31 + 1 month -> apr 30)
	void Date::add_month(int n)
	{
		if (n < 0) error("add_month() cannot add negative months");
		
		add_year(n / 12);			// handle excess years
		int months = n % 12;		// remaining months to add
		if (n + int(m) > 12)		// handle dec -> jan rollover
		{
			m = Month(int(m) + n - 12);
			add_year(1);
		}
		else
			m = Month(int(m) + n);

		if (d > days_in_month(y, m))	// handle new month with fewer days than start
			d = days_in_month(y, m);	// set to last day of month
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y+n)) 
		{
			m = Month::mar;
			d = 1;
		}
		y += n;
	}

	// helper functions

	// return number of days per month, includes leapyears
	int days_in_month(int y, Month m)
	{
		int num_days = 31;
		switch (m)
		{
		case Month::feb:
			num_days = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr:
		case Month::jun:
		case Month::sep:
		case Month::nov:
			num_days = 30;
			break;
		}
		return num_days;
	}

	bool is_date(int y, Month m, int d)
	{
		// assume that y is valid
		if (d <= 0) return false;					// d must be positive
		if (m < Month::jan || Month::dec < m) return false;

		if (days_in_month(y,m) < d) return false;

		return true;
	}


	bool leapyear(int y)
	{
		// every 4 years except when ends in xx00, in which case only x400 is leap year	
		return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
	}

	
	Month operator++(Month& m)
	{
		m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
		return m;
	}

	Month operator--(Month& m)
	{
		m = (m == Month::jan) ? Month::dec : Month(int(m) - 1);
		return m;
	}

	std::ostream& operator<<(std::ostream& os, const Month& m)
	{
		return os << int(m);
	}



	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << d.month()
			<< ',' << d.day() << ')';
	}

	std::istream& operator >> (std::istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')	// oops: format error
		{
			is.clear(std::ios_base::failbit);						// set the fail bit
			return is;
		}
		dd = Date(y, Month(m), d);		// update dd
		return is;
	}

	enum class Day {
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};


/*
	Day day_of_week(const Date& d)
	{
		// not implemented
	}

	Date next_Sunday(const Date& d)
	{
		// not implemented
	}

	Date next_weekday(const Date& d)
	{
		// not implemented
	}
	*/

}
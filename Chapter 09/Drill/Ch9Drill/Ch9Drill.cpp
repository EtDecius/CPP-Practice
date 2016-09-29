// Ch9Drill.cpp
// Chapter 9 Drills (p.338)

#include "../../../std_lib_facilities.h"

// 9.4.1 implementation 
/* struct Date {
	int y;		// year
	int m;		// month
	int d;		// day

};

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.y
		<< ',' << d.m
		<< ',' << d.d << ')';
}

void add_day(Date& dd, int n)
{
	dd.d += n;
	while (dd.d > 31)
	{
		++dd.m;
		dd.d -= 31;
	}
	while (dd.m > 12)
	{
		++dd.y;
		dd.m -= 12;
	}
}

void init_date(Date& dd, int y, int m, int d)
{
	if (m < 1 || m > 12) error("init_date(): invalid month");
	if (d < 1 || d > 31) error("init_date(): invalid day");
	
	dd.y = y;
	dd.m = m;
	dd.d = d;
}

void drill1()
{
	Date today;
	init_date(today, 1978, 6, 25);
	Date tomorrow = today;
	add_day(tomorrow, 1);

	cout << today << '\n' << tomorrow << '\n';

	Date bad;
	init_date(bad, 2001, 12, 00);

	cout << bad << '\n';
}
*/

// 9.4.2 implementation
/* 
struct Date {
	int y, m, d;
	Date(int y, int m, int d);	// constructor
	void add_day(int n);
};

Date::Date(int yy, int mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	if (m < 1 || m > 12) error("Date(): invalid month");
	if (d < 1 || d > 31) error("Date(): invalid day");
}

void Date::add_day(int n)
{
	d += n;
	while (d > 31)
	{
		++m;
		d -= 31;
	}
	while (m > 12)
	{
		++y;
		m -= 12;
	}
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.y
		<< ',' << d.m
		<< ',' << d.d << ')';
}

void drill2()
{
	Date today{ 1978, 6, 25 };
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << today << '\n' << tomorrow << '\n';

	Date twoweeks = today;
	twoweeks.add_day(365);
	cout << twoweeks << '\n';

	Date bad{ -50,01,01 };
	cout << bad << '\n';
}
*/

// 9.4.3 implementation
/* 
class Date
{
	int y, m, d;
	friend ostream& operator<<(ostream&os, const Date& d);
public:
	Date(int yy, int mm, int dd);
	void add_day(int n);
	int year() { return y; }
	int month() { return m; }
	int day() { return d; }
};

Date::Date(int yy, int mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	if (m < 1 || m > 12) error("Date(): invalid month");
	if (d < 1 || d > 31) error("Date(): invalid day");
}

void Date::add_day(int n)
{
	d += n;
	while (d > 31)
	{
		++m;
		d -= 31;
	}
	while (m > 12)
	{
		++y;
		m -= 12;
	}
}

// operator<< has access to Date members because it is a friend function
ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.y
		<< ',' << d.m
		<< ',' << d.d << ')';
}


void drill3()
{
	Date today = { 1978, 6, 25 };
	Date tomorrow = today;
	tomorrow.add_day(1);

	cout << today << '\n' << tomorrow << '\n';

	Date bad{ 12345, 2, 32 };
	cout << bad << '\n';

}
*/

// 9.7.1 implementation
/*
//------------------------------------------------------------------------
// Month support functions
// example use: Month m = Month::mar; ++m;
enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month int_to_month(int x)
{
	if (x < int(Month::jan) || x > int(Month::dec)) error("bad month");
	return Month(x);
}

Month operator++(Month& m)
{
	// if december, roll over to jan. otherwise incriment normally
	m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
	return m;
}

Month operator--(Month& m)
{
	// if jan, roll back to dec. otherwise decriment normally
	m = (m == Month::jan) ? Month::dec : Month(int(m) - 1);
	return m;
}

ostream& operator<<(ostream& os, Month m)
{
	return os << int(m);
}
//------------------------------------------------------------------------

class Year {
	static const int min = 1800;
	static const int max = 3999;
public:
	class Invalid {};	// to throw
	Year(int x) : y(x) { if (x < min || x > max) throw Invalid{}; } // constructor + initialization list + inline
	int year() { return y; };
	void add_year(int n);
private:
	int y;
};

void Year::add_year(int n)
{
	y += n;
	if (y < min || y > max) error("add_year() year out of range");
}
//------------------------------------------------------------------------

class Date {
public:
	Date(Year yy, Month mm, int dd);
	void add_day(int n);	
	void add_month(int n);
	void add_year(int n) { y.add_year(n); }
	friend ostream& operator<<(ostream& os, Date& d);

	int year() { return y.year(); }
	Month month() { return m; }
	int day() { return d; }

private:
	Year y;
	Month m;
	int d;
};

Date::Date(Year yy, Month mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	if (d < 0 || d > 31) error("Date() invalid day");
}

ostream& operator<<(ostream& os, Date& d)
{
	return os << '(' << d.year()
		<< ", " << d.month()
		<< ", " << d.day() << ')';
}

void Date::add_month(int n)
{
	y.add_year(n / 12);		// handle excess years
	int mths = n % 12;		// leftover months to add
	if (n + int(m) > 12)	// handle dec -> jan rollover
	{
		m = Month(int(m) + n - 12);
		y.add_year(1);
	}
	else
		m = Month(int(m) + n);
}

void Date::add_day(int n)
{
	if (n < 0) error("add_day() negative value");
	d += n;
	while (d > 31)
	{
		d -= 31;
		if (m == Month::dec)
			y.add_year(1);
		++m;
	}
}
//------------------------------------------------------------------------

void drill4()
{
	Date today{ 1978, Month::jun, 25 };
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << today << '\n' << tomorrow << '\n';

	Date bad{ 2015, Month::jan, 18 };
	cout << bad << '\n';
}
*/

// 9.7.4 implementation
/*
//------------------------------------------------------------------------
// Month support functions
// example use: Month m = Month::mar; ++m;
enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month int_to_month(int x)
{
	if (x < int(Month::jan) || x > int(Month::dec)) error("bad month");
	return Month(x);
}

Month operator++(Month& m)
{
	// if december, roll over to jan. otherwise incriment normally
	m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
	return m;
}

Month operator--(Month& m)
{
	// if jan, roll back to dec. otherwise decriment normally
	m = (m == Month::jan) ? Month::dec : Month(int(m) - 1);
	return m;
}

ostream& operator<<(ostream& os, Month m)
{
	return os << int(m);
}
//------------------------------------------------------------------------

class Year {
	static const int min = 1800;
	static const int max = 3999;
public:
	class Invalid {};	// to throw
	Year(int x) : y(x) { if (x < min || x > max) throw Invalid{}; } // constructor + initialization list + inline
	int year() const { return y; };
	void add_year(int n);
private:
	int y;
};

void Year::add_year(int n)
{
	y += n;
	if (y < min || y > max) error("add_year() year out of range");
}
//------------------------------------------------------------------------

class Date {
public:
	Date();
	Date(Year yy, Month mm, int dd);

	void add_day(int n);
	void add_month(int n);
	void add_year(int n) { y.add_year(n); }
	friend ostream& operator<<(ostream& os, const Date& d);

	int year() const { return y.year(); }
	Month month() const { return m; }
	int day() const { return d; }

private:
	Year y;
	Month m;
	int d;
};

Date::Date() : y{ 1900 }, m{ Month::jan }, d{ 1 }
{
}

Date::Date(Year yy, Month mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	if (d < 0 || d > 31) error("Date() invalid day");
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.year()
		<< ", " << d.month()
		<< ", " << d.day() << ')';
}

void Date::add_month(int n)
{
	y.add_year(n / 12);		// handle excess years
	int mths = n % 12;		// leftover months to add
	if (n + int(m) > 12)	// handle dec -> jan rollover
	{
		m = Month(int(m) + n - 12);
		y.add_year(1);
	}
	else
		m = Month(int(m) + n);
}

void Date::add_day(int n)
{
	if (n < 0) error("add_day() negative value");
	d += n;
	while (d > 31)
	{
		d -= 31;
		if (m == Month::dec)
			y.add_year(1);
		++m;
	}
}

void drill5()
{
	Date today{ 1977, Month::jun, 25 };
	Date tomorrow = today;
	tomorrow.add_day(1);

	cout << today << '\n' << tomorrow << '\n';

	const Date david_birthday{ 1983, Month::jan, 12 };
	cout << david_birthday << endl;

	Date default_day;
	cout << default_day << endl;

	Date bad = { 2001, Month::feb, 69 };
	cout << bad << endl;
}
*/

// to use, uncomment drill() function and related implementation code
int main()
try {
//	drill1();
//	drill2();
//	drill3();
//	drill4();
//	drill5();
	
	
	return 0;
}
catch (runtime_error& e)
{
	cout << "error: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cout << "unknown errror\n";
	return 2;
}

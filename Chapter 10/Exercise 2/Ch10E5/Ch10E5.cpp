// Ch10E5.cpp
// Chapter 10, Exercise 5 (p.377)
// Write function print_year() from Chapter 10


#include "../../../std_lib_facilities.h"



// global variables
const int not_a_reading = -7777;		// error code for invalid temperature
const int not_a_month = -1;				// error code for invalid Month
constexpr int implausible_min = -200;	// unlikely temperature reading this low
constexpr int implausible_max = 200;	// unlikely temperature reading this high

// global lookup table for months, range [0:11] aka jan:dec
vector<string> month_input_tbl = {
	"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec"
};

int month_to_int(string s)
// is s the name of a month? if so return its index [0:11] otherwise -1
{
	for (int i = 0; i < 12; ++i)
		if (month_input_tbl[i] == s)	// s matched name of a month...
			return i;					// ...so return month index
	return -1;							// s not name of month, return failure code
}

// global lookup table to print Month name via index [0:11]
vector<string> month_print_tbl = {
	"January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December"
};

string int_to_month(int i)
// months [0:11]
{
	if (i < 0 || 12 <= i) error("bad month index");
	return month_print_tbl[i];
}

struct Day {
	vector<double> hour{ vector<double>(24, not_a_reading) };
};

struct Month {					// a month of temperature readings
	int month{ not_a_month };	// [0,11] January is 0
	vector<Day> day{ 32 };		// [1:31] one vector of readings per day
};

struct Year {					// a year of temperature readings, organized by month
	int year;					// positive == A.D.
	vector<Month> month{ 12 };  // [0:11] January is 0
};

struct Reading {
	int day;
	int hour;
	double temperature;
};



bool is_valid(const Reading& r)
// rough test to determine if Reading values are reasonable
{
	if (r.day < 1 || 31 < r.day) return false;
	if (r.hour < 0 || 23 < r.hour) return false;
	if (r.temperature < implausible_min || implausible_max < r.temperature)
		return false;
	return true;
}

void end_of_loop(istream& ist, char term, const string& message)
{
	if (ist.fail())
	{
		ist.clear();
		char ch;
		if (ist >> ch && ch == term) return;	// all is fine
		error(message);
	}
}


istream& operator >> (istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7 )
// check format, don't bother with data validity
{
	char ch1;
	if (is >> ch1 && ch1 != '(')		// could it be a reading?
	{
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	char ch2;
	int d;
	int h;
	double t;

	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')') error("bad reading");
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

ostream& operator<<(ostream& os, const Day& d)
// print formatted contents of d
{
	for (int i = 0; i < d.hour.size(); ++i)
	{
		if (d.hour[i] != not_a_reading)		// only print temperatures
			os << "Hour " << i << ": " << d.hour[i] << '\n';
	}
	return os;
}

istream& operator >> (istream& is, Month& m)
// read a month from is into m
// format: { month feb ... }
{
	char ch = 0;
	if (is >> ch && ch != '{')
	{
		is.unget();
		is.clear(ios_base::failbit);	// we failed to read a Month
		return is;
	}

	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") error("bad start of month");
	m.month = month_to_int(mm);

	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r;)
	{
		if (is_valid(r))
		{
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
			++invalids;
	}
	if (invalids) error("invalid readings in month ", invalids);
	if (duplicates) error("duplicate readings in month ", duplicates);
	end_of_loop(is, '}', "bad end of month");
	return is;
}

ostream& operator<<(ostream& os, const Month& m)
{
	os << month_print_tbl[m.month] << "\n";
	for (int i = 0; i < m.day.size(); ++i)
	{
		for (int j = 0; j < m.day[i].hour.size(); ++j)
		{
			int count = 0;
			if (m.day[i].hour[j] != not_a_reading)
				++count;

			if (count > 0)
				os << "Day " << i << "\n" << m.day[i];
		}
	}
	return os;
}

istream& operator >> (istream& is, Year& y)
// read a year from is into y
// format: { year 1972 ... }
{
	char ch;
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year") error("bad start of year");
	y.year = yy;

	while (true)
	{
		Month m;		// get a clean m each time around
		if (!(is >> m)) break;
		y.month[m.month] = m;
	}

	end_of_loop(is, '}', "bad end of year");
	return is;
}



void print_year(ostream& os, const Year& y)
{
	os << y.year << '\n';
	for (int i = 0; i < y.month.size(); ++i)
	{
		if (y.month[i].month != not_a_month)
			os << y.month[i];
	}

}


int main()
try {
	
	// open input file
	string filename = "temperature_data.txt";
	ifstream ifs{ filename };
	if (!ifs) error("can't open input file ", filename);
	
	ifs.exceptions(ifs.exceptions() | ios_base::badbit); // throw for bad()

	// open output file
	string outfilename = "results.txt";
	ofstream ofs{ outfilename };
	if (!ofs) error("can't open output file ", outfilename);

	// read an arbitrary number of years:
	vector<Year> ys;
	while (true)
	{
		Year y;
		if (!(ifs >> y)) break;
		ys.push_back(y);
	}
	cout << "read " << ys.size() << " years of readings\n";
	
	for (Year& y : ys)
		print_year(ofs, y);



return 0;
}
catch (runtime_error& e)
{
	cerr << "error: " << e.what() << '\n';
	return 1;
}
catch(...)
{
	cerr << "unknown error\n";
	return 2;
}
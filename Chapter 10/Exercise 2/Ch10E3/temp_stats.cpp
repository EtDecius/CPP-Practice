// temp_stats.cpp
// Chapter 10, Exercise 3 (p.377)
// Write program that reads data from raw_temps.txt (Exercise 2 file)
// into a vector, then calcultes mean and median temps from data set.
// expected file format: hour temperature scale(celcius or fahrenheit)
//		ex: 5 72.8 f
// program terminates if invalid format encountered


#include "../../../std_lib_facilities.h"


// ---------------------------------------

enum class Temp_scale {
	c, f		// Celcius, Fahrenheit
};

// Celcius = c, Fahrenheit = f
ostream& operator << (ostream& os, const Temp_scale& ts)
{
	char t_scale = 'c';							// default celcius
	if (ts == Temp_scale::f) t_scale = 'f';		// update to fahrenheit
	return os << t_scale;
}

istream& operator >> (istream& is, Temp_scale& ts)
{
	char input;
	is >> input;
	if (!is) return is;		// return to handle eof, fail, bad
	
	switch (input) {
	case 'c':
		ts = Temp_scale::c; break;
	case 'f':
		ts = Temp_scale::f; break;
	default:
		error(">>(Temp_scale) invalid scale ", input);
		break;
	}
	return is;
}

// ---------------------------------------

bool valid_hour(int hour);	// forward declaration

struct Reading {			// a temperature reading
	Reading() : hour{ 0 }, temperature{ 0.0 }, scale{ Temp_scale::c } {}; // default constructor
	Reading(int hr, double temp, Temp_scale ts);		// constructor
	int hour;				// hout after midnight [0:23]
	double temperature;
	Temp_scale scale;				// (c)elcius, (f)ahrenheit
};


// print temperature
ostream& operator << (ostream& os, const Reading& r)
{
	return os << r.hour << ' ' << r.temperature << ' ' << r.scale;
}

// compare Reading by temperature value
bool operator<(const Reading& r1, const Reading& r2)
{
	return (r1.temperature < r2.temperature) ? true : false;
}

istream& operator >> (istream& is, Reading& r)
{
	int h = 0;
	double t = 0.0;
	Temp_scale ts = Temp_scale::c;

	if (!(is >> h >> t >> ts))		// attempt read values from stream
	{
		if (is.bad()) error(">>(Reading) bad stream");
		if (is.eof()) return is;		// reached end of file
		if (is.fail()) return is;		// return to handle problem
	}
	
	r.hour = h;
	r.temperature = t;
	r.scale = ts;

	return is;
}

// ------- Reading helper functions -------

bool valid_hour(int hour)
{
	if (hour < 0 || hour > 23)
		return false;
	return true;
}

// convert celcius to fahrenheit
double convert_celc_fahr(double d)
{
	return d * 1.8 + 32;
}

//convert fahrenheit to celcius
double convert_fahr_celc(double d)
{
	return (d - 32) / 1.8;
}

// convert Reading from celcius to fahrenheit, or visa versa
void convert(Reading& r)
{
	switch (r.scale) {
	case Temp_scale::c :
		r.scale = Temp_scale::f;
		r.temperature = convert_celc_fahr(r.temperature);
		break;
	case Temp_scale::f :
		r.scale = Temp_scale::c;
		r.temperature = convert_fahr_celc(r.temperature);
		break;
	default:
		break;
	}
	return;
}

// ---------------------------------------

// loop reads from file, converts to Reading object and store
void import_from_file(ifstream& fin, vector<Reading>& temp_data)
{
	int line_number = 1;				
	for (Reading r; fin >> r;)			// read inputs and add to vector
	{
		if (!valid_hour(r.hour))		// validate hour range
			error("import_from_file() hour not in range " + to_string(r.hour) + " (line " + to_string(line_number) + ")");
		
		convert(r);						// Convert to other temperature scale per Exercise 4
		temp_data.push_back(r);
		++line_number;
	}

	if (fin.eof())	return;				// reached end of file, success
	if (fin.fail())						// read failed, throw exception with line number
		error("import_from_file() invalid format (line " + to_string(line_number) + ")");
}

// open file for read access
void load_from_file(const string filename, vector<Reading>& temp_data)
{
	ifstream fin{ filename };
	if (!fin) error("load_from_file() can't open input file ", filename);
	fin.exceptions(fin.exceptions() | ios_base::badbit); // throw exception if ifstream ever bad
	import_from_file(fin, temp_data);	// start reading data
}

void print_temps(const vector<Reading>& temp_data)
{
	for (const Reading& r : temp_data)
		cout << r << '\n';
}

// calculate arithmetic mean
double mean(const vector<Reading>& temp_data)
{
	if (temp_data.size() == 0)	error("median() can't find mean of zero elements");
	double sum = 0.0;
	for (const Reading& r : temp_data)
		sum += r.temperature;
	return sum / temp_data.size();
}

bool is_even(const int n) { return (n % 2 == 0) ? true : false; }

// calculate arithmethic median
double median(const vector<Reading>& temp_data)
{
	if (temp_data.size() == 0)	error("median() can't find median of zero elements");
	vector<Reading> copy = temp_data;	// create copy for modification
	sort(copy.begin(), copy.end());		// sort by temperature value

	if (is_even(copy.size()))			
	{									// get average of two middle elements
		double left = copy[copy.size() / 2 - 1 ].temperature;
		double right = copy[copy.size() / 2].temperature;
		return (left + right) / 2;
	}
	else
		return temp_data[temp_data.size() / 2].temperature;
}

int main()
try {
	vector<Reading> temps;
	string filename = "../../Exercise 2/Ch10E2/raw_temps.txt";	// file in another folder
																// PROBABLY NOT PORTABLE
	load_from_file(filename, temps);
	print_temps(temps);											// for testing purposes

	cout << "Temperature mean: " << mean(temps) << '\n';
	cout << "Temperature median: " << median(temps) << '\n';

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
// store_temps.cpp
// Chapter 10, Exercise 2 (p.377)
// Write program that creates a file of data in the form of 
// the temperature Reading defined in chapter.
// Fill file with at least 50 readings.

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

// ---------------------------------------

bool valid_hour(int hour);	// forward declaration

struct Reading {			// a temperature reading
	Reading() : hour{ 0 }, temperature{ 0.0 }, scale{ Temp_scale::c } {}; // default constructor
	Reading(int hr, double temp, Temp_scale ts);		// constructor
	int hour;				// hout after midnight [0:23]
	double temperature;		
	Temp_scale scale;				// (c)elcius, (f)ahrenheit
};

// constructor
Reading::Reading(int hr, double temp, Temp_scale ts)
	: hour{ hr }, temperature{ temp }, scale{ ts }
{
	if (!valid_hour(hour)) error("Reading() hour not in range");
}

// print Reading
ostream& operator << (ostream& os, const Reading& r)
{
	return os << r.hour << ' ' << r.temperature << ' ' << r.scale;
}

// ------- Reading helper functions -------

bool valid_hour(int hour)
{
	if (hour < 0 || hour > 23)
		return false;
	return true;
}

// ---------------------------------------

void export_to_file(ofstream& fout, const vector<Reading>& temp_data)
{
	if (fout.bad()) error("export_to_file() bad ostream");
	
	cout << temp_data.size() << endl;
	for (const Reading& r : temp_data)
		fout << r << '\n';
}

void save_to_file(string filename, vector<Reading> temp_data)
{
	ofstream fout{ filename };			// create and open file
	if (!fout) error("save_to_file() can't open output file ", filename);
	export_to_file(fout, temp_data);
}

// manually add temp data, source: Irvine, CA, USA 3/1/2016 - 3/3/2016
void generate_manual_temps(vector<Reading>& temp_data)
{
	temp_data.push_back(Reading{ 0, 55.4, Temp_scale::f});
	temp_data.push_back(Reading{ 1, 55.9, Temp_scale::f });
	temp_data.push_back(Reading{ 2, 55.9, Temp_scale::f });
	temp_data.push_back(Reading{ 3, 55.4, Temp_scale::f });
	temp_data.push_back(Reading{ 4, 55.9, Temp_scale::f });
	temp_data.push_back(Reading{ 5, 55.0, Temp_scale::f });
	temp_data.push_back(Reading{ 6, 55.4, Temp_scale::f });
	temp_data.push_back(Reading{ 7, 53.6, Temp_scale::f });
	temp_data.push_back(Reading{ 8, 55.4, Temp_scale::f });
	temp_data.push_back(Reading{ 9, 57.2, Temp_scale::f });
	temp_data.push_back(Reading{ 10, 62.1, Temp_scale::f });
	temp_data.push_back(Reading{ 11, 64.0, Temp_scale::f });
	temp_data.push_back(Reading{ 12, 70.0, Temp_scale::f });
	temp_data.push_back(Reading{ 13, 71.1, Temp_scale::f });
	temp_data.push_back(Reading{ 14, 66.9, Temp_scale::f });
	temp_data.push_back(Reading{ 15, 66.0, Temp_scale::f });
	temp_data.push_back(Reading{ 16, 64.0, Temp_scale::f });
	temp_data.push_back(Reading{ 17, 62.1, Temp_scale::f });
	temp_data.push_back(Reading{ 18, 59.0, Temp_scale::f });
	temp_data.push_back(Reading{ 19, 55.0, Temp_scale::f });
	temp_data.push_back(Reading{ 20, 60.1, Temp_scale::f });
	temp_data.push_back(Reading{ 21, 59.0, Temp_scale::f });
	temp_data.push_back(Reading{ 22, 57.9, Temp_scale::f });
	temp_data.push_back(Reading{ 23, 57.0, Temp_scale::f });
	temp_data.push_back(Reading{ 0, 57.2, Temp_scale::f });
	temp_data.push_back(Reading{ 1, 57.9, Temp_scale::f });
	temp_data.push_back(Reading{ 2, 57.0, Temp_scale::f });
	temp_data.push_back(Reading{ 3, 55.9, Temp_scale::f });
	temp_data.push_back(Reading{ 4, 57.0, Temp_scale::f });
	temp_data.push_back(Reading{ 5, 57.0, Temp_scale::f });
	temp_data.push_back(Reading{ 6, 55.9, Temp_scale::f });
	temp_data.push_back(Reading{ 7, 55.0, Temp_scale::f });
	temp_data.push_back(Reading{ 8, 55.9, Temp_scale::f });
	temp_data.push_back(Reading{ 9, 59.0, Temp_scale::f });
	temp_data.push_back(Reading{ 10, 61.0, Temp_scale::f });
	temp_data.push_back(Reading{ 11, 64.9, Temp_scale::f });
	temp_data.push_back(Reading{ 12, 66.0, Temp_scale::f });
	temp_data.push_back(Reading{ 13, 68.0, Temp_scale::f });
	temp_data.push_back(Reading{ 14, 68.0, Temp_scale::f });
	temp_data.push_back(Reading{ 15, 68.0, Temp_scale::f });
	temp_data.push_back(Reading{ 16, 64.9, Temp_scale::f });
	temp_data.push_back(Reading{ 17, 64.0, Temp_scale::f });
	temp_data.push_back(Reading{ 18, 62.1, Temp_scale::f });
	temp_data.push_back(Reading{ 19, 60.1, Temp_scale::f });
	temp_data.push_back(Reading{ 20, 59.0, Temp_scale::f });
	temp_data.push_back(Reading{ 21, 60.1, Temp_scale::f });
	temp_data.push_back(Reading{ 22, 59.0, Temp_scale::f });
	temp_data.push_back(Reading{ 23, 57.9, Temp_scale::f });
	temp_data.push_back(Reading{ 0, 57.9, Temp_scale::f });
	temp_data.push_back(Reading{ 1, 55.9, Temp_scale::f });
}


int main()
try {

	vector<Reading> irvine_temps;
	generate_manual_temps(irvine_temps);


	string filename = "raw_temps.txt";
	save_to_file(filename, irvine_temps);

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





// Ch10Drill.cpp
// Ch 10 Drill (p.376)
// Implement a Points class to represent point coordinates: (x,y)
// Write IO functions for console, file
// Possible improvements: 
// - make reading multiple Points on one line more robust (currently discards rest of line on invalid input)

#include "../../../std_lib_facilities.h"

// simple (x,y) coordinate
struct Point
{
	Point() : x{ 0 }, y{ 0 } {};
	Point(double xx, double yy) : x{ xx }, y{ yy } {};
	double x, y;
};

// true if same x,y values
bool operator==(const Point& p1, const Point& p2)
{
	return (p1.x == p2.x && p1.y == p2.y) ? true : false;
}

// true if Points have different x or y values
bool operator!=(const Point& p1, const Point& p2)
{
	return !(p1 == p2);
}

// print formatted Point to ostream
// format: (x,y)
ostream& operator<<(ostream& os, const Point& p)
{
	return os << '(' << p.x << ',' << p.y << ")\n";
}

// read Point values from input stream
// format: (x,y)
istream& operator>>(istream& is, Point& p)
{
	char ch1 = '!', ch2 = '!', ch3 = '!';
	double xx = 0.0, yy = 0.0;

	if (!(is >> ch1 >> xx >> ch2 >> yy >> ch3))	// validate correct input types
	{
		if (is.bad()) error(">>(Point) bad istream"); // unrecoverable
		if (is.eof()) return is;				// reached end of stream
		if (is.fail())							// input didn't match
		{
			is.clear(ios_base::failbit);
			return is;
		}
	}

	if (ch1 != '(' || ch2 != ',' || ch3 != ')') // format error
	{
		is.clear(ios_base::failbit);
		return is;
	}

	p.x = xx;
	p.y = yy;
	return is;
}

// read next Point input and report success
// this breaks Single Responsibility Principle; modifies Point P and reports success/failure
bool get_point_from_user(Point& p)
{
	if (!(cin >> p))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	return true;
}

// store vector of Points from user
void fill_from_user(vector<Point>& points, int to_gather)
{
	cout << "Enter " << to_gather << " coordinates. Format: (x,y)\n";
	int count = 0;

	while (count < to_gather)
	{
		Point p;
		while (!get_point_from_user(p))
			cout << "invalid input, expect format: (x,y)\n";
		points.push_back(p);
		++count;
	}
}

// ouput formatted Points to specified ostream
void print_points(ostream& os, vector<Point>& points)
{
	for (Point p : points)
		os << p;
}

// print to console screen
void print_to_console(vector<Point>& points)
{
	print_points(cout, points);
}

// save to file
void print_to_file(vector<Point>& points)
{
	string filename = "mydata.txt";
	ofstream fout{ filename };
	if (!fout) error("can't open output file ", filename);
	print_points(fout, points);
}

// read in list of Points from file
void import_from_file(vector<Point>& points)
{
	string filename = "mydata.txt";
	ifstream fin{ filename };
	if (!fin) error("can't open input file ", filename);
	fin.exceptions(fin.exceptions() | ios_base::badbit); // throw exception if ifstream ever in bad state

	for (Point p; fin >> p;)	// read and store Points until eof
	{
		if (fin.eof()) break;	// eof found, exit loop
		points.push_back(p);
	}

	if (fin.eof()) return;		// eof reached, all good
	if (fin.fail())				// failed to read proper format
		error("import_from_file() file not formatted properly ", filename);
}

// true if Point x,y coordinates are same
bool is_equivalent(const vector<Point>& p1, const vector<Point>& p2)
{
	if (p1.size() != p2.size()) return false;
	for (int i = 0; i < p1.size(); ++i)
		if (p1[i] != p2[i]) return false;
	return true;
}

int main()
try {
	const int num_points = 3;		// arbitrary num. elements to get from user

	vector<Point> original_points;
	fill_from_user(original_points, num_points);

	cout << "\nDisplay points:\n";
	print_to_console(original_points);
	cout << endl;

	print_to_file(original_points);
	cout << "File save successful.\n";

	vector<Point> processed_points;
	import_from_file(processed_points);
	cout << "File read successful.\n";

	cout << "\nOriginal Points: \n";
	print_to_console(original_points);
	cout << "\nProcessed Points: \n";
	print_to_console(processed_points);

	cout << endl;
	if (is_equivalent(original_points, processed_points))
		cout << "Lists are the same\n";
	else
		cout << "Something's wrong!\n";
	
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

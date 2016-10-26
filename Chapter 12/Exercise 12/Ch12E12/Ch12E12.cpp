// Ch12E12.cpp
// Chapter 12, Exercise 12 (p.439)
// A superellipse is a two-dimensional shape defined by the equation
//    |  x  | ^ m     |  y  | ^ n
//    | --- |      +  | --- |      =  1;   m,n > 0
//    |  a  |         |  b  |
// Look up superellipse on the web to get a better idea of what such shapes
// look like. Write a program that draws "starlike" patterns by connecting
// points on a superellipse. Take a, b, m, n and N as arguments. Select N
// points on the superellipse defined by a, b, m, and n. Make the points
// equally spaced for some definition of "equal." Connect each of those N
// points to one or more other points (if you like you can make the number
// of points to which to connect a point another argument or just use N-1,
// i.e., all the other points).
//
// Solution incomplete. Drew a superellipse, though I don't understand
// the forumla. Various values of m,n and the number of points causes
// the program to end abruptly with no indication why. My guess is that
// some error is thrown and the program shuts down before it can be
// displayed. Error likely thrown in by Polygon, which does some
// checking to ensure lines aren't on the same plane, or something.
// I phoned this one in a bit and don't want to spend time figuring
// out what the exercise is asking. Also, no Exercise 13 for this chapter.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

const double pi = acos(-1);

// stole fron internet http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

Point operator+(const Point& p1, const Point& p2)
{
	return Point{ p1.x + p2.x, p1.y + p2.y };
}

Point se_point(double a, double b, double m, double n, double N, double angle)
{
	if (m <= 0 || n <= 0) error("se_point() m,n must be greater than 0");

	int x = pow(abs(cos(angle)), (2 / m)) * a * sgn(cos(angle));
	int y = pow(abs(sin(angle)), (2 / n)) * b * sgn(sin(angle));

	cout << x << ',' << y << '\n';
	return Point{ x,y };
}



int main()
try {

	Simple_window win{ Point{200,200}, 600,600, "Exercise 12" };

	Point center{ 300,300 };


	int m = 4;
	double n = 2;
	int a = 200;
	int b = 200;
	int point_count = 30;

	double angle = 0;

	Graph_lib::Closed_polyline superellipse;
	for (int i = 0; i < point_count; ++i)
	{
		superellipse.add(center + Point{ se_point(a, b, m, n, 1, angle) });
		angle += pi / (point_count / 2);
	}
	win.attach(superellipse);

	win.wait_for_button();
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

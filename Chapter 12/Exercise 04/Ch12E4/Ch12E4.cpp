// Ch12E4.cpp
// Chapter 12, Exercise 4 (p.438)
// Draw a 3x3 tic-tac-toe board of alternating white and red squares.
//
// Note: Tried to implement this using a data structure to hold all the
// Rectangles, but it didn't work. Was unable to store the Rectangles
// and still be able to access them to attach. Said deleted function.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

// returns vector of Points that indicate top-left start position for
// each square Rectangles, in pixels
vector<Point> start_point(int rows, int columns, int side, int padding)
{
	vector<Point> points;
	int x = padding;
	int y = padding;

	for (int i = 0; i < rows; ++i)
	{
		y = padding + (i * side);

		for (int j = 0; j < columns; ++j)
		{
			x = padding + (j * side);
			points.push_back(Point{ x,y });
		}
		x = padding;
	}
	return points;
}

int main()
try {

	Simple_window win{ Point{200,200}, 400,400,"Exercise 4" };

	int num_rows = 3;
	int num_cols = 3;
	int side = 100;  // in pixels
	int padding = 50;

	vector<Point> points = start_point(num_rows, num_cols, side, padding);

	Graph_lib::Rectangle r0{ points[0], side, side };
	win.attach(r0);
	Graph_lib::Rectangle r1{ points[1], side, side };
	win.attach(r1);
	Graph_lib::Rectangle r2{ points[2], side, side };
	win.attach(r2);
	
	Graph_lib::Rectangle r3{ points[3], side, side };
	win.attach(r3);
	Graph_lib::Rectangle r4{ points[4], side, side };
	win.attach(r4);
	Graph_lib::Rectangle r5{ points[5], side, side };
	win.attach(r5);
	
	Graph_lib::Rectangle r6{ points[6], side, side };
	win.attach(r6);
	Graph_lib::Rectangle r7{ points[7], side, side };
	win.attach(r7);
	Graph_lib::Rectangle r8{ points[8], side, side };
	win.attach(r8);

	r0.set_fill_color(Color::white); 	r1.set_fill_color(Color::red);
	r2.set_fill_color(Color::white); 	r3.set_fill_color(Color::red);
	r4.set_fill_color(Color::white); 	r5.set_fill_color(Color::red);
	r6.set_fill_color(Color::white); 	r7.set_fill_color(Color::red);
	r8.set_fill_color(Color::white);

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
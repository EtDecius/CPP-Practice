// Ch12E1.cpp
// Chapter 12, Exercise 1 (p.438)
// Draw a rectangle as a Rectangle and as a Polygon. Make the lines of the
// Polygon red and the lines of the Rectangle blue.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"



int main()
try {

	Simple_window win{ Point{100,100}, 600,400, "Exercise 1" };
	Graph_lib::Rectangle real_rect{ Point{50,50}, 200,300 };
	real_rect.set_color(Color::blue);

	win.attach(real_rect);

	Graph_lib::Polygon poly_rect;
	poly_rect.add(Point{ 300,50 });
	poly_rect.add(Point{ 500,50 });
	poly_rect.add(Point{ 500,350 });
	poly_rect.add(Point{ 300,350 });
	poly_rect.set_color(Color::red);

	win.attach(poly_rect);


	
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
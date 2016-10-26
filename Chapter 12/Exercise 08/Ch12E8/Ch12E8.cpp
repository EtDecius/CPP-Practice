// Ch12E8.cpp
// Chapter 12, Exercise 8 (p.439)
// Draw the Olympic five rings. If you can't remember the colors, look
// them up.
// Centers the rings based on window size.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

int main()
try {
	
	int window_width = 600;
	int window_height = 400;

	Simple_window win{ Point{200,200}, window_width, window_height, "Exercise 8" };

	int ring_radius = 50;
	int high_y_axis = int( window_height / 2  - (0.5 * ring_radius));	// horizontal center, top rings
	int low_y_axis = high_y_axis + ring_radius;			// horizontal center, bot rings
	int x_gap = 8;										// small offset between rings
	int x_axis_increment = ring_radius;					// separation between rings
	int x_space_needed = 6 * ring_radius + 4 * x_gap;	// sum of rings horizontal axis
	int x_offset = int((window_width - x_space_needed)/2);  // rough centering


	Circle c1{ Point{x_offset + x_axis_increment, high_y_axis}, ring_radius };
	c1.set_color(Color::blue);
	c1.set_style(Line_style(Line_style::solid, 5));
	x_axis_increment += ring_radius + x_gap;

	Circle c2{ Point{ x_offset + x_axis_increment, low_y_axis }, ring_radius };
	c2.set_color(Color::yellow);
	c2.set_style(Line_style(Line_style::solid, 5));
	x_axis_increment += ring_radius + x_gap;

	Circle c3{ Point{ x_offset + x_axis_increment, high_y_axis }, ring_radius };
	c3.set_color(Color::black);
	c3.set_style(Line_style(Line_style::solid, 5));
	x_axis_increment += ring_radius + x_gap;

	Circle c4{ Point{ x_offset + x_axis_increment, low_y_axis }, ring_radius };
	c4.set_color(Color::green);
	c4.set_style(Line_style(Line_style::solid, 5));
	x_axis_increment += ring_radius + x_gap;

	Circle c5{ Point{ x_offset + x_axis_increment, high_y_axis }, ring_radius };
	c5.set_color(Color::red);
	c5.set_style(Line_style(Line_style::solid, 5));

	win.attach(c1);
	win.attach(c2);
	win.attach(c3);
	win.attach(c4);
	win.attach(c5);

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
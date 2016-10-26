// Ch12E5.cpp
// Chapter 12, Exercise 5 (p.438)
// Draw a red 1/4-inch frame around a rectangle that is three-quarters the
// height of your screen and two-thirds the width.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

int main()
try {
	int width_inch = 20;					// personal monitor dimension
	int width_pixel = 1920;					// personal monitor resolution
	int ppi = width_pixel / width_inch;	    // pixels per inch

	int border_thickness = int(ppi * 0.25);
	int frame_width = int(x_max() * 0.66);
	int frame_height = int(y_max() * 0.75);

	Simple_window win{ Point{0,0}, 1800,900, "Exercise 5" };

	Graph_lib::Rectangle frame{ Point{50,50}, frame_width,frame_height };
	frame.set_color(Color::red);
	frame.set_style(Line_style(Line_style::solid, border_thickness));
	
	win.attach(frame);

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
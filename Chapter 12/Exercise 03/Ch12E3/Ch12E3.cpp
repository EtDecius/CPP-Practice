// Ch12E3.cpp
// Chapter 12, Exercise 3 (p.438)
// Draw your initials 150 pixels high. Use a thick line. Draw each initial
// in a different color.
// Note: Simplistic implementation that mostly used a pen and paper to
// to determine proper point coordinates. Would have been better to build
// them into the code using formulas rather than hard values.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

int main()
try {
	// Unnecessary math to set the window size so letters are (mostly) centered
	const int letter_count = 3;
	int padding = 75;  // space above, below and to sides of letters

	int letter_height = 150; 
	int letter_width = 100;
	int letter_spacing = 10;  // space between letters

	int window_height = (padding * 2 + letter_height);
	int window_width = (padding * 2 + (letter_count * letter_width) + ((letter_count - 1) * letter_spacing));
	
	Simple_window win{ Point{200,200}, window_width,window_height, "Exercise 3" };

	Graph_lib::Open_polyline letter_a;
	letter_a.add(Point{ 75,225 });
	letter_a.add(Point{ 125, 75 });
	letter_a.add(Point{ 175,225 });
	letter_a.set_style(Line_style(Line_style::solid, 15));
	letter_a.set_color(Color::blue);

	Graph_lib::Open_polyline letter_a_dash;
	letter_a_dash.add(Point{ 92,160 });
	letter_a_dash.add(Point{ 148,160 });
	letter_a_dash.set_style(Line_style(Line_style::solid, 10));
	letter_a_dash.set_color(Color::blue);

	win.attach(letter_a);
	win.attach(letter_a_dash);

	Graph_lib::Closed_polyline letter_d;
	letter_d.add(Point{ 190, 75 });
	letter_d.add(Point{ 190, 225 });
	letter_d.add(Point{ 280, 210 });
	letter_d.add(Point{ 280, 90 });
	letter_d.set_style(Line_style(Line_style::solid, 15));
	letter_d.set_color(Color::dark_green);

	win.attach(letter_d);

	Graph_lib::Open_polyline letter_g;
	letter_g.add(Point{ 395, 75 });
	letter_g.add(Point{ 300, 75 });
	letter_g.add(Point{ 300, 225 });
	letter_g.add(Point{ 390,225 });
	letter_g.add(Point{ 390,160 });
	letter_g.add(Point{ 360,160 });
	letter_g.set_style(Line_style(Line_style::solid, 15));
	letter_g.set_color(Color::dark_magenta);

	win.attach(letter_g);

	win.wait_for_button();

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

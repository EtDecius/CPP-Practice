// Ch12E7.cpp
// Chapter 12, Exercise 7 (p.439)
// Draw a two-dimensional house seen from the front, the way a child
// would: with a door, two windows, and a roof with a chimney. Feel free to
// add details; maybe have "smoke" come out of the chimney

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

int main()
try {
	// dimensions for various components of house picture
	// w = width, h = height
	int house_w = 400;		
	int house_h = 300;      

	int roof_h = 80;
	int roof_overhang_w = 55;
	int roof_overhang_h = 20;

	int grass_offset = 100;

	int door_w = 80;
	int door_h = 120;

	int window_w = int(door_w * 0.8);

	Simple_window win{ Point{ 100,100 }, 700,500, "Exercise 7" };	// 	// Graphical window
	Point tl{ 150,100 };	// top-left of house, anchor for other parts

	// house frame
	Graph_lib::Rectangle house{ tl, house_w, house_h };
	house.set_fill_color(Color::white);
	house.set_color(Color::white);
	win.attach(house);

	// roof
	Graph_lib::Open_polyline roof;
	roof.add(Point{ tl.x - roof_overhang_w, tl.y + roof_overhang_h });
	roof.add(Point{ tl.x + (house_w / 2) , tl.y - roof_h});
	roof.add(Point{ tl.x + house_w + roof_overhang_w, tl.y + roof_overhang_h});
	roof.set_color(Color::red);
	roof.set_fill_color(Color::red);
	win.attach(roof);

	// door + knob
	Point door_tl{ tl.x + (house_w / 2) - (door_w / 2) , tl.y + house_h - door_h };
	Graph_lib::Rectangle door{ door_tl, door_w , door_h };
	door.set_color(Color::dark_magenta);
	door.set_fill_color(Color::dark_magenta);

	Graph_lib::Circle door_knob { Point{door_tl.x + 10, door_tl.y + (door_h / 2)}, 5 };
	door_knob.set_color(Color::yellow);
	door_knob.set_fill_color(Color::yellow);
	win.attach(door);
	win.attach(door_knob);

	// window
	Graph_lib::Rectangle window1{ Point{tl.x + int(house_w * 0.15), tl.y + int(house_h / 2) - int(window_w / 2)  }, window_w, window_w };
	window1.set_color(Color::cyan);
	window1.set_fill_color(Color::cyan);
	win.attach(window1);

	// second window
	Graph_lib::Rectangle window2{ Point{ tl.x + house_w - int(house_w * 0.15) - window_w, tl.y + int(house_h / 2) - int(window_w / 2) }, window_w, window_w };
	window2.set_color(Color::cyan);
	window2.set_fill_color(Color::cyan);
	win.attach(window2);

	// grass
	Axis grass{ Axis::x, Point{ tl.x - grass_offset, tl.y + house_h }, house_w + grass_offset * 2, 50 };
	grass.set_color(Color::dark_green);
	win.attach(grass);

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
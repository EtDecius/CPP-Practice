// Ch12E2.cpp
// Chapter 12, Exercise 2 (p.438)
// Draw a 100-by-30 Rectangle and place the text "Howdy" inside it.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

int main()
try {

	Simple_window win{ Point{200,200}, 150, 80, "Exercise 2" };

	Graph_lib::Rectangle rect{ Point{25,25}, 100,30 };
	win.attach(rect);

	Text greeting{ Point{50,45}, "Howdy!" };
	win.attach(greeting);

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
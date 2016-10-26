// Ch12E6.cpp
// Chapter 12, Exercise 6 (p.439)
// 1: What happens when y ou draw a Shape that doesn't fit inside it's window?
// 2: What happens when you draw a Window that doesn't fit on your screen?
// Write two programs that illustrate these two phenomena
// Note: Combined into one program with half of it commented out.
//
// Answer 1: Window draws the portion of the shape that is visible, ignores
// anything offscreen. If screen resized, draws rest of shape accordingly.
// Answer 2: Window created that's very large, but still functions. Can
// drag window around, contents move accordingly.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

int main()
try {

//  shape does not fit in window
//	Simple_window win{ Point{100,100}, 800,600,"Exercise 6" };
//	Graph_lib::Ellipse e{ Point{300,300}, 1000, 300 };
//	win.attach(e);

//  window does not fit screen
	Simple_window win{ Point{-1,0}, 3000, 2000, "Exercise 6" };
	Graph_lib::Ellipse e{ Point{400,400}, 300, 200 };
	win.attach(e);
		
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
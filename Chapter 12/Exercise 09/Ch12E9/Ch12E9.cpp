// Ch12E9.cpp
// Chapter 12, Exercise 9 (p.439)
// Display an image on the screen. Label the image both with a title on the
// window and with a caption in the window.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

int main()
try {

	Simple_window win{ Point{200,200}, 597,645, "Celebrity Crush" };

	Image pic{ Point{20,20}, "celebrity_crush.jpg" };
	win.attach(pic);

	Text caption{ Point{372,75}, "Kristen Kruek" };
	caption.set_font_size(24);
	caption.set_font(Font::courier_bold);
	win.attach(caption);

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
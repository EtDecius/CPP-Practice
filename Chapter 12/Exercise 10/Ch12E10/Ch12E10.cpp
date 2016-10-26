// Ch12E10.cpp
// Chapter 12, Exercise 10 (p.439)
// Draw the file diagram from 12.8
//
// Very messy. All objects were created within main() because I could not
// figure out how to create an object within a function, then pass it to main()
// to draw. Attempts to do so resulted in compiler errors stating an attempt
// to call a deleted function. I think this is due to the interface not
// providing a copy constructor for the shapes.
// I tried creating custom shapes myself within Graph.cpp and Graph.h but
// could not figure it out.
//
// The objects of each text box are relative to an anchor point. Moving the
// anchor point will adjust the positions of everything else. However there
// are no checks to prevent overlap or arrows clipping through boxes.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

// holds strings for a single Text box
class TB_strings {
public:
	TB_strings(const string& box_title) : box_title{ box_title }, index { 0 } {}
	string title() { return box_title; }
	string next();
	int num_rows() { return content.size(); }
	int TB_strings::max_length();
	void add(string s) { content.push_back(s); }
private:
	string box_title;
	vector<string> content;
	int index;
};

// returns the next unused string
string TB_strings::next()
{
	string s = content[index];
	++index;
	return s;
}

// returns character length of longest string stored
int TB_strings::max_length()
{
	int num_chars = 0;
	for (const string& s : content)
		if (s.size() > num_chars)
			num_chars = s.size();
	return num_chars;
}

// returns a Point with x,y coordinate centered on bottom of text box
Point arrow_in(const Graph_lib::Rectangle& box, const Point anchor, int title_gap)
{
	int arrow_gap = 3;
	Point in{ anchor.x + int(box.width() / 2), anchor.y + title_gap + box.height() + arrow_gap };
	return in;
}

// returns a Point with x,y coordinate aligned with top of text box
// x_offset of 0 centers horizontally, + offsets to the right
Point arrow_out(const Graph_lib::Rectangle& r, const Point anchor, int x_offset, int title_gap)
{
	Point out{ anchor.x + int(r.width() / 2) + x_offset , anchor.y + title_gap };
	return out;
}

int main()
try {
	using Graph_lib::Rectangle;
	
	Simple_window win{ Point{200,200}, 800,800, "Exercise 10" };
	
	// various spacing values, in pixels
	const int title_gap = 8;
	const int text_indent = 4;
	const int pix_char = 9;
	const int line_spacer = 22;
	const int box_shadow = 4;
	const int arrow_gap = 3;

	// Point.h text box
	Point ph_anchor { 50,100 };
	TB_strings ph_strings{ "Point.h:" };
	ph_strings.add("struct Point { ... };");
	Text ph_title{ ph_anchor, ph_strings.title() };
	Text ph_content{ Point{ph_anchor.x + text_indent, ph_anchor.y + line_spacer}, ph_strings.next() };
	Rectangle ph_box{ Point{ ph_anchor.x, ph_anchor.y + title_gap }, int(ph_strings.max_length() * pix_char), ph_strings.num_rows() * line_spacer };
	ph_box.set_fill_color(Color::yellow);

	win.attach(ph_title);
	win.attach(ph_box);
	win.attach(ph_content);

	// Graph.h text box
	Point gh_anchor{ 50,275 };
	TB_strings gh_strings{ "Graph.h:" };
	gh_strings.add("// graphing interface:");
	gh_strings.add("struct Shape { ... };");
	gh_strings.add("...");
	Text gh_title{ gh_anchor, gh_strings.title() };
	Text gh_content1{ Point{ gh_anchor.x + text_indent, gh_anchor.y + line_spacer }, gh_strings.next() };
	Text gh_content2{ Point{ gh_anchor.x + text_indent, gh_anchor.y + line_spacer * 2 }, gh_strings.next() };
	Text gh_content3{ Point{ gh_anchor.x + text_indent, gh_anchor.y + line_spacer * 3 }, gh_strings.next() };
	Rectangle gh_box{ Point{ gh_anchor.x, gh_anchor.y + title_gap }, int(gh_strings.max_length() * pix_char), gh_strings.num_rows() * line_spacer };
	gh_box.set_fill_color(Color::yellow);

	win.attach(gh_title);
	win.attach(gh_box);
	win.attach(gh_content1);
	win.attach(gh_content2);
	win.attach(gh_content3);

	// Graph.cpp text box
	Point gc_anchor{ 25,450 };
	TB_strings gc_strings{ "Graph.cpp:" };
	gc_strings.add("Graph code");
	Text gc_title{ gc_anchor, gc_strings.title() };
	Text gc_content{ Point{ gc_anchor.x + text_indent, gc_anchor.y + line_spacer }, gc_strings.next() };
	Rectangle gc_box{ Point{ gc_anchor.x, gc_anchor.y + title_gap }, int(gc_strings.max_length() * pix_char), gc_strings.num_rows() * line_spacer };
	gc_box.set_fill_color(Color::yellow);

	win.attach(gc_title);
	win.attach(gc_box);
	win.attach(gc_content);

	// window.cpp text box
	Point wc_anchor{ 185, 400 };
	TB_strings wc_strings{ "window.cpp:" };
	wc_strings.add("Window code");
	Text wc_title{ wc_anchor, wc_strings.title() };
	Text wc_content{ Point{ wc_anchor.x + text_indent, wc_anchor.y + line_spacer }, wc_strings.next() };
	Rectangle wc_box{ Point{ wc_anchor.x, wc_anchor.y + title_gap }, int(wc_strings.max_length() * pix_char), wc_strings.num_rows() * line_spacer };
	wc_box.set_fill_color(Color::yellow);

	win.attach(wc_title);
	win.attach(wc_box);
	win.attach(wc_content);

	// chapter12.cpp text box
	Point ch12_anchor{ 75,650 };
	TB_strings ch12_strings{ "chapter12.cpp:" };
	ch12_strings.add("#include \"Graph.h\"");
	ch12_strings.add("#include \"Simple_window.h\"");
	ch12_strings.add("int main() { ... }");
	Text ch12_title{ ch12_anchor, ch12_strings.title() };
	Text ch12_content1{ Point{ ch12_anchor.x + text_indent, ch12_anchor.y + line_spacer }, ch12_strings.next() };
	Text ch12_content2{ Point{ ch12_anchor.x + text_indent, ch12_anchor.y + line_spacer * 2 }, ch12_strings.next() };
	Text ch12_content3{ Point{ ch12_anchor.x + text_indent, ch12_anchor.y + line_spacer * 3 }, ch12_strings.next() };
	Rectangle ch12_box{ Point{ ch12_anchor.x, ch12_anchor.y + title_gap }, int(ch12_strings.max_length() * pix_char), ch12_strings.num_rows() * line_spacer };
	ch12_box.set_fill_color(Color::yellow);

	win.attach(ch12_title);
	win.attach(ch12_box);
	win.attach(ch12_content1);
	win.attach(ch12_content2);
	win.attach(ch12_content3);

	// Simple_window.h text box
	Point sh_anchor{ 215,525 };
	TB_strings sh_strings{ "Simple_window.h:" };
	sh_strings.add("// window interface:");
	sh_strings.add("class Simple_window { ... };");
	sh_strings.add("...");
	Text sh_title{ sh_anchor, sh_strings.title() };
	Text sh_content1{ Point{ sh_anchor.x + text_indent, sh_anchor.y + line_spacer }, sh_strings.next() };
	Text sh_content2{ Point{ sh_anchor.x + text_indent, sh_anchor.y + line_spacer * 2 }, sh_strings.next() };
	Text sh_content3{ Point{ sh_anchor.x + text_indent, sh_anchor.y + line_spacer * 3 }, sh_strings.next() };
	Rectangle sh_box{ Point{ sh_anchor.x, sh_anchor.y + title_gap }, int(sh_strings.max_length() * pix_char), sh_strings.num_rows() * line_spacer };
	sh_box.set_fill_color(Color::yellow);

	win.attach(sh_title);
	win.attach(sh_box);
	win.attach(sh_content1);
	win.attach(sh_content2);
	win.attach(sh_content3);

	// Window.h text box
	Point wh_anchor{ 280,225 };
	TB_strings wh_strings{ "Window.h:" };
	wh_strings.add("// window interface:");
	wh_strings.add("class Window { ... };");
	wh_strings.add("...");
	Text wh_title{ wh_anchor, wh_strings.title() };
	Text wh_content1{ Point{ wh_anchor.x + text_indent, wh_anchor.y + line_spacer }, wh_strings.next() };
	Text wh_content2{ Point{ wh_anchor.x + text_indent, wh_anchor.y + line_spacer * 2 }, wh_strings.next() };
	Text wh_content3{ Point{ wh_anchor.x + text_indent, wh_anchor.y + line_spacer * 3 }, wh_strings.next() };
	Rectangle wh_box{ Point{ wh_anchor.x, wh_anchor.y + title_gap }, int(wh_strings.max_length() * pix_char), wh_strings.num_rows() * line_spacer };
	wh_box.set_fill_color(Color::yellow);

	win.attach(wh_title);
	win.attach(wh_box);
	win.attach(wh_content1);
	win.attach(wh_content2);
	win.attach(wh_content3);

	// GUI.h text box
	Point guih_anchor{ 450,350 };
	TB_strings guih_strings{ "GUI.h:" };
	guih_strings.add("// GUI interface:");
	guih_strings.add("struct In_box { . . . };");
	guih_strings.add("...");
	Text guih_title{ guih_anchor, guih_strings.title() };
	Text guih_content1{ Point{ guih_anchor.x + text_indent, guih_anchor.y + line_spacer }, guih_strings.next() };
	Text guih_content2{ Point{ guih_anchor.x + text_indent, guih_anchor.y + line_spacer * 2 }, guih_strings.next() };
	Text guih_content3{ Point{ guih_anchor.x + text_indent, guih_anchor.y + line_spacer * 3 }, guih_strings.next() };
	Rectangle guih_box{ Point{ guih_anchor.x, guih_anchor.y + title_gap }, int(guih_strings.max_length() * pix_char), guih_strings.num_rows() * line_spacer };
	guih_box.set_fill_color(Color::yellow);

	win.attach(guih_title);
	win.attach(guih_box);
	win.attach(guih_content1);
	win.attach(guih_content2);
	win.attach(guih_content3);

	// GUI.cpp text box
	Point guic_anchor{ 500, 500 };
	TB_strings guic_strings{ "GUI.cpp:" };
	guic_strings.add("GUI code");
	Text guic_title{ guic_anchor, guic_strings.title() };
	Text guic_content{ Point{ guic_anchor.x + text_indent, guic_anchor.y + line_spacer }, guic_strings.next() };
	Rectangle guic_box{ Point{ guic_anchor.x, guic_anchor.y + title_gap }, int(guic_strings.max_length() * pix_char), guic_strings.num_rows() * line_spacer };
	guic_box.set_fill_color(Color::yellow);

	win.attach(guic_title);
	win.attach(guic_box);
	win.attach(guic_content);

	// FLTK headers text box
	Point fh_anchor{ 340, 20 };
	TB_strings fh_strings{ "" };
	fh_strings.add("FLTK headers");
	fh_strings.add("  ");
	Text fh_title{ fh_anchor, fh_strings.title() };
	Text fh_content{ Point{ fh_anchor.x + text_indent, fh_anchor.y + line_spacer }, fh_strings.next() };
	Text fh_content1{ Point{ fh_anchor.x + text_indent, fh_anchor.y + line_spacer * 2 }, fh_strings.next() };
	Rectangle fh_box{ Point{ fh_anchor.x, fh_anchor.y + title_gap }, int(fh_strings.max_length() * pix_char), fh_strings.num_rows() * line_spacer };
	fh_box.set_fill_color(Color::yellow);

	Rectangle fh_box_back1{ Point{ fh_anchor.x  - box_shadow * 2, fh_anchor.y + title_gap - box_shadow * 2}, int(fh_strings.max_length() * pix_char), fh_strings.num_rows() * line_spacer };
	fh_box_back1.set_fill_color(Color::yellow);
	Rectangle fh_box_back2{ Point{ fh_anchor.x - box_shadow, fh_anchor.y + title_gap - box_shadow }, int(fh_strings.max_length() * pix_char), fh_strings.num_rows() * line_spacer };
	fh_box_back2.set_fill_color(Color::yellow);
	
	win.attach(fh_box_back1);
	win.attach(fh_box_back2);
	win.attach(fh_title);
	win.attach(fh_box);
	win.attach(fh_content);
	win.attach(fh_content1);

	// FLTK code text box
	Point fc_anchor{ 550, 110 };
	TB_strings fc_strings{ "" };
	fc_strings.add("FLTK code");
	fc_strings.add("  ");
	Text fc_title{ fc_anchor, fc_strings.title() };
	Text fc_content{ Point{ fc_anchor.x + text_indent, fc_anchor.y + line_spacer }, fc_strings.next() };
	Text fc_content1{ Point{ fc_anchor.x + text_indent, fc_anchor.y + line_spacer * 2 }, fc_strings.next() };
	Rectangle fc_box{ Point{ fc_anchor.x, fc_anchor.y + title_gap }, int(fc_strings.max_length() * pix_char), fc_strings.num_rows() * line_spacer };
	fc_box.set_fill_color(Color::yellow);

	Rectangle fc_box_back1{ Point{ fc_anchor.x - box_shadow * 2, fc_anchor.y + title_gap - box_shadow * 2 }, int(fc_strings.max_length() * pix_char), fc_strings.num_rows() * line_spacer };
	fc_box_back1.set_fill_color(Color::yellow);
	Rectangle fc_box_back2{ Point{ fc_anchor.x - box_shadow, fc_anchor.y + title_gap - box_shadow }, int(fc_strings.max_length() * pix_char), fc_strings.num_rows() * line_spacer };
	fc_box_back2.set_fill_color(Color::yellow);

	win.attach(fc_box_back1);
	win.attach(fc_box_back2);
	win.attach(fc_title);
	win.attach(fc_box);
	win.attach(fc_content);
	win.attach(fc_content1);

	// set up arrow connection points

	// arrow destination points
	Point ph_arrow_in = arrow_in(ph_box, ph_anchor, title_gap);
	Point gh_arrow_in = arrow_in(gh_box, gh_anchor, title_gap);
	Point sh_arrow_in = arrow_in(sh_box, sh_anchor, title_gap);
	Point wh_arrow_in = arrow_in(wh_box, wh_anchor, title_gap);
	Point guih_arrow_in = arrow_in(guih_box, guih_anchor, title_gap);
	Point fh_arrow_in = arrow_in(fh_box, fh_anchor, title_gap);

	// arrow origin points
	Point gh_arrow_out = arrow_out(gh_box, gh_anchor, 0, title_gap);
	Point gc_arrow_out = arrow_out(gc_box, gc_anchor, 25, title_gap);
	Point ch12_arrow_out = arrow_out(ch12_box, ch12_anchor, 10, title_gap);
	Point sh_arrow_out = arrow_out(sh_box, sh_anchor, 0, title_gap);
	Point wc_arrow_out = arrow_out(wc_box, wc_anchor, 20, title_gap);
	Point guic_arrow_out = arrow_out(guic_box, guic_anchor, 30, title_gap);
	Point guih_arrow_out = arrow_out(guih_box, guih_anchor, 70, title_gap);
	Point wh_arrow_out = arrow_out(wh_box, wh_anchor, 0, title_gap);
	Point fc_arrow_out = arrow_out(fc_box, fc_anchor, 0, title_gap);

	// connect the points
	Open_polyline arrow_gh_ph;
	arrow_gh_ph.add(gh_arrow_out);
	arrow_gh_ph.add(ph_arrow_in);
	Circle arrowhead_gh_ph{ ph_arrow_in, 3 };
	arrowhead_gh_ph.set_fill_color(Color::black);
	win.attach(arrow_gh_ph);
	win.attach(arrowhead_gh_ph);

	Open_polyline arrow_gc_gh;
	arrow_gc_gh.add(gc_arrow_out);
	arrow_gc_gh.add(gh_arrow_in);
	Circle arrowhead_gc_gh{ gh_arrow_in, 3 };
	arrowhead_gc_gh.set_fill_color(Color::black);
	win.attach(arrow_gc_gh);
	win.attach(arrowhead_gc_gh);

	Open_polyline arrow_ch12_gh;
	arrow_ch12_gh.add(ch12_arrow_out);
	arrow_ch12_gh.add(gh_arrow_in);
	Circle arrowhead_ch12_gh{ gh_arrow_in, 3 };
	arrowhead_ch12_gh.set_fill_color(Color::black);
	win.attach(arrow_ch12_gh);
	win.attach(arrowhead_gc_gh);

	Open_polyline arrow_ch12_sh;
	arrow_ch12_sh.add(ch12_arrow_out);
	arrow_ch12_sh.add(sh_arrow_in);
	Circle arrowhead_ch12_sh{ sh_arrow_in, 3 };
	arrowhead_ch12_sh.set_fill_color(Color::black);
	win.attach(arrow_ch12_sh);
	win.attach(arrowhead_ch12_sh);

	Open_polyline arrow_wc_wh;
	arrow_wc_wh.add(wc_arrow_out);
	arrow_wc_wh.add(wh_arrow_in);
	Circle arrowhead_wc_wh{ wh_arrow_in, 3 };
	arrowhead_wc_wh.set_fill_color(Color::black);
	win.attach(arrow_wc_wh);
	win.attach(arrowhead_wc_wh);

	Open_polyline arrow_sh_wh;
	arrow_sh_wh.add(sh_arrow_out);
	arrow_sh_wh.add(wh_arrow_in);
	Circle arrowhead_sh_wh{ wh_arrow_in, 3 };
	arrowhead_sh_wh.set_fill_color(Color::black);
	win.attach(arrow_sh_wh);
	win.attach(arrowhead_sh_wh);

	Open_polyline arrow_sh_guih;
	arrow_sh_guih.add(sh_arrow_out);
	arrow_sh_guih.add(guih_arrow_in);
	Circle arrowhead_sh_guih{ guih_arrow_in, 3 };
	arrowhead_sh_guih.set_fill_color(Color::black);
	win.attach(arrow_sh_guih);
	win.attach(arrowhead_sh_guih);

	Open_polyline arrow_guic_guih;
	arrow_guic_guih.add(guic_arrow_out);
	arrow_guic_guih.add(guih_arrow_in);
	Circle arrowhead_guic_guih{ guih_arrow_in, 3 };
	arrowhead_guic_guih.set_fill_color(Color::black);
	win.attach(arrow_guic_guih);
	win.attach(arrowhead_guic_guih);

	Open_polyline arrow_guih_wh;
	arrow_guih_wh.add(guih_arrow_out);
	arrow_guih_wh.add(wh_arrow_in);
	Circle arrowhead_guih_wh{ wh_arrow_in, 3 };
	arrowhead_guih_wh.set_fill_color(Color::black);
	win.attach(arrow_guih_wh);
	win.attach(arrowhead_guih_wh);

	Open_polyline arrow_guih_fh;
	arrow_guih_fh.add(guih_arrow_out);
	arrow_guih_fh.add(fh_arrow_in);
	Circle arrowhead_guih_fh{ fh_arrow_in, 3 };
	arrowhead_guih_fh.set_fill_color(Color::black);
	win.attach(arrow_guih_fh);
	win.attach(arrowhead_guih_fh);

	Open_polyline arrow_gh_fh;
	arrow_gh_fh.add(gh_arrow_out);
	arrow_gh_fh.add(fh_arrow_in);
	Circle arrowhead_gh_fh{ fh_arrow_in, 3 };
	arrowhead_gh_fh.set_fill_color(Color::black);
	win.attach(arrow_gh_fh);
	win.attach(arrowhead_gh_fh);

	Open_polyline arrow_wh_fh;
	arrow_wh_fh.add(wh_arrow_out);
	arrow_wh_fh.add(fh_arrow_in);
	Circle arrowhead_wh_fh{ fh_arrow_in, 3 };
	arrowhead_wh_fh.set_fill_color(Color::black);
	win.attach(arrow_wh_fh);
	win.attach(arrowhead_wh_fh);

	// custom corner origin point for window.h
	Open_polyline arrow_wh_ph;
	arrow_wh_ph.add(Point{ wh_anchor.x, wh_anchor.y + title_gap });
	arrow_wh_ph.add(ph_arrow_in);
	Circle arrowhead_wh_ph{ ph_arrow_in, 3 };
	arrowhead_wh_ph.set_fill_color(Color::black);
	win.attach(arrow_wh_ph);
	win.attach(arrowhead_wh_ph);

	// custom corner origin for FLTK code
	Open_polyline arrow_fc_fh;
	arrow_fc_fh.add(Point{ fc_anchor.x - box_shadow * 2, fc_anchor.y + title_gap - box_shadow * 2 });
	arrow_fc_fh.add(fh_arrow_in);
	Circle arrowhead_fc_fh{ fh_arrow_in, 3 };
	arrowhead_fc_fh.set_fill_color(Color::black);
	win.attach(arrow_fc_fh);
	win.attach(arrowhead_fc_fh);
	
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
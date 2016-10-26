// Ch12E11.cpp
// Chapter 12, Exercise 11 (p.439)
// Draw a series of regular polygons, one inside the other. The innermost
// should be an equilateral triangle, enclosed by a square, enclosed by a
// pentagon, etc. For the mathematically adept only: let all the points of
// each N-polygon touch the sides of the (N+1)-polygon. Hint: The
// trigonometric functions are found in <cmath>.
//
// Note: Draws polygons from Triangle to Octagon. Can be extended to draw
// more polygons by using the same approach as shapes shown.
// All shapes are drawn so that their verticies touch the sides of the
// next greater shape. This required adjustments the start
// positions of each shape to intersect with the prior shape's verticies.
//
// I was able to automatically scale the square's size and position based
// on triangle's size and position. However I couldn't figure out the
// math to automatically scale/move pentagon and higher. As a result, the
// position and size of pentagon and greater are hard-coded and will not
// adjust automatically if the triangle is moved. They will all move
// appropriate if the center point is moved.

#include "../../../std_lib_facilities.h"
#include "../../../Simple_window.h"
#include "../../../Graph.h"

// global variable
const double pi = acos(-1);

// adds x values and y values of two points, respectively
Point operator+(Point& p1, Point& p2)
{
	int x = p1.x + p2.x;
	int y = p1.y + p2.y;
	return Point{ x,y };
}

// returns sum of all angels for regular n-sided polygon
double angle_sum(int num_points)
{
	if (num_points < 3) 
		error("angle_sum() can't create poly with number points:", num_points);
	return pi * (num_points - 2);
}

// returns angle between center and each point of n-sided polygon
double angle(int num_points)
{
	return angle_sum(num_points) / num_points;
}

// returns horizontal distance from polygon center to a point
// @ distance: length of radius (center to point), in pixels
// @ angle: angle leaving center
int get_x(double dist, double angle)
{
	return round(dist * cos(angle));
}

// returns vertical distance from polygon center to a point
// @ distance: length of radius (center to point), in pixels
// @ angle: angle leaving center
int get_y(double dist, double angle)
{
	return round(dist * sin(angle));
}

// Returns Point containing x,y coordinate to represent vertex of n-sided polygon
// @ dist: length of radius (center to point), in pixels
// @ start_angle: initial angle of first vertex; changing angle rotates shape
// @ curr_point: number of rotations from start_angle for current vertex
// @ total_points: number of verticies for this polygon (same as number of sides)
Point get_point(double dist, double start_angle, int curr_point, int total_points)
{
	double total_angle = pi * (total_points - 2);	// sum of interior angles
	double increment = (2 * pi) / total_points;		// angle between verticies
	double angle = start_angle + curr_point * increment;  // current angle

	return Point{ get_x(dist, angle), get_y(dist, angle) };
}

// length of side for equilateral triangle
int triangle_side(const Point& pt1, const Point& pt2)
{
	double a = abs(pt1.y - pt2.y);
	double b = abs(pt1.x - pt2.x);
	return round(sqrt(a*a + b*b));	// pythagorean theorem
}

// returns square distance to ensure that square side = triangle side
int square_distance(double triangle_side, int num_sides)
{
	// sin(angle) = opposite / hypontenuse
	double hypotenuse;						// distance from center to corner
	double half_side = triangle_side / 2 ;	// distance from center to side
	double ang = angle(num_sides) / 2;		// angle to corner
	hypotenuse = half_side / sin(ang);		// solve for hypotenuse
	return ceil(hypotenuse);				// round up
}

int main()
try {
	// setup program's graphical window
	const int win_width = 600;
	const int win_height = 600;
	Simple_window win{ Point{300,300}, win_width,win_height, "Exercise 12" };

	// center point
	Point center{ win_width / 2, win_height / 2 };

	// triangle
	int triangle_points = 3;
	int t_distance = 100;			// arbitrary distance from center to vertex
	double t_start_angle = -pi / 2;	// rotate half turn so first point on top

	Point pt1 = center + get_point(t_distance, t_start_angle, 0, triangle_points);
	Point pt2 = center + get_point(t_distance, t_start_angle, 1, triangle_points);
	Point pt3 = center + get_point(t_distance, t_start_angle, 2, triangle_points);

	double t_side = triangle_side(pt1, pt2);  // required for other shapes

	Closed_polyline triangle;		// create polygon
	triangle.add(pt1);				// and add it's points
	triangle.add(pt2);
	triangle.add(pt3);
	win.attach(triangle);			// attach shape so window draws it

	// square
	int square_points = 4;
	int s_distance = square_distance(t_side, square_points);  // to line shapes up
	double s_start_angle = -pi / 4;	// rotate so shape is box rather than diamond
	Point s_center = center + Point{ 0, int(sin(pi / 4) * s_distance) - t_distance};

	Point ps1 = s_center + get_point(s_distance, s_start_angle, 0, square_points);
	Point ps2 = s_center + get_point(s_distance, s_start_angle, 1, square_points);
	Point ps3 = s_center + get_point(s_distance, s_start_angle, 2, square_points);
	Point ps4 = s_center + get_point(s_distance, s_start_angle, 3, square_points);

	Closed_polyline square;
	square.add(ps1);
	square.add(ps2);
	square.add(ps3);
	square.add(ps4);
	win.attach(square);

	// pentagon
	int pentagon_points = 5;
	int p_distance = 141;
	double p_start_angle = -pi / 2;
	Point p_center = center + Point{ 0, -24 };

	Point pp1 = p_center + get_point(p_distance, p_start_angle, 0, pentagon_points);
	Point pp2 = p_center + get_point(p_distance, p_start_angle, 1, pentagon_points);
	Point pp3 = p_center + get_point(p_distance, p_start_angle, 2, pentagon_points);
	Point pp4 = p_center + get_point(p_distance, p_start_angle, 3, pentagon_points);
	Point pp5 = p_center + get_point(p_distance, p_start_angle, 4, pentagon_points);

	Closed_polyline pentagon;
	pentagon.add(pp1);
	pentagon.add(pp2);
	pentagon.add(pp3);
	pentagon.add(pp4);
	pentagon.add(pp5);
	win.attach(pentagon);

	// hexagon
	int hexagon_points = 6;
	int h_distance = 155;
	double h_start_angle = 0;
	Point h_center = center + Point{ 0, -33 };

	Point ph1 = h_center + get_point(h_distance, h_start_angle, 0, hexagon_points);
	Point ph2 = h_center + get_point(h_distance, h_start_angle, 1, hexagon_points);
	Point ph3 = h_center + get_point(h_distance, h_start_angle, 2, hexagon_points);
	Point ph4 = h_center + get_point(h_distance, h_start_angle, 3, hexagon_points);
	Point ph5 = h_center + get_point(h_distance, h_start_angle, 4, hexagon_points);
	Point ph6 = h_center + get_point(h_distance, h_start_angle, 5, hexagon_points);

	Closed_polyline hexagon;
	hexagon.add(ph1);	hexagon.add(ph2);	hexagon.add(ph3);
	hexagon.add(ph4);	hexagon.add(ph5);	hexagon.add(ph6);
	win.attach(hexagon);

	// heptagon
	int heptagon_points = 7;
	int e_distance = 165;
	double e_start_angle = -pi / 2;
	Point e_center = center + Point{ 0, -40 };

	Point pe1 = e_center + get_point(e_distance, e_start_angle, 0, heptagon_points);
	Point pe2 = e_center + get_point(e_distance, e_start_angle, 1, heptagon_points);
	Point pe3 = e_center + get_point(e_distance, e_start_angle, 2, heptagon_points);
	Point pe4 = e_center + get_point(e_distance, e_start_angle, 3, heptagon_points);
	Point pe5 = e_center + get_point(e_distance, e_start_angle, 4, heptagon_points);
	Point pe6 = e_center + get_point(e_distance, e_start_angle, 5, heptagon_points);
	Point pe7 = e_center + get_point(e_distance, e_start_angle, 6, heptagon_points);

	Closed_polyline heptagon;
	heptagon.add(pe1);	heptagon.add(pe2);	heptagon.add(pe3);	heptagon.add(pe4);
	heptagon.add(pe5);	heptagon.add(pe6);	heptagon.add(pe7);
	win.attach(heptagon);

	// octogon
	int octagon_points = 8;
	int o_distance = 174;
	double o_start_angle = pi / 8;
	Point o_center = center + Point{ 0, -46 };

	Point po1 = o_center + get_point(o_distance, o_start_angle, 0, octagon_points);
	Point po2 = o_center + get_point(o_distance, o_start_angle, 1, octagon_points);
	Point po3 = o_center + get_point(o_distance, o_start_angle, 2, octagon_points);
	Point po4 = o_center + get_point(o_distance, o_start_angle, 3, octagon_points);
	Point po5 = o_center + get_point(o_distance, o_start_angle, 4, octagon_points);
	Point po6 = o_center + get_point(o_distance, o_start_angle, 5, octagon_points);
	Point po7 = o_center + get_point(o_distance, o_start_angle, 6, octagon_points);
	Point po8 = o_center + get_point(o_distance, o_start_angle, 7, octagon_points);

	Closed_polyline octagon;
	octagon.add(po1);	octagon.add(po2);	octagon.add(po3);	octagon.add(po4);
	octagon.add(po5);	octagon.add(po6);	octagon.add(po7);	octagon.add(po8);
	win.attach(octagon);

	// draw shapes
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
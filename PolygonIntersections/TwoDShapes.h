#pragma once
#include <vector>

/*
Reference: https://www.gorillasun.de/blog/an-algorithm-for-polygon-intersections/

*/

constexpr double PI = 3.14159;

//Axis aligned rectangle. (x,y) refers to the top left corner
struct Rectangle
{
	Rectangle(double _x, double _y, double _w, double _h):
		x(_x), y(_y), w(_w), h(_h){}

	bool collidesWith(const Rectangle& other);

	double x, y;
	double w, h;
};


/*	Rotated rectangle. (x, y) represents the center of the rectangle rather than the top
	left corner. The rectangle is assume to be centered at the origin which makes rotation
	simple.
*/
struct RotatedRectangle
{
	RotatedRectangle(double _x, double _y, double _w, double _h);

	std::vector<std::pair<double, double>> getVertices() { return vertices; }

	void rotate(double angleInDegrees);

	void translate(double transX, double transY);

	std::vector<std::pair<double, double>> intersects(const RotatedRectangle& other);

	double x, y;
	double w, h;
	double angle;
	std::vector<std::pair<double, double>> vertices;
};
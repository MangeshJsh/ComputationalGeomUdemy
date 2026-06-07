#include "TwoDShapes.h"
#include <cmath>

namespace
{
/*
  Line intercept math by Paul Bourke http://paulbourke.net/geometry/pointlineplane/

  - Returns the coordinate of the intersection point
  - Returns FALSE if the lines don't intersect

  Coordinates x1, y1, x2 and y2 designate the start and end point of the first line
  Coordinates x3, y3, x4 and y4 designate the start and end point of the second line
*/
bool intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4,
	double& intptX, double& intptY)
{

	// Check if none of the lines are of length 0
	if ((x1 == x2 && y1 == y2) || (x3 == x4 && y3 == y4)) {
		return false;
	}

	double denominator = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// Lines are parallel
	if (denominator == 0) {
		return false;
	}

	double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denominator;
	double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;

	// is the intersection along the segments
	if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
		return false;
	}

	// Return a object with the x and y coordinates of the intersection
	intptX = x1 + ua * (x2 - x1);
	intptY = y1 + ua * (y2 - y1);

	return true;
}
}

bool Rectangle::collidesWith(const Rectangle& other)
{
	if (x < other.x + other.w && other.x < x + w && y < other.y + other.h && other.y < y + h)
		return true;

	return false;
}

RotatedRectangle::RotatedRectangle(double _x, double _y, double _w, double _h)
	:x(_x), y(_y), w(_w), h(_h)
{
	auto halfWidth = w / 2;
	auto halfHeight = h / 2;

	auto topLeft = std::make_pair(x - halfWidth, y - halfHeight);
	auto bottomleft = std::make_pair(x - halfWidth, y + halfHeight);
	auto topRight = std::make_pair(x + halfWidth, y - halfHeight);
	auto bottomRight = std::make_pair(x + halfWidth, y + halfHeight);

	vertices.push_back(topLeft);
	vertices.push_back(bottomleft);
	vertices.push_back(bottomRight);
	vertices.push_back(topRight);
}

std::vector<std::pair<double, double>> RotatedRectangle::getVertices() { return vertices; }

double degreesToRadians(double deg)
{
	return (deg * PI) / 180;
}

void RotatedRectangle::rotate(double angleInDegrees)
{
	auto sinTheta = std::sin(degreesToRadians(angle));
	auto cosTheta = std::cos(degreesToRadians(angle));

	//translate to origin
	double currX = x;
	double currY = y;
	translate(-currX, -currY);

	for (auto& vertex : vertices)
	{
		double rotatedX = vertex.first * cosTheta - vertex.second * sinTheta;
		double rotatedY = vertex.first * sinTheta + vertex.second * cosTheta;
		vertex.first = rotatedX;
		vertex.second = rotatedY;
	}
	translate(currX, currY);
}


void RotatedRectangle::translate(double transX, double transY)
{
	for (auto& vertex : vertices)
	{
		vertex.first = vertex.first + transX;
		vertex.second = vertex.second + transY;
	}

	x = x + transX;
	y = y + transY;
}

std::vector<std::pair<double, double>> RotatedRectangle::intersects(const RotatedRectangle& other)
{


}

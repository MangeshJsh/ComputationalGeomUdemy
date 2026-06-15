#include "GeoUtils.h"

double areaTriangle2D(const Point2d& a, const Point2d& b, const Point2d& c)
{
	auto AB = b - a;
	auto AC = c - a;

	auto result = crossProduct2D(AB, AC); // Area of the parallelogram with AB as diagonal and AC as side.

	return result / 2; //Area of triangle will be half of the parallelogram
}

RelativePosition orientation2D(const Point2d& a, const Point2d& b, const Point2d& c)
{
	auto area = areaTriangle2D(a,b,c);

	if (area > 0 && area < TOLERANCE) area = 0;
	if (area < 0 && area > -TOLERANCE) area = 0;

	if (area > 0) return RelativePosition::LEFT;
	if (area < 0) return RelativePosition::RIGHT;

	auto ab = b - a;
	auto ac = c - a;

	// Two equal mag but opposite direction vectors will have coefficients with opposite signs.
	//For example v = 2i+3j, Neg(v) = -2i-3j. So multiplication of atleast one coefficient 
	//should be less than 0. 

	if (ab[X] * ac[X] < 0 || ab[Y] * ac[Y] < 0) return RelativePosition::BEHIND;
	if (ac.length() > ab.length()) return RelativePosition::BEYOND;
	if (a == c) return RelativePosition::ORIGIN;
	if (b == c) return RelativePosition::DESTINATION;
	return RelativePosition::BETWEEN;
}

bool isIntersecting(const Line<float, DIM2>& l1, const Line<float, DIM2>& l2)
{
	RelativePosition l2StartPtWrtL1 = orientation2D(l1.startPoint(), l1.endPoint(), l2.startPoint());
	RelativePosition l2EndPtWrtL1 = orientation2D(l1.startPoint(), l1.endPoint(), l2.endPoint());

	RelativePosition l1StartPtWrtL2 = orientation2D(l2.startPoint(), l2.endPoint(), l1.startPoint());
	RelativePosition l1EndPtWrtL2 = orientation2D(l2.startPoint(), l2.endPoint(), l1.endPoint());

	if (l2StartPtWrtL1 == RelativePosition::BETWEEN || l2StartPtWrtL1 == RelativePosition::ORIGIN || l2StartPtWrtL1 == RelativePosition::DESTINATION ||
		l2EndPtWrtL1 == RelativePosition::BETWEEN || l2EndPtWrtL1 == RelativePosition::ORIGIN || l2EndPtWrtL1 == RelativePosition::DESTINATION ||
		l1StartPtWrtL2 == RelativePosition::BETWEEN || l1StartPtWrtL2 == RelativePosition::ORIGIN || l1StartPtWrtL2 == RelativePosition::DESTINATION ||
		l1EndPtWrtL2 == RelativePosition::BETWEEN || l1EndPtWrtL2 == RelativePosition::ORIGIN || l1EndPtWrtL2 == RelativePosition::DESTINATION)
	{
		return true;
	}

	return _xor(l2StartPtWrtL1 == RelativePosition::LEFT, l2EndPtWrtL1 == RelativePosition::LEFT) &&
		_xor(l1StartPtWrtL2 == RelativePosition::LEFT, l1EndPtWrtL2 == RelativePosition::LEFT);
}

bool isIntersecting(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d)
{
	return isIntersecting(Line<float, DIM2>(a, b), Line<float, DIM2>(c, d));
}

/*
			|b
			|
	c		| p        d
	--------|----------
	<-------|
	n		|a

p = a + (b -a)t  ----> (1)
p - c and d - c are in the same direction.

 n.(p - c) = 0
 n. (a + (b -a)t - c) = 0
 n.(a-c) + n.(b - a)t = 0

 t = n.(c - a) / n. (b - a)

 insert t in (1) to get the intersection point.
*/
Point2d getIntersectionPoint(const Line<float, DIM2>& l1, const Line<float, DIM2>& l2)
{
	auto a = l1.startPoint();
	auto b = l1.endPoint();
	auto c = l2.startPoint();
	auto d = l2.endPoint();

	auto ab = b - a;
	auto cd = d - c;

	Vector2f n(cd[Y], -cd[X]);

	if (n.dot(ab) == 0) return Point2d(); // lines will be parallel or collinear

	float t = n.dot(c - a) / n.dot(ab);

	return a + (ab * t);
}

Point2d getIntersectionPoint(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d)
{
	return getIntersectionPoint(Line<float, DIM2>(a, b), Line<float, DIM2>(c, d));
}

template<typename T, size_t dim>
static float getAngle(Vector<T, dim> v1, Vector<T, dim> v2)
{
	float numerator = v1.dot(v2);
	float denominator = v1.length() * v2.length();
	return radianToDegree(std::acos(numerator / denominator));
}

float angleBetweenLines2D(const Line<float, DIM2>& l1, const Line<float, DIM2>& l2)
{
	return getAngle(l1.direction(), l2.direction());
}

float angleBetweenLines3D(const Line<float, DIM3>& l1, const Line<float, DIM3>& l2)
{
	return getAngle(l1.direction(), l2.direction());
}

float angleBetweenLineAndPlane(const Line<float, DIM3>& l1, const Plane<float>& plane)
{
	float angleBetweenPlaneNormalAndLine = getAngle(l1.direction(), plane.normal());
	return 90 - angleBetweenPlaneNormalAndLine;
}

//Same as angle between the normals of the two planes
float angleBetweenTwoPlanes(const Plane<float>& plane1, const Plane<float>& plane2)
{
	return getAngle(plane1.normal(), plane2.normal());
}

/*
* for collinear vectors v1 = k * v2
v1[X]   v1[Y]     v1[Z]
----- = ------ = ------
v2[X]   v2[Y]     v2[Z]

all ratios should yield the same value.
*/

bool collinear(Vector3f v1, Vector3f v2)
{
	auto a = v1[X] * v2[Y] - v1[Y] * v2[X];

	auto b = v1[Y] * v2[Z] - v1[Z] * v2[Y];

	auto c = v1[X] * v2[Z] - v1[Z] * v2[X];

	return isEqualD(a, 0.0) && isEqualD(b, 0.0) && isEqualD(c, 0.0);
}

bool collinear(Point3d p1, Point3d p2, Point3d p3)
{
	return collinear(p2 - p1, p3 - p1);
}

bool coplanar(Vector3f v1, Vector3f v2, Vector3f v3)
{
	return isEqualD(scalarTripleProduct(v1, v2, v3), 0.0);
}

bool coplanar(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d)
{
	return coplanar(b - a, c - a, d - a);
}

float distance(const Point3d& p1, const Point3d& p2)
{
	auto a = p1[X] - p2[X] * p1[X] - p2[X];
	auto b = p1[Y] - p2[Y] * p1[Y] - p2[Y];
	auto c = p1[Z] - p2[Z] * p1[Z] - p2[Z];
	return std::sqrt(a+b+c);
}

float distanceSquared(const Point3d& p1, const Point3d& p2)
{
	auto a = p1[X] - p2[X] * p1[X] - p2[X];
	auto b = p1[Y] - p2[Y] * p1[Y] - p2[Y];
	auto c = p1[Z] - p2[Z] * p1[Z] - p2[Z];
	return a + b + c;
}

float distantPointToLine(const Point3d& point, const Line<float, DIM3>& line)
{
	auto pa = point - line.startPoint();
	float t = pa.dot(line.direction()) / (line.direction().length() * line.direction().length());
	Point3d intPt = line.startPoint() + (line.direction() * t);
	return distance(point, intPt);
}

float distancePointToPlane(const Point3d& q, const Plane<float>& plane)
{
	auto n = plane.normal();
	n.normalize();

	auto PQ = q - plane.point();
	return n.dot(PQ);
}

 bool intersectionPlaneAndPlane(const Plane<float>& plane1, const Plane<float>& plane2, Line<float, DIM3>& intersectionLine)
{
	auto dir = crossProduct3D(plane1.normal(), plane2.normal());
	if (isEqualD(dir.length(), 0.0)) return false;

	auto n1Sqr = plane1.normal().length() * plane1.normal().length();
	auto n2Sqr = plane2.normal().length() * plane2.normal().length();
	auto n1DotN2 = plane1.normal().dot(plane2.normal());
	auto d1 = plane1.getD();
	auto d2 = plane2.getD();

	auto denominator = (n1DotN2 * n1DotN2) - (n1Sqr * n2Sqr);

	auto a = ((d2 * n1DotN2) - (d1 * n2Sqr) ) / denominator;

	auto b = ((d1 * n1DotN2) - (d2 * n1Sqr)) / denominator;

	auto pointOnPlane = (plane1.normal() * a) + (plane2.normal() * b);

	intersectionLine =  Line<float, DIM3>(dir, pointOnPlane);

	return true;
}

 bool left(const Point2d& a, const Point2d& b, const Point2d& c)
 {
	 return orientation2D(a, b, c) == RelativePosition::LEFT;
 }

 bool leftOrBeyond(const Point2d& a, const Point2d& b, const Point2d& c)
 {
	 auto orientation = orientation2D(a, b, c);
	 return orientation == RelativePosition::LEFT || orientation == RelativePosition::BEYOND;
 }

 static bool isInterior(const Vertex2d* v1, const Vertex2d* v2)
 {
	 if (leftOrBeyond(v1->point, v1->next->point, v1->prev->point))
	 {
		 //v1 is convex vertex

		 return left(v1->point, v2->point, v1->prev->point) &&
			 left(v2->point, v1->point, v1->next->point);
	 }

	 return !(leftOrBeyond(v1->point, v2->point, v1->next->point) &&
		 leftOrBeyond(v2->point, v1->point, v1->prev->point));
 }

 bool isDiagonal(const Vertex2d* v1, const Vertex2d* v2, PolygonS2d* poly)
 {
	 bool prospect = true;
	 std::vector<Vertex2d*> vertices;

	 if (poly)
	 {
		 vertices = poly->getVertices();
	 }
	 else
	 {
		 auto vertexPtr = v1->next;
		 vertices.push_back((Vertex2d*)v1);
		 while (vertexPtr != v1)
		 {
			 vertices.push_back(vertexPtr);
			 vertexPtr = vertexPtr->next;
		 }
	 }

	 Vertex2d* current, * next;
	 current = vertices[0];

	 do
	 {
		 next = current->next;
		 if (current != v1 && next != v1 && current != v2 && next != v2
			 && isIntersecting(v1->point, v2->point, current->point, next->point))
		 {
			 prospect = false;
			 break;
		 }
		 current = next;

	 } while (current != vertices[0]);

	 return prospect && isInterior(v1, v2) && isInterior(v2, v1);
 }

 float polarAngle(const Point2d& _other, const Point2d& _ref)
 {
	 // Consider the given points as 2D ones which are in XY plane
	 float _x = _other[X] - _ref[X];
	 float _y = _other[Y] - _ref[Y];

	 if ((isEqualD(_x, 0.0)) && (isEqualD(_y, 0.0)))
		 return -1.0;
	 if (isEqualD(_x, 0.0))
		 return ((_y > 0.0) ? 90 : 270);

	 double theta = atan(_y / _x);
	 theta = radianToDegree(theta);

	 if (_x > 0.0)
		 return ((_y >= 0.0) ? theta : 360 + theta);
	 else
		 return (180 + theta);
 }

 float angle(const Vector2f& _v1, const Vector2f& _v2)
 {
	 float dot = _v1.dot(_v2);
	 float v1_mag = _v1.length();
	 float v2_mag = _v2.length();
	 auto deno = v1_mag * v2_mag;
	 if (isEqualD(dot, deno))
		 return 0;

	 return acos(dot / (v1_mag * v2_mag));
 }

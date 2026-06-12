#pragma once
#include "Vector.h"

/*
* n(A,B,C)
* Q(x1, y1, z1)
* P(x, y, z)
n.(P-Q) = 0 : Q is the known point in plane. 
(A, B, C).((x -x1), (y - y1), (z-z1)) = 0
A(x -x1) + B(y-y1) + C(z-z1) = 0
Ax+By+Cz = Ax1+By1+Cz1
Ax+By+Cz = D where D = Ax1+By1+Cz1
*/
template<typename coordinate_type>
class Plane
{
	Vector<coordinate_type, DIM3> m_normal;
	Vector<coordinate_type, DIM3> m_point;
	float d = 0; // dot product of normal with any known point in the plane

public:
	Plane(Vector<coordinate_type, DIM3>& _normal, Vector<coordinate_type, DIM3>& _point)
		: m_normal(_normal),
		m_point(_point),
		d(_normal[X] * _point[X] + _normal[Y] * _point[Y] + _normal[Z] * _point[Z]) // can also use dot product function
	{}

	Plane(Vector<coordinate_type, DIM3>& p1, Vector<coordinate_type, DIM3>& p2, Vector<coordinate_type, DIM3>& p3)
	{
		auto a = p2 - p1;
		auto b = p3 - p1;
		m_normal = crossProduct3D(a, b);
		m_point = p1;
		d = m_normal[X] * p1[X] + m_normal[Y] * p1[Y] + m_normal[Z] * p1[Z];
	}

	Plane(Vector<coordinate_type, DIM3>& _normal, double _d) :
		m_normal(_normal), d(_d){}


	Vector<coordinate_type, DIM3> normal() const { return m_normal; }
	Vector<coordinate_type, DIM3> point() const { return m_point; }
	float getD() const { return d; }
};
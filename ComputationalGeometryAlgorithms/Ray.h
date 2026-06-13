#pragma once

#include "Vector.h"
#include "Point.h"

class Ray
{
public:
	Ray() {	}

	Ray(const Point3d& point, const Vector3f& dir) :
		m_origin(point), m_direction(dir) {	}

	const Point3d& origin() { return m_origin; }
	const Vector3f& direction() { return m_direction; }

	Point3d at(float t)
	{
		return m_origin + (m_direction * t);
	}

private:
	Point3d m_origin;
	Vector3f m_direction;
};
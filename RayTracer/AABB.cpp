#include "AABB.h"

AABB::AABB(const Point3d& a, const Point3d& b)
{
	x = a[X] <= b[X] ? IntervalF(a[X], b[X]) : IntervalF(b[X], a[X]);
	y = a[Y] <= b[Y] ? IntervalF(a[Y], b[Y]) : IntervalF(b[Y], a[Y]);
	z = a[Z] <= b[Z] ? IntervalF(a[Z], b[Z]) : IntervalF(b[Z], a[Z]);
}

AABB::AABB(const AABB& box0, const AABB& box1)
{
	x = IntervalF(box0.x, box1.x);
	y = IntervalF(box0.y, box1.y);
	z = IntervalF(box0.z, box1.z);
}

const IntervalF& AABB::axisInterval(int n) const
{
	if (n == 1) return y;
	if (n == 2) return z;
	return x;
}

bool AABB::hit(const Ray& r, IntervalF ray_t) const
{
	const Point3d& rayOrigin = r.origin();
	const Vector3f& rayDir = r.direction();

	for (int axis = 0; axis < 3; ++axis)
	{
		const IntervalF& axisInt = axisInterval(axis);
		const float adInv = 1.0f / rayDir[axis];

		auto t0 = (axisInt.m_min - rayOrigin[axis]) * adInv;
		auto t1 = (axisInt.m_max - rayOrigin[axis]) * adInv;

		if (t0 < t1)
		{
			if (t0 > ray_t.m_min) ray_t.m_min = t0;
			if (t1 < ray_t.m_max) ray_t.m_max = t1;
		}
		else
		{
			if (t1 > ray_t.m_min) ray_t.m_min = t1;
			if (t0 < ray_t.m_max) ray_t.m_max = t0;
		}

		if (ray_t.m_max <= ray_t.m_min)
		{
			return false;
		}
	}
	return true;
}
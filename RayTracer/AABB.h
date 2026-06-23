#pragma once

#include "Interval.h"
#include "Point.h"
#include "Ray.h"

class AABB
{
public:

	using IntervalF = Interval<float>;

	IntervalF x, y, z;

	AABB() {}

	AABB(const IntervalF& _x, const IntervalF& _y, const IntervalF& _z) :
		x(_x), y(_y), z(_z) {}

	AABB(const Point3d& a, const Point3d& b);

	AABB(const AABB& box0, const AABB& box1);

	const IntervalF& axisInterval(int n) const;

	bool hit(const Ray& r, IntervalF ray_t) const;
};
#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public:

	Sphere(const Point3d center, float radius);

	bool hit(const Ray& r, IntervalF& ray_t, HitRecord& rec) const override;

private:

	Point3d m_center;
	float m_radius;

};
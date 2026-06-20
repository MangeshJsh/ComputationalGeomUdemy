#pragma once

#include "Hittable.h"


class Sphere : public Hittable
{
public:

	Sphere(const Point3d center, float radius, std::shared_ptr<Material> mat);

	bool hit(const Ray& r, const IntervalF& ray_t, HitRecord& rec) const override;

private:

	Point3d m_center;
	float m_radius;
	std::shared_ptr<Material> m_material;

};
#pragma once

#include "Hittable.h"


class Sphere : public Hittable
{
public:

	//stationary sphere
	Sphere(const Point3d center, float radius, std::shared_ptr<Material> mat);

	//moving sphere
	Sphere(const Point3d center1, const Point3d center2, float radius, std::shared_ptr<Material> mat);

	bool hit(const Ray& r, const IntervalF& ray_t, HitRecord& rec) const override;

	AABB boundingBox() const override { return m_boundingBox; }
private:

	Point3d m_center;
	float m_radius;
	std::shared_ptr<Material> m_material;
	AABB m_boundingBox;
	Ray m_displacementVec;
};
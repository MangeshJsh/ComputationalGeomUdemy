#include "Sphere.h"

Sphere::Sphere(const Point3d center, float radius) :
	m_center(center), m_radius(std::fmax(0, radius))
{}

bool Sphere::hit(const Ray& r, IntervalF& ray_t, HitRecord& rec) const
{
	Vector3f oc = m_center - r.origin();
	auto dir = r.direction();
	auto a = dir.length_squared();
	auto h = dir.dot(oc);
	auto c = oc.length_squared() - (m_radius * m_radius);

	auto discriminant = h * h - a * c;
	if (discriminant < 0)
	{
		return false;
	}

	auto sqrtd = std::sqrt(discriminant);
	auto t = (h - sqrtd) / a; //solve for t using ray sphere intersection
	if (t <= ray_t.m_min || t >= ray_t.m_max)
	{
		t = (h + sqrtd) / a;
		if (t <= ray_t.m_min || t >= ray_t.m_max)
		{
			return false;
		}
	}

	rec.t = t;
	rec.point = r.at(t);
	auto outwardNormal = (rec.point - m_center) / m_radius;
	rec.setFaceNormal(r, outwardNormal);

	return true;
}
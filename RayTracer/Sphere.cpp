#include "Sphere.h"

Sphere::Sphere(const Point3d center, float radius, std::shared_ptr<Material> mat) :
	m_center(center), m_radius(std::fmax(0.0f, radius)), m_material(mat)
{}

bool Sphere::hit(const Ray& r, const IntervalF& ray_t, HitRecord& rec) const
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
	if (!ray_t.surrounds(t))
	{
		t = (h + sqrtd) / a;
		if (!ray_t.surrounds(t))
		{
			return false;
		}
	}

	rec.t = t;
	rec.point = r.at(t);
	auto outwardNormal = (rec.point - m_center) / m_radius;
	rec.setFaceNormal(r, outwardNormal);
	rec.material = m_material;
	return true;
}
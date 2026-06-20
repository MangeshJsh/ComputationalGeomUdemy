#include "Material.h"
#include "Utils.h"

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec,
	Color& attenuation, Ray& scattered) const
{
	auto scatterDir = rec.normal + randomUnitVec();

	if (scatterDir.nearZero())
	{
		scatterDir = rec.normal;
	}

	scattered = Ray(rec.point, scatterDir);
	attenuation = m_albedo;
	return true;

}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec,
	Color& attenuation, Ray& scattered) const
{
	Vector3f reflected = reflect(r_in.direction(), rec.normal);
	scattered = Ray(rec.point, reflected);
	attenuation = m_albedo;
	return true;
}
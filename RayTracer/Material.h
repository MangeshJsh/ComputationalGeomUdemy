#pragma once
#include "Hittable.h"
#include "Color.h"

class Material
{
public:
	virtual ~Material() = default;

	virtual bool scatter(const Ray& r_in, const HitRecord& rec,
		Color& attenuation, Ray& scattered) const
	{
		return false;
	}
};

class Lambertian : public Material
{
public:

	Lambertian(const Color& albedo) : m_albedo(albedo) {}

	bool scatter(const Ray& r_in, const HitRecord& rec,
		Color& attenuation, Ray& scattered) const;

private:

	Color m_albedo;
};

class Metal : public Material
{
public:

	Metal(const Color& albedo) : m_albedo(albedo) {}

	bool scatter(const Ray& r_in, const HitRecord& rec,
		Color& attenuation, Ray& scattered) const;

private:

	Color m_albedo;
};
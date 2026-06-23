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


class MetalWithFuzz : public Material
{
public:

	MetalWithFuzz(const Color& albedo, float fuzz) : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1){}

	bool scatter(const Ray& r_in, const HitRecord& rec,
		Color& attenuation, Ray& scattered) const;

private:

	Color m_albedo;
	float m_fuzz;
};
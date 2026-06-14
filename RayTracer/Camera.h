#pragma once
#include <utility>
#include "Vector.h"
#include "Point.h"

#include "Hittable.h"
#include "Color.h"

class Camera
{
public:

	float m_aspectRatio = 1.0f;
	int m_imageWidth = 100;

	void render(const Hittable& world);
	
private:
	void initialize();
	Color rayColor(const Ray& r, const Hittable& world) const;

private:
	int m_imageHeight;
	Vector3f m_cameraCenter;
	float m_focalLength;
	
	float m_viewportHeight = 2.0f;
	float m_viewportWidth;

	Vector3f m_viewport_u;
	Vector3f m_viewport_v;

	Vector3f m_pixel_delta_u;
	Vector3f m_pixel_delta_v;

	Vector3f m_viewport_upper_left;
	Vector3f m_pixel00;
};
#pragma once
#include <utility>
#include "Vector.h"
#include "Point.h"

#include "Hittable.h"
#include "Color.h"
#include "Ray.h"

class Camera
{
public:

	float m_aspectRatio = 1.0f; //Ratio of image width over hight
	int m_imageWidth = 100;     //rendered image width in pixel count
	int m_samplesPerPixel = 10; //number of random samples per pixel
	int m_maxDepth = 10;			//number of ray bounces into the scene

	void render(const Hittable& world);
	
private:
	void initialize();
	Color rayColor(const Ray& r, int max_depth, const Hittable& world) const;

	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	Vector3f sampleSquare() const;

	// Construct a camera ray originating from the origin and directed at randomly sampled
	// point around the pixel location i, j.
	Ray getRay(int i, int j) const;

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

	float m_pixelSamplesScale;
};
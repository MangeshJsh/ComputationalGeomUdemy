#include "Camera.h"
#include "Utils.h"
#include "Material.h"


/*
world.hit(r, IntervalF{ 0.001, INF<float> }, tempRec))
Use tolerance in hit() function (0.001) because intersection point (starting point of
the bounced ray) could be slightly inside the surface in which case the ray will find
intersection with the surface again. Applying tolerance allows to exclude hits very close
to the intersection point.
*/


//Below function generates uniform distribution of reflected rays where each ray has equal probability
// to get reflected in a particular direction.
//Color Camera::rayColor(const Ray& r, int max_depth, const Hittable& world) const
//{
//	HitRecord tempRec;
//
//	if (max_depth <= 0) return Color(0.0, 0.0, 0.0);
//
//	if (world.hit(r, IntervalF{ 0.001, INF<float> }, tempRec))
//	{
//		//return (tempRec.normal + Color(1.0f, 1.0f, 1.0f)) * 0.5;
//
//		auto direction = randomOnHemisphere(tempRec.normal);
//		return rayColor(Ray(tempRec.point, direction), max_depth - 1, world) * 0.5;
//	}
//
//	Vector3f unit_direction = r.direction();
//	unit_direction.normalize();
//	float a = 0.5 * (unit_direction[Y] + 1.0);
//	return Color(1.0f, 1.0f, 1.0f) * (1.0 - a) + Color(0.5f, 0.7f, 1.0f) * a;
//}

//Below function creates LAMBERTIAN reflection where reflected ray has more probabilty
//to reflect closer to surface normal than away from the normal. This is more closer to the
//actual diffuse material.
Color Camera::rayColor(const Ray& r, int max_depth, const Hittable& world) const
{
	HitRecord tempRec;

	if (max_depth <= 0) return Color(0.0, 0.0, 0.0);

	if (world.hit(r, IntervalF{ 0.001, INF<float> }, tempRec))
	{
		Ray scattered;
		Color attenuation;

		if (tempRec.material->scatter(r, tempRec, attenuation, scattered))
		{
			return rayColor(scattered, max_depth - 1, world) * attenuation;
		}

		return Color(0.0f,0.0f,0.0f);
	}

	Vector3f unit_direction = r.direction();
	unit_direction.normalize();
	float a = 0.5 * (unit_direction[Y] + 1.0);
	return Color(1.0f, 1.0f, 1.0f) * (1.0 - a) + Color(0.5f, 0.7f, 1.0f) * a;
}

void Camera::render(const Hittable& world)
{
	initialize();

	std::cout << "P3\n" << m_imageWidth << " " << m_imageHeight << "\n255\n";
	for (int i = 0; i < m_imageHeight; ++i) //height
	{
		for (int j = 0; j < m_imageWidth; ++j) //width
		{
			/*Vector3f pixelCenter = m_pixel00 +
				(m_pixel_delta_u * j) +
				(m_pixel_delta_v * i);

			auto rayDirection = pixelCenter - m_cameraCenter;

			Ray r(m_cameraCenter, rayDirection);

			Color pixelColor = rayColor(r, world);*/


			Color pixelColor(0.0f, 0.0f, 0.0f);
			for (int sample = 0; sample < m_samplesPerPixel; ++sample)
			{
				Ray r = getRay(j, i);
				pixelColor +=  rayColor(r, m_maxDepth, world);
			}
			write_color(std::cout, pixelColor * m_pixelSamplesScale);
		}
	}
}

void Camera::initialize()
{
	m_imageHeight = int(m_imageWidth / m_aspectRatio);
	m_imageHeight = (m_imageHeight < 1) ? 1 : m_imageHeight;

	m_cameraCenter = Point3d(0.0f, 0.0f, 0.0f);

	// Determine viewport dimensions.
	m_focalLength = 1.0;
	m_viewportWidth = m_viewportHeight * float(m_imageWidth / m_imageHeight);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	m_viewport_u = Vector3f(m_viewportWidth, 0.0f, 0.0f);
	m_viewport_v = Vector3f(0.0f, -m_viewportHeight, 0.0f);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	m_pixel_delta_u = m_viewport_u / static_cast<float>(m_imageWidth);
	m_pixel_delta_v = m_viewport_v / static_cast<float>(m_imageHeight);

	m_viewport_upper_left = m_cameraCenter -
		Vector3f(0, 0, m_focalLength)
		- m_viewport_u / 2
		- m_viewport_v / 2;

	m_pixel00 = m_viewport_upper_left +
		(m_pixel_delta_u + m_pixel_delta_v) * 0.5;

	m_pixelSamplesScale = 1.0f / m_samplesPerPixel;
}

Vector3f Camera::sampleSquare() const
{
	return Vector3f{randomf() - 0.5f, randomf() - 0.5f, 0};
}

Ray Camera::getRay(int i, int j) const
{
	Vector3f offset = sampleSquare();

	Vector3f sampledPixelPoint = m_pixel00 + (m_pixel_delta_u * (i + offset[X])) + (m_pixel_delta_v * (j + offset[Y]));

	auto rayOrigin = m_cameraCenter;
	auto rayDirection = sampledPixelPoint - m_cameraCenter;
	return Ray(rayOrigin, rayDirection);
}

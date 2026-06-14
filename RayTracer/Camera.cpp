#include "Camera.h"

Color Camera::rayColor(const Ray& r, const Hittable& world) const
{
	HitRecord tempRec;

	if (world.hit(r, IntervalF{ 0.0, INF<float> }, tempRec))
	{
		return (tempRec.normal + Color(1.0f, 1.0f, 1.0f)) * 0.5;
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
			Vector3f pixelCenter = m_pixel00 +
				(m_pixel_delta_u * j) +
				(m_pixel_delta_v * i);

			auto rayDirection = pixelCenter - m_cameraCenter;

			Ray r(m_cameraCenter, rayDirection);

			Color pixelColor = rayColor(r, world);

			write_color(std::cout, pixelColor);
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
}


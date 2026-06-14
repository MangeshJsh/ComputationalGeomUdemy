#include "ImageParameters.h"
#include "Ray.h"
#include "Color.h"

double hit_sphere(const Point3d& center, double radius, const Ray& r) {
	Vector3f oc = center - r.origin();
	auto dir = r.direction();
	auto a = dir.length_squared();
	auto h = dir.dot(oc);
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = h * h - a * c;
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (h - std::sqrt(discriminant)) / a;
	}
}

Color rayColor(Ray& r)
{
	/*if (hit_sphere(Point3d(0, 0, -1), 0.3, r))
		return Color(1, 0, 0);
	else if (hit_sphere(Point3d(0, 0.3, -1.5), 0.5, r))
		return Color(0, 1, 0);*/

	auto t = hit_sphere(Point3d(0, 0, -1), 0.6, r);
	if (t > 0.0) {
		Vector3f N = r.at(t) - Vector3f(0, 0, -1);
		N.normalize();
		return  Color(N[X] + 1 , N[Y] + 1, N[Z] + 1) * 0.5;
	}
	 
	Vector3f unit_direction = r.direction();
	unit_direction.normalize();
	auto a = 0.5 * (unit_direction[Y] + 1.0);
	return Color(1.0, 1.0, 1.0) * (1.0 - a) +  Color(0.5, 0.7, 1.0) * a;
}

int main()
{
	ImageParams params(16/9, 500);
	auto imageParams = params.getImageParams();
	auto cameraParams = params.getCameraParams();
	
	std::cout << "P3\n" << imageParams.first << " " << imageParams.second << "\n255\n";
	for (int i = 0; i < imageParams.second ; ++i) //height
	{
		for (int j = 0; j < imageParams.first; ++j) //width
		{
			Vector3f pixelCenter = cameraParams.pixel00 +
				(cameraParams.pixel_delta_u * j) +
				(cameraParams.pixel_delta_v * i);

			auto rayDirection = pixelCenter - cameraParams.cameraCenter;

			Ray r(cameraParams.cameraCenter, rayDirection);

			Color pixelColor = rayColor(r);

			write_color(std::cout, pixelColor);
		}
	}

	return 0;
}
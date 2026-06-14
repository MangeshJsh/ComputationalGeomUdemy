#include "ImageParameters.h"

#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"


Color rayColor(Ray& r, const Hittable& obj)
{
	HitRecord tempRec;

	if (obj.hit(r, 0.0, INF, tempRec))
	{
		return (tempRec.normal + Color(1.0f, 1.0f, 1.0f)) * 0.5;
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

	HittableList world;

	world.add(make_shared<Sphere>(Point3d(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(Point3d(0, -100.5, -1), 100));
	
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

			Color pixelColor = rayColor(r, world);

			write_color(std::cout, pixelColor);
		}
	}

	return 0;
}
#include "ImageParameters.h"
#include "Ray.h"
#include "Color.h"

Color rayColor(const Ray& r)
{
	return Color(0, 0, 0);
}

int main()
{
	ImageParams params(16/9, 400);
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
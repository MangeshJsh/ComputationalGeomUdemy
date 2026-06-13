#pragma once
#include <utility>
#include "Vector.h"
#include "Point.h"


class ImageParams
{
public:

	struct CameraParams
	{
		double focalLength;
		Vector3f cameraCenter;
		Vector3f viewport_u;
		Vector3f viewport_v;

		Vector3f pixel_delta_u;
		Vector3f pixel_delta_v;

		Vector3f viewport_upper_left;
		Vector3f pixel00;
	};

	ImageParams(double aspectRatio, int imageWidth, double viewportHeight = 2.0);

	std::pair<double, double> getViewportParams();

	std::pair<int, int> getImageParams();

	CameraParams getCameraParams();

	
private:
	void initializeCameraParams();;

private:

	double m_aspectRatio = 16.0 / 9.0;
	int m_imageHeight = 1;
	int m_imageWidth;
	double m_viewportHeight = 2.0;
	double m_viewportWidth;

	struct CameraParams m_cameraParams;
};
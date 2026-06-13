#pragma once
#include <utility>
#include "Vector.h"
#include "Point.h"


class ImageParams
{
public:

	struct CameraParams
	{
		float focalLength;
		Vector3f cameraCenter;
		Vector3f viewport_u;
		Vector3f viewport_v;

		Vector3f pixel_delta_u;
		Vector3f pixel_delta_v;

		Vector3f viewport_upper_left;
		Vector3f pixel00;
	};

	ImageParams(float aspectRatio, int imageWidth, float viewportHeight = 2.0f);

	std::pair<float, float> getViewportParams();

	std::pair<int, int> getImageParams();

	CameraParams getCameraParams();

	
private:
	void initializeCameraParams();;

private:

	float m_aspectRatio = 16.0f / 9.0f;
	int m_imageHeight = 1;
	int m_imageWidth;
	float m_viewportHeight = 2.0f;
	float m_viewportWidth;

	struct CameraParams m_cameraParams;
};
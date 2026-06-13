#include "ImageParameters.h"

ImageParams::ImageParams(double aspectRatio, int imageWidth, double viewportHeight) :
	m_aspectRatio(aspectRatio), m_imageWidth(imageWidth), m_viewportHeight(viewportHeight)
{
	m_imageHeight = int(m_imageWidth / aspectRatio);
	m_imageHeight = (m_imageHeight < 1) ? 1 : m_imageHeight;

	m_viewportWidth = m_viewportHeight * double(m_imageWidth / m_imageHeight);

	initializeCameraParams();
}

void ImageParams::initializeCameraParams()
{
	m_cameraParams.focalLength = 1.0;
	m_cameraParams.cameraCenter = Point3d(0.0, 0.0, 0.0);
	m_cameraParams.viewport_u = Vector3f(m_viewportWidth, 0.0, 0.0);
	m_cameraParams.viewport_v = Vector3f(0.0, -m_viewportHeight, 0.0);

	m_cameraParams.pixel_delta_u = m_cameraParams.viewport_u / m_imageWidth;
	m_cameraParams.pixel_delta_v = m_cameraParams.viewport_v / m_imageHeight;

	m_cameraParams.viewport_upper_left = m_cameraParams.cameraCenter -
		Vector3f(0, 0, m_cameraParams.focalLength)
		- m_cameraParams.viewport_u / 2
		- m_cameraParams.viewport_v / 2;

	m_cameraParams.pixel00 = m_cameraParams.viewport_upper_left +
		(m_cameraParams.pixel_delta_u + m_cameraParams.pixel_delta_v) * 0.5;
}

std::pair<double, double> ImageParams::getViewportParams()
{
	return std::make_pair(m_viewportWidth, m_viewportHeight);
}

std::pair<int, int> ImageParams::getImageParams()
{
	return std::make_pair(m_imageWidth, m_imageHeight);
}

ImageParams::CameraParams ImageParams::getCameraParams()
{
	return m_cameraParams;
}


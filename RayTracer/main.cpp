#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"


int main()
{
    HittableList world;

    world.add(make_shared<Sphere>(Point3d(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3d(0, -100.5, -1), 100));

    Camera cam;

    cam.m_aspectRatio = 1.0f; // 16.0f / 9.0f;
    cam.m_imageWidth = 400;

    cam.render(world);
	return 0;
}
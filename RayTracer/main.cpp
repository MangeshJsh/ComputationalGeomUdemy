#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Material.h"

int main()
{
    HittableList world;

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = make_shared<MetalWithFuzz>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right = make_shared<MetalWithFuzz>(Color(0.8, 0.6, 0.2), 0.9);

    world.add(make_shared<Sphere>(Point3d(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3d(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3d(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3d(1.0, 0.0, -1.0), 0.5, material_right));

    Camera cam;

    cam.m_aspectRatio = 1.0f; // 16.0f / 9.0f;
    cam.m_imageWidth = 400;
    cam.m_samplesPerPixel = 200;
    cam.m_maxDepth = 10;

    cam.render(world);
	return 0;
}
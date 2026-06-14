#pragma once

#include "Ray.h"

/*
It is important to determine which side of the object the ray is on.
Also, we can always maintain the normal to point outwards or point against the ray.
Here, we keep normal pointing against the ray. 
* if dot(ray, outwardNormal) < 0, then ray is coming from outside the object and hitting the
 front face. Outward normal remains the same in this case. 

* if dot(ray, outwardNormal) > 0, (normal pointing in the same direction as the ray), then
* ray is coming from inside the object and hitting the back face (frontFace = false)
* 
* outwardNormal is assumed to be unit lenght. It can be normalized here but its better to normalize it in
* the geometry code.
 
 */
struct HitRecord
{
	Point3d point;
	Vector3f normal;
	float t;
	bool frontFace;

	void setFaceNormal(const Ray& r, const Vector3f& outwardNormal)
	{
		auto rayDir = r.direction();
		frontFace = rayDir.dot(outwardNormal) < 0.0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

/* Hittable is the object the ray can hit with. */
class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const = 0;
};
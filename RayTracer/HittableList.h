#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
public:
	HittableList() {}
	HittableList(shared_ptr<Hittable> object) { add(object); }

	void add(shared_ptr<Hittable> obj)
	{
		m_objects.push_back(obj);
		m_boundingBox = AABB(m_boundingBox, obj->boundingBox());
	}

	bool hit(const Ray& r, const IntervalF& ray_t, HitRecord& rec) const override
	{
		HitRecord tempRec;
		bool hitAnything = false;
		auto closestSoFar = ray_t.m_max;

		for (const auto& obj : m_objects)
		{
			if (obj->hit(r, IntervalF{ ray_t.m_min, closestSoFar }, tempRec))
			{
				hitAnything = true;
				closestSoFar = tempRec.t;
				rec = tempRec;
			}
		}
		return hitAnything;
	}

	void clear() { m_objects.clear(); }

private:
	std::vector<shared_ptr<Hittable>> m_objects;
	AABB m_boundingBox;

};
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
	}

	bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const override
	{
		HitRecord tempRec;
		bool hitAnything = false;
		auto closestSoFar = tmax;

		for (const auto& obj : m_objects)
		{
			if (obj->hit(r, tmin, tmax, tempRec))
			{
				hitAnything = true;
				if (tempRec.t < closestSoFar)
				{
					closestSoFar = tempRec.t;
					rec = tempRec;
				}
			}
		}
		return hitAnything;
	}

	void clear() { m_objects.clear(); }

private:
	std::vector<shared_ptr<Hittable>> m_objects;

};
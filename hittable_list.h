#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>
#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
public:
	HittableList() {}

	void add(shared_ptr<Hittable> object)
	{
		objects.push_back(object);
	}

	void clear()
	{
		objects.clear();
	}

	bool hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const override
	{
		bool hitted = false;
		float closestHitDist = interval.max;
		HitRecord tmpHitRecord;
		for (const auto& object : objects)
		{
			if (object->hit(ray, Interval(interval.min, closestHitDist), tmpHitRecord))
			{
				hitted = true;
				hitRecord = tmpHitRecord;
				closestHitDist = hitRecord.t;
			}
		}

		return hitted;
	}

	std::vector<shared_ptr<Hittable>> objects;
};

#endif // HITTABLE_LIST_H
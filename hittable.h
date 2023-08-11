#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct HitRecord
{
	Vec3 pos;
	float t;

	Vec3 normal;
	bool frontFace;
	char _padding[3];
};

class Hittable {
public:
	virtual bool hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const = 0;
};

#endif // #ifndef HITTABLE_H
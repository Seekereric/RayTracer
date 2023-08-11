#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
public:
	Sphere(Vec3 in_center, float in_radius) : center(in_center), radius(in_radius) {};

	bool hit(const Ray& ray, Interval interval, HitRecord& hitRecord) const override
	{
		// a - sphere: (P - c)^2 = r^2
		// b - ray: P(t) = o + dt
		// insert b into a we have: d^2 * t^2 + 2 * (o - c) * d * t + (o - c)^2 - r^2 = 0
		// calculate discriminant b^2 - 4ac for this quadratic equation
		// >0: two solution (intersections)
		// =0: one solution (intersections)
		// <0: no solution (intersections)

		// original method
		//float a = r.dir.lengthSquare();
		//float b = 2 * dot(r.origin - center, r.dir);
		//float c = (r.origin - center).lengthSquare() - radius * radius;
		//float discriminant = b * b - 4 * a * c;
		//if (discriminant < 0)
		//	return -1.0f;
		//return (-b - sqrt(discriminant)) / (2.0f * a);

		// optimized method (please reference 6.2 for math deduction)
		float a = ray.dir.lengthSquare();
		float half_b = dot(ray.origin - center, ray.dir);
		float c = (ray.origin - center).lengthSquare() - radius * radius;
		float discriminant = half_b * half_b - a * c;
		float sqrtDiscriminant = sqrt(discriminant);
		
		if (discriminant < 0)
			return false;

		float root = (-half_b - sqrtDiscriminant) / a;
		if (root <= interval.min || root >= interval.max)
		{
			root = (-half_b + sqrtDiscriminant) / a;
			if (root <= interval.min || root >= interval.max)
				return false;
		}

		hitRecord.t = root;
		hitRecord.pos = ray.at(root);
		hitRecord.normal = (hitRecord.pos - center) / radius;
		hitRecord.frontFace = dot(ray.dir, hitRecord.normal) < 0;
		hitRecord.normal = hitRecord.frontFace ? hitRecord.normal : -hitRecord.normal; // 6.4 ray casting to front or back face of the surface? Different side different rendering

		return true;
	}

private:
	Vec3 center;
	float radius;
};

#endif // #ifndef SPHERE_H
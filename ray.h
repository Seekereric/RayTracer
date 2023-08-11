#ifndef RAY_H
#define RAY_H

#include<iostream>
#include"vec3.h"

class Ray {
public:
	Ray() {}
	Ray(const Point3& in_origin, const Vec3& in_dir) : origin(in_origin), dir(in_dir) {}

	Point3 at(float t) const
	{
		return origin + dir * t;
	}

	Point3 origin;
	Vec3 dir;
};

#endif // RAY_H
#ifndef RAY_H
#define RAY_H

#include<iostream>
#include"vec3.h"

class ray {
public:
	ray() {}
	ray(const point3& in_origin, const vec3& in_dir) : origin(in_origin), dir(in_dir) {}

	point3 at(float t) const
	{
		return origin + dir * t;
	}

	point3 origin;
	vec3 dir;
};

#endif // RAY_H
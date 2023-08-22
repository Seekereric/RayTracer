#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"

class Interval {
public:
	Interval() : min(-infinity), max(+infinity) {}
	Interval(float in_min, float in_max) : min(in_min), max(in_max) {}

	bool contain(const float x) const
	{
		return x >= min && x <= max;
	}

	bool surround(const float x) const
	{
		return x > min && x < max;
	}

	float clamp(const float x) const
	{
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	static const Interval empty, universe;

	float min, max;
};

const static Interval empty(+infinity, -infinity);
const static Interval universe(-infinity, +infinity);

#endif //INTERVAL_H
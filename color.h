#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"
#include "interval.h"

void ppmWritePixelColor(std::ostream& out, Color c)
{
	out << static_cast<int>(c.r * 255.999f) << ' ' 
		<< static_cast<int>(c.g * 255.999f) << ' ' 
		<< static_cast<int>(c.b * 255.999f) << '\n';
}

void ppmWritePixelColor(std::ostream& out, Color c, int sampleCount)
{
	static const Interval interval(0.0f, 0.9999f);
	out << static_cast<int>(interval.clamp(c.r / sampleCount) * 255.999f) << ' ' 
		<< static_cast<int>(interval.clamp(c.g / sampleCount) * 255.999f) << ' ' 
		<< static_cast<int>(interval.clamp(c.b / sampleCount) * 255.999f) << '\n';
}
#endif // !COLOR_H

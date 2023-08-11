#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"

void ppmWritePixelColor(std::ostream& out, Color c)
{
	out << static_cast<int>(c.r * 255.999f) << ' ' << static_cast<int>(c.g * 255.999f) << ' ' << static_cast<int>(c.b * 255.999f) << '\n';
}

#endif // !COLOR_H

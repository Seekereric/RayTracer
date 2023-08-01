#include <iostream>

#include "vec3.h"
#include "color.h"

int main()
{

	const int imgWidth = 256;
	const int imgHeight = 256;

	std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

	for (int i = 0; i < imgHeight; i++)
	{
		std::cerr << "\rScanline remaining: " << imgHeight - i << ' ' << std::flush;
		for (int j = 0; j < imgWidth; j++)
		{
			float r = float(j) / (imgWidth - 1);
			float g = 1.0f - float(i) / (imgHeight - 1);
			float b = 0.25f;

			ppmWritePixelColor(std::cout, color(r, g, b));
		}
	}

	std::cerr << "Done.\n";
}
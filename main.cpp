#include <iostream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

bool hitSphere(ray r, vec3 center, float radius)
{
	// a - sphere: (P - c)^2 = r^2
	// b - ray: P(t) = o + dt
	// insert b into a we have: d^2 * t^2 + 2 * (o - c) * d * t + (o - c)^2 - r^2 = 0
	// calculate discriminant b^2 - 4ac for this quadratic equation
	// >0: two solution (intersections)
	// =0: one solution (intersections)
	// <0: no solution (intersections)
	float a = r.dir.lengthSquare();
	float b = 2 * dot(r.origin - center, r.dir);
	float c = (r.origin - center).lengthSquare() - radius * radius;

	return b * b - 4 * a * c > 0;
}

color rayColor(ray r)
{
	if (hitSphere(r, point3(0, 0, -1), 0.5))
		return color(1, 0, 0);
	vec3 dir = r.dir.normalize();
	float t = (dir.y + 1) * 0.5f;
	return t * color(0.5f, 0.7f, 1.0f) + (1 - t) * color(1.0f, 1.0f, 1.0f);
}

int main()
{
	const float aspectRatio = 16.0f / 9.0f;

	const int imgHeight = 400;
	const int imgWidth  = int(imgHeight * aspectRatio);

	const float viewportHeight = 2.0;
	const float viewportWidth = viewportHeight * aspectRatio;

	const vec3 horizontal = vec3(imgWidth, 0, 0);
	const vec3 vertical = vec3(0, imgHeight, 0);

	const point3 focalPoint = vec3(0, 0, 0);
	const float focalLength = 1.0;

	const vec3 bottomLeftCorner = vec3(-viewportWidth / 2.0, -viewportHeight / 2.0, -focalLength);

	std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

	// scanline rendering start from the top left
	for (int i = 0; i < imgHeight; i++)
	{
		std::cerr << "\rScanline remaining: " << imgHeight - i << ' ' << std::flush;
		for (int j = 0; j < imgWidth; j++)
		{
			float pixelPosX = bottomLeftCorner.x + float(j) / (imgWidth - 1) * viewportWidth;
			float pixelPosY = bottomLeftCorner.y + float(imgHeight - 1 - i) / (imgHeight - 1) * viewportHeight;

			ray r = ray(focalPoint, vec3(pixelPosX, pixelPosY, -focalLength) - focalPoint);

			color c = rayColor(r);

			ppmWritePixelColor(std::cout, c);
		}
	}

	std::cerr << "Done.\n";
}
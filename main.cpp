#include <iostream>

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"


Color rayColor(const Ray& r, const HittableList& world)
{
	HitRecord hitRecord;
	if (world.hit(r, Interval(0, infinity), hitRecord))
	{
		return 0.5 * (hitRecord.normal + Vec3(1.0));
	}

	Vec3 dir = r.dir.normalize();
	float t = (dir.y + 1) * 0.5f;
	return t * Color(0.5f, 0.7f, 1.0f) + (1 - t) * Color(1.0f, 1.0f, 1.0f);
}

int main()
{
	HittableList world;
	world.add(make_shared<Sphere>(Vec3(0, 0, -1), 0.5f));
	world.add(make_shared<Sphere>(Vec3(0, -100.5, -1), 100.0f));

	const float aspectRatio = 16.0f / 9.0f;

	const int imgHeight = 400;
	const int imgWidth  = int(imgHeight * aspectRatio);

	const float viewportHeight = 2.0f;
	const float viewportWidth = viewportHeight * aspectRatio;

	const Vec3 horizontal = Vec3(imgWidth, 0, 0);
	const Vec3 vertical = Vec3(0, imgHeight, 0);

	const Point3 focalPoint = Vec3(0, 0, 0);
	const float focalLength = 1.0f;

	const Vec3 bottomLeftCorner = Vec3(-viewportWidth / 2.0f, -viewportHeight / 2.0f, -focalLength);

	std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

	// scanline rendering start from the top left
	for (int i = 0; i < imgHeight; i++)
	{
		std::cerr << "\rScanline remaining: " << imgHeight - i << ' ' << std::flush;
		for (int j = 0; j < imgWidth; j++)
		{
			float pixelPosX = bottomLeftCorner.x + float(j) / (imgWidth - 1) * viewportWidth;
			float pixelPosY = bottomLeftCorner.y + float(imgHeight - 1 - i) / (imgHeight - 1) * viewportHeight;

			Ray r = Ray(focalPoint, Vec3(pixelPosX, pixelPosY, -focalLength) - focalPoint);


			Color c = rayColor(r, world);

			ppmWritePixelColor(std::cout, c);
		}
	}

	std::cerr << "Done.\n";
}
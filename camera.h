#ifndef CAMREA_H
#define CAMERA_H
#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"

class Camera {
public:

	void render(const HittableList& world)
	{
		initialize();

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

	float aspectRatio;
	int imgHeight;
	int imgWidth;

private:
	void initialize()
	{
		viewportHeight = 2.0f;
		viewportWidth = viewportHeight * aspectRatio;

		horizontal = Vec3(imgWidth, 0, 0);
		vertical = Vec3(0, imgHeight, 0);

		focalPoint = Vec3(0, 0, 0);
		focalLength = 1.0f;

		bottomLeftCorner = Vec3(-viewportWidth / 2.0f, -viewportHeight / 2.0f, -focalLength);
	}

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

	float viewportHeight;
	float viewportWidth;
	Vec3 horizontal;
	Vec3 vertical;
	Point3 focalPoint;
	float focalLength;
	Vec3 bottomLeftCorner;
};

#endif // !CAMREA_H

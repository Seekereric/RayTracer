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
				Color c(0, 0, 0);

				float pixelPosX = topLeftCorner.x + j * viewportDeltaU;
				float pixelPosY = topLeftCorner.y + i * viewportDeltaV;
				Vec3 pixelCenter = Vec3(pixelPosX, pixelPosY, -focalLength);

				for (int k = 0; k < samplesPerPixel; k++)
				{
					// sampling within the 0.5 pixel range around the pixel center
					Vec3 offset((-0.5f + randomNum()) * viewportDeltaU, (-0.5f + randomNum()) * viewportDeltaV, 0);
					Ray r = Ray(focalPoint, normalize((pixelCenter + offset) - focalPoint));

					c += rayColor(r, world, maxDepth);
				}
				

				ppmWritePixelColor(std::cout, c, samplesPerPixel);
			}
		}

		std::cerr << "Done.\n";
	}

	float aspectRatio;
	int imgHeight;
	int imgWidth;
	int samplesPerPixel;
	int maxDepth;

private:
	void initialize()
	{
		viewportHeight = 2.0f;
		viewportWidth = viewportHeight * aspectRatio;

		viewportDeltaU = viewportWidth / imgWidth; 
		viewportDeltaV = -viewportHeight / imgHeight;

		focalPoint = Vec3(0, 0, 0);
		focalLength = 1.0f;

		// + 0.5 so it's on the pixel center
		topLeftCorner = Vec3(-viewportWidth * 0.5f + viewportDeltaU * 0.5f, viewportHeight * 0.5f + viewportDeltaV * 0.5f, -focalLength);
	}

	Color rayColor(const Ray& r, const HittableList& world, int depth)
	{
		if (depth <= 0)
			return Color(0, 0, 0);

		HitRecord hitRecord;
		if (world.hit(r, Interval(0.001f, infinity), hitRecord))
		{
			// Uniform reflection
			//Vec3 randomDir = randomPosInsidePositiveHemisphere(hitRecord.normal).normalize();

			// Lambertian reflection
			Vec3 randomDir = normalize(hitRecord.normal + randomPosInsideUnitSphere().normalize());

			return 0.5 * rayColor(Ray(hitRecord.pos, randomDir), world, depth - 1);
		}

		Vec3 dir = r.dir.normalize();
		float t = (dir.y + 1) * 0.5f;
		return t * Color(0.5f, 0.7f, 1.0f) + (1 - t) * Color(1.0f, 1.0f, 1.0f);
	}

	float viewportHeight;
	float viewportWidth;
	float viewportDeltaU;
	float viewportDeltaV;
	Point3 focalPoint;
	float focalLength;
	Vec3 topLeftCorner;
};

#endif // !CAMREA_H

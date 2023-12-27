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

				//float pixelPosX = topLeftCorner.x + j * viewportDeltaU;
				//float pixelPosY = topLeftCorner.y + i * viewportDeltaV;
				//Vec3 pixelCenter = Vec3(pixelPosX, pixelPosY, -focalLength);

				Vec3 pixelCenter = topLeftCorner + viewportDeltaU * (float)j + viewportDeltaV * (float)i;

				for (int k = 0; k < samplesPerPixel; k++)
				{
					// sampling within the 0.5 pixel range around the pixel center
					Vec3 offset((-0.5f + randomNum()) * viewportDeltaU + (-0.5f + randomNum()) * viewportDeltaV);
					Vec3 defocusRandomPos = defocusDiskSample();
					Ray r = Ray(defocusRandomPos, normalize((pixelCenter + offset) - defocusRandomPos));

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
	float vFov = 90.0f;
	float defocusAngle = 0; // Simulating aperture
	float focusLength = 10.0f; // Simulating where to focus
	Vec3 lookFrom = Vec3(0.0f, 0.0f, -1.0f);
	Vec3 lookAt = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 worldUp = Vec3(0.0f, 1.0f, 0.0f);

private:
	void initialize()
	{

		// tan(vFov/2) = h / d, h = half viewport image height, d = focal length
		float h = tanf(degreesToRadians(vFov / 2.0f)) * fabs(focusLength);

		//viewportHeight = 2.0f;
		viewportHeight = 2 * h;
		viewportWidth = viewportHeight * aspectRatio;

		forward = normalize(lookFrom - lookAt);
		right = normalize(cross(worldUp, forward));
		up = cross(forward, right);

		viewportDeltaU = right * viewportWidth / (float)imgWidth; 
		viewportDeltaV = -up * viewportHeight / (float)imgHeight;

		// + 0.5 so it's on the pixel center
		//topLeftCorner = Vec3(-viewportWidth * 0.5f + viewportDeltaU * 0.5f, viewportHeight * 0.5f + viewportDeltaV * 0.5f, -focalLength);
		topLeftCorner = (lookFrom - focusLength * forward) + (-right * viewportWidth / 2.0f) + (up * viewportHeight / 2.0f);
		topLeftCorner = topLeftCorner + 0.5 * (viewportDeltaU + viewportDeltaV);
	}

	Vec3 defocusDiskSample()
	{
		float defocusRadius = focusLength * tanf(degreesToRadians(defocusAngle));
		Vec3 randomPosInDisk = randomPosInsideUnitDisk();

		// Convert from viewport space to world space
		Vec3 defocusDiskPos = lookFrom + randomPosInDisk.x * defocusRadius * right + randomPosInDisk.y * defocusRadius * up;

		return defocusDiskPos;
	}

	Color rayColor(const Ray& r, const HittableList& world, int depth)
	{
		if (depth <= 0)
			return Color(0, 0, 0);

		HitRecord hitRecord;
		if (world.hit(r, Interval(0.001f, infinity), hitRecord))
		{
			Color attenuation;
			Ray out;
			if(hitRecord.mat->scatter(r, hitRecord, attenuation, out))
				return attenuation * rayColor(out, world, depth - 1);
			return Color(0, 0, 0);
		}

		Vec3 dir = r.dir.normalize();
		float t = (dir.y + 1) * 0.5f;
		return t * Color(0.5f, 0.7f, 1.0f) + (1 - t) * Color(1.0f, 1.0f, 1.0f);
	}

	float viewportHeight;
	float viewportWidth;
	Vec3 viewportDeltaU;
	Vec3 viewportDeltaV;
	Vec3 topLeftCorner;
	Vec3 forward;
	Vec3 right;
	Vec3 up;
};

#endif // !CAMREA_H

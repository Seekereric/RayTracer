#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

class HitRecord;

class Material {
public:
	virtual ~Material() = default;

	virtual bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const = 0;
};

// Diffuse
class Lambertian : public Material{
public:
	Lambertian(const Color& c) : albedo(c) {}

	bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override
	{
		// Uniform reflection
		//Vec3 randomDir = randomPosInsidePositiveHemisphere(hitRecord.normal).normalize();

		// Lambertian reflection
		//Vec3 randomDir = normalize(hitRecord.normal + randomPosInsideUnitSphere().normalize());

		Vec3 scatterDir = normalize(hitRecord.normal + randomPosInsideUnitSphere().normalize());
		if (scatterDir.nearZero())
			scatterDir = hitRecord.normal;
		scattered.dir = scatterDir;
		scattered.origin = hitRecord.pos;
		attenuation = albedo;
		return true;
	}
private:
	Color albedo;
};

// Metal
class Metal : public Material {
public:
	Metal(const Color& c, const float f) : albedo(c), fuzziness(f < 1 ? f : 1) {}

	bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override
	{
		Vec3 scatterDir = reflect(ray.dir, hitRecord.normal) + fuzziness * randomPosInsideUnitSphere().normalize();
		scattered.dir = scatterDir.normalize();
		scattered.origin = hitRecord.pos;
		attenuation = albedo;
		return true;
	}

private:
	Color albedo;
	float fuzziness;
};
#endif // MATERIAL_H
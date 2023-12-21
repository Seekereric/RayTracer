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

// Dielectric
class Dielectric : public Material {
public:
	Dielectric(float indexOfRefraction) : ir(indexOfRefraction) {}

	bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override
	{
		// snell's law: 
		// eta * sin(theta) = eta` * sine(theta`)

		float refractiveIndexRatio = hitRecord.frontFace ? 1.0f / ir : ir;
		float cos_theta = dot(-ray.dir, hitRecord.normal);
		float sin_theta = sqrtf(1 - cos_theta * cos_theta);

		Vec3 scatterDir;
		if (refractiveIndexRatio * sin_theta > 1 || reflectance(cos_theta, refractiveIndexRatio) > randomNum())
		{
			// reflect
			scatterDir = reflect(ray.dir, hitRecord.normal);
		}
		else
		{
			// refract
			scatterDir = refract(ray.dir, hitRecord.normal, refractiveIndexRatio);
		}
		 
		scattered.dir = scatterDir;
		scattered.origin = hitRecord.pos;
		attenuation = Vec3(1.0f, 1.0f, 1.0f);

		return true;
	}
private:
	float ir;

	float reflectance(float cosine, float ref_idx) const
	{
		// Schlick's approximation, the result is from 0 to 1.
		// The more we look at a surface from a obligue angle the more we are seeing reflect lights
		float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
		r0 = r0 * r0;
		float res = r0 + (1.0f - r0) * powf((1.0f - cosine), 5);
		return res;
	}
};
#endif // MATERIAL_H
#include <iostream>

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"


int main()
{
	shared_ptr<Lambertian> mat_ground = make_shared<Lambertian>(Color(0.8f, 0.8f, 0));
	//shared_ptr<Lambertian> mat_center = make_shared<Lambertian>(Color(0.7f, 0.3f, 0.3f));
	//shared_ptr<Metal> mat_left = make_shared<Metal>(Color(0.8f, 0.8f, 0.8f), 0.3f);
	//shared_ptr<Dielectric> mat_center = make_shared<Dielectric>(1.5f);
	shared_ptr<Lambertian> mat_center = make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f));
	shared_ptr<Dielectric> mat_left = make_shared<Dielectric>(1.5f);
	shared_ptr<Metal> mat_right = make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 0.0f);

	//shared_ptr<Lambertian> mat_test1 = make_shared<Lambertian>(Color(0, 0, 1));
	//shared_ptr<Lambertian> mat_test2 = make_shared<Lambertian>(Color(1, 0, 0));

	//float R = cos(pi / 4);

	HittableList world;
	//world.add(make_shared<Sphere>(Vec3(-R, 0, -1), R, mat_test1)); 
	//world.add(make_shared<Sphere>(Vec3( R, 0, -1), R, mat_test2));
	world.add(make_shared<Sphere>(Vec3(0, 0, -1.0f), 0.5f, mat_center));
	world.add(make_shared<Sphere>(Vec3(1.0f, 0, -1.0f), 0.5f, mat_right));
	world.add(make_shared<Sphere>(Vec3(0, -100.5f, -1.0f), 100.0f, mat_ground));

	// hollow glass sphere: space between big and small sphere is glass, space inside small sphere is air
	world.add(make_shared<Sphere>(Vec3(-1.0f, 0, -1.0f), 0.5f, mat_left));
	world.add(make_shared<Sphere>(Vec3(-1.0f, 0, -1.0f), -0.4f, mat_left));

	Camera camera;
	camera.vFov = 20.0f;
	camera.worldUp = Vec3(0.0f, 1.0f, 0.0f);
	camera.lookAt = Vec3(0.0f, 0.0f, -1.0f);
	camera.lookFrom = Vec3(-2.0f, 2.0f, 1.0f);
	camera.aspectRatio = 16.0f / 9.0f;
	camera.imgHeight = 400;
	camera.imgWidth  = int(camera.imgHeight * camera.aspectRatio);
	camera.samplesPerPixel = 20;
	camera.maxDepth = 50;
	camera.render(world);
}
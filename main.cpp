#include <iostream>

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"
#include "camera.h"



int main()
{
	HittableList world;
	world.add(make_shared<Sphere>(Vec3(0, 0, -1.0f), 0.5f));
	world.add(make_shared<Sphere>(Vec3(0, -100.5f, -1.0f), 100.0f));

	Camera camera;
	camera.aspectRatio = 16.0f / 9.0f;
	camera.imgHeight = 400;
	camera.imgWidth  = int(camera.imgHeight * camera.aspectRatio);
	camera.samplesPerPixel = 10;
	camera.maxDepth = 50;
	camera.render(world);
}
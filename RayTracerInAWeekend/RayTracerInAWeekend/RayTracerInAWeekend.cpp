#pragma once
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "FileHandler.h"
#include "RayTracerInAWeekend.h"
#include "Camera.h"
#include "vec3.h"
#include <limits>


float hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.get_origin() - center;
	float a = dot(r.get_direction(), r.get_direction());
	float b = 2.0f * dot(oc, r.get_direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1;
	}
	else
	{
		return (-b - std::sqrt(discriminant)) / (2.0f*a);
	}
}
vec3 set_color(const ray& r, const hitable& world, int depth)
{
	hitInfo info;

    if (depth <= 0)
    {
        return ColorRGB(0,0,0);
    }

	if (world.hit(r, 0.0, std::numeric_limits<float>::max(), info))
	{
        point3 target = info.p + info.normal + randPointInUnitSphere();
        return 0.5*set_color(ray(info.p, target - info.p), world, depth-1); //vec3(info.normal.x() + 1, info.normal.y() + 1, info.normal.z() + 1);
	}

	vec3 normalizedDir = r.get_direction();
	normalizedDir.normalize();
	float t = 0.5f*(normalizedDir.y() + 1.0f);
	return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	const auto DAR = 16.0f / 9.0f;
	const int imageWidth = 200;
    const int imageHeight = static_cast<int>(imageWidth / DAR);
	const int samplesPerPixel = 5;
    const int max_depth = 3;

	ClearFile("image.ppm");
	std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
	std::string line = "P3\n" + std::to_string(imageWidth) + " " + std::to_string(imageHeight) + "\n255\n";
	WriteLine("image.ppm", line);

	vec3 botLeft(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0, 0, 0);

	hitable_list world;
	world.add(std::make_shared<sphere>(point3(0.0f, 0.0f, -1.0f), 0.5f, nullptr ));
	world.add(std::make_shared<sphere>(point3(0.0f, -100.5f, -1.0f), 100.0f, nullptr));

	Camera cam;
	window window;
	for (int j = imageHeight - 1; j >= 0; j--)
	{
		for (int i=0; i < imageWidth; i++)
		{
			ColorRGB pixelColor = ColorRGB(0.0f, 0.0f, 0.0f);
			
			for (int s=0; s < samplesPerPixel; s++) 
			{
				window.pixelProgressX = (float(i) + randf()) / (float(imageWidth));
				window.pixelProgressY = (float(j) + randf()) / (float(imageHeight));

				vec3 dir = botLeft + window.pixelProgressX * horizontal + window.pixelProgressY * vertical;
				ray r = cam.getRay(origin, dir);

				pixelColor += set_color(r, world, max_depth);

			}
			// Divide the color total by the number of samples
			pixelColor /= samplesPerPixel;

            line = WriteColor(pixelColor, samplesPerPixel);
			WriteLine("image.ppm", line);
		}
	}
	return 0;
}

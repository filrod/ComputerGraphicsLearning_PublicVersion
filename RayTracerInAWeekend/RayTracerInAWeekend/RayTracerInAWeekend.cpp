#pragma once
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "FileHandler.h"
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
vec3 set_color(const ray& r, sphere* s)
{
	hitInfo info;
	//if (s->hit(r, 0.0, std::numeric_limits<float>::max(), info))
	//{
	float time = hit_sphere(s->center, s->radius, r); //s->hit(r, 0.0, std::numeric_limits<float>::max(), info);
	if (time > 0.0f)
	{
		vec3 normalVec = r.get_point_at(time) - vec3(0, 0, -1);
		normalVec.normalize();
		return 0.5f * ( normalVec + vec3(1, 1, 1) ) ;
	}
	//}
	vec3 uint_dir = r.get_direction();
	uint_dir.normalize();

	time = 0.5f*uint_dir.y() + 1.0f;
	return (1.0f - time)*vec3(1.0f, 1.0f, 1.0f) + time * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	int nx = 200;
	int ny = 100;

	ClearFile("image.ppm");
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	std::string line = "P3\n" + std::to_string(nx) + " " + std::to_string(ny) + "\n255\n";
	WriteLine("image.ppm", line);

	vec3 botLeft(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0, 0, 0);

	struct window
	{
		float pixelProgressX;
		float pixelProgressY;
	};
	window window;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i=0; i < nx; i++)
		{
			window.pixelProgressX = float(i) / float(nx);
			window.pixelProgressY = float(j) / float(ny);

			vec3 dir = botLeft + window.pixelProgressX * horizontal + window.pixelProgressY * vertical;
			ray r(origin, dir);

			sphere s = sphere(point3(0, 0, -1), 0.5f, nullptr);

			ColorRGB color = set_color(r, &s);
			int ir = int(255.99*color.r());
			int ig = int(255.99*color.g());
			int ib = int(255.99*color.b());

			//std::cout << ir << " " << ig << " " << ib << "\n";
			line = "" + std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib);
			WriteLine("image.ppm", line);
		}
	}
	return 0;
}

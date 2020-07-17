#pragma once
#include "vec3.h"
#include "ray.h"
#include "RayTracerInAWeekend.h"

struct ViewportInfo
{
	float height;
	float width;
};

class Camera
{
private:
	point3 origin;
	point3 botLeft;
	vec3 horizontal;
	vec3 vertical;

public:
	Camera()
	{
		auto DAR = 16.0f / 9.0f;
		ViewportInfo viewportInfo;
		viewportInfo.height = 2.0f;
		viewportInfo.width = DAR * viewportInfo.height;
		auto focalLength = 1.0f;

		origin = point3(0.0f, 0.0f, 0.0f);
		horizontal = vec3(4.0f, 0.0f, 0.0f);
		vertical = vec3(0.0f, viewportInfo.height, 0.0f);
		botLeft = origin - horizontal / 2 - vertical / 2 - vec3(0.0f, 0.0f, focalLength);
	}

	ray getRay(vec3 origin, vec3 dir) const { return ray(origin, dir); }

};
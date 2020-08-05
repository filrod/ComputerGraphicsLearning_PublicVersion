#pragma once
#include "vec3.h"
#include "ray.h"
#include "RayTracerInAWeekend.h"

struct ViewportInfo
{
	float height;
	float width;
};

inline float DegToRad(float degrees) { return degrees * 3.14159f / 180.0f; }

class Camera
{
private:
	point3 origin;
	point3 botLeft;
	vec3 horizontal;
	vec3 vertical;

public:
	Camera(float vFOV, float DAR)
	{
        float theta = DegToRad(vFOV);
        float h = std::tan(theta/2.f);
		ViewportInfo viewportInfo;
		viewportInfo.height = 2.0f*h;
		viewportInfo.width = DAR * viewportInfo.height;
		auto focalLength = 1.0f;

		origin = point3(0.0f, 0.0f, 0.0f);
		horizontal = vec3(4.0f, 0.0f, 0.0f);
		vertical = vec3(0.0f, viewportInfo.height, 0.0f);
		botLeft = origin - horizontal / 2 - vertical / 2 - vec3(0.0f, 0.0f, focalLength);
	}

	ray getRay(vec3 origin, vec3 dir) const { return ray(origin, dir); }

};
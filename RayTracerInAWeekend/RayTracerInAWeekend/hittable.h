#pragma once
#include "vec3.h"
#include "ray.h"

struct hitInfo
{
	point3 p;

};

class hittable
{
	public:
		virtual bool hit(const ray& r, double t_min, double t_max, hitInfo& rec) const = 0;
};
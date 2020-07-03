#pragma once
#include "vec3.h"
#include "ray.h"

class material;

struct hitInfo
{
	point3 p;
	vec3 normal;
	std::shared_ptr<material> material_ptr;
	float t;
	bool isFrontFace;

	inline void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		isFrontFace = dot(r.get_direction(), outward_normal) < 0;
		normal = isFrontFace ? outward_normal : -outward_normal;
	}
};

class hittable
{
	public:
		virtual bool hit(const ray& r, float t_min, float t_max, hitInfo& rec) = 0;
};
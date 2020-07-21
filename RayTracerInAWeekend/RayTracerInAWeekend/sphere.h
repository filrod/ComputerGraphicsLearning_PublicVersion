#pragma once
#include "hitable.h"


class sphere : public hitable
{
public:
	point3 center;
	float radius;
	std::shared_ptr<material> material_ptr;

	sphere() {}
	sphere(point3 center, float radius, std::shared_ptr<material> material_ptr)
		: center(center), radius(radius), material_ptr(material_ptr) {}
	
	virtual bool hit(const ray& r, float t_min, float t_max, hitInfo& rec) const override;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hitInfo& info) const
{
	vec3 oc = r.get_origin() - center;
	auto a = dot(r.get_direction(), r.get_direction());
	auto b = 2 * dot(r.get_direction(), oc);
	auto c = dot(oc, oc) - radius * radius;

	float discriminantFactor = b * b - 4 * a*c;
	if (discriminantFactor <= 0) { return false; }

	float t1 = (-b - std::sqrt(discriminantFactor)) / (2 * a);
	float t2 = (-b + std::sqrt(discriminantFactor)) / (2 * a);

	// Find the earlies intersection
	// using guard casses
	if (t_min < t1 && t1 < t_max)
	{
		info.t = t1;
		info.p = r.get_point_at(info.t);
		vec3 outward_normal = (info.p - center) / radius;
		info.set_face_normal(r, outward_normal);
		info.material_ptr = material_ptr;
		return true;
	}

	if (t_min < t2 && t2 < t_max)
	{
		info.t = t2;
		info.p = r.get_point_at(info.t);
		vec3 outward_normal = (info.p - center) / radius;
		info.set_face_normal(r, outward_normal);
		info.material_ptr = material_ptr;
		return true;
	}
	return false;
}
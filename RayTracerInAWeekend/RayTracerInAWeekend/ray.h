#pragma once
#include "vec3.h"

class ray
{

public:
	vec3 origin;
	vec3 dir;
	ray() {}
	ray(const vec3& origin, const vec3 dir) : origin(origin), dir(dir) {}

	vec3 get_origin() const
	{
		return this->origin;
	}

	vec3 get_direction() const
	{
		return this->dir;
	}

	vec3 get_point_at(float t) const
	{
		return origin + t * dir;
	}

	~ray() {}
};


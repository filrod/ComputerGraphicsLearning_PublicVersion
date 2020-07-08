#pragma once

#include "hitable.h"
class hitable_list : public hitable
{
public:
	hitable** list;
	int size;
	hitable_list() {}
	hitable_list(hitable** list, int size):list(list), size(size) {}

	virtual bool hit(const ray&, float t_min, float t_max, hitInfo& info) const;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hitInfo& info) const
{
	hitInfo tmpInfo;
	bool hitSomething = false;
	float closest_so_far = t_max;

	for (int i = 0; i < hitable_list::size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, tmpInfo))
		{
			hitSomething = true;
			closest_so_far = tmpInfo.t;
			info = tmpInfo;
		}
	}
	return hitSomething;
}
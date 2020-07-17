#pragma once
#include <vector>
#include <memory>
#include "hitable.h"

using std::shared_ptr;
using std::make_shared;

class hitable_list : public hitable
{
public:
	std::vector < shared_ptr < hitable >> hitables;
	hitable_list() {}
	hitable_list(shared_ptr<hitable> object)
	{
		add(object);
	}
	void add(shared_ptr<hitable> object) { hitables.push_back(object); }
	void clear() { hitables.clear(); }

	virtual bool hit(const ray&, float t_min, float t_max, hitInfo& info) const;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hitInfo& info) const
{
	hitInfo tmpInfo;
	bool hitSomething = false;
	float closest_so_far = t_max;

	for (const auto& object : hitables)
	{
		if (object->hit(r, t_min, closest_so_far, tmpInfo))
		{
			hitSomething = true;
			closest_so_far = tmpInfo.t;
			info = tmpInfo;
		}
	}
	return hitSomething;
}
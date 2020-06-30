#pragma once
#include "hittable.h"


class sphere : public hittable
{
	virtual bool hit(const ray& r, double t_min, double t_max, hitInfo& rec) const;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hitInfo& rec) const
{
	return false;
}
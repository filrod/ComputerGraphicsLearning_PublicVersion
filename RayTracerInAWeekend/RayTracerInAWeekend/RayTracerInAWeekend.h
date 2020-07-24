#pragma once

#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "FileHandler.h"
#include "RayTracerInAWeekend.h"
#include "Camera.h"
#include "vec3.h"
#include "Material.h"
#include "UtilityFunctions.h"
// #include <cstdlib>
// #include <limits>

struct window
{
	float pixelProgressX;
	float pixelProgressY;
};

// enum Render_OPTIONS
// {
//     RANDOM_UINT_SPHERE_DIFFUSE,
//     LAMBERTIAN_DIFFUSE,
//     PBR_HEMISPHERICAL_SCATTERING
// };
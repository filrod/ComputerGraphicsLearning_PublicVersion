#pragma once
#include "RayTracerInAWeekend.h"

struct hitInfo;

class Material
{
public:
    virtual bool Scatter(const ray& incidentRay, const hitInfo& info, ColorRGB& attenuation, ray& scatteredRay) const = 0;
};

class Lambertian : public Material
{
public:
    ColorRGB albedo;
    Lambertian(const ColorRGB& a) : albedo(a) {}
    virtual bool Scatter(const ray& incidentRay, const hitInfo& info, ColorRGB& attenuation, ray& scatteredRay) const override
    {
        vec3 scatterDir = info.normal + randUintVec();
        scatteredRay = ray(info.p, scatterDir);
        attenuation = albedo;
        return true;
    }
};

class Metal : public Material
{
public:
    ColorRGB albedo;
    Metal(const ColorRGB& a) : albedo(a) {}

    virtual bool Scatter(const ray& incidentRay, const hitInfo& info, ColorRGB& attenuation, ray& scatteredRay) const override
    {
        vec3 reflected = incidentRay.get_direction();
        reflected.normalize();
        reflected = reflect(reflected, info.normal);
        scatteredRay = ray(info.p, reflected);
        attenuation = albedo;
        return (dot(scatteredRay.get_direction(), info.normal) > 0);
    }
};
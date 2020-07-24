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
    enum Render_OPTIONS
    {
        RANDOM_UINT_SPHERE_DIFFUSE,
        LAMBERTIAN_DIFFUSE,
        PBR_HEMISPHERICAL_SCATTERING
    };

public:
    ColorRGB albedo;
    Lambertian(const ColorRGB& a) : albedo(a) {}
    virtual bool Scatter(const ray& incidentRay, const hitInfo& info, ColorRGB& attenuation, ray& scatteredRay) const override
    {
        Render_OPTIONS renderOption = PBR_HEMISPHERICAL_SCATTERING;
        vec3 scatterDir = info.normal;
        switch (renderOption) {
        case RANDOM_UINT_SPHERE_DIFFUSE:
            scatterDir += randPointInUnitSphere();
            break;
        case LAMBERTIAN_DIFFUSE:
            scatterDir += randUintVec();
            break;
        default:
            scatterDir += randPBRScatter(info.normal);
        }
        scatteredRay = ray(info.p, scatterDir);
        attenuation = albedo;
        return true;
    }
};

class Metal : public Material
{
public:
    ColorRGB albedo;
    float fuzz;
    Metal(const ColorRGB& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool Scatter(const ray& incidentRay, const hitInfo& info, ColorRGB& attenuation, ray& scatteredRay) const override
    {
        vec3 reflected = incidentRay.get_direction();
        reflected.normalize();
        reflected = reflect(reflected, info.normal);
        scatteredRay = ray(info.p, reflected + fuzz*randPointInUnitSphere());
        attenuation = albedo;
        return (dot(scatteredRay.get_direction(), info.normal) > 0);
    }
};
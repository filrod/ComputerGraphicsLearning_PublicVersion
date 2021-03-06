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
        Render_OPTIONS renderOption = RANDOM_UINT_SPHERE_DIFFUSE;
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

class Dielectric : public Material
{
public:
    float refractionIndex;
    Dielectric(float refractionIndex) :refractionIndex(refractionIndex){}
    virtual bool Scatter(const ray& incidentRay, const hitInfo& info, ColorRGB& attenuation, ray& scatteredRay) const override
    {
//         attenuation = ColorRGB(1.f, 1.f, 1.f);
//         float refractionIndexRatio = info.isFrontFace ? (1.f / refractionIndex) : refractionIndex;
//         vec3 dirNormalized = incidentRay.get_direction();
//         dirNormalized.normalize();
// 
//         float projMag = fmin(dot(-dirNormalized, info.normal), 1.f);
//         float reflectionProbe = SchlickFresnelApproximation(projMag, refractionIndexRatio);
// 
//         if ( ( refractionIndexRatio * sqrt(1- projMag * projMag) > 1.f ) ||  (randf() < reflectionProbe) )
//         {
//             vec3 reflected = reflect(dirNormalized, info.normal);
//             scatteredRay = ray(info.p, reflected);
//             return true;
//         }
// 
//         vec3 refracted = Refract(dirNormalized, info.normal, refractionIndexRatio);
//         scatteredRay = ray(info.p, refracted);
//         return true;

        // online code
        attenuation = ColorRGB(1.0f, 1.0f, 1.0f);
        float etai_over_etat = info.isFrontFace ? (1.0f / refractionIndex) : refractionIndex;

        vec3 unit_direction = incidentRay.get_direction() / incidentRay.get_direction().length();
        float cos_theta = fmin(dot(-unit_direction, info.normal), 1.0f);
        float sin_theta = sqrt(1.0f - cos_theta * cos_theta);

        if ((etai_over_etat * sin_theta > 1.0f)
            || (randf() < SchlickFresnelApproximation(cos_theta, etai_over_etat))
            ) {
            vec3 reflected = reflect(unit_direction, info.normal);
            scatteredRay = ray(info.p, reflected);
            return true;
        }

        vec3 refracted = Refract(unit_direction, info.normal, etai_over_etat);
        scatteredRay = ray(info.p, refracted);
        return true;
    }
};
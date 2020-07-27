#pragma once
#include <cstdlib>
#include <limits>

inline float randf()
{
    return rand() / (RAND_MAX + 1.0f);
}

inline float randf(float min, float max)
{
    return min + (max - min)*randf();
}

inline float clamp(float x, float min, float max)
{
    //float returnVal = (x < min) ? min : x;
    //returnVal = (x > max) ? max : x;
    //return returnVal;
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline float SchlickFresnelApproximation(float cosTheataTerm, float refractionIndexRatio)
{
    auto r0 = (1 - refractionIndexRatio) / (1 + refractionIndexRatio);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1-cosTheataTerm), 5);
}
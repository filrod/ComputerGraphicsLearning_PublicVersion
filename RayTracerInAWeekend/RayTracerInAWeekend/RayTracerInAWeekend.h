#pragma once

#include <cstdlib>


struct window
{
	float pixelProgressX;
	float pixelProgressY;
};

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
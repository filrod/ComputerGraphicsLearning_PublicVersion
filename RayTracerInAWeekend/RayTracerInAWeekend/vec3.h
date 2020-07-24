#pragma once
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "UtilityFunctions.h"
#include "RayTracerInAWeekend.h"

class vec3
{
public:
	float e[3];

	vec3() : e{0,0,0} {}

	vec3(float e0, float e1, float e2) :e{e0, e1, e2} {}


	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }

	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline vec3 operator-(const vec3& v)
	{
		return vec3(e[0] - v[0], e[1] - v[1], e[2] - v[2]);
	}
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline vec3& operator+=(const vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	inline vec3& operator-=(const vec3& v)
	{
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	inline vec3& operator*=(const vec3& v)
	{
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	inline vec3& operator/=(const vec3& v)
	{
		if (v.e[0] == 0.0 || v.e[1] == 0.0 || v.e[2] == 0.0)
		{
			throw std::runtime_error("Arithmetic Error; Cannot divide by zero");
		}

		e[0] /= v.e[0]; 
		e[1] /= v.e[1]; 
		e[2] /= v.e[2];
		return *this;
	}

	inline vec3& operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}


	inline vec3& operator/=(const float t)
	{
		if (t == 0) { throw std::runtime_error("Arithmetic Error; Cannot divide by zero");  }
		return *this *= 1 / t;
	}

	

	inline float length() const 
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	inline float squared_length() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	

	inline void normalize()
	{
		float k = float(1.0) / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
	}

    inline static vec3 Random()
    {
        return vec3(randf(), randf(), randf());
    }

    inline static vec3 Random(float min, float max)
    {
        return vec3(randf(min, max), randf(min, max), randf(min, max));
    }

    
}; 

vec3 randPointInUnitSphere()
{
    while (true)
    {
        auto p = vec3::Random(-1, 1);
        if (p.squared_length() < 1) return p;
    }
}

vec3 randUintVec() 
{
    auto a = randf(0.f, 2 * 3.14159f);
    auto z = randf(-1.f, 1.f);
    auto r = sqrt(1-z*z);
    return vec3(r*std::cosf(a), r*std::sinf(a), z);
}



using point3 = vec3;
using ColorRGB = vec3;

inline float dot(const vec3& v1, const vec3& v2)
{
	float k = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	return k;
}

vec3 randPBRScatter(const vec3& normal)
{
    vec3 ptInUnitSphere = randPointInUnitSphere();
    if (dot(ptInUnitSphere, normal) > 0.0) // in the same hemisphere as the normal
    {
        return ptInUnitSphere;
    }
    else
    {
        return -ptInUnitSphere;
    }
}

inline vec3 cross(const vec3& v, const vec3& u)
{
	return vec3(v[1] * u[2] - u[1] * v[2], v[2] * u[0] - v[0] * u[2], v[0] * u[1] - u[0] * v[1]);
}

inline vec3 operator*(float t, const vec3 &v) {
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, float t) {
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator/(float t, const vec3 &v) {
	return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline vec3 operator/(const vec3 &v, float t) {
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2.0f * dot(v, n) * n;
}

inline vec3 operator+(const vec3& u, const vec3&v)
{
	return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline std::istream& operator>>(std::istream &is, vec3 &v)
{
	is >> v.e[0] >> v.e[1] >> v.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3 &v)
{
	os << v.e[0] << " " << v.e[1] << " " << v.e[2];
	return os;
}

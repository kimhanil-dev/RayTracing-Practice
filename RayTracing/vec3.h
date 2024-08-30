#pragma once
#include "type.h"

#include <cmath>
#include <iostream>

class vec3
{
public:
	Double e[3];

	vec3() : e{ 0,0,0 } {}
	vec3(Double e0, Double e1, Double e2) : e{e0,e1,e2} {}

	Double x() const { return e[0]; }
	Double y() const { return e[1]; }
	Double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	Double operator[](int i) const { return e[i]; }
	Double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v)
	{
		e[0] += v[0];
		e[1] += v[1];
		e[2] += v[2];
		return *this;
	}

	vec3& operator*=(const Double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const Double t)
	{
		_ASSERT(t != 0);
		return *this *= 1 / t;
	}

	Double length() const
	{
		return std::sqrt(length_squared());
	}

	Double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
};

using point3 = vec3;

inline std::ostream& operator << (std::ostream& out, const vec3& v)
{
	return out << v.e[0] << v.e[1] << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const Double t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(const vec3& v, Double t)
{
	_ASSERT(t != 0);
	return (1 / t) * v;
}

inline Double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v)
{
	return v / v.length();
}
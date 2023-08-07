#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class vec3 {
public:
	vec3() : e{ 0, 0, 0 } {};
	vec3(float in_x, float in_y, float in_z) : x(in_x), y(in_y), z(in_z) {};

	float& operator[](int i)
	{
		return e[i];
	}

	vec3 operator-()
	{
		return vec3(-x, -y, -z);
	}

	vec3& operator+=(const vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	vec3& operator-=(const vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	vec3& operator*=(const float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	vec3& operator/=(const float f)
	{
		return *this *= (1 / f);
	}

	float lengthSquare() const
	{
		return x * x + y * y + z * z;
	}

	float length() const
	{
		return sqrt(lengthSquare());
	}

	vec3 normalize() const
	{
		float len = length();
		return vec3(x / len, y / len, z / len);
	}

	union 
	{
		float e[3];
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
	};
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3& a, const vec3& b)
{
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline vec3 operator-(const vec3& a, const vec3& b)
{
	return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline vec3 operator*(const vec3& a, const vec3& b)
{
	return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline vec3 operator*(const vec3& v, const float f)
{
	return vec3(v.x * f, v.y * f, v.z * f);
}

inline vec3 operator*(const float f, const vec3& v)
{
	return v * f;
}

inline vec3 operator/ (const vec3& v, const float f)
{
	return v * (1 / f);
}

inline float dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 cross(const vec3& a, const vec3& b)
{
	// a.x a.y a.z
	// b.x b.y b.z
	return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline vec3 normalize(const vec3& v)
{
	return v / v.length();
}

#endif
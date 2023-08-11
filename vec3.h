#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class Vec3 {
public:
	Vec3() : e{ 0, 0, 0 } {};
	Vec3(float a) : e{ a, a, a } {};
	Vec3(float in_x, float in_y, float in_z) : x(in_x), y(in_y), z(in_z) {};

	float& operator[](int i)
	{
		return e[i];
	}

	Vec3 operator-()
	{
		return Vec3(-x, -y, -z);
	}

	Vec3& operator+=(const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	Vec3& operator-=(const Vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vec3& operator*=(const float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	Vec3& operator/=(const float f)
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

	Vec3 normalize() const
	{
		float len = length();
		return Vec3(x / len, y / len, z / len);
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

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator+(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vec3 operator*(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline Vec3 operator*(const Vec3& v, const float f)
{
	return Vec3(v.x * f, v.y * f, v.z * f);
}

inline Vec3 operator*(const float f, const Vec3& v)
{
	return v * f;
}

inline Vec3 operator/ (const Vec3& v, const float f)
{
	return v * (1 / f);
}

inline float dot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 cross(const Vec3& a, const Vec3& b)
{
	// a.x a.y a.z
	// b.x b.y b.z
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline Vec3 normalize(const Vec3& v)
{
	return v / v.length();
}

#endif
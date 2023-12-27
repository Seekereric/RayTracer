#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include "vec3.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float pi = 3.1415926535897932385f;
const float infinity = std::numeric_limits<float>::infinity();

inline float degreesToRadians(float degrees)
{
    return degrees * pi / 180.0f;
}

inline float randomNum()
{
    // range from [0, 1)
    return rand() / (RAND_MAX + 1.0f);
}

inline float randomNum(float min, float max)
{
    return min + (max - min) * randomNum();
}

inline Vec3 randomVec3()
{
    return Vec3(randomNum(), randomNum(), randomNum());
}

inline Vec3 randomVec3(float min, float max)
{
    return Vec3(randomNum(min, max), randomNum(min, max), randomNum(min, max));
}

inline Vec3 randomPosInsideUnitSphere()
{
    Vec3 pos;
    while (1)
    {
        pos = randomVec3(-1.0f, 1.0f);
        if (pos.lengthSquare() < 1.0f)
            break;
    }
    return pos;
}

inline Vec3 randomPosInsideUnitDisk()
{
    Vec3 pos;
    while (1)
    {
        pos = Vec3(randomNum(-1.0f, 1.0f), randomNum(-1.0f, 1.0f), 0);
        if (pos.lengthSquare() < 1.0f)
            break;
    }
    return pos;
}

inline Vec3 randomPosInsidePositiveHemisphere(const Vec3& n)
{
    Vec3 center = Vec3(0, 0, 0);
    Vec3 pos = randomPosInsideUnitSphere();
    if (dot(n, pos - center) > 0)
        return pos;
    return -pos;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return -dot(v, n) * 2 * n + v;
}


inline Vec3 refract(const Vec3& v_in, const Vec3& n, const float etaIn_over_etaOut)
{
    Vec3 v_out_perp = etaIn_over_etaOut * (v_in + dot(-v_in, n) * n);
    Vec3 v_out_parall = -n * sqrt(fabs(1.0f - v_out_perp.lengthSquare()));
    return normalize(v_out_parall + v_out_perp);
}

#include "vec3.h"
#include "ray.h"
#include "interval.h"

#endif // RTWEEKEND_H
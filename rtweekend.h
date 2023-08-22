#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

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

#include "vec3.h"
#include "ray.h"
#include "interval.h"

#endif // RTWEEKEND_H
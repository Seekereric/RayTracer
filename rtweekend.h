#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float pi = 3.1415926535897932385f;
const float infinity = std::numeric_limits<float>::infinity();

inline float degreesToRadians(float degrees) {
    return degrees * pi / 180.0f;
}

#include "vec3.h"
#include "ray.h"
#include "interval.h"

#endif // RTWEEKEND_H
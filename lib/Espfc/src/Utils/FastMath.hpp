#pragma once

#if defined(USE_CMSIS_DSP)
#include <cstdint>
#include <cmath>
#include <cstdlib>

namespace Espfc {
namespace Utils {

constexpr float ESPFC_PI = 3.14159265358979f;
constexpr float ESPFC_TWO_PI = 6.28318530717958f;
constexpr float ESPFC_HALF_PI = 1.57079632679490f;

inline float fastSin(float x)
{
    x = fmodf(x, ESPFC_TWO_PI);
    if (x < 0) x += ESPFC_TWO_PI;

    constexpr float A = -0.1666666666f;
    constexpr float B =  0.00833333333f;
    constexpr float C = -0.000198412698f;
    constexpr float D =  0.00000275573f;

    float x2 = x * x;
    float x3 = x2 * x;
    return x + x3 * (A + x2 * (B + x2 * (C + x2 * D)));
}

inline float fastCos(float x)
{
    return fastSin(x + ESPFC_HALF_PI);
}

inline float fastAtan2(float y, float x)
{
    if (x == 0.0f)
    {
        if (y > 0.0f) return ESPFC_HALF_PI;
        if (y < 0.0f) return -ESPFC_HALF_PI;
        return 0.0f;
    }

    float atan;
    float z = y / x;

    if (fabsf(z) < 1.0f)
    {
        atan = z / (1.0f + 0.28f * z * z);
        if (x < 0.0f)
        {
            if (y >= 0.0f) atan += ESPFC_PI;
            else atan -= ESPFC_PI;
        }
    }
    else
    {
        atan = ESPFC_HALF_PI - z / (z * z + 0.28f);
        if (y < 0.0f) atan = -atan;
    }
    return atan;
}

inline float fastAsin(float x)
{
    if (x <= -1.0f) return -ESPFC_HALF_PI;
    if (x >= 1.0f) return ESPFC_HALF_PI;

    constexpr float PI_2 = 1.57079632679f;
    float sign = (x < 0.0f) ? -1.0f : 1.0f;
    x = fabsf(x);

    float y = -0.018781727f + x * (0.151314579f + x * (-0.003285597f + x * 0.31f));
    y = PI_2 - sqrtf(1.0f - x) * y;
    return sign * y;
}

inline float fastSqrt(float x)
{
    if (x <= 0.0f) return 0.0f;

    float y = x;
    long i;
    unsigned char* p = reinterpret_cast<unsigned char*>(&y);
    unsigned char* q = reinterpret_cast<unsigned char*>(&i);
    q[0] = p[0];
    q[1] = p[1];
    q[2] = p[2];
    q[3] = p[3];
    i = 0x5f3759df - (i >> 1);
    p = reinterpret_cast<unsigned char*>(&y);
    q = reinterpret_cast<unsigned char*>(&i);
    p[0] = q[0];
    p[1] = q[1];
    p[2] = q[2];
    p[3] = q[3];
    y = y * (1.5f - (x * 0.5f * y * y));
    return x * y;
}

}
}

#else

#include <cmath>
namespace Espfc {
namespace Utils {
using std::sinf;
using std::cosf;
using std::atan2f;
using std::asinf;
using std::sqrtf;
}
}

#endif

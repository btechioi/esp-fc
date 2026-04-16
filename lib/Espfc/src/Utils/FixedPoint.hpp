#pragma once

#if defined(USE_CMSIS_DSP)
#include <cstdint>
#include <cmath>

namespace Espfc {
namespace Utils {

constexpr float Q31_SCALE = 2147483648.0f;
constexpr float Q31_INV_SCALE = 4.6566128730773926e-10f;

constexpr float Q15_SCALE = 32768.0f;
constexpr float Q15_INV_SCALE = 3.051850947599719e-5f;

inline q31_t floatToQ31(float f)
{
    if (f >= 1.0f) return INT32_MAX;
    if (f <= -1.0f) return INT32_MIN;
    return static_cast<q31_t>(f * Q31_SCALE);
}

inline float q31ToFloat(q31_t q)
{
    return static_cast<float>(q) * Q31_INV_SCALE;
}

inline q15_t floatToQ15(float f)
{
    if (f >= 1.0f) return INT16_MAX;
    if (f <= -1.0f) return INT16_MIN;
    return static_cast<q15_t>(f * Q15_SCALE);
}

inline float q15ToFloat(q15_t q)
{
    return static_cast<float>(q) * Q15_INV_SCALE;
}

inline q63_t q31Mul(q31_t a, q31_t b)
{
    return static_cast<q63_t>(a) * static_cast<q63_t>(b);
}

inline q31_t q31Sat(q63_t val)
{
    if (val > INT32_MAX) return INT32_MAX;
    if (val < INT32_MIN) return INT32_MIN;
    return static_cast<q31_t>(val >> 32);
}

}
}
#endif

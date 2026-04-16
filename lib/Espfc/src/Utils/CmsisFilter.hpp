#pragma once

#if defined(USE_CMSIS_DSP)
#include <cstdint>
#include <arm_math_types.h>
#include <dsp/filtering_functions.h>
#include "FixedPoint.hpp"
#include "FastMath.hpp"
#include "Utils/Math.hpp"
#include "Utils/BiquadFilterType.h"

namespace Espfc {
namespace Utils {

class FilterStateBiquadQ31
{
public:
    void init(BiquadFilterType filterType, float rate, float freq, float q);
    void reconfigure(const FilterStateBiquadQ31& from);
    float update(float input);

private:
    arm_biquad_casd_df1_inst_q31 _pInst;
    q31_t _coeffs[5];
    q31_t _state[4];
    q31_t _prevInput;
    q31_t _prevOutput;
};

inline void FilterStateBiquadQ31::init(BiquadFilterType filterType, float rate, float freq, float q)
{
    constexpr float TWO_PI_CONST = 6.28318530717958f;
    const float omega = (TWO_PI_CONST * freq) / rate;
    const float sn = fastSin(omega);
    const float cs = fastCos(omega);
    const float alpha = sn / (2.0f * q);

    float b0 = 0.0f, b1 = 0.0f, b2 = 0.0f, a0 = 0.0f, a1 = 0.0f, a2 = 0.0f;

    switch (filterType)
    {
        case BIQUAD_FILTER_LPF:
            b0 = (1.0f - cs) * 0.5f;
            b1 = 1.0f - cs;
            b2 = (1.0f - cs) * 0.5f;
            a0 = 1.0f + alpha;
            a1 = -2.0f * cs;
            a2 = 1.0f - alpha;
            break;
        case BIQUAD_FILTER_NOTCH:
            b0 = 1.0f;
            b1 = -2.0f * cs;
            b2 = 1.0f;
            a0 = 1.0f + alpha;
            a1 = -2.0f * cs;
            a2 = 1.0f - alpha;
            break;
        case BIQUAD_FILTER_BPF:
            b0 = alpha;
            b1 = 0.0f;
            b2 = -alpha;
            a0 = 1.0f + alpha;
            a1 = -2.0f * cs;
            a2 = 1.0f - alpha;
            break;
    }

    const float invA0 = 1.0f / a0;
    _coeffs[0] = floatToQ31(b0 * invA0);
    _coeffs[1] = floatToQ31(b1 * invA0);
    _coeffs[2] = floatToQ31(b2 * invA0);
    _coeffs[3] = floatToQ31(a1 * invA0);
    _coeffs[4] = floatToQ31(a2 * invA0);

    arm_biquad_cascade_df1_init_q31(&_pInst, 1, _coeffs, _state, 1);

    _state[0] = 0;
    _state[1] = 0;
    _state[2] = 0;
    _state[3] = 0;
    _prevInput = 0;
    _prevOutput = 0;
}

inline void FilterStateBiquadQ31::reconfigure(const FilterStateBiquadQ31& from)
{
    _coeffs[0] = from._coeffs[0];
    _coeffs[1] = from._coeffs[1];
    _coeffs[2] = from._coeffs[2];
    _coeffs[3] = from._coeffs[3];
    _coeffs[4] = from._coeffs[4];
    arm_biquad_cascade_df1_init_q31(&_pInst, 1, _coeffs, _state, 1);
    _state[0] = 0;
    _state[1] = 0;
    _state[2] = 0;
    _state[3] = 0;
    _prevInput = 0;
    _prevOutput = 0;
}

inline float FilterStateBiquadQ31::update(float input)
{
    q31_t inputQ31 = floatToQ31(input);

    q31_t pData = inputQ31;
    arm_biquad_cascade_df1_q31(&_pInst, &pData, &pData, 1);

    _prevInput = inputQ31;
    _prevOutput = pData;

    return q31ToFloat(pData);
}

}
}
#endif

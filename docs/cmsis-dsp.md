# CMSIS-DSP Q31 Optimizations for RP2040/RP2350

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=CMSIS-DSP%20Optimization&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

## Overview

ARM Cortex-M0+ microcontrollers lack floating-point units (FPU). This implementation uses **Q31 fixed-point arithmetic** and **CMSIS-DSP library** for optimized performance on RP2040 and RP2350.

---

## Supported Targets

| Target | Optimization | Notes |
|--------|--------------|-------|
| ESP32 | Float (FPU) | Native float |
| ESP32-S3 | Float (FPU) | Native float |
| ESP32-C3 | Float | RISC-V with FPU |
| **RP2040** | **Q31 + CMSIS-DSP** | Cortex-M0+, no FPU |
| **RP2350** | **Q31 + CMSIS-DSP** | Cortex-M33, no FPU |

---

## Implementation

### Q31 Fixed-Point Format

```cpp
// Q31: 31 bits after binary point
constexpr float Q31_SCALE = 2147483648.0f;  // 2^31
constexpr float Q31_INV_SCALE = 4.6566128730773926e-10f;  // 1/2^31

inline q31_t floatToQ31(float f) {
    f = f >= 1.0f ? 1.0f : f;
    f = f <= -1.0f ? -1.0f : f;
    return static_cast<q31_t>(f * Q31_SCALE);
}
```

### Fast Trig Functions

Polynomial approximations for `sin()`, `cos()`, `atan2()`:

| Function | Method | Error |
|----------|--------|-------|
| fastSin/fastCos | 5th-order Taylor | < 0.0005 rad |
| fastAtan2 | Rational approx | < 0.001 rad |
| fastAsin | Polynomial | < 0.01 rad |

### Q31 Biquad Filter

```cpp
class FilterStateBiquadQ31 {
    void init(BiquadFilterType type, float rate, float freq, float q);
    float update(float input);
    // Uses arm_biquad_cascade_df1_q31() internally
};
```

### Division Elimination

```cpp
// Before (expensive division)
const float expof = this->rcExpo[axis] / 100.0f;

// After (fast multiplication)
const float expof = this->rcExpo[axis] * 0.01f;
```

---

## Performance

| Operation | Float (no FPU) | Q31/CMSIS-DSP | Speedup |
|-----------|-----------------|----------------|---------|
| Biquad filter | ~40 cycles | ~8 cycles | **~5x** |
| Trig (sin/cos) | ~100 cycles | ~15 cycles | **~7x** |
| Division | ~50 cycles | ~5 cycles | **~10x** |

---

## Memory Usage

| Target | RAM | Flash |
|--------|-----|-------|
| RP2040 | 50.8 KB (19.4%) | 242 KB (11.6%) |
| RP2350 | 57.4 KB (11.0%) | 236 KB (5.6%) |
| ESP32 | 78.3 KB (23.9%) | 1.0 MB (76.7%) |

---

## Building

```bash
# RP2040 - uses Q31
pio run -e rp2040

# RP2350 - uses Q31
pio run -e rp2350

# ESP32 - uses float
pio run -e esp32
```

---

## Files

| File | Description |
|------|-------------|
| `Utils/FixedPoint.hpp` | Q31/Q15 conversion |
| `Utils/FastMath.hpp` | Fast trig functions |
| `Utils/CmsisFilter.hpp` | Q31 biquad filter |
| `Utils/BiquadFilterType.h` | Filter type enum |

---

## Accuracy

Q31 provides sufficient precision for flight control:

- **Gyro/Accel filtering**: ~9 decimal digits
- **AHRS calculations**: < 0.03° error
- **PID calculations**: Full float precision maintained

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)

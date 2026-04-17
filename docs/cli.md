# ESP-FC CLI Reference

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=ESP-FC%20CLI%20Reference&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

## Quick Commands

```
help        - Show available commands
dump        - Dump all configuration
get <param> - Get parameter value
set <param> <value> - Set parameter value
save        - Save configuration
reboot      - Reboot device
defaults    - Reset to defaults
cal gyro    - Calibrate gyroscope
status      - Show system status
version     - Show firmware version
```

---

## System Status

```
status
CPU: 240 MHz | Gyro: 3200 Hz | Loop: 1600 Hz
Input: 43 Hz | ARM: FAILSAFE
```

```
stats
gyro_r: 187us  | accel_r: 45us
pid_o:   2us   | mix_w:  39us
CPU: 23.1% total
```

---

## Essential Configuration

### Receiver

```bash
# Serial RX provider
set serialrx_provider = SBUS   # SBUS, IBUS, CRSF

# Deadband
set input_deadband = 3

# RC rates
set rate[0] = 20    # Roll
set rate[1] = 20    # Pitch
set rate[2] = 30    # Yaw
```

### Output

```bash
# ESC Protocol
set output_protocol = DSHOT300

# Motor output rate
set output_rate = 480

# Min/Max throttle
set output_min_throttle = 1070
set output_max_throttle = 2000
```

### 3D Mode

```bash
# Enable 3D mode
set output_3d_enable = 1

# 3D deadbands
set output_3d_deadband_low = 1406
set output_3d_deadband_high = 1514
set output_3d_neutral = 1460
```

### GPS

```bash
# Enable GPS feature
set feature GPS = ON

# GNSS mode (0=auto, 1=GPS, 2=GPS+GLO, 3=GPS+GAL, 4=GPS+BDS, 5=All)
set gps_gnss_mode = 5

# Min satellites
set gps_min_sats = 8

# Dual-band (M10)
set gps_enable_dual_band = 1
```

### Filters

```bash
# Gyro filter
set gyro_filter = PT1,100    # type, cutoff

# Dterm filter
set dterm_filter = PT1,128
```

### PID Tuning

```bash
# Roll PID
set pid[0] = 42,85,24,72    # P,I,D,F

# Pitch PID
set pid[1] = 46,90,26,76

# Yaw PID
set pid[2] = 45,90,0,72
```

---

## Pin Functions

```bash
# View current pinout
get pin

# Set pin functions
set pin_output_0 = 2
set pin_output_1 = 3
set pin_output_2 = 4
set pin_output_3 = 5

# Unmap pin
set pin_output_3 = -1
```

---

## Complete Parameter List

| Category | Parameters |
|----------|-----------|
| System | `loop_sync`, `mixer_sync`, `telemetry` |
| Gyro | `gyro_dev`, `gyro_filter`, `gyro_dlpf` |
| Accel | `accel_dev`, `accel_filter` |
| Input | `serialrx_provider`, `input_deadband`, `rate[]` |
| Output | `output_protocol`, `output_rate`, `output_3d_*` |
| PID | `pid[]`, `dterm_filter`, `iterm_*` |
| GPS | `gps_gnss_mode`, `gps_min_sats` |
| Modes | `mode_0` to `mode_7` |

---

## Presets

```bash
# Load modes preset (ARM, ANGLE, AIRMODE)
preset modes

# Load scaler preset (PID scaling via AUX)
preset scaler

# Load brobot preset (gimbal configuration)
preset brobot
```

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)

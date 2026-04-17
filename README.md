<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=200&section=header&text=Banumath%20%7C%20ESP-FC%20Flight%20Controller&fontSize=40&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

# 🛠️ Hi, I'm Banumath (btechioi)

**Hardware Hacker | Cybersecurity Researcher | Astro Developer**

I build high-performance web experiences, autonomous robotics, and secure systems. I run **Arch Linux** (btw), deploy on **Netlify**, and believe in the power of the **Astro** islands architecture.

---

# 🛸 ESP-FC - DIY Flight Controller

**Custom ESP32/RP2040/RP2350 Flight Controller Firmware**

A high-performance, open-source flight controller for multirotor drones. Forked from [rtlopez/esp-fc](https://github.com/rtlopez/esp-fc) with enhancements for RP2040/RP2350 support and CMSIS-DSP optimizations.

---

# 🚀 Features

* **Multi-Platform Support:** ESP32, ESP32-S3, RP2040, RP2350
* **ESC Protocols:** PWM, Oneshot125/42, Multishot, Brushed, Dshot150/300/600 bidirectional
* **RC Receivers:** PPM, SBUS, IBUS, CRSF/ELRS, ESP-NOW
* **Sensors:** SPI/I2C gyro modules (MPU6050, MPU9250, ICM20602, BMI160)
* **GPS:** u-blox M8, M9, F9, M10 with dual-band L1+L5 support
* **Flight Modes:** ACRO, ANGLE, AIRMODE, ALTHOLD, GPS Rescue
* **Filters:** LPF, Dynamic Notches, dTerm, RPM filtering
* **Blackbox:** OpenLog/OpenLager/Flash recording
* **Betaflight Compatible:** Configurable via Betaflight Configurator v10.10
* **MSP/CLI Interface:** Full command-line configuration
* **CMSIS-DSP Optimizations:** Q31 fixed-point for no-FPU targets

---

# 🔥 Performance

| Platform | Loop Rate | Gyro | Filters |
|----------|-----------|------|---------|
| ESP32-S3 | 4kHz | SPI | Full Dyna Notch |
| RP2040 | 2kHz | SPI | Q31 optimized |
| RP2350 | 2kHz | SPI | Q31 optimized |

---

# 💻 Tech Stack

<p>
<img src="https://skillicons.dev/icons?i=cpp,arduino,raspberrypi"/>
</p>

**CMSIS-DSP** • **PlatformIO** • **Betaflight MSP** • **ArduPilot**

---

# 📦 Quick Start

### Hardware Requirements
* **ESP32/ESP32-S3** or **RP2040/RP2350** board
* **Gyro:** MPU9250 SPI or MPU6050 I2C (GY-88, GY-91, GY-521)
* **PDB** with 5V BEC
* **Buzzer** and components (optional)

### Software Requirements
* [Betaflight Configurator](https://github.com/betaflight/betaflight-configurator/releases) v10.10+
* [PlatformIO](https://platformio.org/install/ide?install=vscode) (for development)
* [CH340 Driver](https://sparks.gogo.co.nz/ch340.html) (for USB serial)

### Flashing Pre-built Firmware

```bash
# Download from Releases
# Visit https://espressif.github.io/esptool-js/
# Connect device → Add firmware → Flash Address 0x00 → Program
```

### Building from Source

```bash
# Clone and build
git clone https://github.com/btechioi/esp-fc.git
cd esp-fc
pio run -e esp32s3    # or rp2040, rp2350, etc.
```

---

# 📚 Documentation

> [!IMPORTANT]
> Read the documentation carefully before flying!

* [📖 Setup Guide](/docs/setup.md) - Initial configuration
* [🔌 Wiring](/docs/wiring.md) - Pin connections
* [💻 CLI Commands](/docs/cli.md) - Full command reference
* [📡 ESP-NOW RC Bridge](/docs/espnow-bridge.md) - Wireless RC for RP2040
* [⚡ CMSIS-DSP Optimization](/docs/cmsis-dsp.md) - Q31 for ARM M0+
* [🔗 Connections](/docs/connections.md) - UART/I2C/SPI wiring
* [🌐 Wireless Setup](/docs/wireless.md) - WiFi configuration
* [🛠️ Development](/docs/development.md) - Building and debugging

---

# 🎮 Supported Hardware

### Microcontrollers
| Platform | Status | Notes |
|----------|--------|-------|
| ESP32-S3 | ✅ Recommended | Best performance, FPU |
| ESP32 | ✅ Recommended | Good performance, FPU |
| RP2350 | ✅ Beta | Cortex-M33, CMSIS-DSP |
| RP2040 | ✅ Beta | Cortex-M0+, no FPU |
| ESP32-C3 | 🟡 Experimental | RISC-V, limited |
| ESP8266 | 🔴 Obsolete | No longer supported |

### Sensors
| Type | Supported |
|------|-----------|
| Gyro | MPU6050, MPU6000, MPU6500, MPU9250, ICM20602, BMI160 |
| Accel | Integrated with gyro |
| Baro | BMP180, BMP280, SPL06 |
| Mag | HMC5883, QMC5883, AK8963 |
| GPS | u-blox M8, M9, F9, M10 (dual-band) |

### ESC Protocols
PWM • ONESHOT125 • ONESHOT42 • MULTISHOT • BRUSHED • DSHOT150/300/600 (bidirectional)

---

# 🌱 Current Projects

🛸 **Autonomous Drone Fleet**
Custom flight paths and computer vision obstacle avoidance with **ROS2**.

🔒 **IoT Security Sandbox**
Penetration testing for smart home **MQTT** vulnerabilities.

---

# 🔥 GitHub Stats
<p align="left">
<img src="https://streak-stats.demolab.com/?user=btechioi&theme=tokyonight" alt="GitHub Streak" />
</p>

---

# 📫 Reach Out
📧 **Email:** [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)
🌐 **Blog:** [btechioi.netlify.app](https://btechioi.netlify.app)
🐙 **GitHub:** [github.com/btechioi](https://github.com/btechioi)

---

# 📄 License

MIT License - Forked from [rtlopez/esp-fc](https://github.com/rtlopez/esp-fc)

⭐ *“Simplicity is the ultimate sophistication.” — Built on Arch.*

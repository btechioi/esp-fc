<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&amp;color=0:00e1ff,100:0055ff&amp;height=200&amp;section=header&amp;text=esp-fc&amp;fontSize=50&amp;fontAlignY=35&amp;animation=fadeIn&amp;fontColor=ffffff"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/-C%2B%2B-00599C?logo=cplusplus&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-Python-3776AB?logo=python&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-PlatformIO-FF6600?logo=data:image/svg%2Bxml;base64,PHN2ZyB2aWV3Qm94PSIwIDAgMjQgMjQiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0iTTEyIDJDNi40OCAyIDIgNi40OCAyIDEyczQuNDggMTAgMTAgMTAgMTAtNC40OCAxMC0xMFMxNy41MiAyIDEyIDJ6bTAgMThjLTQuNDEgMC04LTMuNTktOCA4czMuNTkgOCA4IDggOC0zLjU5IDgtOC0zLjU5LTgtOC04eiIvPjwvc3ZnPg==&amp;logoColor=white&amp;style=for-the-badge"/>
</p>

<p align="center">
  <b>Multi-platform ESP32 / RP2040 flight controller firmware</b>
</p>

---

## 🛸 Overview

A multi-platform flight controller supporting ESP32, ESP8266, and RP2040, with Betaflight-compatible libraries, MSP and CRSF protocols, advanced AHRS fusion, and GPS navigation.

---

## 🛠️ Features

```mermaid
flowchart LR
    A[Gyro / Accel] --> B[AHRS\nMadgwick/Mahony/Kalman]
    B --> C[PID Controller]
    C --> D[ESC Drivers]
    E[RC Input\nCRSF/MSP/ESP-NOW] --> C
    F[GPS] --> G[Navigation]
    G --> C
    C --> H[Telemetry\nMSP/CRSF]
```

- **Targets:** ESP32, ESP8266, RP2040
- **AHRS:** Madgwick, Mahony, Kalman filter
- **Protocols:** MSP, CRSF, ESP-NOW
- **Hardware:** Multiple ESC drivers, GPS, barometer, compass

---

## 🚀 Tech Stack

<img src="https://img.shields.io/badge/-C%2B%2B-00599C?logo=cplusplus&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-Python-3776AB?logo=python&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-PlatformIO-FF6600?logo=data:image/svg%2Bxml;base64,PHN2ZyB2aWV3Qm94PSIwIDAgMjQgMjQiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0iTTEyIDJDNi40OCAyIDIgNi40OCAyIDEyczQuNDggMTAgMTAgMTAgMTAtNC40OCAxMC0xMFMxNy41MiAyIDEyIDJ6bTAgMThjLTQuNDEgMC04LTMuNTktOCA4czMuNTkgOCA4IDggOC0zLjU5IDgtOC0zLjU5LTgtOC04eiIvPjwvc3ZnPg==&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-ESP32-E7352C?logo=espressif&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-Docker-2496ED?logo=docker&amp;logoColor=white&amp;style=for-the-badge"/>

---

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=soft&amp;color=0:00e1ff,100:0055ff&amp;height=100&amp;section=footer&amp;text=one%20firmware%2C%20many%20boards&amp;fontSize=20&amp;fontAlignY=50&amp;fontColor=ffffff"/>
</p>

# ESP-NOW RC Bridge for RP2040

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=ESP-NOW%20RC%20Bridge&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

## Overview

RP2040 lacks native WiFi. ESP-NOW support is implemented via UART SBUS bridge with bidirectional telemetry.

```
┌─────────────┐         SBUS (100k, 8E2)         ┌─────────────┐
│   RC        │◄────── Wireless ESP-NOW ────────►│   RP2040    │
│ Transmitter │         via ESP32 module          │  Flight     │
│   (TX)      │                                  │ Controller │
└─────────────┘                                  └─────────────┘
      ▲                                                  │
      │              ESP-NOW Telemetry                    │
      └──────────────────────────────────────────────────┘
```

---

## Components

| Component | Description |
|-----------|-------------|
| ESP32 Transmitter | Receives RC via ESP-NOW, forwards via SBUS |
| RP2040 Flight Controller | Receives SBUS, sends telemetry |

---

## Wiring

| ESP32 | RP2040 | Description |
|-------|--------|-------------|
| GPIO 1 (TX) | GPIO 5 (RX2) | SBUS data (RC input) |
| GPIO 3 (RX) | GPIO 4 (TX2) | Telemetry data (optional) |
| GND | GND | Ground reference |

---

## RP2040 Configuration

```bash
# Enable serial RX
set feature RX_SERIAL = ON

# Set provider
set serialrx_provider = SBUS

# Configure UART2 for RC
serial 1 1024 115200 115200 0 115200

save
reboot
```

---

## SBUS Protocol

| Parameter | Value |
|-----------|-------|
| Baud Rate | 100000 |
| Data Bits | 8 |
| Parity | Even |
| Stop Bits | 2 |
| Channels | 16 |
| Frame Rate | ~50 Hz |

---

## Telemetry Format

### Frame Structure

| Byte | Field | Description |
|------|-------|-------------|
| 0 | Sync | 0xA5 |
| 1 | Length | Payload length + 3 |
| 2 | Type | 0x01 = Sensor data |
| 3-N | Payload | Sensor values |
| N+1 | Checksum | XOR of bytes 0 to N |

### Payload Structure

| Offset | Size | Field | Description |
|--------|------|-------|-------------|
| 0 | 2 | vbat | Battery voltage (mV) |
| 2 | 2 | current | Current draw (mA) |
| 4 | 2 | rpm[0] | Motor 0 RPM |
| 6 | 2 | rpm[1] | Motor 1 RPM |
| 8 | 2 | rpm[2] | Motor 2 RPM |
| 10 | 2 | rpm[3] | Motor 3 RPM |
| 12 | 2 | temp | Temperature (°C) |

---

## Performance

| Metric | Value |
|--------|-------|
| RC Latency | ~15ms total |
| RC Update Rate | 50 Hz |
| Telemetry Rate | 20 Hz |
| Channels | 16 |
| Range | ~100m |

---

## Troubleshooting

### No RC Signal
- Check UART wiring (TX→RX, GND→GND)
- Verify baud rate (100000 8E2)
- Check UART2 configuration

### ESP-NOW Not Connecting
- Ensure same WiFi channel
- Check peer MAC addresses
- Verify ESP-NOW enabled on both modules

### Telemetry Not Working
- Verify bidirectional UART wiring
- Check sync byte (0xA5)
- Ensure parity and baud rate match

---

## Files

| File | Description |
|------|-------------|
| `Device/InputEspNowBridge.h` | RP2040 SBUS receiver |
| `Device/InputEspNowBridge.cpp` | SBUS implementation |
| `examples/espnow-bridge/esp32-transmitter/` | ESP32 transmitter |

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)

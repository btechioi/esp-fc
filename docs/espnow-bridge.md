# ESP-NOW RC Bridge for RP2040

This document describes how to use ESP-NOW RC with the RP2040 flight controller using an external ESP32 module as a bridge.

## Overview

The RP2040 lacks native WiFi capability, so ESP-NOW support is implemented via a UART SBUS bridge with bidirectional telemetry:

```
┌─────────────┐         SBUS (100k, 8E2)         ┌─────────────┐
│   RC        │◄────── Wireless ESP-NOW ────────►│   RP2040    │
│ Transmitter │         via ESP32 module          │  Flight     │
│   (TX)      │                                  │ Controller  │
└─────────────┘                                  └─────────────┘
      ▲                                                  │
      │              ESP-NOW Telemetry                    │
      └──────────────────────────────────────────────────┘
```

## Components

1. **ESP32 Transmitter Module** - Receives RC commands via ESP-NOW and forwards via SBUS UART, sends telemetry back
2. **RP2040 Flight Controller** - Receives SBUS via UART2 and processes as normal RC input, sends telemetry

## Wiring

| ESP32 | RP2040 | Description |
|-------|--------|-------------|
| GPIO 1 (TX) | GPIO 5 (RX2) | SBUS data (RC input) |
| GPIO 3 (RX) | GPIO 4 (TX2) | Telemetry data (optional) |
| GND | GND | Ground reference |

**Note**: For bidirectional communication, both TX/RX are needed. For RC-only mode, only ESP32 TX → RP2040 RX is required.

## ESP32 Transmitter Setup

1. Flash the `esp32-transmitter` sketch to your ESP32 module
2. Connect the ESP32 to your RC transmitter (PPM, SBUS, or direct sticks)
3. Connect UART TX to RP2040 RX2 (GPIO 5)
4. Optionally connect UART RX to RP2040 TX2 (GPIO 4) for telemetry

### ESP32 Pinout
- **UART TX**: GPIO 1 (to RP2040 RX)
- **UART RX**: GPIO 3 (from RP2040 TX, optional)
- **SBUS Output**: Serial2 at 100000 baud, 8E2

## RP2040 Flight Controller Setup

1. Enable `FEATURE_RX_SERIAL` in the configuration
2. Set `serial_rx_provider` to `SBUS`
3. Configure UART2 pins (GPIO 4/5 by default)
4. Set UART2 function to `RX_SERIAL`

## Example Configuration (CLI)

```
set feature RX_SERIAL = ON
set serialrx_provider = SBUS
set serial_port = 2
set serial_rx = ON
```

## Protocol Details

### SBUS Format (RC → RP2040)
- **Baud Rate**: 100000
- **Data Bits**: 8
- **Parity**: Even
- **Stop Bits**: 2
- **Channels**: 16
- **Frame Rate**: ~50 Hz

### Telemetry Format (RP2040 → ESP32)
| Byte | Field | Description |
|------|-------|-------------|
| 0 | Sync | 0xA5 |
| 1 | Length | Payload length + 3 |
| 2 | Type | 0x01 = Sensor data |
| 3-N | Payload | Sensor values |
| N+1 | Checksum | XOR of bytes 0 to N |

### Telemetry Payload Structure
| Offset | Size | Field | Description |
|--------|------|-------|-------------|
| 0 | 2 | vbat | Battery voltage (mV) |
| 2 | 2 | current | Current draw (mA) |
| 4 | 2 | rpm[0] | Motor 0 RPM |
| 6 | 2 | rpm[1] | Motor 1 RPM |
| 8 | 2 | rpm[2] | Motor 2 RPM |
| 10 | 2 | rpm[3] | Motor 3 RPM |
| 12 | 2 | temp | Temperature (°C) |

## API

### Sending Telemetry (from flight controller)

```cpp
#include "Device/InputEspNowBridge.h"

// Get bridge device
auto* bridge = dynamic_cast<Espfc::Device::InputEspNowBridge*>(
    input.getInputDevice());

if (bridge) {
    uint8_t telemetry[14];
    telemetry[0] = vbat & 0xFF;
    telemetry[1] = (vbat >> 8) & 0xFF;
    // ... fill other fields
    bridge->sendTelemetry(telemetry, sizeof(telemetry));
}
```

## Files

| File | Description |
|------|-------------|
| `Device/InputEspNowBridge.h` | RP2040 SBUS receiver header with telemetry |
| `Device/InputEspNowBridge.cpp` | RP2040 SBUS receiver implementation |
| `examples/espnow-bridge/esp32-transmitter/` | ESP32 transmitter sketch |

## Performance

| Metric | Value |
|--------|-------|
| RC Latency | ~10ms (ESP-NOW) + ~5ms (SBUS) |
| Telemetry Latency | ~15ms |
| RC Update Rate | 50 Hz |
| Telemetry Rate | 20 Hz |
| Channels | 16 |
| Range | ~100m (ESP-NOW) |

## Troubleshooting

### No RC Signal
- Check UART wiring (TX→RX, GND→GND)
- Verify baud rate (100000 8E2)
- Check RP2040 UART2 configuration

### ESP-NOW Not Connecting
- Ensure transmitter and receiver are on same WiFi channel
- Check peer MAC addresses in espnow-rclink documentation
- Verify ESP-NOW is enabled on both modules

### Telemetry Not Working
- Verify bidirectional UART wiring (ESP32 RX → RP2040 TX)
- Check telemetry packet format (sync 0xA5)
- Ensure parity and baud rate match

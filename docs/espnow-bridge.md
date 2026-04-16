# ESP-NOW RC Bridge for RP2040

This document describes how to use ESP-NOW RC with the RP2040 flight controller using an external ESP32 module as a bridge.

## Overview

The RP2040 lacks native WiFi capability, so ESP-NOW support is implemented via a UART SBUS bridge:

```
┌─────────────┐         SBUS (100k, 8E2)         ┌─────────────┐
│   RC        │◄────── Wireless ESP-NOW ────────►│   RP2040    │
│ Transmitter │         via ESP32 module          │  Flight     │
│   (TX)      │                                  │ Controller  │
└─────────────┘                                  └─────────────┘
```

## Components

1. **ESP32 Transmitter Module** - Receives RC commands via ESP-NOW and forwards via SBUS UART
2. **RP2040 Flight Controller** - Receives SBUS via UART2 and processes as normal RC input

## Wiring

| ESP32 | RP2040 | Description |
|-------|--------|-------------|
| GPIO 1 (TX) | GPIO 5 (RX2) | SBUS data |
| GND | GND | Ground reference |

## ESP32 Transmitter Setup

1. Flash the `esp32-transmitter` sketch to your ESP32 module
2. Connect the ESP32 to your RC transmitter (PPM, SBUS, or direct sticks)
3. Connect UART TX to RP2040 RX2 (GPIO 5)

### ESP32 Pinout
- **UART TX**: GPIO 1 (default)
- **UART RX**: GPIO 3 (for debugging)
- **SBUS Output**: Serial2 at 100000 baud, 8E2

### Configuration
The ESP32 will automatically:
- Listen for ESP-NOW RC packets
- Convert RC channels to SBUS format
- Send SBUS over UART to RP2040

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

### SBUS Format
- **Baud Rate**: 100000
- **Data Bits**: 8
- **Parity**: Even
- **Stop Bits**: 2
- **Channels**: 16
- **Frame Rate**: ~50 Hz

### Frame Structure
```
Byte 0:  0x0F (start byte)
Byte 1-22: Channel data (11 bits per channel, 16 channels)
Byte 23: Flags (signal loss, failsafe)
Byte 24: 0x00 (end byte)
```

## Files

| File | Description |
|------|-------------|
| `Device/InputEspNowBridge.h` | RP2040 SBUS receiver header |
| `Device/InputEspNowBridge.cpp` | RP2040 SBUS receiver implementation |
| `examples/espnow-bridge/esp32-transmitter/` | ESP32 transmitter sketch |

## Usage

1. **Build ESP32 Transmitter**
   ```bash
   cd examples/espnow-bridge/esp32-transmitter
   pio run -e esp32-transmitter
   pio run -e esp32-transmitter -t upload
   ```

2. **Configure RP2040 Flight Controller**
   - Connect via Betaflight Configurator or CLI
   - Enable serial RX and SBUS provider
   - Set UART pins for your wiring

3. **Pair ESP-NOW**
   - The transmitter will automatically try to pair
   - Hold bind button on your RC transmitter
   - Status LED will indicate connection

## Troubleshooting

### No RC Signal
- Check UART wiring (TX→RX, GND→GND)
- Verify baud rate (100000 8E2)
- Check RP2040 UART2 configuration

### ESP-NOW Not Connecting
- Ensure transmitter and receiver are on same WiFi channel
- Check peer MAC addresses in espnow-rclink documentation
- Verify ESP-NOW is enabled on both modules

### SBUS Parsing Issues
- SBUS is inverted by default
- Ensure even parity (8E2) is configured
- Check for voltage level compatibility (3.3V)

## Performance

| Metric | Value |
|--------|-------|
| Latency | ~10ms (ESP-NOW) + ~5ms (SBUS) |
| Update Rate | 50 Hz |
| Channels | 16 |
| Range | ~100m (ESP-NOW) |

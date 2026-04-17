# ESP-FC Installation Guide

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=ESP-FC%20Installation&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

## Quick Download

Download pre-built firmware from [Releases](https://github.com/btechioi/esp-fc/releases):

| Target | File | Notes |
|--------|------|-------|
| ESP32-S3 | `espfc_*_esp32s3_0x00.bin` | Recommended |
| ESP32 | `espfc_*_esp32_0x00.bin` | Full flash |
| RP2040 | `espfc_*.uf2` | Drag & drop |
| RP2350 | `espfc_*.uf2` | Drag & drop |

---

## ESP32 / ESP32-S3 / ESP32-C3 / ESP32-S2

### Method 1: Web Flasher (Recommended)

1. Go to [ESP Web Flasher](https://espressif.github.io/esptool-js/)
2. Click **Connect** → Select your board's COM port
3. Click **Erase** (optional, for clean install)
4. Download firmware from [Releases](https://github.com/btechioi/esp-fc/releases)
5. Click **Add File** → Select the `_0x00.bin` file
6. Set Address to `0x00000`
7. Click **Program**
8. Wait for completion, then power cycle

### Method 2: esptool.py

```bash
# Install esptool
pip install esptool

# Find your device port
# Linux: /dev/ttyUSB0
# macOS: /dev/cu.usbserial-*
# Windows: COM3

# Flash firmware
esptool.py --chip esp32s3 \
  --port /dev/ttyUSB0 \
  --baud 921600 \
  write_flash 0x00000 espfc_vX.X.X_esp32s3_0x00.bin
```

### Method 3: PlatformIO

```bash
# Clone repo
git clone https://github.com/btechioi/esp-fc.git
cd esp-fc

# Build
pio run -e esp32s3

# Flash
pio run -e esp32s3 -t upload
```

---

## RP2040 / RP2350

### Method 1: Drag & Drop (Recommended)

1. Download `espfc_vX.X.X_rp2040.uf2` from [Releases](https://github.com/btechioi/esp-fc/releases)
2. **Hold** the BOOT/UF2 button on your RP2040 board
3. **Connect** USB while holding BOOT
4. Board appears as mass storage drive
5. **Drag** the `.uf2` file onto the drive
6. Board auto-reboots and runs ESP-FC

> [!TIP]
> On Raspberry Pi Pico, hold BOOT button, press and release RESET, then release BOOT.

### Method 2: picotool

```bash
# Install picotool
pip install picotool

# Flash firmware
picotool upload espfc_vX.X.X_rp2040.uf2

# Or reboot into UF2 mode first
picotool reboot -f
```

---

## ESP8266

### Using esptool.py

```bash
esptool.py --chip esp8266 \
  --port /dev/ttyUSB0 \
  --baud 921600 \
  write_flash 0x00000 espfc_vX.X.X_esp8266.bin
```

---

## First Boot

After flashing:

1. **Connect** to Betaflight Configurator
2. Go to **CLI** tab
3. Type `status` to verify
4. Configure pins per [Wiring Guide](/docs/wiring.md)
5. Calibrate gyro: `cal gyro`
6. Set up receiver
7. **Save** configuration

---

## Driver Installation

### CH340 (ESP32/ESP8266)

| OS | Driver |
|----|--------|
| Windows | Auto-installs or [CH340 Driver](https://sparks.gogo.co.nz/ch340.html) |
| macOS | Usually auto-detected |
| Linux | `sudo apt install linux-tools-common` (usually pre-installed) |

### CP2102 (Some boards)

| OS | Driver |
|----|--------|
| Windows | [CP210x Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) |
| macOS | [CP210x Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) |
| Linux | Usually pre-installed |

### USB on RP2040

No driver needed! USB is natively supported.

---

## Troubleshooting

### Board Not Detected
- Try a different USB cable (data cable, not charge-only)
- Try a different USB port (USB 2.0 preferred)
- Press RESET button on the board
- Check device manager for COM port

### Flash Failed
- Hold BOOT button while flashing (ESP32)
- Try lower baud rate: `--baud 460800`
- Erase flash first: `esptool.py erase_flash`

### RP2040 Not Entering UF2 Mode
- Hold BOOT button before connecting USB
- On Pico: hold BOOT, press RESET, release BOOT

---

## Building from Source

```bash
# Install PlatformIO
pip install platformio

# Clone repository
git clone https://github.com/btechioi/esp-fc.git
cd esp-fc

# Build for specific target
pio run -e esp32s3

# Build all targets
pio run

# Flash
pio run -e esp32s3 -t upload --upload-port /dev/ttyUSB0
```

### Build Targets

| Environment | MCU | Command |
|-------------|-----|---------|
| `esp32` | ESP32 | `pio run -e esp32` |
| `esp32s3` | ESP32-S3 | `pio run -e esp32s3` |
| `esp32s2` | ESP32-S2 | `pio run -e esp32s2` |
| `esp32c3` | ESP32-C3 | `pio run -e esp32c3` |
| `esp8266` | ESP8266 | `pio run -e esp8266` |
| `rp2040` | RP2040 | `pio run -e rp2040` |
| `rp2350` | RP2350 | `pio run -e rp2350` |

---

## Update Firmware

### ESP32
1. Download new firmware
2. Flash same way as initial install
3. Settings are preserved (or use `defaults` to reset)

### RP2040
1. Hold BOOT, connect USB
2. Drag new `.uf2` file
3. Done!

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)
🐙 [github.com/btechioi](https://github.com/btechioi)

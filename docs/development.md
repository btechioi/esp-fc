# ESP-FC Development Guide

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=ESP-FC%20Development&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

## Requirements

* [PlatformIO](https://platformio.org/install/ide?install=vscode)
* [VSCode](https://code.visualstudio.com/) (recommended)
* Git

---

## Building

```bash
# Clone repository
git clone https://github.com/btechioi/esp-fc.git
cd esp-fc

# Build for ESP32-S3
pio run -e esp32s3

# Build for RP2040
pio run -e rp2040

# Build for RP2350
pio run -e rp2350

# Build all targets
pio run
```

---

## Environment Targets

| Environment | MCU | Notes |
|-------------|-----|-------|
| `esp32` | ESP32 | Basic |
| `esp32s3` | ESP32-S3 | Recommended |
| `esp32s2` | ESP32-S2 | Experimental |
| `esp32c3` | ESP32-C3 | RISC-V |
| `rp2040` | RP2040 | CMSIS-DSP |
| `rp2350` | RP2350 | CMSIS-DSP |
| `native` | PC | Unit tests |

---

## Flashing

```bash
# Flash to device
pio run -e esp32s3 -t upload

# With specific port
pio run -e esp32s3 -t upload --upload-port /dev/ttyUSB0
```

---

## Testing

```bash
# Run unit tests
pio test -e native

# Specific test
pio test -e native -f test_filter
```

---

## Project Structure

```
esp-fc/
├── lib/
│   └── Espfc/           # Main firmware
│       └── src/
│           ├── Control/     # PID, rates
│           ├── Connect/      # MSP, CLI
│           ├── Device/       # Hardware drivers
│           ├── Output/       # Motor control
│           ├── Sensor/       # Gyro, GPS, etc
│           └── Utils/        # Math, filters
├── examples/
│   └── espnow-bridge/   # ESP-NOW transmitter
├── docs/                # Documentation
└── platformio.ini       # Build config
```

---

## Key Files

| File | Purpose |
|------|---------|
| `platformio.ini` | Build configuration |
| `Model.h/cpp` | Main state machine |
| `Mixer.cpp` | Motor mixing |
| `Controller.cpp` | PID controller |
| `MspProcessor.cpp` | Betaflight MSP |
| `Cli.cpp` | CLI commands |

---

## Adding New Features

1. Create feature branch
2. Implement in appropriate module
3. Add MSP/CLI interface if needed
4. Test on target hardware
5. Submit PR

---

## Debugging

### Serial Monitor
```bash
pio device monitor -e esp32s3
```

### CPU Usage
```bash
# In CLI
stats
```

---

## Docker (Optional)

```bash
# Build in container
docker-compose run pio pio run -e esp32s3

# Run tests
docker-compose run pio pio test -e native
```

> [!NOTE]
> Docker needs device access for flashing

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)
🐙 [github.com/btechioi](https://github.com/btechioi)

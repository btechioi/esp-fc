# ESP-FC Setup Guide

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=ESP-FC%20Setup%20Guide&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

> [!IMPORTANT]
> Read carefully before first flight!

---

## Connecting to Betaflight Configurator

1. Install [Betaflight Configurator](https://github.com/betaflight/betaflight-configurator/releases)
2. Go to **Options** tab:
   - Disable `Advanced CLI AutoComplete`
   - Enable `Show all serial devices`
   - Disable `Auto-Connect`

3. Select your device and click **Connect**

![Options](./images/bfc/bfc_options.png)

> [!NOTE]
> Not all configurator options are available. If an option doesn't save, it's not supported.

---

## Configure Wiring

Go to **CLI** tab and type:
```
get pin
```

This shows current pin assignments. Adjust with:
```
set pin_output_0 2
save
```

---

## Gyro Calibration

1. Place quad in horizontal position
2. Go to **Setup** tab
3. Click **"Calibrate Accelerometer"**
4. Wait 2 seconds

> [!CAUTION]
> Ensure model preview matches your actual orientation. If not, adjust **Board Orientation** or **Sensor Alignment** in Configuration tab.

---

## System Configuration

In **Configuration** tab, set **Pid loop frequency**:
- Recommended: 1kHz to 2kHz
- CPU Load should stay below 50%

---

## Receiver Setup

### Serial RX (SBUS/IBUS/CRSF)

1. Go to **Ports** tab
2. Enable `Serial Rx` on your UART
3. Go to **Receiver** tab
4. Select **Receiver Mode** and **Serial Receiver Provider**

### ESP-NOW

1. Choose "SPI Rx" as Receiver Mode
2. See [ESP-NOW Bridge](/docs/espnow-bridge.md) for RP2040 setup

---

## GPS Setup

### Hardware Connection

| GPS | FC |
|-----|-----|
| TX | UART RX |
| RX | UART TX |
| VCC | 3.3V/5V |
| GND | GND |

### Enable GPS

```bash
set feature GPS = ON
save
```

### Configure Serial Port

```bash
# UART2 at 115200 baud
serial 1 1024 115200 115200 0 115200
save
```

### M10 Dual-Band Configuration

```bash
# All constellations
set gps_gnss_mode 5

# Enable L1+L5 dual-band
set gps_enable_dual_band 1

save
reboot
```

---

## Motor Setup

### Verify Motor Direction

1. Remove propellers!
2. Connect battery
3. Go to **Motors** tab
4. Enable test mode
5. Spin each motor to verify direction

> [!CAUTION]
> Motor order and direction MUST be correct before flying!

### ESC Protocol

| Protocol | Use Case |
|----------|----------|
| DSHOT600 | Best performance |
| DSHOT300 | Good balance |
| DSHOT150 | Compatible |
| ONESHOT125 | Older ESCs |
| BRUSHED | Brushed motors only |

> [!NOTE]
> For multirotor, DSHOT150 or DSHOT300 is recommended.

### ESC Calibration (Analog protocols only)

1. Move master slider to highest value
2. Connect battery
3. Wait for ESC calibration beeps
4. Move slider to lowest
5. ESCs should confirm

---

## Flight Modes

| Mode | Description |
|------|-------------|
| ARM | Required to arm motors |
| ANGLE | Self-leveling (roll/pitch) |
| AIRMODE | Extended control range |
| ALTHOLD | Altitude hold (needs baro) |
| FAILSAFE | Auto-land on signal loss |

### Configuration

1. Go to **Modes** tab
2. Assign modes to AUX channels
3. Set range (e.g., 1700-2100)

---

## Blackbox

### Enable Recording

**Onboard Flash:**
1. Go to **Blackbox** tab
2. Select **Onboard Flash**

**Serial (OpenLog):**
1. Configure UART for Blackbox in **Ports** tab
2. Select **Serial Port** in **Blackbox** tab

### Recommended Settings

| Loop Rate | Min Serial Speed |
|-----------|------------------|
| 1kHz | 500kbps |
| 2kHz | 1Mbps |

---

## Limitations

### Configuration Tab
- Only `Dynamic Filter`, `GPS`, `SoftSerial` are functional
- AIRMODE is in Modes tab only

### Modes Tab
- Add range works only (no add link)

### Adjustments
- Not implemented - use `scaler` CLI instead

### Servos
- Not implemented - use `output_*` CLI

### Motors
- 3D mode supported (enable via CLI)
- Only Quad-X mixer

### GPS
- CLI-only configuration for GNSS settings

### PID Tuning
- Single PID profile only
- Some Betaflight features disabled

---

## Troubleshooting

### No Gyro Detected
- Check SPI/I2C wiring
- Verify CS pin configuration
- Try different gyro `dev` setting

### Motors Not Spinning
- Verify protocol matches ESC capability
- Check pin assignments
- Ensure feature is enabled

### RC Signal Lost
- Check UART wiring
- Verify serial rx provider
- Check failsafe settings

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)
🌐 [btechioi.netlify.app](https://btechioi.netlify.app)

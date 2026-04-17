# ESP-FC Wiring & Pin Mapping

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=ESP-FC%20Wiring&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

## Overview

ESP32/RP2040 MCUs allow pin remapping, so wiring is not final. Use `get pin` command in CLI to check current assignments.

### Quick Reference

| Function | CLI Command | RP2040 | ESP32 | ESP32-S3 |
|----------|-------------|--------|-------|----------|
| Motor 1 | `pin_output_0` | 2 | 27 | 39 |
| Motor 2 | `pin_output_1` | 3 | 25 | 40 |
| Motor 3 | `pin_output_2` | 4 | 4 | 41 |
| Motor 4 | `pin_output_3` | 5 | 12 | 42 |

---

## Remapping Pins

```bash
# Set output 0 to pin 1
set pin_output_0 1

# Unmap a pin
set pin_output_3 -1
```

> [!NOTE]
> Not all pins work with all functions. Some pins are input-only or strapping pins. Consult MCU documentation.

---

## I2C Pin Mapping

| Module Pin | CLI Name | ESP32 | ESP32-S3 | RP2040 |
|------------|----------|-------|----------|--------|
| SCK/SCL | `pin_i2c_scl` | 22 | 10 | 17 |
| SDA/SDI | `pin_i2c_sda` | 21 | 9 | 16 |

---

## SPI Pin Mapping

| Module Pin | CLI Name | ESP32 | ESP32-S3 | RP2040 |
|------------|----------|-------|----------|--------|
| SCK | `pin_spi_0_sck` | 18 | 12 | 14 |
| MOSI | `pin_spi_0_mosi` | 23 | 11 | 15 |
| MISO | `pin_spi_0_miso` | 19 | 13 | 12 |
| CS Gyro | `pin_spi_cs_0` | 5 | 8 | 13 |
| CS Baro | `pin_spi_cs_1` | 13 | 7 | 11 |

> [!TIP]
> For better performance, prefer SPI over I2C.

---

## UART Pin Mapping

| UART | CLI Name | ESP32 | ESP32-S3 | RP2040 |
|------|----------|-------|----------|--------|
| RX0 | `pin_serial_0_rx` | 3 | 44 | 1 |
| TX0 | `pin_serial_0_tx` | 1 | 43 | 0 |
| RX1 | `pin_serial_1_rx` | 32 | 15 | 9 |
| TX1 | `pin_serial_1_tx` | 33 | 16 | 8 |
| RX2 | `pin_serial_2_rx` | 16 | 17 | 5 |
| TX2 | `pin_serial_2_tx` | 17 | 18 | 4 |

---

## ADC Pin Mapping

| Function | CLI Name | ESP32 | ESP32-S3 | RP2040 |
|----------|----------|-------|----------|--------|
| Voltage | `pin_input_adc_0` | 36 | 1 | 26 |
| Current | `pin_input_adc_1` | 39 | 4 | 27 |

---

## RC Input Pin

| Function | CLI Name | ESP32 | ESP32-S3 | RP2040 |
|----------|----------|-------|----------|--------|
| PPM | `pin_input_rx` | 35 | 6 | -1 |

---

## Other Pins

| Function | CLI Name | ESP32 | ESP32-S3 | RP2040 |
|----------|----------|-------|----------|--------|
| Buzzer | `pin_buzzer` | 26 | 5 | -1 |
| LED | `pin_led` | 0 | -1 | -1 |

---

## Wiring Diagrams

### ESP32 SPI MPU-6500/MPU-9250

![ESP32 SPI Wiring](./images/esp-fc-esp32_spi_wiring.png)

### ESP32 I2C MPU-6050

![ESP32 I2C Wiring](./images/esp-fc-esp32_i2c_wiring.png)

### RP2040 Connections

| RP2040 | Gyro | Description |
|--------|------|-------------|
| GPIO 14 | SCK | SPI clock |
| GPIO 15 | MOSI | SPI data out |
| GPIO 12 | MISO | SPI data in |
| GPIO 13 | CS | Gyro chip select |
| GPIO 16 | SDA | I2C data |
| GPIO 17 | SCL | I2C clock |

| RP2040 | GPS/RC | Description |
|--------|--------|-------------|
| GPIO 8 | TX | Serial to RC/GPS |
| GPIO 9 | RX | Serial from RC/GPS |
| GPIO 4 | TX2 | Telemetry (optional) |
| GPIO 5 | RX2 | Telemetry (optional) |

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)

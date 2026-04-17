# ESP-FC Pinout Reference

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=ESP-FC%20Pinouts&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

## ESP32-S3 Pinout

| Pin | Function | ESPFC |
|-----|----------|-------|
| 1 | ADC_VOLTAGE | `pin_input_adc_0` |
| 4 | ADC_CURRENT | `pin_input_adc_1` |
| 5 | BUZZER | `pin_buzzer` |
| 6 | PPM | `pin_input_rx` |
| 7 | SPI_CS_BARO | `pin_spi_cs_1` |
| 8 | SPI_CS_GYRO | `pin_spi_cs_0` |
| 9 | I2C_SDA | `pin_i2c_0_sda` |
| 10 | I2C_SCL | `pin_i2c_0_scl` |
| 11 | SPI_MOSI | `pin_spi_0_mosi` |
| 12 | SPI_SCK | `pin_spi_0_sck` |
| 13 | SPI_MISO | `pin_spi_0_miso` |
| 39 | MOTOR_0 | `pin_output_0` |
| 40 | MOTOR_1 | `pin_output_1` |
| 41 | MOTOR_2 | `pin_output_2` |
| 42 | MOTOR_3 | `pin_output_3` |
| 43 | UART0_TX | `pin_serial_0_tx` |
| 44 | UART0_RX | `pin_serial_0_rx` |

---

## RP2040 Pinout

| Pin | Function | ESPFC |
|-----|----------|-------|
| 0 | UART0_TX | `pin_serial_0_tx` |
| 1 | UART0_RX | `pin_serial_0_rx` |
| 2 | MOTOR_0 | `pin_output_0` |
| 3 | MOTOR_1 | `pin_output_1` |
| 4 | MOTOR_2 / UART2_TX | `pin_output_2`, `pin_serial_2_tx` |
| 5 | MOTOR_3 / UART2_RX | `pin_output_3`, `pin_serial_2_rx` |
| 8 | UART1_TX | `pin_serial_1_tx` |
| 9 | UART1_RX | `pin_serial_1_rx` |
| 12 | SPI_MISO | `pin_spi_0_miso` |
| 13 | SPI_CS_GYRO | `pin_spi_cs_0` |
| 14 | SPI_SCK | `pin_spi_0_sck` |
| 15 | SPI_MOSI | `pin_spi_0_mosi` |
| 16 | I2C_SDA | `pin_i2c_0_sda` |
| 17 | I2C_SCL | `pin_i2c_0_scl` |
| 26 | ADC_VOLTAGE | `pin_input_adc_0` |
| 27 | ADC_CURRENT | `pin_input_adc_1` |

---

## ESP32 Pinout

| Pin | Function | ESPFC |
|-----|----------|-------|
| 1 | UART0_TX | CLI/MSP |
| 3 | UART0_RX | CLI/MSP |
| 5 | SPI_CS_GYRO | `pin_spi_cs_0` |
| 12 | MOTOR_3 | `pin_output_3` |
| 13 | SPI_CS_BARO | `pin_spi_cs_1` |
| 16 | UART2_RX | GPS |
| 17 | UART2_TX | GPS |
| 18 | SPI_SCK | Gyro |
| 19 | SPI_MISO | Gyro |
| 21 | I2C_SDA | Sensors |
| 22 | I2C_SCL | Sensors |
| 23 | SPI_MOSI | Gyro |
| 25 | MOTOR_1 | `pin_output_1` |
| 26 | BUZZER | `pin_buzzer` |
| 27 | MOTOR_0 | `pin_output_0` |
| 32 | UART1_RX | RC Serial |
| 33 | UART1_TX | RC Serial |
| 36 | ADC_VOLTAGE | `pin_input_adc_0` |
| 39 | ADC_CURRENT | `pin_input_adc_1` |

---

## Notes

> [!NOTE]
> GPIO 34-39 are input-only on ESP32

> [!TIP]
> For RP2040, use SPI for best gyro performance

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)

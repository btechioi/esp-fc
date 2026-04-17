# ESP-FC Wireless Setup

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:fd79a8,100:a29bfe&height=100&section=header&text=ESP-FC%20Wireless&fontSize=30&fontAlignY=35&animation=fadeIn&fontColor=ffffff"/>
</p>

---

## WiFi Configuration

> [!NOTE]
> WiFi requires `SOFTSERIAL` feature. While WiFi is active, ARM is disabled.

### Enable WiFi

```bash
# Enable softserial for WiFi
set feature SOFTSERIAL = ON
save
reboot
```

WiFi starts automatically after 30 seconds in failsafe mode.

---

## WiFi Modes

### Access Point Mode (Default)

- SSID: `ESP-FC`
- Password: None (open)
- IP: `192.168.4.1:1111`

### Station Mode

```bash
# Connect to home network
set wifi_ssid YOUR_NETWORK
set wifi_pass YOUR_PASSWORD
save
reboot
```

### Check Connection

```bash
wifi
ST IP4: tcp://192.168.1.100:1111
ST MAC: 30:30:F9:6E:10:74
AP IP4: tcp://192.168.4.1:1111
AP MAC: 32:30:F9:6E:10:74
```

---

## ESP-NOW (ESP32 Only)

ESP-NOW is a proprietary protocol for direct RC control without router.

### Configuration

1. Select "SPI Rx (built-in Rx)" as Receiver Mode
2. Transmitter binds automatically

### Startup Order

1. Turn on transmitter first
2. Then power up flight controller

---

## ESP-NOW Bridge (RP2040)

For RP2040, use external ESP32 as bridge. See [ESP-NOW Bridge Guide](/docs/espnow-bridge.md).

---

## Troubleshooting

### WiFi Not Connecting
- Check SSID/password (no spaces)
- Ensure router supports 2.4GHz
- Check DHCP range

### ESP-NOW Not Binding
- Ensure same WiFi channel
- Check peer MAC addresses
- Restart both devices

---

# 📫 Questions?

📧 [banumathhettiarachchi@gmail.com](mailto:banumathhettiarachchi@gmail.com)

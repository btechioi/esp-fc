#include <EspNowRcLink/Receiver.h>
#include <esp_now.h>
#include <WiFi.h>

#define SBUS_BAUD 100000

static EspNowRcLink::Receiver rx;

struct SensorData {
    int16_t vbat;
    int16_t current;
    int16_t rpm[4];
    int16_t temp;
} __attribute__((packed));

static SensorData sensors;
static bool hasSensors = false;

void sendSbusUart(const uint16_t* channels) {
    uint8_t sbusBuf[25];
    memset(sbusBuf, 0, sizeof(sbusBuf));

    sbusBuf[0] = 0x0F;

    uint16_t ch[16];
    for (int i = 0; i < 16; i++) {
        ch[i] = (channels[i] - 1000) * 1536 / 1000 + 172;
        ch[i] = constrain(ch[i], 172, 1811);
    }

    sbusBuf[1] = (ch[0] & 0xFF);
    sbusBuf[2] = (ch[0] >> 8) | (ch[1] << 3);
    sbusBuf[3] = (ch[1] >> 5);
    sbusBuf[4] = (ch[1] >> 10) | (ch[2] << 6);
    sbusBuf[5] = (ch[2] >> 2);
    sbusBuf[6] = (ch[2] >> 7) | (ch[3] << 4);
    sbusBuf[7] = (ch[3] >> 4);
    sbusBuf[8] = (ch[3] >> 9) | (ch[4] << 7);
    sbusBuf[9] = (ch[4] >> 1);
    sbusBuf[10] = (ch[4] >> 6) | (ch[5] << 5);
    sbusBuf[11] = (ch[5] >> 3);
    sbusBuf[12] = (ch[5] >> 8) | (ch[6] << 8);
    sbusBuf[13] = (ch[6] >> 3) | (ch[7] << 5);
    sbusBuf[14] = (ch[7] >> 5);
    sbusBuf[15] = (ch[7] >> 10) | (ch[8] << 6);
    sbusBuf[16] = (ch[8] >> 2);
    sbusBuf[17] = (ch[8] >> 7) | (ch[9] << 4);
    sbusBuf[18] = (ch[9] >> 4);
    sbusBuf[19] = (ch[9] >> 9) | (ch[10] << 7);
    sbusBuf[20] = (ch[10] >> 1);
    sbusBuf[21] = (ch[10] >> 6) | (ch[11] << 5);
    sbusBuf[22] = (ch[11] >> 3);
    sbusBuf[23] = (ch[11] >> 8) | (ch[12] << 8);
    sbusBuf[24] = 0x00;

    Serial2.write(sbusBuf, 25);
}

void sendTelemetryEspNow() {
    if (hasSensors) {
        rx.setSensor(0, sensors.vbat);
        rx.setSensor(1, sensors.current);
        rx.setSensor(2, sensors.temp);
        hasSensors = false;
    }
}

void handleSerialTelemetry() {
    static uint8_t buf[64];
    static size_t idx = 0;

    while (Serial2.available()) {
        uint8_t b = Serial2.read();

        if (idx == 0 && b != 0xA5) {
            continue;
        }

        if (idx == 1) {
            if (b > 32) {
                idx = 0;
                continue;
            }
            buf[idx++] = b;
        }

        if (idx >= 2) {
            buf[idx++] = b;

            uint8_t len = buf[1];
            if (idx >= len + 3) {
                uint8_t type = buf[2];
                if (type == 0x01) {
                    memcpy(&sensors, &buf[3], sizeof(SensorData));
                    hasSensors = true;
                }
                idx = 0;
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(SBUS_BAUD, SERIAL_8E2);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW init failed");
        return;
    }

    rx.begin();
    Serial.println("ESP-NOW RC Bridge Ready");
    Serial.print("STA MAC: ");
    Serial.println(WiFi.macAddress());
}

void loop() {
    rx.update();

    if (rx.available()) {
        uint16_t channels[16];
        for (int i = 0; i < 16; i++) {
            channels[i] = rx.getChannel(i);
        }
        sendSbusUart(channels);
    }

    handleSerialTelemetry();
    sendTelemetryEspNow();

    delayMicroseconds(100);
}

#pragma once

#if defined(ARDUINO_ARCH_RP2040)

#include "Device/SerialDevice.h"
#include "Device/InputDevice.h"
#include <cstdint>
#include <cstddef>

namespace Espfc {

namespace Device {

class InputEspNowBridge : public InputDevice
{
public:
    InputEspNowBridge();

    int begin(Device::SerialDevice* serial);
    InputStatus update() override;
    uint16_t get(uint8_t i) const override;
    void get(uint16_t* data, size_t len) const override;
    size_t getChannelCount() const override { return 16; }
    bool needAverage() const override { return false; }

    void setBaudRate(uint32_t baud);

private:
    void parse(int d);
    void apply();

    Device::SerialDevice* _serial;
    static constexpr size_t CHANNELS = 16;
    static constexpr size_t SBUS_FRAME_SIZE = 25;

    enum SbusState {
        SBUS_START,
        SBUS_DATA,
        SBUS_END
    };

    SbusState _state = SBUS_START;
    uint8_t _idx = 0;
    bool _newData = false;
    uint32_t _lastReceive = 0;

    uint8_t _data[SBUS_FRAME_SIZE];
    uint16_t _channels[CHANNELS];
    uint8_t _flags = 0;

    static constexpr uint32_t TIMEOUT_MS = 2000;
};

}
}

#endif

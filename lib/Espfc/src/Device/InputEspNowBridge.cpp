#include "InputEspNowBridge.h"
#include "Model.h"

namespace Espfc {

namespace Device {

InputEspNowBridge::InputEspNowBridge()
{
    for (size_t i = 0; i < CHANNELS; i++) {
        _channels[i] = 1024;
    }
}

int InputEspNowBridge::begin(Device::SerialDevice* serial)
{
    _serial = serial;
    return 0;
}

void InputEspNowBridge::parse(int d)
{
    uint8_t byte = d & 0xFF;

    switch (_state)
    {
        case SBUS_START:
            if (byte == 0x0F) {
                _data[_idx++] = byte;
                _state = SBUS_DATA;
            }
            break;

        case SBUS_DATA:
            _data[_idx++] = byte;
            if (_idx >= SBUS_FRAME_SIZE) {
                _state = SBUS_END;
            }
            break;

        case SBUS_END:
            if (byte == 0x00) {
                _data[_idx++] = byte;
                apply();
            }
            _idx = 0;
            _state = SBUS_START;
            break;
    }
}

void InputEspNowBridge::apply()
{
    if (_idx < SBUS_FRAME_SIZE) return;

    _flags = _data[23];

    _channels[0]  = ((_data[1]     | _data[2] << 8)                  & 0x07FF);
    _channels[1]  = ((_data[2] >> 3 | _data[3] << 5)                 & 0x07FF);
    _channels[2]  = ((_data[3] >> 6 | _data[4] << 2 | _data[5] << 10)  & 0x07FF);
    _channels[3]  = ((_data[5] >> 1 | _data[6] << 7)                 & 0x07FF);
    _channels[4]  = ((_data[6] >> 4 | _data[7] << 4)                 & 0x07FF);
    _channels[5]  = ((_data[7] >> 7 | _data[8] << 1 | _data[9] << 9)  & 0x07FF);
    _channels[6]  = ((_data[9] >> 2 | _data[10] << 6)                & 0x07FF);
    _channels[7]  = ((_data[10] >> 5| _data[11] << 3)                & 0x07FF);
    _channels[8]  = ((_data[12]    | _data[13] << 8)                 & 0x07FF);
    _channels[9]  = ((_data[13] >> 3| _data[14] << 5)                & 0x07FF);
    _channels[10] = ((_data[14] >> 6| _data[15] << 2 | _data[16] << 10)& 0x07FF);
    _channels[11] = ((_data[16] >> 1| _data[17] << 7)                & 0x07FF);
    _channels[12] = ((_data[17] >> 4| _data[18] << 4)               & 0x07FF);
    _channels[13] = ((_data[18] >> 7| _data[19] << 1 | _data[20] << 9) & 0x07FF);
    _channels[14] = ((_data[20] >> 2| _data[21] << 6)               & 0x07FF);
    _channels[15] = ((_data[21] >> 5| _data[22] << 3)                & 0x07FF);

    for (size_t i = 0; i < CHANNELS; i++) {
        _channels[i] = (_channels[i] - 172) * 1000 / 1536 + 1000;
        _channels[i] = (_channels[i] < 1000) ? 1000 : (_channels[i] > 2000) ? 2000 : _channels[i];
    }

    _newData = true;
}

InputStatus InputEspNowBridge::update()
{
    if (!_serial) return INPUT_IDLE;

    while (_serial->available()) {
        parse(_serial->read());
    }

    if (_newData) {
        _newData = false;
        return INPUT_RECEIVED;
    }

    return INPUT_IDLE;
}

uint16_t InputEspNowBridge::get(uint8_t i) const
{
    if (i >= CHANNELS) return 1500;
    return _channels[i];
}

void InputEspNowBridge::get(uint16_t* data, size_t len) const
{
    for (size_t i = 0; i < len && i < CHANNELS; i++) {
        data[i] = _channels[i];
    }
}

}
}

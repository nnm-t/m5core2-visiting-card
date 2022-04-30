#include "plus-encoder.h"

void PlusEncoder::begin(std::function<void(int8_t)>&& on_rotate, std::function<void()>&& on_press)
{
    _on_rotate = on_rotate;
    _on_press = on_press;
}

void PlusEncoder::update()
{
    Wire.requestFrom(i2c_address, i2c_payload_size);

    while (Wire.available())
    {
        const int8_t encode = Wire.read();
        const bool is_press = Wire.read() != 0xFF;

        if (_on_rotate != nullptr)
        {
            _on_rotate(encode);
        }

        if (is_press && _on_press != nullptr)
        {
            _on_press();
        }
    }
}
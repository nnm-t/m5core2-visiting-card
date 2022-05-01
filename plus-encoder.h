#pragma once

#include "config.h"

#include <functional>

#include <Arduino.h>
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif
#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif

class PlusEncoder
{
    static constexpr const uint8_t i2c_address = 0x62;
    static constexpr const uint8_t i2c_payload_size = 2;

    TwoWire* const _wire;
    bool _is_pressed = false;

    std::function<void(int8_t)> _on_rotate = nullptr;
    std::function<void()> _on_pressed = nullptr;

public:
    PlusEncoder(TwoWire* const wire) : _wire(wire)
    {

    }

    void begin(std::function<void(int8_t)>&& on_rotate = nullptr, std::function<void()>&& on_pressed = nullptr);

    void update();
};
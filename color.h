#pragma once

#include "config.h"

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <LovyanGFX.h>
#include <ArduinoJson.h>

class Color
{
    const uint8_t _red;
    const uint8_t _green;
    const uint8_t _blue;

public:
    static Color fromJson(JsonVariant& json_color);

    Color(const uint8_t red, const uint8_t green, const uint8_t blue) : _red(red), _green(green), _blue(blue)
    {

    }

    const uint8_t getRed() const
    {
        return _red;
    }

    const uint8_t getGreen() const
    {
        return _green;
    }

    const uint8_t getBlue() const
    {
        return _blue;
    }

    const uint32_t getRGB888() const
    {
        return (_red << 16) + (_green << 8) + _blue;
    }
};
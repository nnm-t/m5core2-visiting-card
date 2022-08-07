
#pragma once

#include "config.h"

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <ArduinoJson.h>
#include <FastLED.h>

#include "color.h"

class LED
{
public:
    static constexpr const uint16_t neopixel_column = 24;
    static constexpr const uint16_t neopixel_row = 8;

    static constexpr const uint16_t neopixel_char_width = 8;

    static constexpr const uint8_t neopixel_gpio = 26;
    static constexpr const uint16_t neopixel_num = neopixel_column * neopixel_row;

private:
    CRGB _leds[neopixel_num];

public:
    LED()
    {
    }

    void begin();

    void set(const uint16_t column, const uint16_t row, CRGB& crgb);

    void set(const uint16_t column, const uint16_t row, Color& color);

    void unset(const uint16_t column, const uint16_t row);

    void show();
};

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
#include <FastLED.h>

#include "color.h"
#include "led-pattern.h"

class LED
{
    static constexpr const uint16_t neopixel_column = 24;
    static constexpr const uint16_t neopixel_row = 8;

public:
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

    void show();
};
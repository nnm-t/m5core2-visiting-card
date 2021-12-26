
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
#include <Adafruit_NeoPixel.h>

#include "color.h"
#include "led-pattern.h"

class LED
{
    static constexpr const size_t neopixel_num = 10;
    static constexpr const uint8_t brightness_min = 0;
    static constexpr const uint8_t brightness_max = 31;
    static constexpr const size_t brightness_count_max = 20;

    const Color _color;
    const LEDPattern _pattern;

    bool _is_enabled = false;
    uint8_t _brightness = brightness_max;
    bool _brightness_reverse = false;
    size_t _brightness_count = 0;

public:
    static LED fromJson(JsonVariant& json_led);

    LED(const Color& color, const LEDPattern pattern) : _color(color), _pattern(pattern)
    {

    }

    void toggle()
    {
        _is_enabled = !_is_enabled;
    }

    void begin(Adafruit_NeoPixel* const neopixel);

    void update(Adafruit_NeoPixel* const neopixel);
};
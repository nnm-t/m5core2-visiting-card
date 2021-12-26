
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

    const Color _color;
    const LEDPattern _pattern;

public:
    static LED fromJson(JsonVariant& json_led);

    LED(const Color& color, const LEDPattern pattern) : _color(color), _pattern(pattern)
    {

    }

    void begin(Adafruit_NeoPixel* const neopixel);

    void update(Adafruit_NeoPixel* const neopixel);
};
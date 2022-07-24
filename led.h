
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
public:
    static constexpr const uint8_t neopixel_gpio = 26;
    static constexpr const uint16_t neopixel_num = 192;

private:
    CRGB _leds[neopixel_num];

public:
    static LED fromJson(JsonVariant& json_led);

    LED()
    {
    }

    void begin();

    void update();
};
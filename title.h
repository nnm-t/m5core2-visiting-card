#pragma once

#include "config.h"

#include <Arduino.h>
#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <LovyanGFX.h>
#include <ArduinoJson.h>
#ifdef ENABLE_SHT31
#include <Adafruit_SHT31.h>
#endif

#include "color.h"
#include "counter.h"

class Title
{
    const Color _foreground;
    const Color _background;

    void init_text(LGFX* const lcd);

public:
    Title(const Color& foreground, const Color& background) : _foreground(foreground), _background(background)
    {
    
    }

    Title(const Color&& foreground, const Color&& background) : _foreground(foreground), _background(background)
    {
    
    }

    static Title fromJson(JsonVariant& json_title);

    void begin(LGFX* const lcd);

#ifdef ENABLE_SHT31
    void update(LGFX* const lcd, Adafruit_SHT31* const sht31);
#else
    void update(LGFX* const lcd);
#endif

    void draw_counter(LGFX* const lcd, Counter* const counter);
};
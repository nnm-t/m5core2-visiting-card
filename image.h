
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

class Image
{
    static constexpr const char* extension_bmp = ".bmp";
    static constexpr const char* extension_png = ".png";
    static constexpr const char* extension_jpg = ".jpg";

    const int32_t _x;
    const int32_t _y;
    String _src;

public:
    Image fromJson(JsonVariant& json_image);

    Image(const uint32_t x, const uint32_t y, String& src) : _x(x), _y(y), _src(src)
    {

    }

    void show(LGFX* const lcd);
};
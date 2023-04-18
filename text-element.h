#pragma once

#include "config.h"

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>
#include <ArduinoJson.h>

#include "text-size.h"
#include "color.h"

class TextElement
{
    const int32_t _x;
    const int32_t _y;
    const TextSize _size;
    String _text;
    const Color _foreground;
    const Color _background;

    void setFont(LGFX* const lcd);

public:
    static TextElement fromJson(JsonObject& json_element);

    TextElement(const int32_t x, const int32_t y, const TextSize size, String& text, const Color& foreground, const Color& background) : _x(x), _y(y), _size(size), _text(text), _foreground(foreground)
, _background(background)
    {

    }

    void show(LGFX* const lcd);
};
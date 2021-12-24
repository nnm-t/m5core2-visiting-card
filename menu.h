#pragma once

#ifdef BOARD_M5STACK
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <LovyanGFX.h>
#include <ArduinoJson.h>

#include "color.h"

class Menu
{
    const Color _foreground;
    const Color _background;

public:
    static Menu fromJson(JsonVariant& json_menu);

    Menu(const Color& foreground, const Color& background) : _foreground(foreground), _background(background)
    {

    }

    void show(LGFX* const lcd);
};
#pragma once

#include "config.h"

#include <vector>

#include <Arduino.h>
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif
#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#include <LovyanGFX.h>
#include <ArduinoJson.h>

#include "color.h"
#include "text-element.h"
#include "image.h"
#include "scroll-led.h"

class Page
{
    Color _background_color;
    Image _image;
    std::vector<TextElement> _texts;
    ScrollLED _scroll_led;

public:
    Page(const Color& background_color, Image& image, JsonArray& texts_json, ScrollLED& scroll_led) : _background_color(background_color), _image(image), _texts(std::vector<TextElement>()), _scroll_led(scroll_led)
    {
        _texts.reserve(texts_json.size());
        
        for (JsonObject&& text_json : texts_json)
        {
            _texts.push_back(TextElement::fromJson(text_json));
        }
    }

    static Page fromJson(JsonObject& page_json);

    void show(LGFX* lcd, std::function<void()>&& on_led_completed);

    void updateScrollLED(LED* led);
};
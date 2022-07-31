#pragma once

#include "config.h"

#include <vector>

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif
#ifdef ENABLE_SHT31
#include "Adafruit_SHT31.h"
#endif

#include <LovyanGFX.h>
#include <ArduinoJson.h>

#include "color.h"
#include "title.h"
#include "menu.h"
#include "page.h"
#include "counter.h"
#include "scroll-led.h"

class Settings
{
    LGFX* _lcd = nullptr;
    LED* _led = nullptr;
    Counter* _counter = nullptr;
#ifdef ENABLE_SHT31
    Adafruit_SHT31* _sht31 = nullptr;
#endif

    Title _title;
    Menu _menu;
    ScrollLED _scroll_led;
    std::vector<Page> _pages;
    std::vector<Page>::iterator _pages_iterator;

public:
    static Settings* fromJson(JsonDocument& json_document);

    Settings(Title& title, Menu& menu, ScrollLED& scroll_led, JsonArray& pages_json) : _menu(menu), _title(title), _scroll_led(scroll_led), _pages(std::vector<Page>())
    {
        _pages.reserve(pages_json.size());
        for (JsonObject&& page_json : pages_json)
        {
            _pages.push_back(Page::fromJson(page_json));
        }

        _pages_iterator = _pages.begin();
    }

#ifdef ENABLE_SHT31
    void begin(LGFX& lcd, LED& led, Counter& counter, Adafruit_SHT31& sht31);
#else
    void begin(LGFX& lcd, LED& led, Counter& counter);
#endif

    void showCommon();

    void clearLCD();

    void update();

    void next();

    void prev();

    void draw_counter()
    {
        _title.draw_counter(_lcd, _counter);
    }
};
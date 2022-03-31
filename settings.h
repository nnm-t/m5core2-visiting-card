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
#include <Adafruit_NeoPixel.h>

#include "color.h"
#include "title.h"
#include "menu.h"
#include "led.h"
#include "image.h"
#include "text-element.h"
#include "qrcode.h"

class Settings
{
    LGFX* _lcd = nullptr;
    Adafruit_NeoPixel* _neopixel = nullptr;
#ifdef ENABLE_SHT31
    Adafruit_SHT31* _sht31 = nullptr;
#endif

    Title _title;
    Menu _menu;

public:
    static Settings* fromJson(JsonDocument& json_document);

    Settings(Title& title, Menu& menu) : _menu(menu), _title(title)
    {

    }

#ifdef ENABLE_SHT31
    void begin(LGFX& lcd, Adafruit_NeoPixel& neopixel, Adafruit_SHT31& sht31);
#else
    void begin(LGFX& lcd, Adafruit_NeoPixel& neopixel);
#endif

    void toggleLED();

    void showCommon();

    void showImage();

    void showQR();

    void clearLCD();

    void update();
};
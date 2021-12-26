#pragma once

#include "config.h"

#include <vector>

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
#include "menu.h"
#include "led.h"
#include "image.h"
#include "text-element.h"
#include "qrcode.h"

class Settings
{
    LGFX* _lcd = nullptr;
    Adafruit_NeoPixel* _neopixel = nullptr;

	Color _background;
    Menu _menu;
    LED _led;
    Image _image;
    std::vector<TextElement> _text_elements;
    QRCode _qrcode;

public:
    static Settings* fromJson(JsonDocument& json_document);

    Settings(Color& background, Menu& menu, LED& led, Image& image, std::vector<TextElement> text_elements, QRCode& qrcode) : _background(background), _menu(menu), _led(led), _image(image), _text_elements(text_elements), _qrcode(qrcode)
    {

    }

    void begin(LGFX* const lcd, Adafruit_NeoPixel* const neopixel);

    void showCommon();

    void showImage();

    void showQR();

    void clearLCD();

    void update();
};
#include "config.h"

#include <Arduino.h>
#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif
#include <Ticker.h>

#include <LovyanGFX.h>
#include <Adafruit_NeoPixel.h>
#ifdef ENABLE_SHT31
#include <Adafruit_SHT31.h>
#endif
#include <ArduinoJson.h>

#include "settings.h"

namespace {
    LGFX lcd;
    Ticker ticker;
    
    StaticJsonDocument<8192> json_document;

    Settings* pSettings = nullptr;

    constexpr uint8_t brightness_min = 63;
    constexpr uint8_t brightness_step = 32;
    constexpr uint8_t brightness_max = 255;

    constexpr size_t neopixel_num = 10;
    #ifdef BOARD_M5CORE
    constexpr size_t neopixel_pin = 15;

        #ifdef ENABLE_SHT31
        Adafruit_SHT31 sht31(&Wire);
        #endif
    #endif
    #ifdef BOARD_M5CORE2
    constexpr size_t neopixel_pin = 2;

        #ifdef ENABLE_SHT31
        Adafruit_SHT31 sht31(&Wire1);
        #endif
    #endif

    Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(neopixel_num, neopixel_pin);

    uint8_t display_brightness = 127;
}

void vibrateOn()
{
#ifdef BOARD_M5CORE2
    M5.Axp.SetLDOEnable(3, true);
#endif
}

void vibrateOff()
{
#ifdef BOARD_M5CORE2
    M5.Axp.SetLDOEnable(3, false);
#endif
}

void setLed(bool is_on)
{
#ifdef BOARD_M5CORE2
    M5.Axp.SetLed(is_on);
#endif
}

void setup() {
    M5.begin();
    lcd.init();
    lcd.setColorDepth(24);

    File json_file = SD.open("/settings.json");

    if (!json_file)
    {
        // ファイル無し
        lcd.setTextFont(&fonts::lgfxJapanGothic_16);
        lcd.drawString("MicroSD or settings.json 無し", 0, 0);
        return;
    }

    DeserializationError error = deserializeJson(json_document, json_file);

    if (error != DeserializationError::Ok)
    {
        Serial.println("JSON Deserialization Error");
        return;
    }

    // 設定/制御
    pSettings = Settings::fromJson(json_document);
    #ifdef ENABLE_SHT31
    pSettings->begin(lcd, neopixel, sht31);
    #else
    pSettings->begin(lcd, neopixel);
    #endif

    // 輝度default
    lcd.setBrightness(display_brightness);

    ticker.attach_ms(100, onTimerTicked);
}

void loop()
{

}


void onTimerTicked()
{
    M5.update();

#ifdef BOARD_M5CORE2
    // タッチ中LED消灯
    if (M5.Touch.ispressed())
    {
        setLed(false);
        vibrateOn();
    }
    else
    {
        setLed(true);
        vibrateOff();
    }
#endif

    if (M5.BtnA.wasPressed())
    {
        // 前
        pSettings->prev();
    }

    if (M5.BtnB.wasPressed())
    {
        // 輝度調整
        display_brightness += brightness_step;
        if (display_brightness >= brightness_max)
        {
            display_brightness = brightness_min;
        }
        lcd.setBrightness(display_brightness);
    }

    if (M5.BtnC.wasPressed())
    {
        // 次
        pSettings->next();
    }

    pSettings->update();
}
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
#ifdef ENABLE_SHT31
#include <Adafruit_SHT31.h>
#endif
#include <ArduinoJson.h>

#include "led.h"
#include "settings.h"
#include "counter.h"
#ifdef ENABLE_PLUS_MODULE
#include "plus-encoder.h"
#endif

namespace {
    LGFX lcd;
    Ticker ticker;
    
    StaticJsonDocument<8192> json_document;

    Settings* pSettings = nullptr;

    constexpr uint8_t brightness_min = 63;
    constexpr uint8_t brightness_step = 32;
    constexpr uint8_t brightness_max = 255;

    LED led;

    #ifdef BOARD_M5CORE
    TwoWire* wire = &Wire;
    #endif

    #ifdef BOARD_M5CORE2
    TwoWire* wire = &Wire1;
    #endif

    Counter counter;

    #ifdef ENABLE_SHT31
    Adafruit_SHT31 sht31(wire);
    #endif

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

    led.begin();
    // 設定/制御
    pSettings = Settings::fromJson(json_document);
    #ifdef ENABLE_SHT31
    pSettings->begin(lcd, led, counter, sht31);
    #else
    pSettings->begin(lcd, led, counter);
    #endif

    counter.begin([&] { pSettings->next(); });

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
    counter.update();
}
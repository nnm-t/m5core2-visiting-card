
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
#include "state-manager.h"

namespace {
    LGFX lcd;
    Ticker ticker;
    
    StaticJsonDocument<4096> json_document;

    Settings* pSettings;
    StateManager* pStateManager;

    constexpr uint8_t brightness_min = 63;
    constexpr uint8_t brightness_step = 32;
    constexpr uint8_t brightness_max = 255;

    constexpr size_t neopixel_num = 10;
    #ifdef BOARD_M5CORE
    constexpr size_t neopixel_pin = 15;
    #endif
    #ifdef BOARD_M5CORE2
    constexpr size_t neopixel_pin = 2;
    #endif

	Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(neopixel_num, neopixel_pin);
#ifdef ENABLE_SHT31
    Adafruit_SHT31 sht31;
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
#ifdef ENABLE_SHT31
	sht31.begin();
#endif
    lcd.init();

    File json_file = SD.open("/settings.json");
    DeserializationError error = deserializeJson(json_document, json_file);

    if (error != DeserializationError::Ok)
    {
        Serial.println("JSON Deserialization Error");
        return;
    }

    // 設定/制御
    pSettings = Settings::fromJson(json_document);
    pSettings->begin(&lcd, &neopixel);

    // 状態管理
    pStateManager = new StateManager(*pSettings);
    pStateManager->begin();

	// 電池アイコン
	lcd.fillRect(10, 7, 15, 10, TFT_WHITE);
	lcd.fillRect(25, 10, 3, 4, TFT_WHITE);
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
        // NeoPixel点灯/消灯
        pSettings->toggleLED();
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
        // QRコード切替
        pStateManager->toggleState();
    }

#ifdef BOARD_M5CORE
    // 電池残量
    int8_t battery_level = M5.Power.getBatteryLevel();
    lcd.drawString(String(battery_level) + "%", 40, 0);
#endif
#ifdef BOARD_M5CORE2
    // 電圧
    float voltage = M5.Axp.GetBatVoltage();
    lcd.drawString(String(voltage) + "V", 40, 0);
#endif

#ifdef ENABLE_SHT31
    // 温湿度
    float temperature = sht31.readTemperature();
    float humidity = sht31.readHumidity();
    lcd.drawString(String(temperature, 0) + "℃, " + String(humidity, 0) + "％", 40, 24);
#endif

    pSettings->update();
    pStateManager->update();
}
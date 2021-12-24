
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

#include "text.h"

namespace {
    LGFX lcd;
    Ticker ticker;
    
    StaticJsonDocument<4096> json_document;

    Text text(&lcd);

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

    bool is_neopixel_on = false;
    bool show_qrcode = false;
    uint8_t display_brightness = 127;

    constexpr uint32_t accent_color = 0xE4688F;
}

void showMenu()
{
    // 背景
    lcd.fillRect(0, 216, 320, 24, accent_color);

    // 文字
    lcd.setFont(&fonts::lgfxJapanGothic_24);
    lcd.setTextColor(TFT_WHITE, accent_color);
    lcd.setTextDatum(TC_DATUM);
    
    lcd.drawString("LED", 60, 216);
    lcd.drawString("輝度", 160, 216);
    String button_c_str = show_qrcode ? "Icon" : "QR";
    lcd.drawString(button_c_str, 260, 216);

    lcd.setTextDatum(TL_DATUM);
    lcd.setTextColor(TFT_WHITE, TFT_BLACK);

    // 枠
    lcd.drawRect(20, 216, 80, 24, TFT_WHITE);
    lcd.drawRect(120, 216, 80, 24, TFT_WHITE);
    lcd.drawRect(220, 216, 80, 24, TFT_WHITE);
}

void showQrCode()
{
    lcd.fillRect(200, 0, 120, 240, TFT_BLACK);
    // QRコード
    lcd.qrcode("https://twitter.com/nnm_t", 200, 60, 120, 6);
    show_qrcode = true;
    showMenu();
}

void showIllust()
{
    lcd.fillRect(200, 0, 120, 240, TFT_BLACK);
    // イラスト
    lcd.drawPngFile(SD, "/nnmchan.png", 200, 0);
    show_qrcode = false;
    showMenu();
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

    File json_file = SD.open("settings.json");
    DeserializationError error = deserializeJson(json_document, json_file);

    if (error != DeserializationError::Ok)
    {
        return;
    }

    JsonVariant json_text = json_document["text"];
    text.begin(json_text);
    text.show();

    showIllust();
	// 電池アイコン
	lcd.fillRect(10, 7, 15, 10, TFT_WHITE);
	lcd.fillRect(25, 10, 3, 4, TFT_WHITE);

    neopixel.begin();

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
        // NeoPixel点灯
        const uint32_t color = neopixel.Color(255, 255, 255);

        neopixel.clear();
        for (size_t i = 0; i < neopixel_num; i++)
        {
            neopixel.setPixelColor(i, color);
            neopixel.setBrightness(is_neopixel_on ? 0 : 31);
            neopixel.show();
        }

        is_neopixel_on = !is_neopixel_on;
    }

    if (M5.BtnB.wasPressed())
    {
        display_brightness += brightness_step;
        if (display_brightness >= brightness_max)
        {
            display_brightness = brightness_min;
        }
        lcd.setBrightness(display_brightness);
    }

    if (M5.BtnC.wasPressed())
    {
        if (show_qrcode)
        {
            showIllust();
        }
        else
        {
            showQrCode();
        }
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
}
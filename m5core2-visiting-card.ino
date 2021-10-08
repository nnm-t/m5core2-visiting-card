#include <Arduino.h>
#include <M5Core2.h>
#include <Ticker.h>

#include <LovyanGFX.h>
#include <Adafruit_NeoPixel.h>

namespace {
    LGFX lcd;
    Ticker ticker;

	Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(10, 2);

    bool is_neopixel_on = false;
    bool show_qrcode = false;
    uint8_t display_brightness = 63;
}

void showQrCode()
{
    lcd.fillRect(200, 0, 120, 240, TFT_BLACK);
    // QRコード
    lcd.qrcode("https://twitter.com/nnm_t", 200, 60, 120, 6);
    show_qrcode = true;
}

void showIllust()
{
    lcd.fillRect(200, 0, 120, 240, TFT_BLACK);
    // イラスト
    lcd.drawPngFile(SD, "/nnmchan.png", 200, 0);
    show_qrcode = false;
}

void setup() {
    M5.begin();
    lcd.init();

    lcd.setFont(&fonts::lgfxJapanGothic_40);
    lcd.drawString("神沢野並", 20, 100);

    lcd.setFont(&fonts::lgfxJapanGothic_24);
    lcd.drawString("F30a", 20, 68);
    lcd.drawString("@nnm_t", 20, 148);

    showIllust();
	// 電池アイコン
	lcd.fillRect(10, 7, 15, 10, TFT_WHITE);
	lcd.fillRect(25, 10, 3, 4, TFT_WHITE);

    neopixel.begin();
    for (size_t i = 0; i < 10; i++)
    {
        neopixel.setPixelColor(i, 255, 255, 255);
    }

    lcd.setBrightness(display_brightness);

    ticker.attach_ms(50, onTimerTicked);
}

void loop()
{
}

void onTimerTicked()
{
    M5.update();

    if (M5.BtnA.wasPressed())
    {
        // NeoPixel点灯
        const uint8_t brightness = is_neopixel_on ? 31 : 0;
        neopixel.setBrightness(brightness);
        is_neopixel_on = !is_neopixel_on;
        neopixel.show();
    }

    if (M5.BtnB.wasPressed())
    {
        display_brightness += 32;
        if (display_brightness >= 255)
        {
            display_brightness = 63;
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

    // 背景埋め
	lcd.fillRect(60, 0, 64, 25, TFT_BLACK);
    // 電圧
    float voltage = M5.Axp.GetBatVoltage();
    lcd.drawString(String(voltage) + "V", 40, 0);
}
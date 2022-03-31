#include "settings.h"

Settings* Settings::fromJson(JsonDocument& json_document)
{
    JsonVariant json_title = json_document["title"];
    Title title = Title::fromJson(json_title);

    JsonVariant json_menu = json_document["menu"];
    Menu menu = Menu::fromJson(json_menu);

    return new Settings(title, menu);
}

#ifdef ENABLE_SHT31
void Settings::begin(LGFX& lcd, Adafruit_NeoPixel& neopixel, Adafruit_SHT31& sht31)
#else
void Settings::begin(LGFX& lcd, Adafruit_NeoPixel& neopixel)
#endif
{
    // 代入
    _lcd = &lcd;
    _neopixel = &neopixel;

    // LCDクリア
    clearLCD();
    // 共通表示
    showCommon();

#ifdef ENABLE_SHT31
    _sht31 = &sht31;
    _sht31->begin(SHT31_ADDRESS);
#endif
}

void Settings::toggleLED()
{
}

void Settings::showCommon()
{
    // 共通表示
    _title.begin(_lcd);
    _menu.show(_lcd);
}

void Settings::showImage()
{
    // 画像表示
}

void Settings::showQR()
{
    // QRコード表示
}

void Settings::clearLCD()
{
    // LCDクリア
    Color black(0, 0, 0);
    _lcd->fillRect(24, 0, 320, 192, black.getRGB888());
}

void Settings::update()
{
    // 更新
#ifdef ENABLE_SHT31
    _title.update(_lcd, _sht31);
#else
    _title.update(_lcd);
#endif
}

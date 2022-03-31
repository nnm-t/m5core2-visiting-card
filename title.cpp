#include "title.h"

Title Title::fromJson(JsonVariant& json_title)
{
    JsonVariant json_foreground = json_title["foreground"];
    JsonVariant json_background = json_title["background"];

    return Title(Color::fromJson(json_foreground), Color::fromJson(json_background));
}

void Title::begin(LGFX* const lcd)
{
    // 電池アイコン
    lcd->fillRect(10, 7, 15, 10, _foreground.getRGB888());
    lcd->fillRect(25, 10, 3, 4, _foreground.getRGB888());
}

#ifdef ENABLE_SHT31
void Title::update(LGFX* const lcd, Adafruit_SHT31* const sht31)
#else
void Title::update(LGFX* const lcd)
#endif
{
    // テキスト色指定等
    lcd->setTextColor(_foreground.getRGB888(), _background.getRGB888());
    lcd->setTextDatum(TL_DATUM);

    // バッテリ残量
    #ifdef BOARD_M5CORE
        // 電池残量
        const int8_t battery_level = M5.Power.getBatteryLevel();
        lcd->drawString(String(battery_level) + "%", 40, 0);
    #endif
    #ifdef BOARD_M5CORE2
        // 電圧
        const float voltage = M5.Axp.GetBatVoltage();
        lcd->drawString(String(voltage) + "V", 40, 0);
    #endif
    #ifdef ENABLE_SHT31
        // 温湿度
        const float temperature = sht31->readTemperature();
        const float humidity = sht31->readHumidity();
        lcd->drawString(String(temperature, 0) + "℃, " + String(humidity, 0) + "％", 160, 0);
    #endif
}
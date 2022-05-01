#include "title.h"

void Title::init_text(LGFX* const lcd)
{
    // テキスト色指定等
    lcd->setTextColor(_foreground.getRGB888(), _background.getRGB888());
    lcd->setTextDatum(TL_DATUM);
    lcd->setTextFont(&fonts::lgfxJapanGothic_24);
}

Title Title::fromJson(JsonVariant& json_title)
{
    JsonVariant json_foreground = json_title["foreground"];
    JsonVariant json_background = json_title["background"];

    return Title(Color::fromJson(json_foreground), Color::fromJson(json_background));
}

void Title::begin(LGFX* const lcd)
{
    // 背景
    lcd->fillRect(0, 0, 320, 24, _background.getRGB888());
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
    init_text(lcd);

    // バッテリ残量
    #ifdef BOARD_M5CORE
    // 電池残量
    const int8_t battery_level = M5.Power.getBatteryLevel();
    lcd->drawString(String(battery_level) + "%", 32, 0);
    #endif
    #ifdef BOARD_M5CORE2
    // 電圧
    const float voltage = M5.Axp.GetBatVoltage();
    lcd->drawString(String(voltage) + "V", 32, 0);
    #endif
    #ifdef ENABLE_SHT31
    // 温湿度
    const float temperature = sht31->readTemperature();
    const float humidity = sht31->readHumidity();
    lcd->drawString(String(temperature, 0), 96, 0);
    lcd->drawString("℃", 120, 0);
    lcd->drawString(String(humidity, 0), 156, 0);
    lcd->drawString("%", 180, 0);
    #endif
}

void Title::draw_counter(LGFX* const lcd, Counter* const counter)
{
    init_text(lcd);

    const float min = counter->get_count_num_min();
    const int32_t width = 96;

    // 背景
    lcd->fillRect(208, 4, width, 16, _foreground.getRGB888());

    if (!counter->is_enabled())
    {
        // 無効
        lcd->drawLine(208, 20, 304, 4, _background.getRGB888());
        return;
    }

    const int32_t fill_width = (static_cast<float>(counter->get_count_num()) - min) / static_cast<float>(counter->get_count_num_max() - min) * width;
    // 塗りつぶし
    lcd->fillRect(208, 4, fill_width, 16, _background.getRGB888());
    // 枠
    lcd->drawRect(208, 4, width, 16, _foreground.getRGB888());
}
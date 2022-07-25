#include "settings.h"

Settings* Settings::fromJson(JsonDocument& json_document)
{
    JsonVariant json_title = json_document["title"];
    Title title = Title::fromJson(json_title);

    JsonVariant json_menu = json_document["menu"];
    Menu menu = Menu::fromJson(json_menu);

    JsonArray pages_json = json_document["page"];

    return new Settings(title, menu, pages_json);
}

#ifdef ENABLE_SHT31
void Settings::begin(LGFX& lcd, Counter& counter, Adafruit_SHT31& sht31)
#else
void Settings::begin(LGFX& lcd, Counter& counter)
#endif
{
    // 代入
    _lcd = &lcd;
    _counter = &counter;

    // LCDクリア
    clearLCD();
    // 共通表示
    showCommon();

#ifdef ENABLE_SHT31
    _sht31 = &sht31;
    _sht31->begin(SHT31_ADDRESS);
#endif
}

void Settings::showCommon()
{
    // 共通表示
    _title.begin(_lcd);
    draw_counter();
    _menu.show(_lcd);

    _pages_iterator->show(_lcd);
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

void Settings::next()
{
    if (++_pages_iterator >= _pages.end())
    {
        _pages_iterator = _pages.begin();
    }

    showCommon();
}

void Settings::prev()
{
    if (--_pages_iterator < _pages.begin())
    {
        _pages_iterator = _pages.end() - 1;
    }

    showCommon();
}
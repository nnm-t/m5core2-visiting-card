#include "menu.h"

Menu Menu::fromJson(JsonVariant& json_menu)
{
    JsonVariant json_foreground = json_menu["foreground"];
    const Color foreground = Color::fromJson(json_foreground);

    JsonVariant json_background = json_menu["background"];
    const Color background = Color::fromJson(json_background);

    return Menu(foreground, background);
}

void Menu::show(LGFX* const lcd)
{
    /*
    // 背景
    lcd->fillRect(0, 216, 320, 24, _background);

    // 文字
    lcd->setFont(&fonts::lgfxJapanGothic_24);
    lcd->setTextColor(_foreground, _background);
    lcd->setTextDatum(TC_DATUM);
    
    lcd->drawString("LED", 60, 216);
    lcd->drawString("輝度", 160, 216);
    lcd->drawString("QR", 260, 216);

    lcd->setTextDatum(TL_DATUM);

    // 枠
    lcd->drawRect(20, 216, 80, 24, _foreground);
    lcd->drawRect(120, 216, 80, 24, _foreground);
    lcd->drawRect(220, 216, 80, 24, _foreground);
    */
}
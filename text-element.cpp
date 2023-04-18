#include "text-element.h"

TextElement TextElement::fromJson(JsonObject& json_element)
{
    const int32_t x = json_element["x"];
    const int32_t y = json_element["y"];
    const TextSize size = static_cast<TextSize>(json_element["size"].as<uint8_t>());
    String text = json_element["text"];

    JsonVariant json_foreground = json_element["foreground"];
    JsonVariant json_background = json_element["background"];
    const Color foreground = Color::fromJson(json_foreground);
    const Color background = Color::fromJson(json_background);

    return TextElement(x, y, size, text, foreground, background);
}

void TextElement::setFont(LGFX* const lcd)
{
    const lgfx::v1::IFont* font;

    switch(_size)
    {
        case TextSize::Size16:
            font = &fonts::lgfxJapanGothic_16;
            break;
        case TextSize::Size32:
            font = &fonts::lgfxJapanGothic_32;
            break;
        case TextSize::Size40:
            font = &fonts::lgfxJapanGothic_40;
            break;
        default:
            font = &fonts::lgfxJapanGothic_24;
    }

    lcd->setFont(font);
}

void TextElement::show(LGFX* const lcd)
{
    setFont(lcd);
    lcd->setTextColor(_foreground.getRGB888(), _background.getRGB888());
    lcd->drawString(_text, _x, _y);
}
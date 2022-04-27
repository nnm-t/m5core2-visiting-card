#include "page.h"

Page Page::fromJson(JsonObject& page_json)
{
    JsonVariant background_color_json = page_json["background"];
    Color background_color = Color::fromJson(background_color_json);

    JsonVariant image_json = page_json["image"];
    Image image = Image::fromJson(image_json);

    JsonArray texts_json = page_json["text"];

    return Page(background_color, image, texts_json);
}

void Page::show(LGFX* lcd)
{
    lcd->fillRect(0, 24, 320, 192, _background_color.getRGB888());
    _image.show(lcd);
    
    for (TextElement& text : _texts)
    {
        text.show(lcd);
    }
}
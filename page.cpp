#include "page.h"

Page Page::fromJson(JsonObject& page_json)
{
    JsonVariant background_color_json = page_json["background"];
    Color background_color = Color::fromJson(background_color_json);

    JsonVariant image_json = page_json["image"];
    Image image = Image::fromJson(image_json);

    JsonArray texts_json = page_json["text"];

    JsonVariant json_led = page_json["led"];
    ScrollLED scroll_led = ScrollLED::fromJson(json_led);

    return Page(background_color, image, texts_json, scroll_led);
}

void Page::show(LGFX* lcd, std::function<void()>&& on_led_completed)
{
    lcd->fillRect(0, 24, 320, 192, _background_color.getRGB888());
    _image.show(lcd);
    
    for (TextElement& text : _texts)
    {
        text.show(lcd);
    }

    // LED初期化
    _scroll_led.begin(on_led_completed);
}

void Page::updateScrollLED(LED* led)
{
    _scroll_led.update(led);
}
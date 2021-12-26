#include "settings.h"

Settings* Settings::fromJson(JsonDocument& json_document)
{
    JsonVariant json_background = json_document["background"];
    Color background = Color::fromJson(json_background);

    JsonVariant json_menu = json_document["menu"];
    Menu menu = Menu::fromJson(json_menu);

    JsonVariant json_led = json_document["led"];
    LED led = LED::fromJson(json_led);

    JsonVariant json_image = json_document["image"];
    Image image = Image::fromJson(json_image);

    JsonArray json_array = json_document["text"].as<JsonArray>();
    std::vector<TextElement> text_elements;

    text_elements.reserve(json_array.size());

    for (JsonObject json_element: json_array)
    {
        text_elements.push_back(TextElement::fromJson(json_element));
    }

    JsonVariant json_qrcode = json_document["qrcode"];
    QRCode qrcode = QRCode::fromJson(json_qrcode);

    return new Settings(background, menu, led, image, text_elements, qrcode);
}

void Settings::begin(LGFX* const lcd, Adafruit_NeoPixel* const neopixel)
{
    // 代入
    _lcd = lcd;
    _neopixel = neopixel;

    // LCDクリア
    clearLCD();
    // 共通表示
    showCommon();

    // NeoPixel
    _led.begin(_neopixel);
}

void Settings::toggleLED()
{
    _led.toggle();
}

void Settings::showCommon()
{
    // 共通表示
    for (TextElement& text_element: _text_elements)
    {
        text_element.show(_lcd);
    }

    _menu.show(_lcd);
}

void Settings::showImage()
{
    // 画像表示
    _image.show(_lcd);
}

void Settings::showQR()
{
    // QRコード表示
    _qrcode.show(_lcd);
}

void Settings::clearLCD()
{
    // LCDクリア
    _lcd->fillScreen(_background.getRGB888());
}

void Settings::update()
{
    // 更新
    _led.update(_neopixel);
}

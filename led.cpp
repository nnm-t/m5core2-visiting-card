#include "led.h"

LED LED::fromJson(JsonVariant& json_led)
{
    JsonVariant json_color = json_led["color"];
    const Color color = Color::fromJson(json_color);

    const LEDPattern pattern = static_cast<LEDPattern>(json_led["pattern"].as<uint8_t>());

    return LED(color, pattern);
}

void LED::begin(Adafruit_NeoPixel* const neopixel)
{
    const uint32_t neopixel_color = neopixel->Color(_color.getRed(), _color.getGreen(), _color.getBlue());

    neopixel->clear();

    for (size_t i = 0; i < neopixel_num; i++)
    {
        neopixel->setPixelColor(i, neopixel_color);
        // todo: Patternによって変更
        neopixel->setBrightness(31);
        neopixel->show();
    }
}

void LED::update(Adafruit_NeoPixel* const neopixel)
{

}
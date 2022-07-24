#include "led.h"

LED LED::fromJson(JsonVariant& json_led)
{
    JsonVariant json_color = json_led["color"];
    const Color color = Color::fromJson(json_color);

    const LEDPattern pattern = static_cast<LEDPattern>(json_led["pattern"].as<uint8_t>());

    return LED();
}

void LED::begin()
{
    FastLED.addLeds<NEOPIXEL, neopixel_gpio>(_leds, neopixel_num);
}

void LED::update()
{
}
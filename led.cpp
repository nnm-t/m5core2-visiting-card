#include "led.h"

void LED::set(const uint16_t column, const uint16_t row, CRGB& crgb)
{
    _leds[column + row * neopixel_column] = crgb;
}

void LED::set(const uint16_t column, const uint16_t row, Color& color)
{
    CRGB crgb(color.getRed(), color.getGreen(), color.getBlue());

    set(column, row, crgb);
}

void LED::unset(const uint16_t column, const uint16_t row)
{
    _leds[column + row * neopixel_column] = CRGB::Black;
}

void LED::show()
{
    FastLED.show();
}

void LED::begin()
{
    FastLED.addLeds<NEOPIXEL, neopixel_gpio>(_leds, neopixel_num);
}

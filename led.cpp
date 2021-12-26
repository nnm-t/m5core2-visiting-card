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
    neopixel->begin();
}

void LED::update(Adafruit_NeoPixel* const neopixel)
{
    if (!_is_enabled)
    {
        // 無効
        _brightness_count = 0;
        _brightness_reverse = false;

        neopixel->setBrightness(0);
        neopixel->show();
        return;
    }

    // カウント
    _brightness_count++;

    // Patternによって変更
    switch (_pattern)
    {
        case LEDPattern::Blink:
            // 点灯/消灯
            if (_brightness_reverse)
            {
                _brightness = brightness_min;
            }
            else
            {
                _brightness = brightness_max;
            }
            // カウント上限のとき反転
            if (_brightness_count >= brightness_count_max)
            {
                _brightness_reverse = !_brightness_reverse;
            }
            break;
        case LEDPattern::Fade:
            // 明るさ変更
            if (_brightness_reverse)
            {
                _brightness--;
            }
            else
            {
                _brightness++;
            }
            // 上限/下限で反転
            if (_brightness <= brightness_min)
            {
                _brightness_reverse = false;
            }
            else if (_brightness >= brightness_max)
            {
                _brightness_reverse = true;
            }
            break;
        default:
            _brightness_reverse = false;
            _brightness = brightness_max;
            break;
    }

    // カウントリセット
    if (_brightness_count >= brightness_count_max)
    {
        _brightness_count = 0;
    }

    const uint32_t neopixel_color = neopixel->Color(_color.getRed(), _color.getGreen(), _color.getBlue());
    for (size_t i = 0; i < neopixel_num; i++)
    {
        neopixel->setPixelColor(i, neopixel_color);
    }
    neopixel->setBrightness(_brightness);
    neopixel->show();
}
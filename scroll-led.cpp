#include "scroll-led.h"

ScrollLED ScrollLED::fromJson(JsonVariant& json_led)
{
	String text = json_led["text"];

	JsonVariant json_color = json_led["color"];
	const Color color = Color::fromJson(json_color);

	return ScrollLED(text, color);
}

void ScrollLED::begin()
{
	char* ptr = const_cast<char*>(_text.c_str());
	size_t index = 0;
	// 文字数 * 8 bytes
	_led_text.reserve(_text.length());

	while (*ptr)
	{
		// 8bit * 8行
		uint8_t font[8];
		ptr = getFontData(font, ptr);

		if (!ptr)
		{
			break;
		}

		// 配列の中身をコピー
		_led_text.reserve(8);
		std::copy(font, font + 8, _led_text[index].begin());
		index++;
	}
}

void ScrollLED::update(LED* led)
{
	// todo: n列目から表示
}
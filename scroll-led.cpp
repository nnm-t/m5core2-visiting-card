#include "scroll-led.h"

ScrollLED ScrollLED::fromJson(JsonVariant& json_led)
{
	String text = json_led["text"];

	JsonVariant json_color = json_led["color"];
	Color color = Color::fromJson(json_color);

	return ScrollLED(text, color);
}

void ScrollLED::begin(std::function<void()>& on_completed)
{
	_on_completed = on_completed;

	char* ptr = const_cast<char*>(_text.c_str());
	size_t index = 0;
	while (*ptr)
	{
		// 8bit * 8行
		uint8_t font[8];
		ptr = getFontData(font, ptr);

		if (!ptr)
		{
			break;
		}

		_led_text.push_back(std::vector<uint8_t>());
		// 配列の中身をコピー
		_led_text[index].reserve(8);
		std::copy(font, font + 8, _led_text[index].begin());
		index++;
	}
}

void ScrollLED::update(LED* led)
{
	for (uint16_t index = 0; index < get_length(); index++)
	{
		// 各文字左上のx座標
		const int16_t x_text = index * LED::neopixel_char_width + _x_offset;

		// 右上 < 0 または 左上 >= 24 では描画できない
		if (x_text + LED::neopixel_char_width < 0 || x_text >= LED::neopixel_column)
		{
			continue;
		}

		// 各文字を1列ずつ描画
		for (int16_t x_char = 0; x_char < LED::neopixel_char_width; x_char++)
		{
			const int16_t x = x_text + x_char;
			// 右上 < 0 または 左上 >= 24 では描画できない
			if (x < 0 || x >= LED::neopixel_column)
			{
				continue;
			}

			for (size_t y = 0; y < LED::neopixel_row; y++)
			{
				if ((_led_text[index][y] >> (LED::neopixel_char_width - x_char)) & 0x01)
				{
					led->set(x, y, _color);
					continue;
				}

				led->unset(x, y);
			}
		}
	}

	// 文字列の左上と右上
	const int16_t x_start = _x_offset;
	const int16_t x_end = _x_offset + get_length() * LED::neopixel_char_width;

	// 空白埋め
	// 0 ～ 文字列の左上
	for (uint16_t x_blank = 0; x_blank < x_start; x_blank++)
	{
		for (size_t y = 0; y < LED::neopixel_row; y++)
		{
			led->unset(x_blank, y);
		}
	}
	// 文字列の右上 ～ 24
	for (uint16_t x_blank = x_end; x_blank < LED::neopixel_column; x_blank++)
	{
		for (size_t y = 0; y < LED::neopixel_row; y++)
		{
			led->unset(x_blank, y);
		}
	}
	
	_x_offset--;

	led->show();

	// 文字列流し終えたらリセット
	if (_x_offset <= static_cast<int16_t>(get_length()) * -8)
	{
		_x_offset = LED::neopixel_column;
		if (_on_completed != nullptr)
		{
			_on_completed();
		}
	}
}
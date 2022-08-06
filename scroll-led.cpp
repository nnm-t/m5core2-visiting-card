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
	// 表示する文字 index_start ～ index_end
	const size_t index_start = _column / 8;
	size_t index_end = (_column + LED::neopixel_column) / 8;
	if (index_end >= get_length())
	{
		index_end = get_length();
	}

	for (size_t index = index_start; index < index_end; index++)
	{
		uint16_t column_start = 0;
		// 始点 n列目から表示
		if (index == index_start)
		{
			column_start = _column % 8;
		}

		uint16_t column_end = 8;
		// 終点 n列目まで表示
		if (index == index_end - 1)
		{
			column_end = 8 - (_offset_x % 8);
		}

		// ドット n列目
		for (uint16_t column = 0; column < LED::neopixel_column; column++)
		{
			// ドット n行目
			for (uint16_t row = 0; row < LED::neopixel_row; row++)
			{
				if (column + _offset_x < column_start || column + _offset_x >= column_end)
				{
					led->unset(column, row);
					continue;
				}

				if ((_led_text[index][row] >> (8 - column) & 0x01))
				{
					led->set(column, row, _color);
					continue;
				}

				led->unset(column, row);
			}
		}

		if (_offset_x <= 0)
		{
			// _offset_x = 0 のとき _column インクリメント
			_column++;
		}
		else
		{
			// デクリメント
			_offset_x--;
		}
	}

	// 文字列流し終えたらリセット
	if (_column >= get_length() * 8)
	{
		_offset_x = LED::neopixel_column;
		_column = 0;
		if (_on_completed != nullptr)
		{
			_on_completed();
		}
	}
}
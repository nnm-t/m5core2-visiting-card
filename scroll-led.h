#pragma once

#include "config.h"

#include <algorithm>
#include <vector>

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <ArduinoJson.h>

#include "misakiUTF16/misakiUTF16.h"
#include "color.h"
#include "led.h"

class ScrollLED
{
	Color _color;

	String _text;
	std::vector<std::vector<uint8_t>> _led_text;

	// LED位置 オフセット
	uint16_t _offset_x = LED::neopixel_column;
	// 文字ドット オフセット
	size_t _column = 0;

	ScrollLED(String& text, Color& color) : _text(text), _color(color)
	{

	}

public:
	ScrollLED fromJson(JsonVariant& json_led);

	size_t get_length()
	{
		return _led_text.size();
	}
	
	void begin();

	void update(LED* led);
};
#pragma once

#include "config.h"

#include <algorithm>
#include <functional>
#include <vector>

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <ArduinoJson.h>

#include "misakiUTF16.h"
#include "color.h"
#include "led.h"

class ScrollLED
{
	Color _color;

	String _text;
	std::vector<std::vector<uint8_t>> _led_text;

	// 文字列左上のx座標
	int16_t _x_offset = LED::neopixel_column;
	bool _is_prepared = false;

	// リセット
	std::function<void()> _on_completed = nullptr;

	ScrollLED(String& text, Color& color) : _text(text), _color(color)
	{

	}

public:
	static ScrollLED fromJson(JsonVariant& json_led);

	size_t get_length()
	{
		return _led_text.size();
	}
	
	void begin(std::function<void()>& on_completed);

	void update(LED* led);
};
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
	const Color _color;

	String _text;
	std::vector<std::vector<uint8_t>> _led_text;

	ScrollLED(String& text, const Color& color) : _text(text), _color(color)
	{

	}

public:
	ScrollLED fromJson(JsonVariant& json_led);
	
	void begin();

	void update(LED* led);
};
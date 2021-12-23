#pragma once

#include "config.h"

#include <vector>

#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <LovyanGFX.h>
#include <ArduinoJson.h>

#include "text-element.h"

class Text
{
	LGFX* const _lcd;
	std::vector<TextElement> _text_elements;

public:
	Text(LGFX* const lcd) : _lcd(lcd), _text_elements(std::vector<TextElement>())
	{

	}

	void begin(JsonVariant& json_text);

	void show();

	void update();
};
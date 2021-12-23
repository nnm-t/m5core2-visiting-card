#pragma once

#include "config.h"

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <LovyanGFX.h>
#include <ArduinoJson.h>

class QRCode
{
    const int32_t _x;
    const int32_t _y;
	const int32_t _width;
    String _url;

public:
    QRCode fromJson(JsonVariant& json_qrcode);

    QRCode(const uint32_t x, const uint32_t y, const int32_t width, String& url) : _x(x), _y(y), _width(width), _url(url)
    {

    }

    void show(LGFX* const lcd);
};
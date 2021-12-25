#pragma once

#include <Arduino.h>

enum class LEDPattern : uint8_t
{
    Static = 0,
    Blink = 1,
    Fade = 2
};
#pragma once

#include "config.h"

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <LovyanGFX.h>

#include "settings.h"
#include "i-state.h"

class ImageState : public IState
{
    Settings& _settings;

public:
    ImageState(Settings& settings) : _settings(settings)
    {

    }

    void begin() override;

    void update() override
    {

    }
};
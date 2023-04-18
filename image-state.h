#pragma once

#include "config.h"

#ifdef BOARD_M5CORE
#include <M5Stack.h>
#endif
#ifdef BOARD_M5CORE2
#include <M5Core2.h>
#endif

#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

#include "settings.h"
#include "i-state.h"

class ImageState : public IState
{
    Settings* _settings = nullptr;

public:
    ImageState()
    {

    }

    void begin(Settings* settings) override;

    void update() override
    {

    }
};
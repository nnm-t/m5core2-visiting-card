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
#include "image-state.h"
#include "qr-state.h"

class StateManager
{
    ImageState _image_state;
    QRState _qr_state;

    IState* _state;

public:
    StateManager(Settings& settings) : _image_state(ImageState(settings)), _qr_state(QRState(settings))
    {
        _state = &_image_state;
    }

    void begin();

    void toggleState();

    void update();
};
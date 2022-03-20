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
    Settings* _settings = nullptr;
    ImageState& _image_state;
    QRState& _qr_state;

    IState* _state = nullptr;

public:
    StateManager(ImageState& image_state, QRState& qr_state) : _image_state(image_state), _qr_state(qr_state)
    {
    }

    void begin(Settings* settings);

    void toggleState();

    void update();
};
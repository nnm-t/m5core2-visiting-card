#include "state-manager.h"

void StateManager::begin(Settings* settings)
{
    _settings = settings;

    _state = &_image_state;
    _state->begin(_settings);
}

void StateManager::toggleState()
{
    if (_state == &_image_state)
    {
        _state = &_qr_state;
    }
    else
    {
        _state = &_image_state;
    }

    _state->begin(_settings);
}

void StateManager::update()
{
    _state->update();
}
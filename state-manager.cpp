#include "state-manager.h"

void StateManager::begin()
{
    _state->begin();
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

    _state->begin();
}

void StateManager::update()
{
    _state->update();
}
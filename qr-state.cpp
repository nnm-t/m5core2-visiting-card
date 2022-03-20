#include "qr-state.h"

void QRState::begin(Settings* settings)
{
    _settings = settings;

    _settings->clearLCD();
    _settings->showQR();
    _settings->showCommon();
}
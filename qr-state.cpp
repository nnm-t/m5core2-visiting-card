#include "qr-state.h"

void QRState::begin()
{
    _settings.clearLCD();
    _settings.showCommon();
    _settings.showQR();
}
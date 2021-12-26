#include "qr-state.h"

void QRState::begin()
{
    _settings.clearLCD();
    _settings.showQR();
    _settings.showCommon();
}
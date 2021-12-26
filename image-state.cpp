#include "image-state.h"

void ImageState::begin()
{
    _settings.clearLCD();
    _settings.showCommon();
    _settings.showImage();
}
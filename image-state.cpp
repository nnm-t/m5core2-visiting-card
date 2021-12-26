#include "image-state.h"

void ImageState::begin()
{
    _settings.clearLCD();
    _settings.showImage();
    _settings.showCommon();
}
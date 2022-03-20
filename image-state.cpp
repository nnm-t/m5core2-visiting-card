#include "image-state.h"

void ImageState::begin(Settings* settings)
{
    _settings = settings;

    _settings->clearLCD();
    _settings->showImage();
    _settings->showCommon();
}
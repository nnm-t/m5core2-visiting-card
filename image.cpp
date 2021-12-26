#include "image.h"

Image Image::fromJson(JsonVariant& json_image)
{
    const int32_t x = json_image["x"];
    const int32_t y = json_image["y"];
    String src = json_image["src"];

    return Image(x, y, src);
}

void Image::show(LGFX* const lcd)
{
    // 拡張子ごとに分岐
    if (_src.endsWith(extension_bmp))
    {
        lcd->drawBmpFile(SD, _src, _x, _y);
    }
    else if (_src.endsWith(extension_png))
    {
        lcd->drawPngFile(SD, _src, _x, _y);
    }
    else if (_src.endsWith(extension_jpg))
    {
        lcd->drawJpgFile(SD, _src, _x, _y);
    }
}
#include "qrcode.h"

QRCode QRCode::fromJson(JsonVariant& json_qrcode)
{
	const int32_t x = json_qrcode["x"];
	const int32_t y = json_qrcode["y"];
	const int32_t width = json_qrcode["width"];
	String url = json_qrcode["url"];

	return QRCode(x, y, width, url);
}

void QRCode::show(LGFX* const lcd)
{
	lcd->qrcode(_url, _x, _y, _width, 6);
}
#include "color.h"

Color Color::fromJson(JsonVariant& json_color)
{
	const uint8_t red = json_color[0];
	const uint8_t green = json_color[1];
	const uint8_t blue = json_color[2];

	return Color(red, green, blue);
}
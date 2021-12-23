#include "text.h"

void Text::begin(JsonVariant& json_text)
{
	JsonArray json_array = json_text.as<JsonArray>();

	_text_elements.clear();
	_text_elements.reserve(json_array.size());

	for (JsonObject json_element: json_array)
	{
		_text_elements.push_back(TextElement::fromJson(json_element));
	}
}

void Text::show()
{
	for (TextElement& text_element: _text_elements)
	{
		text_element.show(_lcd);
	}
}

void Text::update()
{

}
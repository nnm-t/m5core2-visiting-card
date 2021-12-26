#include "settings.h"

Settings* Settings::fromJson(JsonDocument& json_document)
{
    JsonVariant json_foreground = json_document["foreground"];
    Color foreground = Color::fromJson(json_foreground);

    JsonVariant json_background = json_document["background"];
    Color background = Color::fromJson(json_background);

    JsonVariant json_menu = json_document["menu"];
    Menu menu = Menu::fromJson(json_menu);

    JsonVariant json_led = json_document["led"];
    LED led = LED::fromJson(json_led);

    JsonVariant json_image = json_document["image"];
    Image image = Image::fromJson(json_image);

    JsonArray json_array = json_document["text"].as<JsonArray>();
    std::vector<TextElement> text_elements;

    text_elements.reserve(json_array.size());

    for (JsonObject json_element: json_array)
    {
        text_elements.push_back(TextElement::fromJson(json_element));
    }

    JsonVariant json_qrcode = json_document["qrcode"];
    QRCode qrcode = QRCode::fromJson(json_qrcode);

    return new Settings(foreground, background, menu, led, image, text_elements, qrcode);
}

#ifdef ENABLE_SHT31
void Settings::begin(LGFX* const lcd, Adafruit_NeoPixel* const neopixel, Adafruit_SHT31* const sht31)
#else
void Settings::begin(LGFX* const lcd, Adafruit_NeoPixel* const neopixel)
#endif
{
    // 代入
    _lcd = lcd;
    _neopixel = neopixel;

    // LCDクリア
    clearLCD();
    // 共通表示
    showCommon();

    // NeoPixel
    _led.begin(_neopixel);
#ifdef ENABLE_SHT31
    _sht31.begin();
#endif
}

void Settings::toggleLED()
{
    _led.toggle();
}

void Settings::showCommon()
{
    // 共通表示
    for (TextElement& text_element: _text_elements)
    {
        text_element.show(_lcd);
    }

    _menu.show(_lcd);

    // 電池アイコン
    _lcd->fillRect(10, 7, 15, 10, _foreground.getRGB888());
    _lcd->fillRect(25, 10, 3, 4, _foreground.getRGB888());
}

void Settings::showImage()
{
    // 画像表示
    _image.show(_lcd);
}

void Settings::showQR()
{
    // QRコード表示
    _qrcode.show(_lcd);
}

void Settings::clearLCD()
{
    // LCDクリア
    _lcd->fillScreen(_background.getRGB888());
}

void Settings::update()
{
    // 更新
    // テキスト色指定等
    _lcd->setTextColor(_foreground.getRGB888(), _background.getRGB888());
    _lcd->setTextDatum(TL_DATUM);
    // バッテリ残量
    #ifdef BOARD_M5CORE
        // 電池残量
        int8_t battery_level = M5.Power.getBatteryLevel();
        _lcd->drawString(String(battery_level) + "%", 40, 0);
    #endif
    #ifdef BOARD_M5CORE2
        // 電圧
        float voltage = M5.Axp.GetBatVoltage();
        _lcd->drawString(String(voltage) + "V", 40, 0);
    #endif
    #ifdef ENABLE_SHT31
        // 温湿度
        float temperature = _sht31.readTemperature();
        float humidity = _sht31.readHumidity();
        _lcd->drawString(String(temperature, 0) + "℃, " + String(humidity, 0) + "％", 40, 24);
    #endif
    // LED
    _led.update(_neopixel);
}

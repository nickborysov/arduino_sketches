#include "Adafruit_GFX.h"
#include "RTClib.h"
#include <MCUFRIEND_kbv.h>
//#include <SD.h>
//#include <SPI.h>
#include <Wire.h>
#include <OneWire.h>
#include "bitmaps.h"

//#include "Fonts/Org_01.h"
#include "Fonts/FreeMonoBold12pt7b.h"

#include "DHT.h"

#define DHTPIN 12 // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define BACKGROUND 0x1082

#define CUSTOM_FONT FreeMonoBold12pt7b
#define TEXT_SIZE 1
#define Orientation 1 // PORTRAIT

// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
DateTime now;

MCUFRIEND_kbv tft; // hard-wired for UNO shields anyway.
int Width;
int Height;
int millisDiff;
int16_t BOTTOM_PANEL = 20;

const char dateFormat[] PROGMEM = "%04d/%02d/%02d %02d:%02d:%02d";
uint16_t lastSecond = 0;

// OneWire
#define ONE_WIRE_BUS 11
OneWire ds(ONE_WIRE_BUS);
byte oneWireData[2];

void setupRTC()
{
  RTC_DS3231 RTC;
  Wire.begin();
  RTC.begin();
  //   RTC.adjust(DateTime(__DATE__, __TIME__) + TimeSpan(14));
  now = RTC.now();
  millisDiff = millis();
}

void setup()
{
  setupRTC();

  Serial.begin(9600);

  tft.reset();
  uint16_t ID = tft.readID();
  Serial.print(F("screen ID "));
  Serial.println(ID);
  tft.begin(ID);

  tft.setRotation(Orientation);
  tft.fillScreen(BACKGROUND);
  tft.invertDisplay(true);
  tft.setTextSize(TEXT_SIZE);
  tft.setTextWrap(false);
  tft.setFont(&CUSTOM_FONT);

  Width = tft.width();
  Height = tft.height();

  dht.begin();
}

long lastSecondForTemp;

float getOneWireTemp()
{
  ds.reset();     // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
  ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство
  ds.write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память

  //  delay(1000); // Микросхема измеряет температуру, а мы ждем.

  ds.reset(); // Теперь готовимся получить значение измеренной температуры
  ds.write(0xCC);
  ds.write(0xBE); // Просим передать нам значение регистров со значением температуры

  oneWireData[0] = ds.read();
  oneWireData[1] = ds.read();

  float temperature = ((oneWireData[1] << 8) | oneWireData[0]) * 0.0625;
  return temperature;
}

void loop()
{
  showTime();

  if (millis() / 1000 % 60 != lastSecondForTemp)
  {
    lastSecondForTemp = millis() / 1000 % 60;

    printLocalTemp();
  }
}

float oldHum, oldTemp, oldHic, oldOneWireTemp;
float dhtAdjustment = 1.063;

void printLocalTemp()
{
  //  printFreeRAM(F("printLocalTemp %d"));
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  h = h * dhtAdjustment;
  t = t * dhtAdjustment;

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  tft.setTextSize(2);
  uint8_t offset = 50;
  uint8_t top_offset = 10;
  uint8_t text_fix = 30;
  uint8_t image_offset = 2;
  uint8_t image_size = 70;

  char *textBuffer = new char[25];

  if (oldHum != h)
  {
    oldHum = h;
    char *hum_str = new char[5];
    dtostrf(h, 2, 1, hum_str);

    //    sprintf(textBuffer, "Humidity:    %s", hum_str);
    sprintf(textBuffer, "H: %s", hum_str);
    tft.setTextColor(TFT_BLUE, TFT_BLUE);
    tft.fillRect(0, top_offset, Width, offset, BACKGROUND);
    tft.drawBitmap(Width - 110, top_offset + image_offset, humBitmapArray, image_size, image_size, TFT_BLUE);
    tft.setCursor(3, top_offset + text_fix);
    tft.print(textBuffer);
    delete hum_str;
  }

  if (oldTemp != t)
  {
    oldTemp = t;
    char *temp_str = new char[5];
    dtostrf(t, 2, 1, temp_str);

    //    sprintf(textBuffer, "Temperature: %s", temp_str);
    sprintf(textBuffer, "T: %s", temp_str);
    tft.setTextColor(TFT_GREEN, TFT_GREEN);
    tft.fillRect(0, offset + top_offset, Width, offset, BACKGROUND);
    tft.drawBitmap(Width - 110, offset + top_offset + image_offset, tempBitmapArray, image_size, image_size, TFT_GREEN);
    tft.setCursor(3, offset + top_offset + text_fix);
    tft.print(textBuffer);
    delete temp_str;
  }

  if (oldHic != hic)
  {
    oldHic = hic;
    char *hic_str = new char[5];
    dtostrf(hic, 2, 1, hic_str);

    //    sprintf(textBuffer, "Feels like:  %s", hic_str);
    sprintf(textBuffer, "t: %s", hic_str);
    tft.setTextColor(TFT_GREENYELLOW, TFT_GREENYELLOW);
    tft.fillRect(0, offset * 2 + top_offset, Width, offset, BACKGROUND);
    tft.drawBitmap(Width - 110, offset * 2 + top_offset + image_offset, tempBitmapArray, image_size, image_size, TFT_GREENYELLOW);
    tft.setCursor(3, offset * 2 + top_offset + text_fix);
    tft.print(textBuffer);
    delete hic_str;
  }

  float oneWireTemp = getOneWireTemp();
  if (oldOneWireTemp != oneWireTemp)
  {
    oldOneWireTemp = oneWireTemp;
    char *temp_str = new char[5];
    dtostrf(oneWireTemp, 2, 1, temp_str);
    Serial.println(oneWireTemp);
    sprintf(textBuffer, "T: %s", temp_str);
    tft.setTextColor(TFT_CYAN, TFT_CYAN);
    tft.fillRect(0, offset * 3 + top_offset, Width, offset, BACKGROUND);
    tft.drawBitmap(Width - 110, offset * 3 + top_offset + image_offset, tempBitmapArray, image_size, image_size, TFT_CYAN);
    tft.setCursor(3, offset * 3 + top_offset + text_fix);
    tft.print(textBuffer);
    delete temp_str;
  }

  tft.setTextSize(TEXT_SIZE);
  delete textBuffer;
}

void printFreeRAM(const __FlashStringHelper *message)
{
  char *textBuffer = new char[30];
  sprintf_P(textBuffer, (PGM_P)message, freeRAM());
  Serial.println(textBuffer);
  delete textBuffer;
}

int freeRAM()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void showTime()
{
  DateTime current = now + TimeSpan((millis() - millisDiff) / 1000);
  if (lastSecond == current.second())
  {
    return;
  }
  lastSecond = current.second();
  char *textBuffer = new char[20];
  sprintf_P(textBuffer, dateFormat, current.year(), current.month(),
            current.day(), current.hour(), current.minute(), current.second());

  //  uint16_t textColor = uint16_t((millis() * 10) % 65535);
  tft.setTextColor(TFT_WHITE, TFT_WHITE);
  tft.setCursor(3, Height - BOTTOM_PANEL + 15);

  tft.fillRect(0, Height - BOTTOM_PANEL, Width, BOTTOM_PANEL, BACKGROUND);
  tft.print(textBuffer);
  delete textBuffer;
  //  printFreeRAM(F("Free memory show time is: %d"));
}

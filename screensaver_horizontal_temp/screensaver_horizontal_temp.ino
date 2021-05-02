#include <Adafruit_GFX.h>
#include <RTClib.h>
#include <MCUFRIEND_kbv.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
// #include <Fonts/FreeMono12pt7b.h>
#include <DHT.h>
#include <OneWire.h>

#include "bitmaps.h"
#include "memdebug.h"

#define DHTPIN 12 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

// OneWire
#define ONE_WIRE_BUS 11
OneWire ds(ONE_WIRE_BUS);

// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
DateTime now;

MCUFRIEND_kbv tft; // hard-wired for UNO shields anyway.
int millisDiff;
int16_t BOTTOM_PANEL = 50;
#define TEXT_SIZE 3
#define Orientation 1 // PORTRAIT

// const char dateFormat[] PROGMEM = "%04d/%02d/%02d %02d:%02d:%02d";
const char dateFormat[] PROGMEM = "%02d/%02d %02d:%02d:%02d";
uint16_t lastSecond = 0;
uint16_t lastMinute = -1;
uint16_t timeTextColor = 0;
long lastSecondForTemp;

float oldValues[5] = {0, 0, 0, 0, 0};

void setupRTC()
{
  RTC_DS3231 RTC;
  Wire.begin();
  RTC.begin();
  // RTC.adjust(DateTime(__DATE__, __TIME__) + TimeSpan(14));
  now = RTC.now();
  millisDiff = millis();
}

void setup()
{
  setupRTC();

  Serial.begin(9600);

  tft.reset();
  tft.begin(tft.readID());

  tft.setRotation(Orientation);
  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);
  tft.setTextSize(TEXT_SIZE);
  tft.setTextWrap(false);

  dht.begin();
}

bool needToDrawTepmlates = true;

void loop()
{
  if (needToDrawTepmlates)
  {
    drawTemplates();
    needToDrawTepmlates = false;
  }

  showTime();

  if (millis() / 1000 % 60 != lastSecondForTemp)
  {
    lastSecondForTemp = millis() / 1000 % 60;

    printLocalTemp();

    // loadWeather();
    drawScreenRect();
  }
}

float getOneWireTemp()
{
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);

  //  delay(1000); // Микросхема измеряет температуру, а мы ждем.

  ds.reset();
  ds.write(0xCC);
  ds.write(0xBE);

  byte *oneWireData = new byte[2];
  ds.read_bytes(oneWireData, 2);
  float value = ((oneWireData[1] << 8) | oneWireData[0]) * 0.0625;

  delete oneWireData;
  return value;
}

void printLocalTemp()
{
  // printFreeRAM(F("on start printLocalTemp %d"));
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float hum = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temp = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(hum) || isnan(temp))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temp, hum, false);

  float oneWireTemp = getOneWireTemp();
  // Compute heat index in Celsius (isFahreheit = false)
  float oneWireHic = dht.computeHeatIndex(oneWireTemp, hum, false);

  if (oldValues[0] != hum)
  {
    oldValues[0] = hum;
    drawSensorValue(hum, TFT_BLUE, 0);
  }


  if (oldValues[1] != temp)
  {
    oldValues[1] = temp;
    drawSensorValue(temp, TFT_GREEN, 1);
  }

  if (oldValues[2] != hic)
  {
    oldValues[2] = hic;
    drawSensorValue(hic, TFT_DARKCYAN, 2);
  }

  
  if (oldValues[3] != oneWireTemp)
  {
    oldValues[3] = oneWireTemp;
    drawSensorValue(oneWireTemp, TFT_GREENYELLOW, 3);
  }
  
  if (oldValues[4] != oneWireHic)
  {
    oldValues[4] = oneWireHic;
    drawSensorValue(oneWireHic, TFT_CYAN, 4);
  }
  
  printFreeRAM(F("on end printLocalTemp %d"));
}

void drawTemplates()
{
  drawSensorTemplate("Humid:", TFT_BLUE, humBitmapArray, 0);
  drawSensorTemplate("Temp 1:", TFT_GREEN, tempBitmapArray, 1);
  drawSensorTemplate("Feel 1:", TFT_DARKCYAN, tempBitmapArray, 2);
  drawSensorTemplate("Temp 2:", TFT_GREENYELLOW, tempBitmapArray, 3);
  drawSensorTemplate("Feel 2:", TFT_CYAN, tempBitmapArray, 4);
}

void drawSensorTemplate(const char *text, uint16_t color, const uint8_t *bitmap, uint8_t line)
{
  const uint16_t cursorOffsetX = 25;
  const uint16_t cursorOffsetY = 25;
  const uint16_t bitmapSizeX = 32;
  const uint16_t bitmapSizeY = 32;
  const uint16_t bitmapPositionX = 260;
  const uint16_t bitmapPositionY = 20;

  tft.setTextColor(color, color);
  tft.drawBitmap(bitmapPositionX, bitmapPositionY + bitmapSizeY * line, bitmap, bitmapSizeX, bitmapSizeY, color);
  tft.setCursor(cursorOffsetX, cursorOffsetY + bitmapSizeY * line);
  tft.print(text);
}

void drawSensorValue(float value, uint16_t color, uint8_t line)
{
  const uint16_t cursorOffsetX = 170;
  const uint16_t cursorOffsetY = 25;
  const uint16_t boxPositionX = 170;
  const uint16_t boxPositionY = 15;
  const uint16_t boxSizeX = 70;
  const uint16_t boxSizeY = 32;

  char *textBuffer = new char[6];
  char *text = "%d.%d";

  sprintf(textBuffer, text, uint16_t((value * 10) / 10), uint16_t(uint16_t(value * 10) % 10));

  tft.fillRect(boxPositionX, boxPositionY + boxSizeY * line, boxSizeX, boxSizeY, TFT_BLACK);
  tft.setTextColor(color, color);
  tft.setCursor(cursorOffsetX, cursorOffsetY + boxSizeY * line);
  tft.print(textBuffer);

  delete textBuffer, text;
}

void showTime()
{
  DateTime current = now + TimeSpan((millis() - millisDiff) / 1000);
  if (lastSecond == current.second())
  {
    return;
  }
  lastSecond = current.second();

  if (lastMinute == current.minute())
  {
    // re-draw second only
    tft.setTextColor(timeTextColor, timeTextColor);
    const uint16_t secondPositionX = 25 + 12 * 18;
    const uint16_t secondPositionSize = 2 * 18;
    tft.setCursor(secondPositionX, tft.height() - BOTTOM_PANEL);
    tft.fillRect(secondPositionX, tft.height() - BOTTOM_PANEL, secondPositionSize, BOTTOM_PANEL - 28, TFT_BLACK);

    char *textBuffer = new char[2];
    sprintf(textBuffer, "%02d", current.second());
    tft.print(textBuffer);
    delete textBuffer;

    return;
  }
  lastMinute = current.minute();

  char *textBuffer = new char[20];
  sprintf_P(textBuffer, dateFormat, current.day(), current.month(), current.hour(), current.minute(), current.second());

  timeTextColor = uint16_t((millis() * 10) % 65535);
  tft.setTextColor(timeTextColor, timeTextColor);
  tft.setCursor(25, tft.height() - BOTTOM_PANEL);

  tft.fillRect(25, tft.height() - BOTTOM_PANEL, tft.width() - 30, BOTTOM_PANEL - 28, TFT_BLACK);
  tft.print(textBuffer);
  delete textBuffer;
  // printFreeRAM(F("Free memory show time is: %d"));
}

void drawScreenRect()
{
  uint16_t offset = 5;
  uint8_t thickness = 2;

  uint16_t textColor = uint16_t((millis() * 10) % 65535);

  tft.fillRect(offset, offset, tft.width() - offset * 2, thickness, textColor);
  tft.fillRect(offset, offset, thickness, tft.height() - offset * 2, textColor);
  tft.fillRect(tft.width() - offset, offset, thickness, tft.height() - offset * 2, textColor);
  tft.fillRect(offset,  tft.height() - offset, tft.width() - offset * 2, thickness, textColor);
}
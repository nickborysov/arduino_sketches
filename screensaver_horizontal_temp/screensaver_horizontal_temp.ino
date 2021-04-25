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

#define ESP_RX 8
#define ESP_TX 9
SoftwareSerial ESPserial(ESP_RX, ESP_TX); // RX | TX

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
long lastSecondForTemp;
float oldValues[5] = {0, 0, 0, 0, 0};
// const char accuCommand[] PROGMEM = "accuweather";
const char openCommand[] PROGMEM = "openweather";

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
  ESPserial.begin(74880);

  tft.reset();
  tft.begin(tft.readID());

  tft.setRotation(Orientation);
  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);
  tft.setTextSize(TEXT_SIZE);
  tft.setTextWrap(false);

  dht.begin();
}

void loop()
{
  showTime();

  if (millis() / 1000 % 60 != lastSecondForTemp)
  {
    lastSecondForTemp = millis() / 1000 % 60;

    printLocalTemp();

    // loadWeather();
    drawScreenRect();
  }
}

void loadWeather()
{
  Serial.println("select command");
  ESPserial.write(openCommand);
  uint8_t atempts = 10;
  while (atempts > 0)
  {
    Serial.println(ESPserial.available());
    if (!ESPserial.available())
    {
      atempts--;
      delay(1);
      continue;
    }
    String jsonString = ESPserial.readStringUntil('\n');
    Serial.println(jsonString);
    DynamicJsonDocument weatherJSON(600);
    DeserializationError err = deserializeJson(weatherJSON, jsonString);
    if (err)
    {
      Serial.println(err.c_str());
      Serial.println("error: " + jsonString);
      return;
    }
    JsonArray array = weatherJSON.as<JsonArray>();
    if (array.size() == 0)
    {
      return;
    }
    JsonObject item = array[0].as<JsonObject>();
    //  long timeStamp = item["timestamp"];
    float temp = item["temperature"];
    drawSensorValue(temp, "Forecast:%s", TFT_MAGENTA, tempBitmapArray, 4);
    break;
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
  printFreeRAM(F("on start printLocalTemp %d"));
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
    drawSensorValue(hum, "Humid:  %d.%d", TFT_BLUE, humBitmapArray, 0);
  }


  if (oldValues[1] != temp)
  {
    oldValues[1] = temp;
    drawSensorValue(temp, "Temp 1: %d.%d", TFT_GREEN, tempBitmapArray, 1);
  }

  if (oldValues[2] != hic)
  {
    oldValues[2] = hic;
    drawSensorValue(hic, "Feel 1: %d.%d", TFT_DARKCYAN, tempBitmapArray, 2);
  }

  
  if (oldValues[3] != oneWireTemp)
  {
    oldValues[3] = oneWireTemp; 
    drawSensorValue(oneWireTemp, "Temp 2: %d.%d", TFT_GREENYELLOW, tempBitmapArray, 3);
  }
  
  if (oldValues[4] != oneWireHic)
  {
    oldValues[4] = oneWireHic; 
    drawSensorValue(oneWireHic, "Feel 2: %d.%d", TFT_CYAN, tempBitmapArray, 4);
  }
  
  printFreeRAM(F("on end printLocalTemp %d"));
}

void drawSensorValue(float value, const char *text, uint16_t color, const uint8_t *bitmap, uint8_t line)
{

  const uint16_t cursorOffsetX = 18;
  const uint16_t cursorOffsetY = 20;
  const uint16_t bitmapSizeX = 32;
  const uint16_t bitmapSizeY = 32;
  const uint16_t bitmapPositionX = tft.width() - 75 + 10;
  const uint16_t bitmapPositionY = 0 + 10;
  const uint16_t boxPositionX = 0 + 10;
  const uint16_t boxPositionY = 0 + 10;
  const uint16_t boxSizeX = tft.width() - 30;
  const uint16_t boxSizeY = 32;

  char *textBuffer = new char[25];

  sprintf(textBuffer, text, uint16_t((value*10)/10), uint16_t(uint16_t(value*10)%10));
  tft.setTextColor(color, color);
  tft.fillRect(boxPositionX, boxPositionY + boxSizeY * line, boxSizeX, boxSizeY, TFT_BLACK);
  tft.drawBitmap(bitmapPositionX, bitmapPositionY + boxSizeY * line, bitmap, bitmapSizeX, bitmapSizeY, color);
  tft.setCursor(cursorOffsetX, cursorOffsetY + boxSizeY * line);
  tft.print(textBuffer);

  delete textBuffer, text, bitmap;

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
  sprintf_P(textBuffer, dateFormat, current.day(), current.month(), current.hour(), current.minute(), current.second());

  uint16_t textColor = uint16_t((millis() * 10) % 65535);
  tft.setTextColor(textColor, textColor);
  tft.setCursor(20, tft.height() - BOTTOM_PANEL);

  tft.fillRect(20, tft.height() - BOTTOM_PANEL, tft.width() - 30, BOTTOM_PANEL - 28, TFT_BLACK);
  tft.print(textBuffer);
  delete textBuffer;
  printFreeRAM(F("Free memory show time is: %d"));
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
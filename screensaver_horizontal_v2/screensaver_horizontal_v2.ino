#include <Adafruit_GFX.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <RTClib.h>
#include <MCUFRIEND_kbv.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <OneWire.h>
#include "bitmaps.h"

GFXfont *font = &FreeSerifBold18pt7b;

#define DHTPIN 12  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

// OneWire
#define ONE_WIRE_BUS 11
OneWire ds(ONE_WIRE_BUS);

// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
DateTime *now;


MCUFRIEND_kbv tft;  // hard-wired for UNO shields anyway.
int millisDiff;
#define Orientation 1  // PORTRAIT
#define BACKGROUND_COLOR 0x1082

// Battery
#define BATTERY_PIN A5  // Analog pin for battery voltage
float R1 = 100500.0;    // 100kΩ resistor
float R2 = 50100.0;     // 50kΩ resistor

uint16_t lastSecond = 0;
uint16_t lastMinute = -1;

long lastSecondForTemp;
long lastMiliSecond;

float oldValues[5] = { 0, 0, 0, 0, 0 };

void setupRTC() {
  RTC_DS3231 RTC;
  Wire.begin();
  RTC.begin();
  // RTC.adjust(DateTime(__DATE__, __TIME__) + TimeSpan(14));
  DateTime dt = RTC.now();
  now = &dt;
  millisDiff = millis();
}

void setup() {
  setupRTC();

  Serial.begin(9600);

  tft.reset();
  tft.begin(tft.readID());  // 37696
  tft.setRotation(Orientation);
  tft.fillScreen(BACKGROUND_COLOR);
  tft.setTextWrap(false);

  dht.begin();

  pinMode(BATTERY_PIN, INPUT);
}

bool needToDrawTepmlates = true;


float getOneWireTemp() {
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);

  //  delay(1000);

  ds.reset();
  ds.write(0xCC);
  ds.write(0xBE);

  byte *oneWireData = new byte[2];
  ds.read_bytes(oneWireData, 2);
  float value = ((oneWireData[1] << 8) | oneWireData[0]) * 0.0625;

  delete oneWireData;
  return value;
}


void drawTemplates() {
  const uint16_t bitmapSizeX = 48;
  const uint16_t bitmapSizeY = 48;

  // Humidity icon
  tft.drawBitmap(10, 36 + bitmapSizeY, humBitmapArray48, bitmapSizeX, bitmapSizeY, TFT_CYAN);
  tft.drawBitmap(145, 36 + bitmapSizeY, tempBitmapArray48, bitmapSizeX, bitmapSizeY, TFT_ORANGE);
  tft.drawBitmap(10, 140 + bitmapSizeY, tempBitmapArray32, 32, 32, TFT_OLIVE);
}


void drawSensorValue(float value, uint16_t color, uint16_t posX, uint16_t posY, float multiplier) {
  char *textBuffer = new char[2];
  const char *text = ".%d";

  sprintf(textBuffer, text, uint16_t(uint16_t(value * 10) % 10));

  uint8_t textSize = 5;
  uint16_t boxSizeX = 88 * multiplier;
  uint16_t boxSizeY = 36 * multiplier;

  tft.fillRect(posX, posY, boxSizeX, boxSizeY, BACKGROUND_COLOR);
  tft.setTextColor(color, color);
  tft.setFont(NULL);

  // print integer value
  tft.setTextSize(5 * multiplier);
  tft.setCursor(posX, posY);
  tft.print(uint16_t(uint16_t(value * 10) / 10));

  // print fractinal part
  tft.setCursor(posX + 55 * multiplier, posY + 15);
  tft.setTextSize(3 * multiplier);
  tft.print(textBuffer);

  delete textBuffer, text;
}


void drawLocalTemp() {
  // printFreeRAM(F("on start printLocalTemp %d"));
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float hum = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temp = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float oneWireTemp = getOneWireTemp();

  if (oldValues[0] != hum) {
    oldValues[0] = hum;
    drawSensorValue(hum, TFT_CYAN, 55, 92, 1);
  }


  if (oldValues[1] != temp) {
    oldValues[1] = temp;
    drawSensorValue(temp, TFT_ORANGE, 195, 92, 1);
  }

  if (oldValues[2] != oneWireTemp) {
    oldValues[2] = oneWireTemp;
    drawSensorValue(oneWireTemp, TFT_OLIVE, 40, 190, 0.8);
  }
}

const uint16_t timeTextColor = 0xFFFF;

void showTime() {
  DateTime current = *now + TimeSpan((millis() - millisDiff) / 1000);
  if (lastSecond == current.second()) {
    return;
  }
  lastSecond = current.second();
  uint8_t positionX = 25;
  uint8_t positionY = 70;

  uint8_t textSize = 2;
  uint16_t digitWidth = textSize * 16;
  uint16_t digitHeight = textSize * 25;

  uint16_t bgPosY = positionY - digitHeight + 2;
  uint16_t bgSizeY = digitHeight;

  tft.setTextSize(textSize);
  tft.setTextColor(timeTextColor, timeTextColor);
  tft.setFont(font);

  char *textBuffer;
  uint16_t printPosX;
  uint16_t printSizeX;
  if (lastMinute == current.minute()) {
    textBuffer = new char[2];
    sprintf(textBuffer, "%02d", current.second());
    printPosX = positionX + 6 * digitWidth;
    printSizeX = 2 * digitWidth + 8;
  } else {
    lastMinute = current.minute();
    textBuffer = new char[20];
    sprintf(textBuffer, "%02d:%02d:%02d", current.hour(), current.minute(), current.second());
    printPosX = positionX;
    printSizeX = digitWidth * 8 + 6;
  }

  tft.fillRect(printPosX - 2, bgPosY, printSizeX, bgSizeY, BACKGROUND_COLOR);
  tft.setCursor(printPosX, positionY);
  tft.print(textBuffer);
  delete textBuffer;
}

void drawBatteryValue() {
  int rawValue = analogRead(BATTERY_PIN);


  // Convert to voltage (Arduino uses 5V reference)
  float voltage = 0.0;
  if (rawValue > 0) {
    float voltage = (float(rawValue) * 5.0 / 1023.0) * ((R1 + R2) / R2);
  }

  // Convert to battery percentage (approximate)
  int batteryPercentage = map(voltage * 100, 300, 420, 0, 100);
  batteryPercentage = constrain(batteryPercentage, 0, 100);

  char *textBuffer;
  uint16_t textSize = 3;
  uint16_t digitWidth = textSize * 16;
  uint16_t digitHeight = textSize * 25;
  uint16_t printPosX = 220;
  uint16_t printSizeX = digitWidth * 8 + 6;
  uint16_t positionY = 190;
  uint16_t bgPosY = positionY;
  uint16_t bgSizeY = 40;
  uint16_t batteryTextColor = TFT_GREEN;

  textBuffer = new char[6];
  sprintf(textBuffer, "%02d%%", voltage);

  tft.setTextSize(textSize);
  tft.setTextColor(batteryTextColor, batteryTextColor);
  tft.setFont(NULL);
  tft.fillRect(printPosX, bgPosY, printSizeX, bgSizeY, BACKGROUND_COLOR);
  tft.setCursor(printPosX, positionY);
  tft.print(textBuffer);
  delete textBuffer;


  textBuffer = new char[4];
  sprintf(textBuffer, "%04d", rawValue);

  tft.setTextSize(textSize);
  tft.setTextColor(batteryTextColor, batteryTextColor);
  tft.setFont(NULL);
  tft.fillRect(printPosX - 50, bgPosY - 40, printSizeX, bgSizeY, BACKGROUND_COLOR);
  tft.setCursor(printPosX - 50, positionY - 40);
  tft.print(textBuffer);
  Serial.println(textBuffer);
  delete textBuffer;
}

void loop() {
  if (needToDrawTepmlates) {
    drawTemplates();

    needToDrawTepmlates = false;
  }


  if (millis() / 1000 % 60 != lastSecondForTemp) {
    lastSecondForTemp = millis() / 1000 % 60;

    showTime();
    drawLocalTemp();
    // drawBatteryValue();
  }

  if (millis() / 200 % 60 != lastMiliSecond) {
    lastMiliSecond = millis() / 200 % 60;
  }
}

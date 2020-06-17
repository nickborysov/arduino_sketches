
#include "Adafruit_GFX.h"
#include "RTClib.h"
#include <MCUFRIEND_kbv.h>
//#include <SD.h>
//#include <SPI.h>
#include <Wire.h>
//#include "Fonts/Org_01.h"

#include "Fonts/FreeMono12pt7b.h"

#include "DHT.h"

#define DHTPIN 12 // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


#define CUSTOM_FONT FreeMono12pt7b
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

void setupRTC() {
  RTC_DS3231 RTC;
  Wire.begin();
  RTC.begin();
//   RTC.adjust(DateTime(__DATE__, __TIME__) + TimeSpan(14));
  now = RTC.now();
  millisDiff = millis();
}

void setup() {
  setupRTC();

  Serial.begin(9600);

  tft.reset();
  uint16_t ID = tft.readID();
  Serial.print(F("screen ID "));
  Serial.println(ID);
  tft.begin(ID);

  tft.setRotation(Orientation);
  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);
  tft.setTextSize(TEXT_SIZE);
  tft.setTextWrap(false);
  tft.setFont(&CUSTOM_FONT);

  Width = tft.width();
  Height = tft.height();

  dht.begin();
}


long lastSecondForTemp;


void loop() {
  showTime();

  if (millis() / 1000 % 60 != lastSecondForTemp) {
    lastSecondForTemp = millis() / 1000 % 60;

    printLocalTemp();
  }
}

const  uint8_t humBitmapArray[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00,
  0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00,
  0x00, 0x0c, 0xf0, 0x00, 0x00, 0x18, 0xf8, 0x00, 0x00, 0x39, 0xfc, 0x00, 0x00, 0x31, 0xfc, 0x00,
  0x00, 0x63, 0xfe, 0x00, 0x00, 0xe7, 0xff, 0x00, 0x00, 0xc7, 0xff, 0x00, 0x01, 0x8f, 0xff, 0x80,
  0x01, 0x9f, 0xff, 0x80, 0x01, 0x9f, 0xff, 0x80, 0x03, 0x3f, 0xff, 0xc0, 0x03, 0x3f, 0xff, 0xc0,
  0x03, 0x3f, 0xff, 0xc0, 0x03, 0x3f, 0xff, 0xc0, 0x03, 0x3f, 0xff, 0xc0, 0x01, 0xff, 0xff, 0x80,
  0x01, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xfe, 0x00,
  0x00, 0x1f, 0xf8, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t tempBitmapArray[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xe0, 0x00,
  0x00, 0x0e, 0x70, 0x00, 0x00, 0x0c, 0x37, 0xc0, 0x00, 0x0c, 0x37, 0xc0, 0x00, 0x0c, 0x30, 0x00,
  0x00, 0x0c, 0x30, 0x00, 0x00, 0x0c, 0x37, 0xc0, 0x00, 0x0c, 0x37, 0xc0, 0x00, 0x0c, 0x30, 0x00,
  0x00, 0x0c, 0x30, 0x00, 0x00, 0x0c, 0x37, 0xc0, 0x00, 0x0c, 0x37, 0xc0, 0x00, 0x0c, 0x30, 0x00,
  0x00, 0x0c, 0x30, 0x00, 0x00, 0x0c, 0x37, 0xc0, 0x00, 0x0c, 0x37, 0xc0, 0x00, 0x0c, 0x30, 0x00,
  0x00, 0x1c, 0x38, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x30, 0x0c, 0x00,
  0x00, 0x30, 0x0c, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0x0f, 0xf0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

float oldHum, oldTemp, oldHic;

void printLocalTemp() {
  //  printFreeRAM(F("printLocalTemp %d"));
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  char *textBuffer = new char[25];

  if (oldHum != h ) {
    oldHum = h;
    char* hum_str = new char[5];
    dtostrf(h, 4, 1, hum_str);

    sprintf(textBuffer, "Humidity:    %s", hum_str);
    tft.setTextColor(TFT_BLUE, TFT_BLUE);
    tft.fillRect(0, 0, Width, 32, TFT_BLACK);
    tft.drawBitmap(Width - 75, 0, humBitmapArray, 32, 32, TFT_BLUE);
    tft.setCursor(3, 15 + 10);
    tft.print(textBuffer);
    delete hum_str;
  }

  if (oldTemp != t ) {
    oldTemp = t;
    char* temp_str = new char[5];
    dtostrf(t, 4, 1, temp_str);

    sprintf(textBuffer, "Temperature: %s", temp_str);
    tft.setTextColor(TFT_GREEN, TFT_GREEN);
    tft.fillRect(0, 32, Width, 32, TFT_BLACK);
    tft.drawBitmap(Width - 75, 32, tempBitmapArray, 32, 32, TFT_GREEN);
    tft.setCursor(3, 32 + 15 + 10);
    tft.print(textBuffer);
    delete temp_str;
  }

  if (oldHic != hic) {
    oldHic = hic;
    char* hic_str = new char[5];
    dtostrf(hic, 4, 1, hic_str);

    sprintf(textBuffer, "Feels like:  %s", hic_str);
    tft.setTextColor(TFT_DARKCYAN, TFT_DARKCYAN);
    tft.fillRect(0, 32 * 2, Width, 32, TFT_BLACK);
    tft.drawBitmap(Width - 75, 32 * 2, tempBitmapArray, 32, 32, TFT_DARKCYAN);
    tft.setCursor(3, 32 * 2 + 15 + 10);
    tft.print(textBuffer);
    delete hic_str;
  }

  delete textBuffer;
}

void printFreeRAM(const __FlashStringHelper *message) {
  char *textBuffer = new char[30];
  sprintf_P(textBuffer, (PGM_P)message, freeRAM());
  Serial.println(textBuffer);
  delete textBuffer;
}

int freeRAM() {
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void showTime() {
  DateTime current = now + TimeSpan((millis() - millisDiff) / 1000);
  if (lastSecond == current.second()) {
    return;
  }
  lastSecond = current.second();
  char *textBuffer = new char[20];
  sprintf_P(textBuffer, dateFormat, current.year(), current.month(),
            current.day(), current.hour(), current.minute(), current.second());

  uint16_t textColor = uint16_t((millis() * 10) % 65535);
  tft.setTextColor(textColor, textColor);
  tft.setCursor(3, Height - BOTTOM_PANEL + 15);

  tft.fillRect(0, Height - BOTTOM_PANEL, Width, BOTTOM_PANEL, TFT_BLACK);
  tft.print(textBuffer);
  delete textBuffer;
  //  printFreeRAM(F("Free memory show time is: %d"));
}

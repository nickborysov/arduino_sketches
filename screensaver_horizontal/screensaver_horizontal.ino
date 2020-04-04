
#include <MCUFRIEND_kbv.h>
#include "Adafruit_GFX.h"
#include <SD.h>
#include "RTClib.h"
#include <SPI.h>
#include <Wire.h>
#include "Fonts/Org_01.h"

#define CUSTOM_FONT Org_01
#define TEXT_SIZE 3
#define Orientation 1    //PORTRAIT

// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
DateTime now;

MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
int Width;
int Height;
int millisDiff;
int16_t BOTTOM_PANEL = 20;

File root;
File file;

uint8_t *block;
uint16_t *colorBuffer;

const char dateFormat[] PROGMEM = "%04d/%02d/%02d %02d:%02d:%02d";
uint16_t lastSecond = 0;

void setupRTC() {
  RTC_DS3231 RTC;
  Wire.begin();
  RTC.begin();
  // RTC.adjust(DateTime(__DATE__, __TIME__) + TimeSpan(14));
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

  // Setup pin for SD-card from data logger.
  pinMode(10, OUTPUT);

  if (!SD.begin(10))
  {
    Serial.println(F("Card Failure"));
    return;
  }

  root = SD.open("/");
  // Read random image on start.
  uint8_t n = millis() % 5;
  for (uint8_t i = 0; i < n; i++) {
    if (!nextFile(root)) {
      break;
    }
    file.close();
  }
  readRandomImage();
}

bool nextFile(File dir) {
  uint16_t randomFileNumber = uint16_t(millis() % 10);
  uint16_t i = 0;
  while (true)
  {
    File entry =  dir.openNextFile();
    if (!entry) {
      dir.rewindDirectory();
      continue;
    }
    if (i < randomFileNumber) {
      i++;
      entry.close();
      continue;
    }
    String fileName = entry.name();
    if ((fileName.lastIndexOf(".bmp") == -1 && fileName.lastIndexOf(".BMP") == -1)) {
      entry.close();
      continue;
    }
    file = entry;
    return true;
  }
  return false;
}

void readBmpImage() {
  printFreeRAM(F("Free memory on start is: %d"));
  int imageWidth, imageHeight;
  {
    uint8_t *header = new uint8_t[54];
    file.readBytes(header, 54);
    imageWidth = header[18] | (header[19] << 8) | (header[20] << 16);
    imageHeight = header[22] | (header[23] << 8) | (header[24] << 16);
    delete header;
  }

  if (imageWidth > 320 || imageHeight > 240) {
    Serial.println(F("Invalid image size"));
    return;
  }
  
  char *textBuffer = new char[30];
  sprintf_P(textBuffer, (PGM_P)F("Image size is %04u x %04u"), imageWidth, imageHeight);
  Serial.println(textBuffer);
  delete textBuffer;

  uint16_t blockSize = imageWidth / 16;
  uint8_t colorBufferMultiplier = 8;
  uint16_t colorBufferSize = blockSize * colorBufferMultiplier;
  block = new uint8_t[blockSize * 3];
  colorBuffer = new uint16_t[colorBufferSize];
  for (uint16_t y = imageHeight - 1; y > 0; y--) {
    for (uint16_t i = 0; i < imageWidth / blockSize; i++ ) {
      file.readBytes(block, blockSize * 3);

      if (y >= Height - BOTTOM_PANEL) {
        continue;
      }

      for (uint8_t j = 0; j < blockSize; j++ ) {
        colorBuffer[((i % colorBufferMultiplier)) * blockSize + j] =  tft.color565(block[j * 3 + 2], block[j * 3 + 1], block[j * 3]);
      }
      if (i % colorBufferMultiplier < colorBufferMultiplier - 1) {
        continue;
      }
      uint16_t startX = ((i + 1 - colorBufferMultiplier) * blockSize);
      tft.setAddrWindow(startX, y, startX + colorBufferSize, y);
      tft.pushColors(colorBuffer, colorBufferSize, 1);
    }
    if ((y % 10) == 0 && y < Height - BOTTOM_PANEL) {
      showTime();
    }
    if (y == imageHeight / 2) {
      printFreeRAM(F("Free memory in progress is: %d"));
    }
  }

  file.close();
  delete block;
  delete colorBuffer;

  printFreeRAM(F("Free memory on finish is: %d"));
}

void readRandomImage() {
  printFreeRAM(F("Free memory before start is: %d"));
  if (nextFile(root)) {
    char *textBuffer = new char[30];
    sprintf_P(textBuffer, (PGM_P)F("Next image is %s"), file.name());
    Serial.println(textBuffer);
    delete textBuffer;
    tft.fillScreen(TFT_BLACK);
    readBmpImage();
  } else {
    Serial.println(F("no file found"));
  }
}

void loop() {
  if (( now + TimeSpan((millis() - millisDiff) / 1000)).second() > 55) {
    readRandomImage();
  }
  showTime();
}

void printFreeRAM(const __FlashStringHelper* message) {
  char *textBuffer = new char[30];
  sprintf_P(textBuffer, (PGM_P)message, freeRAM());
  Serial.println(textBuffer);
  delete textBuffer;
}

int freeRAM() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void showTime() {
  DateTime current = now + TimeSpan((millis() - millisDiff) / 1000);
  if (lastSecond == current.second()) {
    return;
  }
  lastSecond = current.second();
  char *textBuffer = new char[20];
  sprintf_P(textBuffer, dateFormat, current.year(), current.month(), current.day() , current.hour(), current.minute(), current.second());
  tft.fillRect(0, Height - BOTTOM_PANEL, Width, BOTTOM_PANEL, TFT_BLACK);

  uint16_t textColor = uint16_t((millis() * 10) % 65535);
  tft.setTextColor(textColor, textColor);
  tft.setCursor(3, Height - BOTTOM_PANEL + 15);

  tft.print(textBuffer);
  delete textBuffer;
  //  printFreeRAM(F("Free memory show time is: %d"));
}

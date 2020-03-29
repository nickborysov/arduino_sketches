
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <SD.h>
#include "RTClib.h"
#include <SPI.h>
#include <Wire.h>


// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
DateTime now;

MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
int Width;
int Height;
#define Orientation 0    //PORTRAIT
File root;
int millisDiff;
int16_t BOTTOM_PANEL = 20;
uint16_t timePanelX;
uint16_t timePanelY;

// TouchScreen variables
const int XP = 7, XM = A1, YP = A2, YM = 6; //240x320 ID=0x9340
const int TS_LEFT = 98, TS_RT = 907, TS_TOP = 959, TS_BOT = 129;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define MINPRESSURE 100
#define MAXPRESSURE 1000
#define PENRADIUS 1
uint16_t xpos, ypos;  //screen coordinates
uint16_t currentColor = TFT_GREEN;
const uint16_t Colors[] PROGMEM = {TFT_RED, TFT_YELLOW, TFT_ORANGE, TFT_GREENYELLOW, TFT_GREEN, TFT_CYAN, TFT_BLUE, TFT_MAGENTA, TFT_PURPLE, TFT_WHITE, TFT_LIGHTGREY, TFT_DARKGREY};

void setupRTC() {
  RTC_DS3231 RTC;
  Wire.begin();
  RTC.begin();
//    RTC.adjust(DateTime(__DATE__, __TIME__) + TimeSpan(16));

  now = RTC.now();
  millisDiff = millis();
}

void setup() {
  setupRTC();
  // put your setup code here, to run once:
  Serial.begin(9600);

  tft.reset();
  uint16_t ID = tft.readID();
  tft.begin(ID);

  tft.setRotation(Orientation);
  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);

  Width = tft.width();
  Height = tft.height();
  timePanelX = 5;
  timePanelY = Height - BOTTOM_PANEL;

  // Setup pin for SD-card from data logger.
  pinMode(10, OUTPUT);

  if (!SD.begin(10))
  {
    Serial.println(F("Card Failure"));
    return;
  }

  root = SD.open("/");
  //  printFiles(root);
  root.rewindDirectory();

  readRandomImage();
}

void printFiles(File dir) {
  dir.rewindDirectory();
  while (true)
  {
    File entry =  dir.openNextFile();
    if (!entry) {
      break;
    }
    Serial.println(entry.name());
    entry.close();
  }
}

File file;

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
    if ((fileName.lastIndexOf(".bmp") == -1 && fileName.lastIndexOf(".BMP") == -1) || fileName.lastIndexOf("~") != -1) {
      entry.close();
      continue;
    }
    file = entry;
    return true;
  }
  return false;
}

uint8_t *block;
uint8_t *header = new uint8_t[54];
char *textBuffer = new char[30];

void readBmpImage() {
  printFreeRAM(F("Free memory on start is: %d"));
  file.readBytes(header, 54);
  int imageWidth = header[18] | (header[19] << 8) | (header[20] << 16);
  int imageHeight = header[22] | (header[23] << 8) | (header[24] << 16);

  if (imageWidth > 240 || imageHeight > 320) {
    return;
  }
  sprintf_P(textBuffer, (PGM_P)F("Image size is %04u x %04u"), imageWidth, imageHeight);
  Serial.println(textBuffer);

  uint16_t blockSize = imageWidth / 8;
  block = new uint8_t[blockSize * 3];
  for (uint16_t y = imageHeight - 1; y > 0; y--) {
    for (uint16_t i = 0; i < imageWidth / blockSize; i++ ) {
      file.readBytes(block, blockSize * 3);
      for (uint16_t x = 0; x < blockSize; x++ ) {
        uint16_t color =  tft.color565(block[x * 3 + 2], block[x * 3 + 1], block[x * 3]);
        if (color == TFT_BLACK) {
          continue;
        }
        tft.fillRect(x + (i * blockSize), y, 1, 1, color);
      }
    }
    if ((y % 5) == 0) {
      showTime();
    }
  }
  printFreeRAM(F("Free memory in progress is: %d"));

  file.close();
  delete block;

  printFreeRAM(F("Free memory on finish is: %d"));
}

void handleTouch() {
  TSPoint tp = ts.getPoint();   //tp.x, tp.y are ADC values
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    xpos = map(tp.x, TS_LEFT, TS_RT, 0, Width);
    ypos = map(tp.y, TS_TOP, TS_BOT, 0, Height);

    if ((ypos + PENRADIUS) < (Height - BOTTOM_PANEL)) {
      tft.fillCircle(xpos, ypos, PENRADIUS, currentColor);
    }
  }
}

void readRandomImage() {
  if (nextFile(root)) {
    sprintf_P(textBuffer, (PGM_P)F("Next image is %s"), file.name());
    Serial.println(textBuffer);
    tft.fillScreen(TFT_BLACK);
    readBmpImage();
  } else {
    Serial.println(F("no file found"));
  }
}

void loop() {
  handleTouch();
  if (( now + TimeSpan((millis() - millisDiff) / 1000)).second() > 55) {
    readRandomImage();
    currentColor = Colors[millis() % 12];
  }
  showTime();
}

void printFreeRAM(const __FlashStringHelper* message) {
  sprintf_P(textBuffer, (PGM_P)message, freeRAM());
  Serial.println(textBuffer);
}

int freeRAM() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}


const char dateFormat[] PROGMEM = "%04d/%02d/%02d %02d:%02d:%02d";
uint16_t lastSecond = 0;
char *timeData = new char[20];

void showTime() {
  DateTime current = now + TimeSpan((millis() - millisDiff) / 1000);
  if (lastSecond == current.second()) {
    return;
  }
  lastSecond = current.second();
  sprintf_P(timeData, dateFormat, current.year(), current.month(), current.day() , current.hour(), current.minute(), current.second());
  tft.fillRect(0, Height - BOTTOM_PANEL, Width, BOTTOM_PANEL, TFT_BLACK);
  drawText(timeData, timePanelX, timePanelY, uint16_t((millis() * 10) % 65535), TFT_BLACK);
}

void drawText(char *timeData, uint16_t x, uint16_t y, uint16_t color , uint16_t bg) {
  for (uint16_t i = 0; i < strlen(timeData); i++ ) {
    tft.drawChar(x + i * 12, y + 3, timeData[i], color, bg, 2);
  }
}

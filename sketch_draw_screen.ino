// the regular Adafruit "TouchScreen.h" library only works on AVRs

// different mcufriend shields have Touchscreen on different pins
// and rotation.
// Run the TouchScreen_Calibr_native sketch for calibration of your shield

#include <SD.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

// RTC
// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
#include "RTClib.h"
DateTime now;

// RTC

const int XP = 7, XM = A1, YP = A2, YM = 6; //240x320 ID=0x9340
const int TS_LEFT = 98, TS_RT = 907, TS_TOP = 959, TS_BOT = 129;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define MINPRESSURE 100
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t BOTTOM_PANEL = 20;
int16_t PENRADIUS = 1;
uint16_t ID, oldcolor;
uint16_t currentcolor = TFT_GREEN;
uint8_t Orientation = 0;    //PORTRAIT
int Width;
int Height;
char *format = "image%u.bmp";
char *dateFormat = "%04d/%02d/%02d %02d:%02d:%02d";
int millisDiff;
uint16_t lastSecond = 0;

uint16_t Colors[] = {TFT_RED, TFT_YELLOW, TFT_ORANGE, TFT_GREENYELLOW, TFT_GREEN, TFT_CYAN, TFT_BLUE, TFT_MAGENTA, TFT_PURPLE, TFT_WHITE, TFT_LIGHTGREY, TFT_DARKGREY};

void setup(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  RTC_DS3231 RTC;
  RTC.begin();
//  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)) + TimeSpan(11));

  now = RTC.now();
  millisDiff = millis();
  Serial.begin(9600);

  tft.reset();
  ID = tft.readID();
  tft.begin(ID);

  tft.setRotation(Orientation);
  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);

  Width = tft.width();
  Height = tft.height();

  BOXSIZE = Width / 12;

  for (uint8_t i = 0; i < Width; i++) {
    tft.fillRect(i, 0, 1, BOXSIZE, colorForIndex(i));
    //    tft.fillRect(i*4, 0, 4, BOXSIZE, (65535 / Width) * 4* i );
  }
  //  for (uint8_t i = 0; i < 12; i++) {
  //    tft.fillRect(BOXSIZE * i, 0, BOXSIZE, BOXSIZE, Colors[i]);
  //  }
  tft.fillRect(0, Height - BOTTOM_PANEL, Width, BOTTOM_PANEL, TFT_BLACK);
  tft.drawRect(0, Height - BOTTOM_PANEL, Width, BOTTOM_PANEL, TFT_RED);
}

uint16_t colorForIndex(uint8_t i) {
  float frequency = .056;
  uint8_t r = (sin(frequency * i + 0) * 127 + 128) / ((i / 120) + 1);
  uint8_t g = (sin(frequency * i + 2) * 127 + 128) / ((i / 120) + 1);
  uint8_t b = (sin(frequency * i + 4) * 127 + 128) / ((i / 120) + 1);

  return tft.color565(r, g, b);
}

uint16_t xpos, ypos;  //screen coordinates
void loop()
{
  TSPoint tp = ts.getPoint();   //tp.x, tp.y are ADC values

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    // most mcufriend have touch (with icons) that extends below the TFT
    // screens without icons need to reserve a space for "erase"
    // scale the ADC values from ts.getPoint() to screen values e.g. 0-239
    //
    // Calibration is true for PORTRAIT. tp.y is always long dimension
    // map to your current pixel orientation
    //    switch (Orientation) {
    //      case 0:
    xpos = map(tp.x, TS_LEFT, TS_RT, 0, Width);
    ypos = map(tp.y, TS_TOP, TS_BOT, 0, Height);
    //        break;
    //      case 1:
    //        xpos = map(tp.y, TS_TOP, TS_BOT, 0, Width);
    //        ypos = map(tp.x, TS_RT, TS_LEFT, 0, Height);
    //        break;
    //      case 2:
    //        xpos = map(tp.x, TS_RT, TS_LEFT, 0, Width);
    //        ypos = map(tp.y, TS_BOT, TS_TOP, 0, Height);
    //        break;
    //      case 3:
    //        xpos = map(tp.y, TS_BOT, TS_TOP, 0, Width);
    //        ypos = map(tp.x, TS_LEFT, TS_RT, 0, Height);
    //        break;
    //    }

    // are we in erase area ?
    // Plain Touch panels use bottom 10 pixels e.g. > h - 10
    // Touch panels with icon area e.g. > h - 0
    if (ypos > Height - 0) {
      if (xpos < Width * 0.25 ) {
        digitalWrite(LED_BUILTIN, LOW);
        //                saveScreen();

      } else if (xpos < Width * 0.5 ) {
        PENRADIUS--;

        delay(200);
      } else if (xpos < Width * 0.75 ) {
        PENRADIUS++;
        delay(200);
      } else if (xpos > Width * 0.75 ) {
        digitalWrite(LED_BUILTIN, HIGH);
        // press the bottom of the screen to erase
        tft.fillRect(0, BOXSIZE, Width, Height - BOXSIZE - BOTTOM_PANEL, TFT_BLACK);
      }
      return;
    }
    if (ypos > Height - BOTTOM_PANEL && ypos < Height) {
      return;
    }

    // are we in top color box area ?
    if (ypos < BOXSIZE) {               //draw white border on selected color box
      currentcolor = colorForIndex(xpos);
      // uint16_t boxIndex = xpos / BOXSIZE;
      // oldcolor = currentcolor;
      // currentcolor = ypos * Width / 2;
      //      currentcolor = Colors[boxIndex];
      //      tft.drawRect(BOXSIZE * boxIndex, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
      //      if (oldcolor != currentcolor) { //rub out the previous white border
      //        for (uint8_t i = 0; i < 12; i++) {
      //          if (oldcolor ==  Colors[i]) {
      //            tft.fillRect(BOXSIZE * i, 0, BOXSIZE, BOXSIZE, Colors[i]);
      //          }
      //        }
      //      }
    }
    // are we in drawing area ?
    if (((ypos - PENRADIUS) > BOXSIZE) && ((ypos + PENRADIUS) < Height - BOTTOM_PANEL)) {
      tft.fillCircle(xpos, ypos, PENRADIUS, currentcolor);
    }
  }
  showTime();
}

void saveScreen() {
  if (!SD.begin(10)) {
    //    Serial.println("initialization failed!");
    return;
  }
  char *fileName =  new char[15];
  sprintf(fileName, format, random(1000));
  while (SD.exists(fileName)) {
    sprintf(fileName, format, random(1000));
  };
  Serial.println(fileName);

  File myFile;
  myFile = SD.open(fileName, FILE_WRITE);
  if (!myFile) {
    //    Serial.println("file is not opened");
    return;
  }
  int imageHeight = Height - BOXSIZE - BOTTOM_PANEL;
  const int pad = (4 - (3 * Width) % 4) % 4;
  const int filesize = 54 + (3 * Width + pad) * imageHeight;
  // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
  //  char padding[3] = { 0, 0, 0 };

  {
    char header[54] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };
    for (uint8_t i = 0; i < 4; i++) {
      header[ 2 + i] = (unsigned char)((filesize >> (8 * i)) & 255);
      header[18 + i] = (unsigned char)((Width   >> (8 * i)) & 255);
      header[22 + i] = (unsigned char)((imageHeight  >> (8 * i)) & 255);
    }
    myFile.write(header, 54);
  }

  uint16_t *block;
  unsigned char* img;
  uint16_t start = 0;
  uint16_t blockSize = Width / 4;
  block = new uint16_t[blockSize];
  img = new unsigned char[blockSize * 3];
  for (int y = Height - 1 - BOTTOM_PANEL; y >= BOXSIZE; y--) {
    for (int i = 0; i < Width / blockSize; i++ ) {
      start = i * blockSize;

      tft.readGRAM(start, y, block, blockSize, 1);

      for (int x = 0; x < blockSize; x++ ) {
        uint16_t value = block[x];
        img[x * 3 + 0] = (unsigned char)((value & 0x1F) << 3);
        img[x * 3 + 1] = (unsigned char)(((value & 0x7E0) >> 5) << 2);
        img[x * 3 + 2] = (unsigned char)(((value & 0xF800) >> 11) << 3);
      }
      //      if (y == Height - 1 && i == 0 ) {
      //        Serial.println(String("Free ram in progress ") + freeRAM() + String(" bytes"));
      //      }
      //      free(block);

      myFile.write((char*)(img), blockSize * 3);
      //      free(img);
      //      myFile.write(padding, pad);
    }
  }
  delete block;
  delete img;
  //  free(img);
  //  free(block);
  myFile.close();

  if (!SD.exists(fileName)) {
    //    Serial.println("File wasn't saved.");
    return;
  }
  //  Serial.println("File saved");
  free(fileName);
  SD.end();
}


void showTime() {
  DateTime current = now + TimeSpan((millis() - millisDiff) / 1000);
  if (lastSecond == current.second()) {
    return;
  }
  lastSecond = current.second();
  char *data = new char[20];
  sprintf(data, dateFormat, current.year(), current.month(), current.day() , current.hour(), current.minute(), current.second());
  drawText(data, 5, Height - BOTTOM_PANEL, uint16_t((millis() * 10) % 65535), TFT_BLACK);
  delete data;
}

void drawText(char *data, uint16_t x, uint16_t y, uint16_t color , uint16_t bg) {
  for (uint16_t i = 0; i < strlen(data); i++ ) {
    tft.drawChar(x + i * 12, y + 3, data[i], color, bg, 2);
  }
}

// the regular Adafruit "TouchScreen.h" library only works on AVRs

// different mcufriend shields have Touchscreen on different pins
// and rotation.
// Run the TouchScreen_Calibr_native sketch for calibration of your shield

#include <SD.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "RTClib.h"

// hard-wired for UNO shields anyway.
MCUFRIEND_kbv tft;

// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
DateTime now;

const int XP = 7, XM = A1, YP = A2, YM = 6; //240x320 ID=0x9340
const int TS_LEFT = 98, TS_RT = 907, TS_TOP = 959, TS_BOT = 129;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define MINPRESSURE 100
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t BOTTOM_PANEL = 20;
int16_t PENRADIUS = 1;
uint16_t currentcolor = TFT_GREEN;
uint16_t Width;
uint16_t Height;
char *format = "image%u.bmp";
char *dateFormat = "%04d/%02d/%02d %02d:%02d:%02d";
int millisDiff;
uint16_t lastSecond = 0;

uint16_t Colors[] = {TFT_RED, TFT_YELLOW, TFT_ORANGE, TFT_GREENYELLOW, TFT_GREEN, TFT_CYAN, TFT_BLUE, TFT_MAGENTA, TFT_PURPLE, TFT_WHITE, TFT_LIGHTGREY, TFT_DARKGREY};

void setup(void)
{
  // Setup pin for SD-card from data logger.
  pinMode(10 , OUTPUT);
  
  RTC_DS3231 RTC;
  RTC.begin();
  //  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)) + TimeSpan(11));

  now = RTC.now();
  millisDiff = millis();
  Serial.begin(9600);

  tft.reset();
  uint16_t ID = tft.readID();
  tft.begin(ID);

  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);

  Width = tft.width();
  Height = tft.height();

  BOXSIZE = Width / 12;

  for (uint8_t i = 0; i < Width; i++) {
    tft.fillRect(i, 0, 1, BOXSIZE, colorForIndex(i));
  }
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
    xpos = map(tp.x, TS_LEFT, TS_RT, 0, Width);
    ypos = map(tp.y, TS_TOP, TS_BOT, 0, Height);

    if (ypos > Height - 0) {
      if (xpos < Width * 0.25 ) {
        saveScreen();

        //      } else if (xpos < Width * 0.5 ) {
        //        PENRADIUS--;
        //        delay(200);
        //      } else if (xpos < Width * 0.75 ) {
        //        PENRADIUS++;
        //        delay(200);
      } else if (xpos > Width * 0.75 ) {
        // press the bottom of the screen to erase
        tft.fillRect(0, BOXSIZE, Width, Height - BOXSIZE - BOTTOM_PANEL, TFT_BLACK);
      }
      return;
    }
    if (ypos > Height - BOTTOM_PANEL && ypos < Height) {
      return;
    }
    if (ypos < BOXSIZE) {
      currentcolor = colorForIndex(xpos);
    }
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
  uint16_t imageHeight = Height - BOXSIZE - BOTTOM_PANEL;
  const uint16_t pad = (4 - (3 * Width) % 4) % 4;
  const uint16_t filesize = 54 + (3 * Width + pad) * imageHeight;
  {
    char header[54] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };
    for (uint8_t i = 0; i < 4; i++) {
      header[2 + i] = (unsigned char)((filesize >> (8 * i)) & 255);
      header[18 + i] = (unsigned char)((Width   >> (8 * i)) & 255);
      header[22 + i] = (unsigned char)((imageHeight  >> (8 * i)) & 255);
    }
    myFile.write(header, 54);
  }

  uint16_t *block;
  unsigned char* img;
  uint16_t blockSize = Width / 4;
  block = new uint16_t[blockSize];
  img = new unsigned char[blockSize * 3];
  for (int y = Height - 1 - BOTTOM_PANEL; y >= BOXSIZE; y--) {
    for (int i = 0; i < Width / blockSize; i++ ) {

      tft.readGRAM(i * blockSize, y, block, blockSize, 1);

      for (int x = 0; x < blockSize; x++ ) {
        uint16_t value = block[x];
        img[x * 3 + 0] = (unsigned char)((value & 0x1F) << 3);
        img[x * 3 + 1] = (unsigned char)(((value & 0x7E0) >> 5) << 2);
        img[x * 3 + 2] = (unsigned char)(((value & 0xF800) >> 11) << 3);
      }
      myFile.write((char*)(img), blockSize * 3);
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


char *data = new char[20];
void showTime() {
  DateTime current = now + TimeSpan((millis() - millisDiff) / 1000);
  if (lastSecond == current.second()) {
    return;
  }
  lastSecond = current.second();
  sprintf(data, dateFormat, current.year(), current.month(), current.day() , current.hour(), current.minute(), current.second());
  drawText(data, 5, Height - BOTTOM_PANEL, uint16_t((millis() * 10) % 65535), TFT_BLACK);
}

void drawText(char *data, uint16_t x, uint16_t y, uint16_t color , uint16_t bg) {
  for (uint16_t i = 0; i < strlen(data); i++ ) {
    tft.drawChar(x + i * 12, y + 3, data[i], color, bg, 2);
  }
}

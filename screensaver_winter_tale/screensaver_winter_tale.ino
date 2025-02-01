#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <stddef.h>
#include <stdlib.h>
#include <TouchScreen.h>
#include "winter.h"
#include "winter.c"

MCUFRIEND_kbv tft; // hard-wired for UNO shields anyway.
int millisDiff;

#define TEXT_SIZE 3
#define Orientation 1 // PORTRAIT


const int XP = 7, XM = A1, YP = A2, YM = 6; //240x320 ID=0x9340
const int TS_LEFT = 98, TS_RT = 907, TS_TOP = 959, TS_BOT = 129;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
uint16_t xpos, ypos;  //screen coordinates
#define MINPRESSURE 100
#define MAXPRESSURE 1000
uint16_t Width;
uint16_t Height;

void setup()
{
  // setupRTC();

  Serial.begin(9600);

  tft.reset();
  tft.begin(tft.readID()); // 37696
  tft.setRotation(Orientation);
  tft.fillScreen(TFT_BLACK);
  // tft.invertDisplay(true);
  tft.setTextSize(TEXT_SIZE);
  tft.setTextWrap(false);


  Width = tft.width();
  Height = tft.height();
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  drawBase();
}

bool needToDrawTepmlates = true;

int running = 1;

int santaX = SCREEN_WIDTH;
long lastMiliSecond;
int waitForSanta = 0;

long lastMiliSecondForSnow;
int snowSpeed = 60;

uint8_t isSnowingHard;

void loop()
{
  if (millis() / snowSpeed % 60 != lastMiliSecondForSnow && true)
  {
    lastMiliSecondForSnow = millis() / snowSpeed % 60;
    drawSnow();

    // if (isSnowingHard > 0) {
    //   isSnowingHard--;
    //   snowSpeed = 10;
    //   return;
    // } else {
    //   snowSpeed = 60;
    // }

    // TSPoint tp = ts.getPoint(); // tp.x, tp.y are ADC values
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!

    // if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE)
    // {
    //   xpos = map(tp.x, TS_LEFT, TS_RT, 0, Width);
    //   ypos = map(tp.y, TS_TOP, TS_BOT, 0, Height);

    //   isSnowingHard = 100;
    // }
  }
  
  uint16_t speed = 60;
  if (millis() / speed % 60 != lastMiliSecond && true)
  {
    lastMiliSecond = millis() / speed % 60;
    if (waitForSanta > 0) {
      waitForSanta--;
    }
    // tft.fillRect(0, 0, tft.width(), tft.height(), TFT_BLACK);
    // drawMoon();
    // drawGifts();

    drawSanta(santaX, santaX + 5);

    santaX -= 5;
    if (santaX < -200)
    {
      santaX = SCREEN_WIDTH;
      waitForSanta = 100;
      snowSpeed = 30 + rand() % 100;
    }
    
  }
}

void drawBase() {
  drawMoon();
  drawChristmasTree();
  initSnowflakes();
}

void fillCircle(int x, int y, int radius, uint16_t color)
{
  tft.fillCircle(x, y, radius, color);
}

void fillRect(int x, int y, int w, int h, uint16_t color)
{
  tft.fillRect(x, y, w, h, color);
}

void drawRect(int x, int y, int w, int h, uint16_t color)
{
  tft.drawRect(x, y, w, h, color);
}


void drawPixel(int x, int y, uint16_t color)
{
  tft.drawPixel(x, y, color);
}

void getPixels(int x, int y, uint16_t * block, int w, int h)
{
  tft.readGRAM(x, y, block, w, h);
}

void printPos(int x, int y)
{
  Serial.print("Snow POS: ");
  Serial.print(x);
  Serial.print(":");
  Serial.println(y);
}
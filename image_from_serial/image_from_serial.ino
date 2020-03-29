
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
int Width;
int Height;
uint16_t ID;
int old_X;
int old_Y;
uint8_t Orientation = 0;    //PORTRAIT

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  tft.reset();
  ID = tft.readID();
  tft.begin(ID);

  tft.setRotation(Orientation);
  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay(true);

  Width = tft.width();
  Height = tft.height();

  Serial.write(255);

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
}

uint16_t color = 0;
uint8_t actionType = 8;


void loop() {
  if (actionType == 0) {
    
//    if (Serial.available()) {
//      actionType = Serial.read();
//    }

  } else if (actionType == 8) {
    byPixel8();
  } else if (actionType == 7) {
    byPixel();
  }
}


void drawBitmap(int x, int y, int sx, int sy, const uint16_t *data, int scale = 1) {
  uint16_t color;
  tft.setAddrWindow(x, y, x + sx * scale - 1, y + sy * scale - 1);
  if (scale == 1) tft.pushColors((const uint8_t*)data, sx * sy, 1);
  else {
    for (int row = 0; row < sy; row++) {
      for (int col = 0; col < sx; col++) {
        color = pgm_read_word(data + (row * sx + col) * 1);
        tft.fillRect(x + col * scale, y + row * scale, scale, scale, color);
      }
    }
  }
}


void byPixel() {
  while (Serial.available()) {
    uint16_t  x, y;
    uint8_t *bytes;
    size_t n = Serial.readBytes(bytes, 8);
    if (n != 8) {
      continue;
    }

    if (bytes[0] != 255) {
      continue;
    }
    x =  ( bytes[1] <<  8) |  bytes[2];
    y =  ( bytes[3] <<  8) |  bytes[4];
    color = tft.color565( bytes[5],  bytes[6],  bytes[7]);

    tft.fillRect(x, y, 1, 1, color);
  }
}

char buf2[25];

uint16_t rgb233ToRGB565(uint8_t value) {

  uint8_t r, g, b;

  r = value & 0b11100000;
  r = r >> 5;
  r = r * 31;

  g = value & 0b00011100;
  g = g >> 2;

  g = g * 31;

  b = value & 0b00000011;
  b = b * 63;

  //  r = (((value & 0b11100000) >> 5)) * 31;
  //  g = (((value & 0b00011100) >> 2)) * 31;
  //  b = (value & 0b00000011) * 63;

  //   snprintf(buf2, 25, "Color:%.3d %.3d %.3d %.3d", r, g, b, value);
  //   Serial.write(buf2);
  //  return value;
  return tft.color565(r, g, b);
}


//uint16_t y = 0;
uint8_t readedBytes = 0;
uint8_t *byPixel8Bytes = new uint8_t[242];

void byPixel8() {
  if (Serial.available()) {
    byPixel8Bytes[readedBytes] = Serial.read();
    if (byPixel8Bytes[0] == 255 || byPixel8Bytes[0] == 254) {
      readedBytes++;
    }
  }
  if (readedBytes >= 242) {
    uint16_t y = ((byPixel8Bytes[0] & 0x1) << 8 ) | byPixel8Bytes[1];

    for (uint8_t x = 0; x < 240; x++) {
      color = rgb233ToRGB565(byPixel8Bytes[x]);
      tft.fillRect(x, y, 1, 1, color);
    }
    //    delete bytes;
    //    bytes = new uint8_t[240];
    readedBytes = 0;
  }
}

#include <Adafruit_GFX.h>
#include <RTClib.h>
#include <MCUFRIEND_kbv.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <OneWire.h>
#include "bitmaps.h"
#include "fonts.h"
// #include "memdebug.h"

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
int16_t BOTTOM_PANEL = 42;
#define TEXT_SIZE 5
const uint16_t digitSize = TEXT_SIZE * 6;
#define Orientation 1 // PORTRAIT

// const char dateFormat[] PROGMEM = "%04d/%02d/%02d %02d:%02d:%02d";
const char dateFormat[] PROGMEM = "%02d/%02d %02d:%02d:%02d";
const char timeFormat[] PROGMEM = "%02d:%02d:%02d";
uint16_t lastSecond = 0;
uint16_t lastMinute = -1;
uint16_t timeTextColor = 0;
long lastSecondForTemp;
long lastMiliSecond;

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
  GFXfont i;

  Serial.begin(9600);

  tft.reset();
  tft.begin(tft.readID()); // 37696
  tft.setRotation(Orientation);
  tft.fillScreen(TFT_BLACK);
  // tft.invertDisplay(true);
  tft.setTextSize(TEXT_SIZE);
  tft.setTextWrap(false);
  // tft.setFont(&digital_7__mono_12pt7b);

  dht.begin();
}

bool needToDrawTepmlates = true;

void loop()
{
  if (needToDrawTepmlates)
  {
    drawTemplates();
    prepareSnake();
    needToDrawTepmlates = false;
  }

  showTime();

  if (millis() / 1000 % 60 != lastSecondForTemp)
  {
    lastSecondForTemp = millis() / 1000 % 60;

    drawLocalTemp();

    drawScreenRect();
  }

  if (millis() / 100 % 60 != lastMiliSecond) {
    lastMiliSecond = millis() / 100 % 60;
    drawSnake();
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

void drawLocalTemp()
{
  // printFreeRAM(F("on start printLocalTemp %d"));
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float hum = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temp = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temp))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float oneWireTemp = getOneWireTemp();

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

  if (oldValues[2] != oneWireTemp)
  {
    oldValues[2] = oneWireTemp;
    drawSensorValue(oneWireTemp, TFT_GREENYELLOW, 2);
  }
  
  // printFreeRAM(F("on end printLocalTemp %d"));
}

void drawTemplates()
{
  drawSensorTemplate(TFT_BLUE, humBitmapArray48, 0);
  drawSensorTemplate(TFT_GREEN, tempBitmapArray48, 1);
  drawSensorTemplate(TFT_GREENYELLOW, tempBitmapArray48, 2);
}

void drawSensorTemplate(uint16_t color, const uint8_t *bitmap, uint8_t line)
{
  const uint16_t bitmapSizeX = 48;
  const uint16_t bitmapSizeY = 48;
  const uint16_t bitmapPositionX = 140;
  const uint16_t bitmapPositionY = 16;

  tft.setTextColor(color, color);
  tft.drawBitmap(bitmapPositionX, bitmapPositionY + (bitmapSizeY + 8)* line, bitmap, bitmapSizeX, bitmapSizeY, color);
}

void drawSensorValue(float value, uint16_t color, uint8_t line)
{
  const uint16_t cursorOffsetX = 188;
  const uint16_t cursorOffsetY = 24;
  const uint16_t boxPositionX = cursorOffsetX;
  const uint16_t boxPositionY = 24;
  const uint16_t boxSizeX = 120;
  const uint16_t boxSizeY = 36;
  const uint16_t textOffset = 19;

  char *textBuffer = new char[5];
  const char *text = "%d.%d";

  sprintf(textBuffer, text, uint16_t((value * 10) / 10), uint16_t(uint16_t(value * 10) % 10));

  tft.fillRect(boxPositionX, boxPositionY + (boxSizeY + textOffset) * line, boxSizeX, boxSizeY, TFT_BLACK);
  tft.setTextColor(color, color);
  tft.setCursor(cursorOffsetX, cursorOffsetY + (boxSizeY + textOffset) * line);
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

  showEyes();

  uint8_t positionX = 40;
  uint8_t positionY = tft.height() - BOTTOM_PANEL;


  if (lastMinute == current.minute())
  {
    // re-draw second only
    const uint16_t secondPositionX = positionX + 6 * digitSize;
    const uint16_t secondSizeX = 2 * digitSize;
    
    tft.setTextColor(timeTextColor, timeTextColor);
    tft.setCursor(secondPositionX, positionY);
    char *textBuffer = new char[2];
    sprintf(textBuffer, "%02d", current.second());
    tft.fillRect(secondPositionX, positionY, secondSizeX, digitSize * 6/5, TFT_BLACK);
    tft.print(textBuffer);
    delete textBuffer;

    return;
  }
  lastMinute = current.minute();

  char *textBuffer = new char[20];
  sprintf_P(textBuffer, timeFormat, current.hour(), current.minute(), current.second());

  timeTextColor = uint16_t((millis() * 10) % 65535);
  tft.setTextColor(timeTextColor, timeTextColor);
  tft.setCursor(positionX, positionY);

  tft.fillRect(positionX, positionY, digitSize * 8, digitSize * 6/5, TFT_BLACK);
  tft.print(textBuffer);
  delete textBuffer;
  // printFreeRAM(F("Free memory show time is: %d"));
}

void drawScreenRect()
{
  uint16_t offset = 1;
  uint8_t thickness = 4;

  uint16_t textColor = uint16_t((millis() * 10) % 65535);

  // draw top line
  tft.fillRect(offset, offset, tft.width() - offset * 2, thickness, textColor);
  // draw left line
  tft.fillRect(offset, offset, thickness, tft.height() - offset * 2, textColor);
  // draw bottom line
  tft.fillRect(offset, tft.height() - offset - 3, tft.width() - offset * 2, thickness, textColor);
  // draw right line
  tft.fillRect(tft.width() - offset - 3, offset, thickness, tft.height() - offset * 2, textColor);
  
  const uint16_t bottomLineOffset = 3;
  const uint16_t bottomLineY = tft.height() - BOTTOM_PANEL - thickness - bottomLineOffset;
  tft.fillRect(0, bottomLineY, tft.width(), thickness, textColor);

  // const uint16_t bottomLineOffset = 3;
  // const uint16_t bottomLineX = 40 - thickness - bottomLineOffset;
  // const uint16_t bottomLineY = tft.height() - BOTTOM_PANEL-thickness -bottomLineOffset;
  // const uint16_t bottomLineWidth = digitSize * 8 + bottomLineOffset * 2;
  // tft.fillRect(bottomLineX, bottomLineY, bottomLineWidth + thickness, thickness, textColor);
  // tft.fillRect(bottomLineX, bottomLineY, thickness, BOTTOM_PANEL+ thickness, textColor);
  // tft.fillRect(bottomLineX + bottomLineWidth+ bottomLineOffset, bottomLineY, thickness, BOTTOM_PANEL+ thickness, textColor);
}


const uint8_t image_data_EYES_arrays_size = 3;
const uint8_t* image_data_EYES_arrays[image_data_EYES_arrays_size] = {
    image_data_EYES_FRONTarray,
    // image_data_EYES_MIDDLEarray,
    // image_data_EYES_NARROWarray,
    // image_data_EYES_WIDEarray,
    image_data_EYES_GLAREarray,
    // image_data_EYES_CROSSEDarray,
    // image_data_EYES_DOWNarray,
    // image_data_EYES_UParray,
    // image_data_EYES_RIGHTarray,
    // image_data_EYES_RIGHT_DOWNarray,
    // image_data_EYES_RIGHT_UParray,
    // image_data_EYES_LEFTarray,
    // image_data_EYES_LEFT_DOWNarray,
    // image_data_EYES_LEFT_UParray,
    image_data_CONFUSSED_1array,
    // image_data_CONFUSSED_2array,
    //image_data_EYES_DISTRESSEDarray,
    // image_data_EYES_CRYarray,
    // image_data_EYES_MADarray,
    // image_data_EYES_GLASSESarray,
    // image_data_EYES_SLEEParray,
    // image_data_BLINK_UPPERarray,
    // image_data_EYES_TIREDarray,
    // image_data_EYES_NIGHTarray,
    // image_data_UPPER_LIDSarray,
    // image_data_LOWER_LIDSarray,
};

void showEyes()
{
  const uint8_t index = lastSecond % image_data_EYES_arrays_size;
  const uint8_t *bitmap = image_data_EYES_arrays[index];
  // Serial.print("Draw eyes with index ");
  // Serial.println(index);
  // tft.fillRect(15, 25, 128, 64, TFT_BLACK);

  const uint16_t boxPositionX = 15;
  const uint16_t boxPositionY = 15;
  const uint16_t boxSizeX = 128;
  const uint16_t boxSizeY = 64;
  const uint16_t roundRadius = 32;

  tft.fillRoundRect(boxPositionX, boxPositionY, boxSizeX , boxSizeY, roundRadius, TFT_MAROON);
  tft.fillRoundRect(boxPositionX + 20, boxPositionY+8, 35, 50, 64, TFT_BLUE);
  tft.fillRoundRect(boxPositionX + 73, boxPositionY+8, 35, 50, 64, TFT_BLUE);
  tft.drawBitmap(boxPositionX, boxPositionY, bitmap, boxSizeX, boxSizeY, TFT_YELLOW);
  tft.drawRoundRect(boxPositionX, boxPositionY, boxSizeX, boxSizeY, roundRadius, TFT_RED);
}


const uint16_t snakeFieldPosX = 32;
const uint16_t snakeFieldPosY = 88;
const uint16_t snakeFieldSizeX = 96;
const uint16_t snakeFieldSizeY = 96;
const uint16_t snakeThickness = 8;
const uint8_t snakeFieldSize = snakeFieldSizeX / snakeThickness - 1;
const uint8_t snakeFieldSquare = snakeFieldSize * snakeFieldSize;
const size_t maxSnakeSize = 50;
uint16_t snakePoints[maxSnakeSize] = {0,1,2};
size_t snakeSize = 3;
uint16_t foodPosition = 0;

void prepareSnake() {
  for (size_t i = 0; i < 4; i++)
  {
    tft.drawRect(snakeFieldPosX+i-4, snakeFieldPosY+i-4, snakeFieldSizeX-i*2+4, snakeFieldSizeY-i*2+4, TFT_WHITE);
  }
}

void drawSnake() {
  if (foodPosition == 0) {
    // find new food position
    newFoodPosition:
      foodPosition = uint16_t((millis() / 10) % snakeFieldSquare);
      for (size_t i = 0; i < snakeSize; i++)
      {
        if (foodPosition == snakePoints[i] && foodPosition == 0) {
          goto newFoodPosition;
        }
      }
      // 48 -> 25 + 13 -> x=1, y=3
  }

  // snake move
  if (snakeSize == 50) {
    // truncate snake to begin size;
    snakeSize = 3;
  }
  Serial.print("food postion: ");
  Serial.println(foodPosition);
  Serial.print("snakeFieldSquare ");
  Serial.println(snakeFieldSquare);
  Serial.print("snake ");
  Serial.print(snakeSize);
  Serial.print(": ");
  for (size_t i = 0; i < snakeSize; i++)
  {
    Serial.print(snakePoints[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  if (snakePoints[snakeSize-1] == foodPosition) {
    // snake got a food.
    Serial.println("snake got a food");
    snakePoints[snakeSize] = foodPosition+1;
    foodPosition = 0;
    snakeSize++;
  } else {
    // snake moving.
    for (size_t i = 0; i < snakeSize-1; i++)
    {
      snakePoints[i] = snakePoints[i+1];
    }
    uint16_t newSnakePoint = snakePoints[snakeSize-1] + 1;
    if (newSnakePoint > snakeFieldSquare - 1) {
      newSnakePoint = 0;
    }
    snakePoints[snakeSize-1] = newSnakePoint;
  }

  // prepare screen
  tft.fillRect(snakeFieldPosX, snakeFieldPosY, snakeFieldSizeX-snakeThickness, snakeFieldSizeY-snakeThickness, TFT_BLACK);
  // draw food
  uint16_t foodPosX = snakeFieldPosX + (foodPosition / snakeFieldSize) * snakeThickness;
  uint16_t foodPosY = snakeFieldPosY + (foodPosition % snakeFieldSize) * snakeThickness;
  tft.drawRect(foodPosX + 1, foodPosY + 1, snakeThickness - 1, snakeThickness -1, TFT_GREEN);
  tft.drawRect(foodPosX + 2, foodPosY + 2, snakeThickness - 2, snakeThickness -2, TFT_GREEN);
  tft.drawRect(foodPosX + 3, foodPosY + 3, snakeThickness - 3, snakeThickness -3, TFT_GREEN);
  // draw snake
  for (size_t i = 0; i < snakeSize; i++)
  {
    uint16_t snakePosX = snakeFieldPosX + (snakePoints[i] / snakeFieldSize) * snakeThickness;
    uint16_t snakePosY = snakeFieldPosY + (snakePoints[i] % snakeFieldSize) * snakeThickness;
    tft.drawRect(snakePosX + 1, snakePosY + 1, snakeThickness - 1, snakeThickness -1, TFT_DARKGREY);
    tft.drawRect(snakePosX + 2, snakePosY + 2, snakeThickness - 2, snakeThickness -2, TFT_DARKGREEN);
  }
}


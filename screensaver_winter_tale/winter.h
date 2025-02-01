#ifndef WINTER_H
#define WINTER_H

#include <stdint.h>

// Constants
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Colors
#define WHITE 0xFFFF
#define GREEN 0x07E0
#define RED   0xF800
#define YELLOW 0xFFE0
#define BLUE  0x001F
#define BROWN 0x8A22
#define BLACK 0x0000
#define GOLD  0xFFD700FF

// Platform-specific rendering functions
void fillCircle(int x, int y, int radius, uint16_t color);
void fillRect(int x, int y, int w, int h, uint16_t color);
void drawRect(int x, int y, int w, int h, uint16_t color);
void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t color);
void drawPixel(int x, int y, uint16_t color);
void getPixels(int x, int y, uint16_t * block, int w, int h);
void printPos(int x, int y);

// Initialization functions
void initSnowflakes(void);

// Abstract drawing functions
void drawMoon(void);
void drawSanta(int x, int lastX);
void drawChristmasTree(void);
void drawTwinklingLights(void);
void drawGifts(void);
void drawSnow(void);

#endif // WINTER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "winter.h"
#include "bitmap.h"
#include <stdio.h>

// Snowflake data
typedef struct {
    int x, y;
    uint16_t snowflakeOldValue[SNOWFLAKE_HEIGHT * SNOWFLAKE_WIDTH];
} Snowflake;

#define MAX_SNOW_HEIGHT (TREE_HEIGHT)
uint16_t snowHeight;

#define SNOW_FLAKES_COUNT 10
Snowflake snowflakes[SNOW_FLAKES_COUNT];

int generateNewSnowFlakePosition()
{
    int x;
again:
    x = rand() % (SCREEN_WIDTH -1) + 1;
    for (int i = 0; i < SNOW_FLAKES_COUNT; i++)
    {
        if (x >= snowflakes[i].x - SNOWFLAKE_WIDTH && x <= snowflakes[i].x + SNOWFLAKE_WIDTH)
        {
            goto again;
        }
    }
    return x;
}

void initSnowflakes(void) {
    for (int i = 0; i < SNOW_FLAKES_COUNT; i++)
    {
        snowflakes[i].x = generateNewSnowFlakePosition();
        snowflakes[i].y = rand() % SCREEN_HEIGHT;
    }
}

void drawMoon(void) {
    fillCircle(SCREEN_WIDTH - 30, 27, 20, WHITE); // Full moon
    fillCircle(SCREEN_WIDTH - 35, 32, 17, BLACK); // Crescent shadow
}

// RGB565 Color Definitions
#define COLOR_BLACK         0x0000  // Black
#define COLOR_DARK_BROWN    0x7B4B  // Dark Brown Shade
#define COLOR_MEDIUM_BROWN  0x83EC  // Medium Brown Shade
#define COLOR_LIGHT_BROWN   0x8BFC  // Light Brown Shade
#define COLOR_DARK_GRAYISH  0xAB6B  // Dark Grayish Brown
#define COLOR_GRAYISH_BROWN 0xAB6C  // Grayish Brown Shade
#define COLOR_BEIGE         0xE63B  // Beige/Tan
#define COLOR_LIGHT_BEIGE   0xE63C  // Light Beige
#define COLOR_VERY_LIGHT_TAN 0xEE5B // Very Light Tan
#define COLOR_ALMOST_WHITE  0xEE5C  // Almost White
#define COLOR_WHITE         0xFFFF  // White

void drawDeer(int startX, int startY) {
    for (int y = 0; y < DEER_HEIGHT; y++) {
        for (int x = 0; x < DEER_WIDTH; x++) {
            #if defined(__AVR__) || defined(ARDUINO)
                uint16_t color = pgm_read_word(&deerBitmap[y][DEER_WIDTH - x - 1]);
            #else
                uint16_t color = deerBitmap[y][DEER_WIDTH - x - 1];
            #endif
            if (color == WHITE) {
                color = BLACK;
                // continue;
            }
            drawPixel(startX + x, startY + y, color);
        }
    }
}

void drawSantaWithSled(int startX, int startY) {
    for (int y = 0; y < SANTA_HEIGHT; y++) {
        for (int x = 0; x < SANTA_WIDTH; x++) {
            #if defined(__AVR__) || defined(ARDUINO)
                uint16_t color = pgm_read_word(&santaBitmap[y][SANTA_WIDTH - x - 1]);
            #else
                uint16_t color = santaBitmap[y][SANTA_WIDTH - x - 1];
            #endif
            if (color == WHITE) {
                color = BLACK;
                //continue;
            }
            drawPixel(startX + x, startY + y, color);
        }
    }
}

void drawTree(int startX, int startY) {
    for (int y = 0; y < TREE_HEIGHT; y++) {
        for (int x = 0; x < TREE_WIDTH; x++) {
            #if defined(__AVR__) || defined(ARDUINO)
                uint16_t color = pgm_read_word(&treeBitmap[y][x]);
            #else
                uint16_t color = treeBitmap[y][x];
            #endif
            if (color == WHITE) {
                continue;
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    drawPixel(startX + x*3+i, startY + y*3+j, color);
                }
            }
        }
    }
}

void drawSnowflake(int startX, int startY) {
    for (int y = 0; y < SNOWFLAKE_HEIGHT; y++) {
        for (int x = 0; x < SNOWFLAKE_WIDTH; x++) {
            #if defined(__AVR__) || defined(ARDUINO)
                uint16_t color = pgm_read_word(&snowflakeBitmap[y][x]);
            #else
                uint16_t color = snowflakeBitmap[y][x];
            #endif
            if (color == BLACK) {
                continue;
            }
            drawPixel(startX + x, startY + y, color);
        }
    }
}

void drawSanta(int x, int lastX) {
    int topOffset = 50;
    // Erase the previous frame

    // --- Draw Reindeers ---
    for (int i = 0; i < 2; i++) {
        // fillRect(lastX+(i * 40)-8, topOffset, 40, 32, 0x0000); // Erase previous scene section
        fillRect(lastX+(i * 40)-8+DEER_WIDTH, topOffset, 40-DEER_WIDTH, 32, 0x0000); // Erase previous scene section
        drawDeer(x + (i * 40), topOffset);
        drawRect(x + (i * 40) + 11, 12+topOffset, 7, 1, 0xFFFF);
        drawRect(x + (i * 40) + 16, 11+topOffset, 5, 1, 0xFFFF);
        drawRect(x + (i * 40) + 20, 12+topOffset, 20, 1, 0xFFFF);
        
        for (int j = 0; j < 4; j++) { 
            drawRect(x + (i * 40) + 12-j*2, 12+j+topOffset, 2, 1, 0xFFFF);
        }
    }

    fillRect(x+80+SANTA_WIDTH, topOffset, lastX-x, 35, 0x0000); // Erase previous scene section
    drawSantaWithSled(x+80, topOffset+3);
}

void drawGifts(void) {
    return;
    // Gift 1
    fillRect(70, 210, 30, 20, RED);
    drawRect(70, 210, 30, 20, WHITE);
    drawRect(83, 210, 4, 20, WHITE);
    fillCircle(85, 215, 3, WHITE);

    // Gift 2
    fillRect(140, 210, 40, 20, BLUE);
    drawRect(140, 210, 40, 20, WHITE);
    drawRect(160, 210, 4, 20, WHITE);
    fillCircle(162, 215, 3, WHITE);

    // Gift 3
    fillRect(220, 210, 30, 20, GREEN);
    drawRect(220, 210, 30, 20, YELLOW);
    drawRect(233, 210, 4, 20, YELLOW);
    fillCircle(235, 215, 3, YELLOW);
}

void drawSnow(void) {
    for (int i = 0; i < SNOW_FLAKES_COUNT; i++) {

        if (snowflakes[i].y >= 0)
        {
            for (int si = 0; si < SNOWFLAKE_WIDTH; si++)
            {
                for (int sj = 0; sj < SNOWFLAKE_HEIGHT; sj++)
                {
                    if (snowflakes[i].y + sj >= SCREEN_HEIGHT || snowflakes[i].y + sj < 0) {
                        continue;
                    }
                    uint16_t color = snowflakes[i].snowflakeOldValue[sj * SNOWFLAKE_WIDTH + si];
                    drawPixel(snowflakes[i].x + si, snowflakes[i].y + sj, color);
                  
                }
            }
        }

        snowflakes[i].y += 9;

        // store previous pixels.
        uint16_t block[SNOWFLAKE_WIDTH * SNOWFLAKE_HEIGHT];
        getPixels(snowflakes[i].x, snowflakes[i].y, block, SNOWFLAKE_WIDTH, SNOWFLAKE_HEIGHT);
        for (int j = 0; j < SNOWFLAKE_WIDTH * SNOWFLAKE_HEIGHT; j++) {
           snowflakes[i].snowflakeOldValue[j] = block[j];
        }
        
        

        if (snowflakes[i].y > SCREEN_HEIGHT-snowHeight) {
            snowflakes[i].y = 0;
            snowflakes[i].x = generateNewSnowFlakePosition();
            for (int k = 0; k < SNOWFLAKE_HEIGHT*SNOWFLAKE_WIDTH; k++)
            {
                snowflakes[i].snowflakeOldValue[k] = BLACK;
            }
            
            snowHeight++;
        } else {
            drawSnowflake(snowflakes[i].x, snowflakes[i].y);
        }

        if (snowHeight < MAX_SNOW_HEIGHT)
        {
            fillRect(0, SCREEN_HEIGHT - snowHeight, SCREEN_WIDTH, 5, WHITE);
        }
        else
        {
            fillRect(0, SCREEN_HEIGHT - snowHeight, SCREEN_WIDTH, snowHeight, BLACK);
            drawChristmasTree();
            snowHeight = 2;
        }
    }
}


// Tree dimensions
#define TREE_HEIGHT 140
#define NUM_LAYERS  5

// Tree color definitions (RGB565)
#define COLOR_GREEN_LIGHT   0x07FF
#define COLOR_GREEN_MID     0x07E0
#define COLOR_GREEN_DARK    0x03E0
#define COLOR_TRUNK_BROWN   0x8C22
#define COLOR_BACKGROUND    0x0000


// Green shades for tree layers
const uint16_t GREEN_SHADES[NUM_LAYERS] = {
    COLOR_GREEN_LIGHT,
    COLOR_GREEN_MID,
    COLOR_GREEN_DARK,
    COLOR_GREEN_MID,
    COLOR_GREEN_LIGHT
};


void drawTriangle(int x0, int y0, int width, int height, uint16_t color) {
    fillTriangle(x0, y0, x0 - width / 2, y0 + height, x0 + width / 2, y0 + height, color);
}

// Draw a Christmas tree with dynamic layers

// Function to calculate RGB565 color for gradient based on row
uint16_t calculateGradientColor(int row, int totalRows) {
    int greenIntensity = 63 - (row * 63 / totalRows);  // Gradually darken green
    return (greenIntensity << 5);  // RGB565 green component
}

// Function to draw a triangle row by row for a gradient effect
void drawGradientTriangle(int x0, int y0, int width, int height, int totalRows) {
    for (int row = 0; row < height; row++) {
        int rowWidth = width - (row * width / height);  // Triangle width decreases with each row
        uint16_t color = calculateGradientColor(row, totalRows);
        drawRect(x0 - rowWidth / 2, y0 + row, rowWidth, 1, color);  // Draw a row of the triangle
    }
}

// Draw the top star
void drawStar(int x0, int y0, int size) {
    uint16_t yellowColor = 0xFFE0;  // Yellow color in RGB565
    drawTriangle(x0, y0, size, size, yellowColor);
}

// Draw the Christmas tree with layered gradient triangles
void drawChristmasTree() {
    int startX = 10;
    int startY = 90;

    drawTree(startX, startY);
}

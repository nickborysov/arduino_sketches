#include "./../winter.h"
#include <SDL2/SDL.h>

SDL_Renderer *renderer;

// Converts a 16-bit RGB565 color to a 32-bit RGBA8888 color
int convertColor(int color) {
    int r = (color >> 11) & 0x1F; // Extract red (5 bits)
    int g = (color >> 5) & 0x3F;  // Extract green (6 bits)
    int b = color & 0x1F;         // Extract blue (5 bits)

    // Expand RGB565 to 8-bit values
    r = (r << 3) | (r >> 2);
    g = (g << 2) | (g >> 4);
    b = (b << 3) | (b >> 2);

    return (r << 24) | (g << 16) | (b << 8) | 0xFF; // RGBA8888
}

void fillCircle(int x, int y, int radius, uint16_t color) {
    int rgbaColor = convertColor(color); // Convert RGB565 to RGBA8888
    int r = (rgbaColor >> 24) & 0xFF;
    int g = (rgbaColor >> 16) & 0xFF;
    int b = (rgbaColor >> 8) & 0xFF;
    int a = rgbaColor & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // SDL_SetRenderDrawColor(renderer, (color >> 11) & 0xFF, (color >> 5) & 0xFF, color & 0xFF, 255);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void fillRect(int x, int y, int w, int h, uint16_t color) {
    int rgbaColor = convertColor(color); // Convert RGB565 to RGBA8888
    int r = (rgbaColor >> 24) & 0xFF;
    int g = (rgbaColor >> 16) & 0xFF;
    int b = (rgbaColor >> 8) & 0xFF;
    int a = rgbaColor & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // SDL_SetRenderDrawColor(renderer, (color >> 11) & 0xFF, (color >> 5) & 0xFF, color & 0xFF, 255);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void drawRect(int x, int y, int w, int h, uint16_t color) {
    int rgbaColor = convertColor(color); // Convert RGB565 to RGBA8888
    int r = (rgbaColor >> 24) & 0xFF;
    int g = (rgbaColor >> 16) & 0xFF;
    int b = (rgbaColor >> 8) & 0xFF;
    int a = rgbaColor & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // SDL_SetRenderDrawColor(renderer, (color >> 11) & 0xFF, (color >> 5) & 0xFF, color & 0xFF, 255);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}

void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t color) {
    int rgbaColor = convertColor(color); // Convert RGB565 to RGBA8888
    int r = (rgbaColor >> 24) & 0xFF;
    int g = (rgbaColor >> 16) & 0xFF;
    int b = (rgbaColor >> 8) & 0xFF;
    int a = rgbaColor & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // SDL_SetRenderDrawColor(renderer, (color >> 11) & 0xFF, (color >> 5) & 0xFF, color & 0xFF, 255);
    for (int y = y1; y <= y3; y++) {
        int xa = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        int xb = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
        if (xa > xb) {
            int temp = xa;
            xa = xb;
            xb = temp;
        }
        for (int x = xa; x <= xb; x++) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void drawPixel(int x, int y, uint16_t color) {
    int rgbaColor = convertColor(color); // Convert RGB565 to RGBA8888
    int r = (rgbaColor >> 24) & 0xFF;
    int g = (rgbaColor >> 16) & 0xFF;
    int b = (rgbaColor >> 8) & 0xFF;
    int a = rgbaColor & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    // SDL_SetRenderDrawColor(renderer, (color >> 11) & 0xFF, (color >> 5) & 0xFF, color & 0xFF, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

// Helper function to convert ARGB8888 to RGB565
uint16_t ARGB8888_to_RGB565(uint32_t pixel) {
    uint8_t r = (pixel >> 16) & 0xFF;
    uint8_t g = (pixel >> 8) & 0xFF;
    uint8_t b = (pixel) & 0xFF;

    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

// Function to get pixel data in RGB565 format
void getPixels(int x, int y, uint16_t *block, int w, int h) {
    // Ensure the renderer and window exist
    extern SDL_Renderer *renderer;  // SDL_Renderer should be defined globally

    // Allocate a buffer to hold pixel data in 32-bit format
    uint32_t *pixelBuffer = (uint32_t *)malloc(w * h * sizeof(uint32_t));
    if (!pixelBuffer) {
        fprintf(stderr, "Failed to allocate pixel buffer\n");
        return;
    }

    // Define the rectangle to read
    SDL_Rect rect = { x, y, w, h };

    // Read pixels from the renderer in ARGB8888 format
    if (SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ARGB8888, pixelBuffer, w * sizeof(uint32_t)) != 0) {
        fprintf(stderr, "Failed to read pixels: %s\n", SDL_GetError());
        free(pixelBuffer);
        return;
    }

    // Convert pixels to RGB565 and store them in the provided block
    for (int i = 0; i < w * h; i++) {
        block[i] = ARGB8888_to_RGB565(pixelBuffer[i]);
    }

    // Free the temporary pixel buffer
    free(pixelBuffer);
}

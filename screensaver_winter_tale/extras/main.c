#include "./../winter.h"
#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Initialization failed: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Winter Scene", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH*3, SCREEN_HEIGHT*3, SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


    initSnowflakes();

    int running = 1;
    int santaX = SCREEN_WIDTH;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = 0; // Exit the loop on ESC key press
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMoon();
        drawChristmasTree();
        drawGifts();
        
        drawSnow();
        drawSanta(santaX, santaX + 5);

        santaX -= 5;
        if (santaX < -100) {
            santaX = SCREEN_WIDTH;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

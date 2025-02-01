#/bin/sh

gcc main.c macos_render.c ../winter.c -o winter_app \
  -I/opt/homebrew/Cellar/sdl2/2.30.10/include \
  -I./../ \
  -L/opt/homebrew/Cellar/sdl2/2.30.10/lib \
  -lSDL2


#ifndef GUI_GUARD
#define GUI_GUARD
#include "defs.h"
#include "game.h"
#include "SDL2/SDL.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} App;

int gui_main(int argc, char **argv);

#endif // GUI_GUARD

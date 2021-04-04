#ifndef GUI_GUARD
#define GUI_GUARD
#include "defs.h"
#include "SDL2/SDL.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

#endif // GUI_GUARD

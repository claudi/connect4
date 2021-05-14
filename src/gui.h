#ifndef GUI_GUARD
#define GUI_GUARD
#include "defs.h"
#include "game.h"

#ifndef HEADLESS
#include "SDL2/SDL.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} App;

App *initSDL(void);
void freeSDL(App *app);

void render(App *app, Game *game);
void update(App *app);

#endif // HEADLESS
#endif // GUI_GUARD
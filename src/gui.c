#include "gui.h"

#ifndef HEADLESS

App *initSDL(void) {
    App *app = malloc(sizeof(App));
    *app = (App) { NULL, NULL };

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Couldn't initialize SDL: %s\n", SDL_GetError());
        freeSDL(app);
        return NULL;
    }

    const char windowName[10] = "Connect 4";
    const int windowFlags = 0;
    app->window = SDL_CreateWindow(windowName,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            windowFlags);

    if(app->window == NULL) {
        SDL_Log("ERROR: Failed to open %d x %d window: %s\n",
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_GetError());
        freeSDL(app);
        return NULL;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    const int index = -1;
    const int rendererFlags = SDL_RENDERER_ACCELERATED;
    app->renderer = SDL_CreateRenderer(app->window, index, rendererFlags);

    if(app->renderer == NULL) {
        SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
        freeSDL(app);
        return NULL;
    }

    return app;
}

void freeSDL(App *app) {
    SDL_Log("Shutting down SDL\n");
    SDL_DestroyWindow(app->window);
    SDL_DestroyRenderer(app->renderer);
	SDL_Quit();
}

#endif // HEADLESS

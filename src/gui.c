#include "defs.h"
#include "game.h"
#include "gui.h"
#include "SDL2/SDL.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} App;

static App *initSDL(void);
static void freeSDL(App *app);

static void render(App *app, Game *game);
static void update(App *app);

static App *initSDL(void) {
    App *app = malloc(sizeof(App));
    *app = (App) { NULL, NULL };

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("ERROR: Couldn't initialize SDL: %s\n", SDL_GetError());
        freeSDL(app);
        return NULL;
    }

    const char windowName[10] = "Connect 4";
    const int windowFlags = 0;
    app->window = SDL_CreateWindow(
            windowName,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            windowFlags);

    if(app->window == NULL) {
        SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "Failed to open %d x %d window: %s\n",
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_GetError());
        freeSDL(app);
        return NULL;
    }

    const char value[2] = "1"; // Enable vsync
    SDL_bool hints = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, value);
    if(hints != SDL_TRUE) {
        SDL_LogWarn(
                SDL_LOG_CATEGORY_APPLICATION,
                "Failed to set hint: SDL_HINT_RENDER_SCALE_QUALITY = %s\n",
                value);
    }

    const int index = -1; // the first rendering driver supporting the requested flags
    const int rendererFlags = SDL_RENDERER_ACCELERATED; // the renderer uses hardware acceleration
    app->renderer = SDL_CreateRenderer(app->window, index, rendererFlags);

    if(app->renderer == NULL) {
        SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "Failed to create renderer: %s\n",
                SDL_GetError());
        freeSDL(app);
        return NULL;
    }

    return app;
}

static void freeSDL(App *app) {
    SDL_Log("Shutting down SDL\n");
    SDL_DestroyWindow(app->window);
    SDL_DestroyRenderer(app->renderer);
	SDL_Quit();
}

static void render(App *app, Game __attribute__((unused)) *game) {
    SDL_SetRenderDrawColor(app->renderer, 0, 100, 100, 100);
    SDL_RenderClear(app->renderer);

    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
    for(size_t iter = 0; iter < BOARD_SIZE - 1; iter++) {
        SDL_RenderDrawLine(
                app->renderer,
                0,
                (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / BOARD_SIZE) * (iter - (BOARD_SIZE - 1) / 2),
                SCREEN_WIDTH,
                (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / BOARD_SIZE) * (iter - (BOARD_SIZE - 1) / 2));
        SDL_RenderDrawLine(
                app->renderer,
                (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / BOARD_SIZE) * (iter - (BOARD_SIZE - 1) / 2),
                0,
                (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / BOARD_SIZE) * (iter - (BOARD_SIZE - 1) / 2),
                SCREEN_HEIGHT);
    }
}

static void update(App *app) {
    SDL_RenderPresent(app->renderer);
}

int gui_main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv) {
    App *app = initSDL();
    if(app == NULL) {
        return EXIT_FAILURE;
    }
    SDL_Log("SDL Successfully initialised\n");

    render(app, NULL);
    update(app);

    freeSDL(app);
    return EXIT_SUCCESS;
}


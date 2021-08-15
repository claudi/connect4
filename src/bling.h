#ifndef BLING_GUARD
#define BLING_GUARD
#include "defs.h"
#include "board.h"
#include "game.h"
#include "minimax.h"
#include <stdio.h>

#define GB_SCREEN_W 18
#define GB_SCREEN_H 10
#define SIDE_W 25
#define SIDE_H 9
#define CREDITS_W 28

#ifdef __linux__
#define COLOR_ON  "\033[0;7m" // inverted background
#define COLOR_OFF "\033[0;0m" // default
#endif // __linux__

void printInterface(const Game *game);
void humanInput(Game *game);
Game *initGame(void);
void keepPlaying(Game *game);

int ascii_main(int argc, char **argv);

#endif // BLING_GUARD


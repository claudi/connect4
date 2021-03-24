#ifndef BLING_GUARD
#define BLING_GUARD
#include "defs.h"
#include "board.h"
#include "game.h"
#include "minimax.h"
#include <stdio.h>

#define SCREEN_W 18
#define SCREEN_H 10
#define SIDE_W 25
#define SIDE_H 9
#define CREDITS_W 28

#ifdef __linux__
#define colorON  "\033[0;7m" // inverted background
#define colorOFF "\033[0;0m" // default
#endif // __linux__

void printInterface(const Game *game);
void humanInput(Game *game);
Game *initGame(void);
Bool keepPlaying(void);

#endif // BLING_GUARD


#ifndef BLING_GUARD
#define BLING_GUARD
#include "defs.h"
#include "board.h"
#include "minimax.h"
#include <stdio.h>

#define not(b) ( (b == TRUE) ? FALSE : TRUE )

#define SCREEN_W 18
#define SCREEN_H 10
#define SIDE_W 25
#define SIDE_H 9
#define CREDITS_W 28

typedef struct {
    Node *node;
    short turn;
    short depth;
    Side playerSide;
    Side side;
    float time;
    Bool help;
} Game;

void printInterface(const Game *game);
void humanInput(Game *game);
Game *initGame(void);

#endif // BLING_GUARD

#ifndef BLING_GUARD
#define BLING_GUARD
#include "defs.h"
#include "board.h"
#include "minimax.h"
#include <stdio.h>

#define not(b) (((b) == TRUE) ? FALSE : TRUE)

#define SCREEN_W 18
#define SCREEN_H 10
#define SIDE_W 25
#define SIDE_H 9
#define CREDITS_W 28

#define START_BOARD initNode()
#define START_TURN 1
#define START_DEPTH 4
#define START_PLAYER_SIDE X
#define START_SIDE X
#define START_HELP TRUE

typedef struct {
    Node *node;
    short turn;
    short depth;
    Side playerSide;
    Side side;
    Bool help;
} Game;

void printInterface(const Game *game);
void humanInput(Game *game);
Game *initGame(void);
Bool keepPlaying(void);

#endif // BLING_GUARD

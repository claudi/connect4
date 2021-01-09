#ifndef GAME_GUARD
#define GAME_GUARD
#include "defs.h"
#include "tree.h"
#include "minimax.h"

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

Game *initGame(void);
void resetGame(Game *game);

#endif // GAME_GUARD
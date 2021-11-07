#ifndef GAME_GUARD
#define GAME_GUARD
#include "defs.h"

typedef struct {
    unsigned exploredPositions;
    double elapsedTime;
    short lastMove;
    long lastHeuristic;
} Stats;

typedef struct {
    Node *node;
    short turn;
    short depth;
    Side playerSide;
    Side side;
    Bool help;
    Stats stats;
    Bool keepPlaying;
} Game;

Game *initGame(void);
void resetGame(Game *game);

#endif // GAME_GUARD


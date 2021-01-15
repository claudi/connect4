#ifndef GAME_GUARD
#define GAME_GUARD
#include "defs.h"
#include "tree.h"

#define START_BOARD initNode()
#define START_TURN 1
#define START_DEPTH 4
#define START_PLAYER_SIDE X
#define START_SIDE X
#define START_HELP TRUE
#define START_STATS emptyStats()

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
} Game;

Game *initGame(void);
void resetGame(Game *game);
Stats emptyStats(void);
Game newGame(void);

#endif // GAME_GUARD


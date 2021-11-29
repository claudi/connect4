#ifndef GAME_GUARD
#define GAME_GUARD
#include "defs.h"
#include "tree.h"

#define START_BOARD initNode()
#define START_TURN 1
#ifndef START_DEPTH
#define START_DEPTH 4
#endif // START_DEPTH
#define START_PLAYER_SIDE X_SIDE
#define START_SIDE X_SIDE
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
    Bool keepPlaying;
} Game;

Game *initGame(void);
void resetGame(Game *game);

#endif // GAME_GUARD

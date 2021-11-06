#include <stdlib.h>
#include "game.h"
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

static Stats emptyStats(void);
static Game newGame(void);

Game *initGame(void) {
    Game *game = (Game *) malloc(sizeof(Game));
    *game = newGame();
    return game;
}

void resetGame(Game *game) {
    free(game->node);
    *game = newGame();
}

static Stats emptyStats(void) {
    Stats stats = {
        .exploredPositions = 0,
        .elapsedTime = 0.0f,
        .lastMove = -1,
        .lastHeuristic = 0
    };
    return stats;
}

static Game newGame(void) {
    Game game = {
        .node = START_BOARD,
        .turn = START_TURN,
        .depth = START_DEPTH,
        .playerSide = START_PLAYER_SIDE,
        .side = START_SIDE,
        .help = START_HELP,
        .stats = START_STATS,
        .keepPlaying = TRUE,
    };
    return game;
}


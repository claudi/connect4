#include "game.h"

static Stats emptyStats(void);
static Game newGame(void);

Game *initGame(void) {
    Game *game = (Game *) malloc(sizeof(Game));
    *game = newGame();

    Topology topology = {3, 2, 4, 2};
    size_t nlayers = 3;
    network = (Network *) initNetwork(nlayers, topology);

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


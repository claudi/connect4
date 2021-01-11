#include "game.h"

Game *initGame(void) {
    Game *game = (Game *) malloc(sizeof(Game));
    *game = newGame();
    return game;
}

void resetGame(Game *game) {
    free(game->node);
    *game = newGame();
}

Stats emptyStats(void) {
    Stats stats = {
        .exploredPositions = 0,
        .elapsedTime = 0.0f,
        .lastMove = 0,
        .lastHeuristic = 0
    };
    return stats;
}

Game newGame(void) {
    Game game = {
        .node = START_BOARD,
        .turn = START_TURN,
        .depth = START_DEPTH,
        .playerSide = START_PLAYER_SIDE,
        .side = START_SIDE,
        .help = START_HELP,
        .stats = START_STATS
    };
    return game;
}


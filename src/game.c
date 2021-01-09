#include "game.h"

Game newGame(void) {
    Game game = {
        .node = START_BOARD,
        .turn = START_TURN,
        .depth = START_DEPTH,
        .playerSide = START_PLAYER_SIDE,
        .side = START_SIDE,
        .help = START_HELP
    };
    return game;
}

Game *initGame(void) {
    Game *game = (Game *) malloc(sizeof(Game));
    *game = newGame();
    elapsedTime = 0;
    return game;
}

void resetGame(Game *game) {
    free(game->node);
    *game = newGame();
}


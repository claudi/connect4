#include "game.h"

Game *initGame(void) {
    Game *game = (Game *) malloc(sizeof(Game));
    *game = (Game) {
        .node = START_BOARD,
        .turn = START_TURN,
        .depth = START_DEPTH,
        .playerSide = START_PLAYER_SIDE,
        .side = START_SIDE,
        .help = START_HELP
    };
    elapsedTime = 0;
    return game;
}


#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "game.h"
#include "headless.h"
#include "minimax.h"

int headless_main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv) {
    Game *game = initGame();
    machineMove(game);

    printf("%u\n", game->stats.exploredPositions);

    free(game->node);
    free(game);
    return EXIT_SUCCESS;
}


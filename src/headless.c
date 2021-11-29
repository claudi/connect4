#include "headless.h"

int headless_main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
    Game *game = initGame();
    machineMove(game);

    printf("%u\n", game->stats.exploredPositions);

    free(game->node);
    free(game);
    return EXIT_SUCCESS;
}

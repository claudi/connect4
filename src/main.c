#include "bling.h"
#include "board.h"
#include "defs.h"
#include "game.h"
#include "heuristic.h"
#include "key.h"
#include "masks.h"
#include "minimax.h"
#include "table.h"
#include "tree.h"

#ifndef HEADLESS
int main(void) {
    Game *game = initGame();
    do {
        while(game->node->nchildren) {
            if(game->side == game->playerSide) {
                humanInput(game);
            } else {
                machineMove(game);
            }
            game->side = next(game->side);
            game->turn += game->side;
        }
        printInterface(game);
        resetGame(game);
    } while(keepPlaying());

    free(game->node);
    free(game);
    return EXIT_SUCCESS;
}
#else
int main(int argc, char **argv) {
    if(argc != 3) {
        return EXIT_FAILURE;
    }
    initCoefs(argv[1], argv[2]);
    Game *game = initGame();
    machineMove(game);
    printf("%u\n", game->stats.exploredPositions);
    return EXIT_SUCCESS;
}
#endif // HEADLESS


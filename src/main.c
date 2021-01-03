#include "bling.h"
#include "board.h"
#include "defs.h"
#include "heuristic.h"
#include "key.h"
#include "masks.h"
#include "minimax.h"
#include "tree.h"

int main(void) {
    initMasks();
    initKeys();

    do {
        Game *game = initGame();
        while(game->node->nchildren) {
            if(game->side == game->playerSide) {
                humanInput(game);
            } else {
                machineMove(game->node, game->depth, game->side);
            }
            game->side = next(game->side);
            game->turn += game->side;
        }
        printInterface(game);
        free(game->node);
        free(game);
    } while(keepPlaying());

    freeMasks();
    freeKeys();
    return EXIT_SUCCESS;
}


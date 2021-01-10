#include "bling.h"
#include "board.h"
#include "defs.h"
#include "game.h"
#include "heuristic.h"
#include "masks.h"
#include "minimax.h"
#include "tree.h"

int main(void) {
    initMasks();
    do {
        Game *game = initGame();
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
        free(game->node);
        free(game);
    } while(keepPlaying());

    freeMasks();
    return EXIT_SUCCESS;
}


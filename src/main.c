#include "bling.h"
#include "board.h"
#include "defs.h"
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
                machineMove(game->node, game->depth, game->side);
            }
            game->side = next(game->side);
            game->turn += game->side;
        }
        printInterface(game);
    } while(keepPlaying());

    return EXIT_SUCCESS;
}


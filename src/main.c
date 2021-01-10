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
    freeMasks();
    return EXIT_SUCCESS;
}


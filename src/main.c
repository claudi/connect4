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
#include "gui.h"

int main(void) {
    App *app = initSDL();
    if(app == NULL) {
        return EXIT_FAILURE;
    }

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
    freeSDL(app);
    return EXIT_SUCCESS;
}
#else
int main(void) {
    Game *game = initGame();
    machineMove(game);
    printf("%u\n", game->stats.exploredPositions);
    return EXIT_SUCCESS;
}
#endif // HEADLESS


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
#include "gui.h"

int main(void) {
    Game *game = initGame();
    machineMove(game);
    printf("%u\n", game->stats.exploredPositions);
    return EXIT_SUCCESS;
}


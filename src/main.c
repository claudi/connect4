#include "defs.h"
#include "board.h"
#include "tree.h"
#include "minimax.h"
#include "masks.h"
#include <stdio.h>

int main(int argc, char **argv) {
    short depth = 6;
    if(argc == 2) {
        depth = atoi(argv[1]);
    }

    initMasks();
    Node *game = initNode();;

    Side side = X;
    while(game->nchildren) {
        makeMove(game, chooseMove(game, depth, side));
        side = next(side);
    }

    free(game);
    return 0;
}


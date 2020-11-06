#include "defs.h"
#include "board.h"
#include "tree.h"
#include "minimax.h"
#include "masks.h"
#include <stdio.h>

int main(int argc, char **argv) {
    size_t depth = 6;

    initMasks();
    initCoefs(argv[1], argv[2]);

    Node *game = initNode();;

    Side side = X;
    while(game->nchildren) {
        makeMove(game, chooseMove(game, depth, side));
        side = next(side);
    }

    if(wonBoard(game->board)) {
        printf("%d\n", game->turn);
    } else {
        printf("-1\n");
    }

    free(game);
    return 0;
}


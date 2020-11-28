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

    short nlayers = 4;
    short topology[4] = {1380, 128, 64, 1};
    FILE *coefsX = fopen(argv[2], "r");
    FILE *coefsO = fopen(argv[3], "r");
    initNetworks(coefsX, coefsO, nlayers, topology);
    initMasks();

    Node *game = initNode();;

    Side side = X;
    while(game->nchildren) {
        makeMove(game, chooseMove(game, depth, side));
        side = next(side);
    }


    // printNode(game);
    int win = 3, lose = 0, even = 1;
    printf("%d %d ", atoi(argv[2] + 6), atoi(argv[3] + 6));
    if(wonBoard(game->board)) {
        printf("%d\n", game->turn == X ? win : lose);
    } else {
        printf("%d\n", even);
    }

    free(game);
    return 0;
}


#include "defs.h"
#include "board.h"
// #include "tree.h"
#include "minimax.h"
#include "masks.h"
#include "bling.h"
#include <stdio.h>

int main(int argc, char **argv) {
    short depth = 6;
    if(argc == 2) {
        depth = atoi(argv[1]);
    }

    // printMenu();

    initMasks();
    Node *game = initNode();;

    // int move;
    short turn = 1;
    Side side = X;
    while(game->nchildren) {
        game = machineMove(game, depth, side);
        side = next(side);
        printInterface(game, turn);
        turn += side;
        // printNode(game);
        // if(wonBoard(game->board)) break;
        // scanf("%d", &move);
        // makeMove(game, move);
        // side = next(side);
    }

    free(game);
    return 0;
}


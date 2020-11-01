#include "defs.h"
#include "board.h"
#include "tree.h"
#include "minimax.h"
#include "masks.h"
#include <stdio.h>

int main(int argc, char **argv) {
    size_t depth = 6;
    if(argc == 2) {
        depth = atoi(argv[1]);
    }

    initMasks();
    Node *game = initNode();;

    srand(time(NULL));
    printf("move: %ld\n", chooseMove(game, depth));

    free(game);
    return 0;
}


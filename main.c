#include "defs.h"
#include "board.h"
#include "tree.h"
#include <stdio.h>

int main(int argc, char **argv) {
    size_t depth = 4;
    if(argc == 2) {
        depth = atoi(argv[1]);
    }

    Node *game = initNode();;
    printNode(game);
    createTree(game, depth);
    return 0;
}


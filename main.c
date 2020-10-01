#include "defs.h"
#include "board.h"
#include "tree.h"
#include <stdio.h>

int main(int argc, char **argv) {
    Node *game = initNode();;
    // printNode(game);
    createTree(game, atoi(argv[1]));
    return 0;
}


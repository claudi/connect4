#include "defs.h"
#include "board.h"
#include "tree.h"
#include "minimax.h"
#include <stdio.h>

void printTree(const Node *root) {
    printNode(root);
    for(size_t iter = 0; iter < root->nchildren; iter++) {
        printTree(root->child[iter]);
    }
}

int main(int argc, char **argv) {
    size_t depth = 4;
    if(argc == 2) {
        depth = atoi(argv[1]);
    }

    Node *game = initNode();;
    // createTree(game, depth);

    // printTree(game);

    srand(time(NULL));
    printf("move: %ld\n", chooseMove(game, depth));

    return 0;
}


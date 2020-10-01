#include "tree.h"
#include "board.h"
#include <stdio.h>

void initNode(Node *node) {
    size_t iter;
    /* ASSERT(node != NULL) */
    for(iter = 0; iter < nsides; iter++) {
        node->board[iter] = (uint64_t) 0;
    }
    node->turn = X;

    node->nchildren = 8;
    node->child = NULL;

    // TODO: Consider node->heuristic = 0f;
}

Node *createChild(Node *parent, const size_t nchild) {
    size_t iter = 0, col = 0;
    Node *child = (Node *) malloc(sizeof(Node));
    /* ASSERT(nchild < N) */
    /* ASSERT(nchild >= 0) */
    while(col != nchild) {
        if(!(parent->board[BOTH] & shift(N - 1, iter))) {
            col++;
        }
        iter++;
    }
    copyNode(child, parent);
    makeMove(child, col);   // TODO: Check return value

    return child;
}

void createChildren(Node *parent) {
    size_t iter;
    for(iter = 0; iter < parent->nchildren; iter++) {
        parent->child[iter] = createChild(parent, iter);
    }
}

void createTree(Node *root, const size_t depth) {
    size_t iter;
    /* ASSERT(depth >= 0) */
    if(depth == 0) {
        root->nchildren = 0;
        root->child = NULL;
    } else {
        createChildren(root);
        for(iter = 0; iter < root->nchildren; iter++) {
            createTree(root->child[iter], depth - 1);
        }
    }
}


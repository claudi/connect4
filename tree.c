#include "tree.h"

Node *initNode(void) {
    /* ASSERT(node != NULL) */
    Node *node = (Node *) malloc(sizeof(Node));
    for(size_t iter = 0; iter < nsides; iter++) {
        node->board[iter] = (uint64_t) 0;
    }
    node->turn = X;

    node->nchildren = 8;
    node->child = NULL;

    return node;
    // TODO: Consider node->heuristic = 0f;
}

Node *createChild(Node *parent, const size_t nchild) {
    /* ASSERT(nchild < N) */
    /* ASSERT(nchild >= 0) */
    size_t col = 0;
    for(size_t iter = 0; col != nchild; iter++) {
        if(!(parent->board[BOTH] & shift(N - 1, iter))) {
            col++;
        }
    }

    Node *child = (Node *) malloc(sizeof(Node));
    copyNode(child, parent);
    makeMove(child, col);   // TODO: Check return value

    printNode(child);
    return child;
}

void createChildren(Node *parent) {
    parent->child = (Node **) malloc(sizeof(Node *));
    for(size_t iter = 0; iter < parent->nchildren; iter++) {
        parent->child[iter] = (Node *) malloc(sizeof(Node));
    }
    for(size_t iter = 0; iter < parent->nchildren; iter++) {
        parent->child[iter] = createChild(parent, iter);
    }
}

void createTree(Node *root, const ssize_t depth) {
    /* ASSERT(depth >= 0) */
    if(depth == 0) {
        root->nchildren = 0;
        root->child = NULL;
    } else {
        createChildren(root);
        for(size_t iter = 0; iter < root->nchildren; iter++) {
            createTree(root->child[iter], depth - 1);
        }
    }
}


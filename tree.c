#include "tree.h"

Node *initNode(void) {
    Node *node = (Node *) malloc(sizeof(Node));
    for(size_t iter = 0; iter < nsides; iter++) {
        node->board[iter] = (Board) 0;
    }
    node->turn = X;

    node->nchildren = 8;
    node->child = NULL;

    return node;
    // TODO: Consider node->heuristic = 0f;
}

Node *createChild(Node *parent, const size_t col) {
    ASSERT(col < N);
    ASSERT(col >= 0);

    Node *child = (Node *) malloc(sizeof(Node));
    copyNode(child, parent);
    makeMove(child, col);   // TODO: Check return value

    return child;
}

void createChildren(Node *parent) {
    parent->child = (Node **) malloc(parent->nchildren * sizeof(Node *));

    for(size_t iter = 0, col = 0; iter < parent->nchildren; iter++) {
        while(( parent->board[X] | parent->board[O] ) & shift(N - 1, col)) {
            col++;
            ASSERT(col < N);
        }
        parent->child[iter] = createChild(parent, col);
        col++;
    }
}

void createTree(Node *root, const ssize_t depth) {
    ASSERT(depth >= 0);

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

void printTree(const Node *root) {
    printNode(root);
    for(size_t iter = 0; iter < root->nchildren; iter++) {
        printTree(root->child[iter]);
    }
}


#include "tree.h"

Node *initNode(void) {
    Node *node = (Node *) malloc(sizeof(Node));
    for(short iter = 0; iter < nboards; iter++) {
        node->board[iter] = (Board) 0;
    }
    node->turn = O;

    node->nchildren = 8;
    node->child = NULL;

    return node;
}

Node *createChild(Node *parent, const short col) {
    ASSERT(col < N);
    ASSERT(col >= 0);

    Node *child = (Node *) malloc(sizeof(Node));
    copyNode(child, parent);
    makeMove(child, col);   // TODO: Check return value

    return child;
}

void createChildren(Node *parent) {
    parent->child = (Node **) malloc(parent->nchildren * sizeof(Node *));

    short col = 0;
    for(short iter = 0; iter < parent->nchildren; iter++) {
        while(fullColumn(parent->board, col)) {
            col++;
            ASSERT(col < N);
        }
        ASSERT(col < N);
        parent->child[iter] = createChild(parent, col);
        col++;
    }
    ASSERT(col >= 0);
}

void createTree(Node *root, const short depth) {
    ASSERT(depth >= 0);

    if(depth == 0) {
        root->nchildren = 0;
        root->child = NULL;
    } else {
        createChildren(root);
        for(short iter = 0; iter < root->nchildren; iter++) {
            createTree(root->child[iter], depth - 1);
        }
    }
}

void printTree(const Node *root) {
    printNode(root);
    for(short iter = 0; iter < root->nchildren; iter++) {
        printTree(root->child[iter]);
    }
}


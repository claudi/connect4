#include "tree.h"

static Node *createChild(const Node *parent, const short child);
static void orderChildren(Node *parent);

Node *initNode(void) {
    Node *node = (Node *) malloc(sizeof(Node));
    for(short iter = 0; iter < NBOARDS; iter++) {
        node->board[iter] = (Board) 0;
    }
    node->turn = O_SIDE;

    node->nchildren = 8;
    node->child = NULL;

    return node;
}

static Node *createChild(const Node *parent, const short col) {
    ASSERT(col < BOARD_SIZE);
    ASSERT(col >= 0);

    Node *child = (Node *) malloc(sizeof(Node));
    copyNode(child, parent);
    makeMove(child, col);

    return child;
}

void createChildren(Node *parent) {
    parent->child = (Node **) malloc(parent->nchildren * sizeof(Node *));

    short col = 0;
    for(short iter = 0; iter < parent->nchildren; iter++) {
        while(FULL_COLUMN(parent->board, col)) {
            col++;
            ASSERT(col < BOARD_SIZE);
        }
        ASSERT(col < BOARD_SIZE);
        parent->child[iter] = createChild(parent, col);
        col++;
    }
    ASSERT(col >= 0);

    orderChildren(parent);
}

static void orderChildren(Node *parent) {
    Side side = NEXT(parent->turn);
    long *values = (long *) malloc(parent->nchildren * sizeof(long));
    for(short iter = 0; iter < parent->nchildren; iter++) {
        values[iter] = getOrderingHeuristic(parent->child[iter], side);
    }

    for(short iter = 1; iter < parent->nchildren; iter++) {
        Node *auxn = parent->child[iter];
        long auxv = values[iter];

        short j = iter - 1;
        while((j >= 0) && (values[j] < auxv)) {
            parent->child[j+1] = parent->child[j];
            values[j+1] = values[j];

            j = j - 1;
        }
        parent->child[j+1] = auxn;
        values[j+1] = auxv;
    }
    free(values);
}

static void createTree(Node *root, const short depth) {
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

static void printTree(const Node *root) {
    printNode(root);
    for(short iter = 0; iter < root->nchildren; iter++) {
        printTree(root->child[iter]);
    }
}

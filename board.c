#include "board.h"

Mask shift(const size_t row, const size_t col) {
    return ((Mask) 1) << ((N * row) + col); // TODO: change into macro
}

void copyNode(Node *dest, const Node *orig) {
    copyBoard(dest->board, orig->board);
    dest->turn = orig->turn;
    dest->nchildren = orig->nchildren;
}

void copyBoard(Board *dest, const Board *orig) {
    for(size_t iter = 0; iter < nsides; iter++) {
        dest[iter] = orig[iter];
    }
}

int makeMove(Node *node, const size_t col) {
    ASSERT(col < N);
    ASSERT(col >= 0);

    ssize_t row = -1;
    for(size_t iter = 0; iter < N; iter++) {
        if(!(( node->board[X] | node->board[O] ) & shift(iter, col))) {
            row = iter;
            break;
        }
    }

    ASSERT(row != -1);
    // Check for won board, and if so set nchildren to 0 and return 0
    if(row == N - 1) {
        node->nchildren = node->nchildren - 1;
    }

    node->board[node->turn] |= shift(row, col);
    node->turn = next(node->turn);
    return 0;
}

void printBoard(const Board *board) {
    ssize_t row, col;
    printf("\n");
    for(row = N - 1; row >= 0; row--) {
        for(col = 0; col < N; col++) {
            if(board[X] & shift(row, col)) {
                printf(" X");
            } else if (board[O] & shift(row, col)) {
                printf(" O");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    for(col = 0; col < N; col++) {
        printf(" %lu", col);
    }
    printf("\n");
}

void printNode(const Node *node) {
    printBoard(node->board);

    printf("turn:\t\t%c\n", (node->turn == X) ? 'X' : 'O');
    printf("nchildren:\t%d\n", node->nchildren);
}


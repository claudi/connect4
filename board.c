#include "board.h"
#include <stdio.h>

uint64_t shift(const size_t row, const size_t col) {
    size_t shift = ((N-(row+1))*N)+col;
    uint64_t result = ((uint64_t) 1) << shift;
    return result;
}

void copyNode(Node *dest, const Node *orig) {
    copyBoard(dest->board, orig->board);
    dest->turn = orig->turn;
    dest->nchildren = orig->nchildren;
}

void copyBoard(Board *dest, const Board *orig) {
    size_t iter;
    for(iter = 0; iter < nsides; iter++) {
        dest[iter] = orig[iter];
    }
}

int makeMove(Node *node, const size_t col) {
    size_t iter;
    int row = -1;
    /* ASSERT(col < N) */
    /* ASSERT(col >= 0) */
    for(iter = 0; iter < N; iter++) {
        if(!(node->board[BOTH] & shift(iter, col))) {
            row = iter;
            break;
        }
    }

    if(row == -1) {
        return 1; // Error: column was full
    } else if(row == N - 1) {
        node->nchildren = node->nchildren - 1;
    }

    node->board[BOTH] |= shift(row, col);
    node->board[node->turn] |= shift(row, col);
    node->turn = next(node->turn);
    return 0;
}

void printBoard(const Board *board) {
    size_t row, col;
    for(row = 0; row < N; row++) {
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
    printf(" turn:\t%c\n", (node->turn == X) ? 'X' : 'O');
    printf(" nchildren:\t%d", node->nchildren);

    printBoard(node->board);
}


#include "board.h"

uint64_t shift(const size_t row, const size_t col) {
    return ((uint64_t) 1) << ((N * row) + col); // TODO: change into macro
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
    ssize_t row = -1;
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
    ssize_t row, col;
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
    printf("\n\n");
}

void printNode(const Node *node) {
    printf(" turn:\t\t%c\n", (node->turn == X) ? 'X' : 'O');
    printf(" nchildren:\t%d", node->nchildren);
    printf("\n");

    printBoard(node->board);
}


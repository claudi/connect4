#include "board.h"

Mask shift(const short row, const short col) {
    return (((Mask) 1) << pos2Shift(row, col));
}

void copyNode(Node *dest, const Node *orig) {
    copyBoard(dest->board, orig->board);
    dest->turn = orig->turn;
    dest->nchildren = orig->nchildren;
}

void copyBoard(Board *dest, const Board *orig) {
    for(short iter = 0; iter < nboards; iter++) {
        dest[iter] = orig[iter];
    }
}

short makeMove(Node *node, const short col) {
    ASSERT(col < N);
    ASSERT(col >= 0);
    ASSERT(!(node->board[BOTH] & shift(N - 1, col)));

    short row = 0;
    for(short iter = 0; iter < N; iter++) {
        row = row + ((node->board[BOTH] & shift(iter, col)) == shift(iter, col));
    }

    ASSERT(row < N);

    // Check for won board, and if so set nchildren to 0 and return 0
    node->board[TURN] ^= node->board[BOTH];
    node->board[TURN] |= shift(row, col);
    node->board[BOTH] |= shift(row, col);

    node->turn = next(node->turn);

    if(wonBoard(node->board)) {
        node->nchildren = 0;
    } else if(row == N - 1) {
        node->nchildren = node->nchildren - 1;
    }

    return 0;
}

char showTurn(const Side turn) {
    return (turn == X) ? 'X' : 'O';
}

void printBoard(const Node *node) {
    short row, col;
    char lastMove = showTurn(node->turn);
    char nextMove = showTurn(next(node->turn));
    printf("\n");
    for(row = N - 1; row >= 0; row--) {
        for(col = 0; col < N; col++) {
            if(node->board[TURN] & shift(row, col)) {
                printf(" %c", lastMove);
            } else if (node->board[BOTH] & shift(row, col)) {
                printf(" %c", nextMove);
            } else {
                printf(" ·");
            }
        }
        printf("\n");
    }
    for(col = 0; col < N; col++) {
        printf(" %d", col);
    }
    printf("\n");
}

void printNode(const Node *node) {
    printBoard(node);

    // printf("last move:\t%c\n", showTurn(node->turn));
    // printf("nchildren:\t%d\n", node->nchildren);
}


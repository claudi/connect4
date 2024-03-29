#include <stdio.h>
#include "board.h"
#include "masks.h"

static unsigned wonBoard(const Board *board);
static void printBoard(const Node *node);

void copyNode(Node *dest, const Node *orig) {
    copyBoard(dest->board, orig->board);
    dest->turn = orig->turn;
    dest->nchildren = orig->nchildren;
}

void copyBoard(Board *dest, const Board *orig) {
    for(short iter = 0; iter < NBOARDS; iter++) {
        dest[iter] = orig[iter];
    }
}

short makeMove(Node *node, const short col) {
    ASSERT(col < BOARD_SIZE);
    ASSERT(col >= 0);
    ASSERT(!FULL_COLUMN(node->board, col));

    short row = 0;
    for(short iter = 0; iter < BOARD_SIZE; iter++) {
        row = row + ((node->board[BOTH] & shift(iter, col)) == shift(iter, col));
    }

    ASSERT(row < BOARD_SIZE);

    // Check for won board, and if so set nchildren to 0 and return 0
    node->board[TURN] ^= node->board[BOTH];
    node->board[TURN] |= shift(row, col);
    node->board[BOTH] |= shift(row, col);

    node->turn = NEXT(node->turn);

    if(wonBoard(node->board)) {
        node->nchildren = 0;
    } else if(row == BOARD_SIZE - 1) {
        node->nchildren = node->nchildren - 1;
    }

    return 0;
}

static unsigned wonBoard(const Board *board) {
    return matches(board, MATCH4);
}

char showTurn(const Side turn) {
    return (turn == X_SIDE) ? 'X' : 'O';
}

static void printBoard(const Node *node) {
    short row, col;
    char lastMove = showTurn(node->turn);
    char nextMove = showTurn(NEXT(node->turn));
    printf("\n");
    for(row = BOARD_SIZE - 1; row >= 0; row--) {
        for(col = 0; col < BOARD_SIZE; col++) {
            if(node->board[TURN] & shift(row, col)) {
                printf(" %c", lastMove);
            } else if(node->board[BOTH] & shift(row, col)) {
                printf(" %c", nextMove);
            } else {
                printf(" ·");
            }
        }
        printf("\n");
    }
    for(col = 0; col < BOARD_SIZE; col++) {
        printf(" %d", col);
    }
    printf("\n");
}

void printNode(const Node *node) {
    printBoard(node);

    // printf("last move:\t%c\n", showTurn(node->turn));
    // printf("nchildren:\t%d\n", node->nchildren);
}


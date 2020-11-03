#ifndef HEURISTIC_GUARD
#define HEURISTIC_GUARD
#include "heuristic.h"

int simpleHeuristic(const Node *node, const Side side) {
    Board board[nboards];
    copyBoard(board, node->board);

    if(node->turn != side) {
        board[TURN] ^= board[BOTH];
    }

    if(matches(board, match4) > 0) {
        return INT_MIN;
    }

    board[TURN] ^= board[BOTH];

    if(matches(board, match4) > 0) {
        return INT_MAX;
    }

    return 0;
}

int heuristic(const Node *node, const Side side) {
    int val4 = matches(node->board, match4);
    if(val4 > 0) {
        return INT_MAX;
    }
    int val3 = matches(node->board, match3);
    int val2 = matches(node->board, match2);
    int val1 = matches(node->board, match1);
    return (val1 + 10*val2 + 100*val3 + 1000*val4);
}

#endif // HEURISTIC_GUARD


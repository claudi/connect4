#ifndef HEURISTIC_GUARD
#define HEURISTIC_GUARD
#include "heuristic.h"

int myHeuristic(Board *board, const Side __attribute((unused)) side) {
    int heuristic = 0;

    heuristic += 2*(matches(board, match1) + 5*matches(board, match2) + 15*matches(board, match3));
    board[TURN] ^= board[BOTH];
    heuristic -= matches(board, match1) + 5*matches(board, match2) + 10*matches(board, match3);

    return heuristic;
}

int controlHeuristic(Board *board, const Side __attribute((unused)) side) {
    int heuristic = 0;

    heuristic += 2*(matches(board, match2) + 10*matches(board, match3));
    board[TURN] ^= board[BOTH];
    heuristic -= matches(board, match2) + 10*matches(board, match3);

    return heuristic;
}

int simpleHeuristic(Board __attribute((unused)) *board, const Side __attribute((unused)) side) {
    return 0;
}

int heuristic(const Node *node, const Side side) {
    Board board[nboards];
    copyBoard(board, node->board);

    if(node->turn == side) {
        board[TURN] ^= board[BOTH];
    }

    if(matches(board, match4) > 0) {
        return INT_MIN;
    }

    board[TURN] ^= board[BOTH];

    if(matches(board, match4) > 0) {
        return INT_MAX;
    }

    return myHeuristic(board, side);
}

#endif // HEURISTIC_GUARD


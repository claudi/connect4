#include "heuristic.h"

long myHeuristic(Board *board, const Side __attribute((unused)) side) {
    long heuristic = 0;

    heuristic += 2*(matches(board, match1) + 5*matches(board, match2) + 15*matches(board, match3));
    board[TURN] ^= board[BOTH];
    heuristic -= matches(board, match1) + 5*matches(board, match2) + 10*matches(board, match3);

    return heuristic;
}

long controlHeuristic(Board *board, const Side __attribute((unused)) side) {
    long heuristic = 0;

    heuristic += 2*(matches(board, match2) + 10*matches(board, match3));
    board[TURN] ^= board[BOTH];
    heuristic -= matches(board, match2) + 10*matches(board, match3);

    return heuristic;
}

long simpleHeuristic(Board __attribute((unused)) *board, const Side __attribute((unused)) side) {
    return 0;
}

long heuristic(const Node *node, const Side side) {
    Board board[nboards];
    copyBoard(board, node->board);

    if(node->turn == side) {
        board[TURN] ^= board[BOTH];
    }

    if(matches(board, match4) > 0) {
        return LONG_MIN;
    }

    board[TURN] ^= board[BOTH];

    if(matches(board, match4) > 0) {
        return LONG_MAX;
    }

    return myHeuristic(board, side);
}


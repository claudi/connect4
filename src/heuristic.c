#include "heuristic.h"

static long myHeuristic(Board *board, const Side __attribute__((unused)) side) {
    long heuristic = 0;

    heuristic += 2*(matches(board, match1) + 5*matches(board, match2) + 15*matches(board, match3));
    board[TURN] ^= board[BOTH];
    heuristic -= matches(board, match1) + 5*matches(board, match2) + 10*matches(board, match3);

    return heuristic;
}

static long controlHeuristic(Board *board, const Side __attribute__((unused)) side) {
    long heuristic = 0;

    heuristic += 2*(matches(board, match2) + 10*matches(board, match3));
    board[TURN] ^= board[BOTH];
    heuristic -= matches(board, match2) + 10*matches(board, match3);

    return heuristic;
}

static long simpleHeuristic(Board __attribute__((unused)) *board, const Side __attribute__((unused)) side) {
    return 0;
}

long getHeuristic(const Node *node, const Side side) {
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

    return simpleHeuristic(board, side);
}

long getOrderingHeuristic(const Node *node, const Side side) {
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


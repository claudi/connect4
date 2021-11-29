#include "heuristic.h"

static long myHeuristic(Board *board, __attribute__((unused)) const Side side) {
    long heuristic = 0;

    heuristic += 2*(matches(board, MATCH1) + 5*matches(board, MATCH2) + 15*matches(board, MATCH3));
    board[TURN] ^= board[BOTH];
    heuristic -= matches(board, MATCH1) + 5*matches(board, MATCH2) + 10*matches(board, MATCH3);

    return heuristic;
}

static long controlHeuristic(Board *board, __attribute__((unused)) const Side side) {
    long heuristic = 0;

    heuristic += 2*(matches(board, MATCH2) + 10*matches(board, MATCH3));
    board[TURN] ^= board[BOTH];
    heuristic -= matches(board, MATCH2) + 10*matches(board, MATCH3);

    return heuristic;
}

static long simpleHeuristic(__attribute__((unused)) Board *board, __attribute__((unused)) const Side side) {
    return 0;
}

long getHeuristic(const Node *node, const Side side) {
    Board board[NBOARDS];
    copyBoard(board, node->board);

    if(node->turn == side) {
        board[TURN] ^= board[BOTH];
    }

    if(matches(board, MATCH4) > 0) {
        return LONG_MIN;
    }

    board[TURN] ^= board[BOTH];

    if(matches(board, MATCH4) > 0) {
        return LONG_MAX;
    }

    return simpleHeuristic(board, side);
}

long getOrderingHeuristic(const Node *node, const Side side) {
    Board board[NBOARDS];
    copyBoard(board, node->board);

    if(node->turn == side) {
        board[TURN] ^= board[BOTH];
    }

    if(matches(board, MATCH4) > 0) {
        return LONG_MIN;
    }

    board[TURN] ^= board[BOTH];

    if(matches(board, MATCH4) > 0) {
        return LONG_MAX;
    }

    return myHeuristic(board, side);
}

#ifndef HEURISTIC_GUARD
#define HEURISTIC_GUARD
#include "heuristic.h"

int simpleHeuristic(const Node *node, const Side side);
int weightedHeuristic(const Node *node, const Side side);
int manualHeuristic(const Node *node, const Side side);

int heuristic(const Node *node, const Side side) {
    return manualHeuristic(node, side);
}

int simpleHeuristic(const Node *node, const Side side) {
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

    return 0;
}

int weightedHeuristic(const Node *node, const Side side) {
    Board board[nboards];
    copyBoard(board, node->board);

    if(node->turn == side) {
        board[TURN] ^= board[BOTH];
    }

    int heuristic = 0;
    
    if(matches(board, match4)) {
        return INT_MIN;
    }
    heuristic -= weightedMatches(board);

    board[TURN] ^= board[BOTH];

    if(matches(board, match4)) {
        return INT_MAX;
    }
    heuristic += weightedMatches(board);

    return heuristic;
}

int manualHeuristic(const Node *node, const Side side) {
    Board board[nboards];
    copyBoard(board, node->board);

    if(node->turn == side) {
        board[TURN] ^= board[BOTH];
    }

    int heuristic = 0;
    int /*nmatch1,*/ nmatch2, nmatch3, nmatch4;
    nmatch4 = matches(board, match4);
    if(nmatch4 > 0) {
        return INT_MIN;
    }
    nmatch3 = matches(board, match3);
    nmatch2 = matches(board, match2);
    // nmatch1 = matches(board, match1);

    heuristic -= 2*(nmatch2 + 10*nmatch3);

    board[TURN] ^= board[BOTH];

    nmatch4 = matches(board, match4);
    if(nmatch4 > 0) {
        return INT_MAX;
    }
    nmatch3 = matches(board, match3);
    nmatch2 = matches(board, match2);
    // nmatch1 = matches(board, match1);

    heuristic += (nmatch2 + 10*nmatch3);

    return heuristic;
}

#endif // HEURISTIC_GUARD


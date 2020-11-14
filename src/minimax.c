#include "minimax.h"

int alphaBeta(Node *root, int alpha, int beta, const short depth, const Side side, const Bool maximizing);

int side(const Side side) {
    return (side == X) ? 1 : -1;
}

short chooseMove(Node *root, const short depth, const Side side) {
    ASSERT(root != NULL);
    ASSERT(depth > 0);

    createChildren(root);

    int value = INT_MIN;
    int alpha = INT_MIN;
    int beta = INT_MAX;

    int heuristic;
    short move = 0;
    for(short iter = 0; iter < root->nchildren; iter++) {
        heuristic = alphaBeta(root->child[iter], alpha, beta, depth - 1, side, FALSE);
        free(root->child[iter]);
        if(heuristic > value) {
            value = heuristic;
            move = iter;
        }
    }
    free(root->child);

    ASSERT(move >= 0);
    ASSERT(move < root->nchildren);

    short col = -1;
    for(short iter = 0; iter <= move; iter++) {
        col++;
        ASSERT(col < N);
        while(root->board[BOTH] & shift(N - 1, col)) {
            col++;
            ASSERT(col < N);
        }
    }

    ASSERT(col >= 0);
    return col;
}

int alphaBeta(Node *root, int alpha, int beta, const short depth, const Side side, const Bool maximizing) {
    if(depth == 0 || root->nchildren == 0) {
        int h = heuristic(root, side);
        return h;
    }

    int value;
    createChildren(root);
    if(maximizing) {
        value = INT_MIN;
        for(size_t iter = 0; iter < root->nchildren; iter++) {
            int heuristic = alphaBeta(root->child[iter], alpha, beta, depth - 1, side, FALSE);

            if(heuristic > value) {
                value = heuristic;
            }
            if(value > alpha) {
                alpha = value;
            }
            if(alpha >= beta) {
                for(size_t free_the_children = iter; free_the_children < root->nchildren; free_the_children++) {
                    free(root->child[free_the_children]);
                }
                break;
            }
            free(root->child[iter]);
        }
    } else {
        value = INT_MAX;
        for(size_t iter = 0; iter < root->nchildren; iter++) {
            int heuristic = alphaBeta(root->child[iter], alpha, beta, depth - 1, side, TRUE);

            if(heuristic < value) {
                value = heuristic;
            }
            if(value < beta) {
                beta = value;
            }
            if(beta <= alpha) {
                for(size_t free_the_children = iter; free_the_children < root->nchildren; free_the_children++) {
                    free(root->child[free_the_children]);
                }
                break;
            }
            free(root->child[iter]);
        }
    }
    return value;
}


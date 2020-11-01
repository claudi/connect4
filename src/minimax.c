#include "minimax.h"

int alphaBetaMax(Node *root, int alpha, int beta, const ssize_t depth);
int alphaBetaMin(Node *root, int alpha, int beta, const ssize_t depth);

int side(const Side side) {
    return (side == X) ? 1 : -1;
}

size_t chooseMove(Node *root, const ssize_t depth) {
    ASSERT(root != NULL);
    ASSERT(depth > 0);

    createChildren(root);

    int best = INT_MIN;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    ssize_t move = -1;
    for(size_t iter = 0; iter < root->nchildren; iter++) {
        int score = alphaBetaMax(root->child[iter], alpha, beta, depth - 1);
        free(root->child[iter]);
        if(score > best) {
            best = score;
            move = iter;
        }
    }
    free(root->child);

    ASSERT(move != -1);
    return move;
}

int alphaBetaMax(Node *root, int alpha, int beta, const ssize_t depth) {
    // if(depth * (root->nchildren) == 0)
    if((depth == 0) || (root->nchildren == 0)) {
        return heuristic(root);
    }

    createChildren(root);
    for(size_t iter = 0; iter < root->nchildren; iter++) {
        int score = alphaBetaMin(root->child[iter], alpha, beta, depth - 1);
        free(root->child[iter]);
        if(score >= beta) {
            return beta;
        }
        if(score > alpha) {
            alpha = score;
        }
    }
    free(root->child);

    return alpha;
}

int alphaBetaMin(Node *root, int alpha, int beta, const ssize_t depth) {
    // if(depth * (root->nchildren) == 0)
    if((depth == 0) || (root->nchildren == 0)) {
        return -heuristic(root);
    }

    createChildren(root);
    for(size_t iter = 0; iter < root->nchildren; iter++) {
        int score = alphaBetaMax(root->child[iter], alpha, beta, depth - 1);
        free(root->child[iter]);
        if(score <= alpha) {
            return alpha;
        }
        if(score < beta) {
            beta = score;
        }
    }
    free(root->child);

    return beta;
}


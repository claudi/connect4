#include "minimax.h"

int side(const Side side) {
    return (side == X) ? 1 : -1;
}

size_t chooseMove(Node *root, const ssize_t depth) {
    ASSERT(root != NULL);
    ASSERT(depth > 0);

    createChildren(root);

    float best = -FLT_MAX;
    ssize_t move = -1;
    for(size_t iter = 0; iter < root->nchildren; iter++) {
        float heuristic = minimax(root->child[iter], depth - 1);
        free(root->child[iter]);
        if(heuristic > best) {
            best = heuristic;
            move = iter;
        }
    }
    free(root->child);

    ASSERT(move != -1);
    return move;
}

float minimax(Node *root, const ssize_t depth) {
    if((depth == 0) || (root->nchildren == 0)) {
        return (side(root->turn) * heuristic(root));
    }

    createChildren(root);
    float best = -FLT_MAX;
    for(size_t iter = 0; iter < root->nchildren; iter++) {
        float heuristic = -minimax(root->child[iter], depth - 1);
        free(root->child[iter]);
        if(heuristic > best) {
            best = heuristic;
        }
    }
    free(root->child);

    return best;
}


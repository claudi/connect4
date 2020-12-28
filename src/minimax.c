#include "minimax.h"

unsigned exploredPositions;
double elapsedTime;
long alphaBeta(Node *root, long alpha, long beta, const short depth, const Side side, const Bool maximizing);

int color(const Side side) {
    return (side == X) ? 1 : -1;
}

void machineMove(Node *root, const short depth, const Side side) {
    ASSERT(root != NULL);
    ASSERT(depth > 0);
    ASSERT(root->nchildren > 0);

    createChildren(root);
    Node *answer = (Node *) malloc(sizeof(Node));

    long value = LONG_MIN;
    long alpha = LONG_MIN;
    long beta = LONG_MAX;
    long heuristic;

    exploredPositions = 0;
    clock_t start = clock();
    for(short iter = 0; iter < root->nchildren; iter++) {
        heuristic = alphaBeta(root->child[iter], alpha, beta, depth - 1, side, FALSE);
        if(heuristic > value) {
            value = heuristic;
            copyNode(answer, root->child[iter]);
        }
        free(root->child[iter]);
    }
    clock_t end = clock();
    elapsedTime = (double) (end - start);

    copyNode(root, answer);
    free(answer);
}

long alphaBeta(Node *root, long alpha, long beta, const short depth, const Side side, const Bool maximizing) {
    exploredPositions++;

    if(depth == 0 || root->nchildren == 0) {
        long h = heuristic(root, side) - color(side) * color(root->turn) * ( N*N - depth );
        return h;
    }

    long value;
    createChildren(root);
    if(maximizing) {
        value = LONG_MIN;
        for(short iter = 0; iter < root->nchildren; iter++) {
            long heuristic = alphaBeta(root->child[iter], alpha, beta, depth - 1, side, FALSE);

            if(heuristic > value) {
                value = heuristic;
            }
            if(value > alpha) {
                alpha = value;
            }
            if(alpha >= beta) {
                for(short free_the_children = iter; free_the_children < root->nchildren; free_the_children++) {
                    free(root->child[free_the_children]);
                }
                break;
            }
            free(root->child[iter]);
        }
    } else {
        value = LONG_MAX;
        for(short iter = 0; iter < root->nchildren; iter++) {
            long heuristic = alphaBeta(root->child[iter], alpha, beta, depth - 1, side, TRUE);

            if(heuristic < value) {
                value = heuristic;
            }
            if(value < beta) {
                beta = value;
            }
            if(beta <= alpha) {
                for(short free_the_children = iter; free_the_children < root->nchildren; free_the_children++) {
                    free(root->child[free_the_children]);
                }
                break;
            }
            free(root->child[iter]);
        }
    }
    free(root->child);
    return value;
}


#include "minimax.h"

static unsigned exploredPositions;
static long alphaBeta(Node *root, Prune prune, const short depth, const Side side, const Bool maximizing);

static int color(const Side side) {
    return (side == X) ? 1 : -1;
}

void machineMove(Game *game) {
    Node *root = game->node;
    const short depth = game->depth;
    const Side side = game->side;

    ASSERT(root != NULL);
    ASSERT(depth > 0);
    ASSERT(root->nchildren > 0);

    const Prune start_prune = {
        .alpha = LONG_MIN,
        .beta = LONG_MAX
    };

    for(short iter = 0; iter < depth - 1; iter++) {
        alphaBeta(root, start_prune, iter, side, FALSE);
    }

    createChildren(root);
    Node *answer = (Node *) malloc(sizeof(Node));

    long value = LONG_MIN;

    exploredPositions = 0;
    clock_t start = clock();
    for(short iter = 0; iter < root->nchildren; iter++) {
        long heuristic = alphaBeta(root->child[iter], start_prune, depth - 1, side, FALSE);
        if(heuristic > value) {
            value = heuristic;
            copyNode(answer, root->child[iter]);
        }
        free(root->child[iter]);
    }
    clock_t end = clock();

    game->stats.elapsedTime = (double) (end - start);
    game->stats.exploredPositions = exploredPositions;
    // game->stats.lastMove = col;
    game->stats.lastHeuristic = value;

    free(root->child);
    copyNode(root, answer);
    free(answer);
}

static long alphaBeta(Node *root, Prune prune, const short depth, const Side side, const Bool maximizing) {
    exploredPositions++;

    if(depth == 0 || root->nchildren == 0) {
        long h = getHeuristic(root, side) - color(side) * color(root->turn) * ( N*N - depth );
        return h;
    }

    long value;
    createChildren(root);
    if(maximizing) {
        value = LONG_MIN;
        for(short iter = 0; iter < root->nchildren; iter++) {
            long heuristic;
            Key key = boardToKey(root->child[iter]->board);
            const Entry *entry = findEntry(tables, key);
            if(entry == NULL) {
                heuristic = alphaBeta(root->child[iter], prune, depth - 1, side, FALSE);
                addEntry(tables, (Entry) { .key = key, .heuristic = heuristic });
            } else {
                heuristic = entry->heuristic;
            }

            if(heuristic > value) {
                value = heuristic;
            }
            if(value > prune.alpha) {
                prune.alpha = value;
            }
            if(prune.alpha >= prune.beta) {
                break;
            }
        }
    } else {
        value = LONG_MAX;
        for(short iter = 0; iter < root->nchildren; iter++) {
            long heuristic;
            Key key = boardToKey(root->child[iter]->board);
            const Entry *entry = findEntry(tables, key);
            if(entry == NULL) {
                heuristic = alphaBeta(root->child[iter], prune, depth - 1, side, TRUE);
                addEntry(tables, (Entry) { .key = key, .heuristic = heuristic });
            } else {
                heuristic = entry->heuristic;
            }

            if(heuristic < value) {
                value = heuristic;
            }
            if(value < prune.beta) {
                prune.beta = value;
            }
            if(prune.beta <= prune.alpha) {
                break;
            }
        }
    }

    for(short iter = 0; iter < root->nchildren; iter++) {
        free(root->child[iter]);
    }
    free(root->child);
    return value;
}


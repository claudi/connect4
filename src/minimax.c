#include "minimax.h"

static unsigned exploredPositions;
static long alphaBeta(Node *root, Prune prune, const MinimaxStatus status);
static MinimaxStatus nextStatus(const MinimaxStatus status);

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
        const MinimaxStatus start_status = {
            .depth = iter,
            .side = side,
            .maximizing = FALSE
        };
        alphaBeta(root, start_prune, start_status);
    }

    createChildren(root);
    Node *answer = (Node *) malloc(sizeof(Node));

    long value = LONG_MIN;
    const MinimaxStatus start_status = {
        .depth = depth - 1,
        .side = side,
        .maximizing = FALSE,
    };

    exploredPositions = 0;
    clock_t start = clock();
    for(short iter = 0; iter < root->nchildren; iter++) {
        long heuristic = alphaBeta(root->child[iter], start_prune, start_status);
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

static long alphaBeta(Node *root, Prune prune, const MinimaxStatus status) {
    exploredPositions++;

    if(status.depth == 0 || root->nchildren == 0) {
        long h = getHeuristic(root, status.side) - color(status.side) * color(root->turn) * ( N*N - status.depth );
        return h;
    }

    long value;
    createChildren(root);
    if(status.maximizing) {
        value = LONG_MIN;
        for(short iter = 0; iter < root->nchildren; iter++) {
            long heuristic;
            Key key = boardToKey(root->child[iter]->board);
            const Entry *entry = findEntry(tables, key);
            if(entry == NULL) {
                heuristic = alphaBeta(root->child[iter], prune, nextStatus(status));
                const Entry tmp = {
                    .key = key,
                    .heuristic = heuristic
                };
                addEntry(tables, tmp);
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
                heuristic = alphaBeta(root->child[iter], prune, nextStatus(status));
                const Entry tmp = {
                    .key = key,
                    .heuristic = heuristic
                };
                addEntry(tables, tmp);
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

static MinimaxStatus nextStatus(const MinimaxStatus status) {
    const MinimaxStatus next =  {
        .depth = status.depth - 1,
        .side = status.side,
        .maximizing = NOT(status.maximizing),
    };
    return next;
}


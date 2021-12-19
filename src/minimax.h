#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD
#include "defs.h"
#include "game.h"
#include "heuristic.h"
#include "table.h"
#include "tree.h"
#include <time.h>

typedef struct {
    long alpha;
    long beta;
} Prune;

typedef struct {
    short depth;
    const Side side;
    Bool maximizing;
} MinimaxStatus;

void machineMove(Game *game);

#endif // MINIMAX_GUARD

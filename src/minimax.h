#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD
#include "defs.h"
#include "tree.h"
#include "table.h"
#include "game.h"
#include "heuristic.h"
#include "tree.h"
#include <time.h>

typedef struct {
    long alpha;
    long beta;
} Prune;

void machineMove(Game *game);

#endif // MINIMAX_GUARD


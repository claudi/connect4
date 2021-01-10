#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD
#include "defs.h"
#include "game.h"
#include "heuristic.h"
#include "tree.h"
#include <time.h>

int color(const Side side);
void machineMove(Game *game);

#endif // MINIMAX_GUARD


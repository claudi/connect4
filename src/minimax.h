#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD
#include "defs.h"
#include "tree.h"
#include "table.h"
#include "heuristic.h"
#include <time.h>

extern unsigned exploredPositions;
extern double elapsedTime;

int color(const Side side);
void machineMove(Node *root, const short depth, const Side side);

#endif // MINIMAX_GUARD


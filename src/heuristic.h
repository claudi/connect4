#ifndef HEURISTIC_GUARD
#define HEURISTIC_GUARD
#include "board.h"
#include "defs.h"
#include "masks.h"
#include <stdlib.h>

long getHeuristic(const Node *node, const Side side);
long getOrderingHeuristic(const Node *node, const Side side);

#endif // HEURISTIC_GUARD

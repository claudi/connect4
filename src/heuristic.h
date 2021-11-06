#ifndef HEURISTIC_GUARD
#define HEURISTIC_GUARD
#include "defs.h"
#include "masks.h"

long getHeuristic(const Node *node, const Side side);
long getOrderingHeuristic(const Node *node, const Side side);

#endif // HEURISTIC_GUARD


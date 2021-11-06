#ifndef TREE_GUARD
#define TREE_GUARD
#include "board.h"
#include "defs.h"
#include "heuristic.h"

/*
 * Nodes called root or parent are assumed to
 * be initialized with real board and values
 */
Node *initNode(void);
void createChildren(Node *parent);

#endif // TREE_GUARD


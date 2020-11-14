#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD
#include "defs.h"
#include "tree.h"
#include "heuristic.h"
#include <time.h>

int side(const Side side);
short chooseMove(Node *root, const short depth, const Side side);
int minimax(Node *root, const short depth);

#endif // MINIMAX_GUARD


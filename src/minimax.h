#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD
#include "defs.h"
#include "tree.h"
#include "heuristic.h"
#include <time.h>

int side(const Side side);
size_t chooseMove(Node *root, const ssize_t depth);
int minimax(Node *root, const ssize_t depth);

#endif // MINIMAX_GUARD

#include "defs.h"
#include "tree.h"
#include "heuristic.h"
#include <time.h>

int side(const Side side);
size_t chooseMove(Node *root, const ssize_t depth);
float minimax(Node *root, const ssize_t depth);


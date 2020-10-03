#include "defs.h"
#include "tree.h"
#include <time.h>
#include <stdlib.h>

int side(const Side side);
float heuristic(const Node *node);
size_t chooseMove(Node *root, const ssize_t depth);
float minimax(Node *root, const ssize_t depth);


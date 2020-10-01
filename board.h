#include "defs.h"
#include <stdlib.h>

uint64_t shift(const size_t row, const size_t col);
void copyNode(Node *destination, const Node *origin);
void copyBoard(Board *destination, const Board *origin);
int makeMove(Node *node, const size_t column);

// TODO: return values

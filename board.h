#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

uint64_t shift(const size_t row, const size_t col);
void copyNode(Node *destination, const Node *origin);
void copyBoard(Board *destination, const Board *origin);
int makeMove(Node *node, const size_t column);
void printBoard(const Board *board);
void printNode(const Node *node);

// TODO: return values

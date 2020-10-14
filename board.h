#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

Mask shift(const size_t row, const size_t col);
size_t pos2Shift(const size_t row, const size_t col);
void copyNode(Node *destination, const Node *origin);
void copyBoard(Board *destination, const Board *origin);
int makeMove(Node *node, const size_t column);
void printBoard(const Node *node);
void printNode(const Node *node);


#ifndef BOARD_GUARD
#define BOARD_GUARD
#include "defs.h"
#include "heuristic.h"
#include <stdio.h>
#include <stdlib.h>

#define pos2Shift(row, col) ((N * row) + col)

Mask shift(const short row, const short col);
void copyNode(Node *destination, const Node *origin);
void copyBoard(Board *destination, const Board *origin);
short makeMove(Node *node, const short col);
void printBoard(const Node *node);
void printNode(const Node *node);

#endif // BOARD_GUARD


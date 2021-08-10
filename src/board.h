#ifndef BOARD_GUARD
#define BOARD_GUARD
#include "defs.h"
#include "heuristic.h"
#include <stdio.h>
#include <stdlib.h>

#define POS_TO_SHIFT(row, col) ((N * (row)) + (col))
#define FULL_COLUMN(b,c) ((b)[BOTH] & shift(N - 1, (c)))

Mask shift(const short row, const short col);
void copyNode(Node *destination, const Node *origin);
void copyBoard(Board *destination, const Board *origin);
short makeMove(Node *node, const short col);
char showTurn(const Side side);
void printBoard(const Node *node);
void printNode(const Node *node);

#endif // BOARD_GUARD


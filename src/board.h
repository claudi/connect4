#ifndef BOARD_GUARD
#define BOARD_GUARD
#include "defs.h"
#include "masks.h"
#include <stdio.h>
#include <stdlib.h>

#define FULL_COLUMN(b,c) ((b)[BOTH] & shift(N - 1, (c)))

void copyNode(Node *destination, const Node *origin);
void copyBoard(Board *destination, const Board *origin);
short makeMove(Node *node, const short col);
unsigned wonBoard(const Board *board);
char showTurn(const Side side);
void printBoard(const Node *node);
void printNode(const Node *node);

#endif // BOARD_GUARD


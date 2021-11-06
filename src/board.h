#ifndef BOARD_GUARD
#define BOARD_GUARD
#include "defs.h"

#define FULL_COLUMN(b,c) ((b)[BOTH] & shift(BOARD_SIZE - 1, (c)))

void copyNode(Node *destination, const Node *origin);
char showTurn(const Side side);
short makeMove(Node *node, const short col);
void copyBoard(Board *destination, const Board *origin);
void printNode(const Node *node);

#endif // BOARD_GUARD


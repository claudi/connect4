#ifndef RED_BLACK_GUARD
#define RED_BLACK_GUARD
#include "defs.h"
#include "board.h"
#include <stdio.h>

typedef __uint128_t Key;

void printKey(const Key key);
Key boardToKey(const Board *board);
void printRBTree(void);

#endif // RED_BLACK_GUARD

#ifndef KEY_GUARD
#define KEY_GUARD
#include "defs.h"
#include "board.h"

typedef __uint128_t Key;

void printKey(const Key key);
Key boardToKey(const Board *board);

#endif // KEY_GUARD

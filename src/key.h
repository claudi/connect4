#ifndef KEY_GUARD
#define KEY_GUARD
#include "defs.h"
#include "board.h"

typedef __uint128_t Key;

Key boardToKey(const Board *board);

#endif // KEY_GUARD


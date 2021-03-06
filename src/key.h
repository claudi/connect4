#ifndef KEY_GUARD
#define KEY_GUARD
#include "defs.h"
#include "board.h"

typedef __uint128_t Key;

extern Key *verticalKeys;

void printKey(const Key key);
Key boardToKey(const Board *board);
Key mirrorKey(const Key key);
void initKeys(void);
void freeKeys(void);

#endif // KEY_GUARD


#ifndef RED_BLACK_GUARD
#define RED_BLACK_GUARD
#include "defs.h"
#include "board.h"
#include <stdio.h>

typedef __uint128_t Key;
typedef enum {BLACK, RED} Color;

typedef struct RBNode RBNode;
struct RBNode {
    RBNode *parent;
    RBNode *left;
    RBNode *right;
    Color color;
    Key key;
    long heuristic;
};

extern Key *verticalKeys;

void printKey(const Key key);
Key boardToKey(const Board *board);
Key mirrorKey(const Key key);
void initKeys(void);
void freeKeys(void);
void printRBTree(void);

#endif // RED_BLACK_GUARD

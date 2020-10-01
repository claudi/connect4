#ifndef DEFS_GUARD
#define DEFS_GUARD
#include <stdint.h>

#define N 8
#define next(turn) ((turn == X) ? O : X)
// #define next(turn) (b*(turn-b)/(a-b) + a*(turn-a)/(b-a))

typedef enum {FALSE, TRUE} Bool;
typedef enum {X, O, BOTH, nsides} Side;
// typedef char Board [N][N];
typedef uint64_t Board;

typedef struct Node Node;
struct Node {
    Board board[nsides];
    Side turn;                  // Next to move
    short int nchildren;
    Node **child;
    float heuristic;
};

#endif

#ifndef DEFS_GUARD
#define DEFS_GUARD
#include <stdint.h>

#define N 8
#define next(turn) ((turn == X) ? O : X)
// #define next(turn) (O*(turn-O)/(X-O) + X*(turn-X)/(O-X))

typedef enum {FALSE, TRUE} Bool;
typedef enum {X, O, BOTH, nsides} Side; // TODO: Get rid of BOTH
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

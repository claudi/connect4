#ifndef DEFS_GUARD
#define DEFS_GUARD
#include <stdint.h> // for uint64_t
#include <float.h>  // for FLT_MAX and FLT_MIN

#define N 8
#define next(turn) ((turn == X) ? O : X)
// #define next(turn) (O*(turn-O)/(X-O) + X*(turn-X)/(O-X))

typedef enum {FALSE, TRUE} Bool;
typedef enum {X, O, BOTH, nsides} Side; // TODO: Get rid of BOTH
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

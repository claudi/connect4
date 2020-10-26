#ifndef DEFS_GUARD
#define DEFS_GUARD
#include <stdint.h> // for uint64_t
#include <float.h>  // for FLT_MAX and FLT_MIN

#define N 8
#define next(turn) ((turn == X) ? O : X)
// #define next(turn) (O*(turn-O)/(X-O) + X*(turn-X)/(O-X))

enum {TURN, BOTH, nboards};
typedef enum {FALSE, TRUE} Bool;
typedef enum {X, O, nsides} Side;
typedef uint64_t Board;
typedef uint64_t Mask;

typedef struct Node Node;
struct Node {
    Board board[nboards];
    Side turn;                  // Last move
    short int nchildren;
    Node **child;
    float heuristic;
};

#ifndef DEBUG
    #define ASSERT(n) {}
#else
    #define ASSERT(n)                                   \
    if(!(n)) {                                          \
        fprintf(stderr, "\n\t  DEBUG INFO  \n");        \
        fprintf(stderr, "\t Failed: %s\n", #n);         \
        fprintf(stderr, "\t     On: %s\n", __DATE__);   \
        fprintf(stderr, "\t     At: %s\n", __TIME__);   \
        fprintf(stderr, "\tIn File: %s\n", __FILE__);   \
        fprintf(stderr, "\tAt Line: %d\n", __LINE__);   \
        fprintf(stderr, "\n");                          \
        exit(1);                                        \
    }
#endif // DEBUG

#endif // DEFS_GUARD


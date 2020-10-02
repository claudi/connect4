#ifndef DEFS_GUARD
#define DEFS_GUARD
#include <stdlib.h>
#include <stdint.h>

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
#endif

#endif


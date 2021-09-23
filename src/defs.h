#ifndef DEFS_GUARD
#define DEFS_GUARD
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // for uint64_t
#include <limits.h> // for LONG_MIN and LONG_MAX
#include <time.h>

#define N 8

#define NEXT(turn) (((turn) == X_SIDE) ? O_SIDE : X_SIDE)
#define NOT(b) (((b) == TRUE) ? FALSE : TRUE)

enum { TURN, BOTH, NBOARDS };
typedef enum { FALSE, TRUE } Bool;
typedef enum { X_SIDE, O_SIDE, NSIDES } Side;
typedef uint64_t Board;
typedef uint64_t Mask;

typedef struct Node Node;
struct Node {
    Board board[NBOARDS];
    Side turn;                  // Last move
    short nchildren;
    Node **child;
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
        exit(EXIT_FAILURE);                             \
    }
#endif // DEBUG

#endif // DEFS_GUARD


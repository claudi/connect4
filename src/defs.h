#ifndef DEFS_GUARD
#define DEFS_GUARD
#include <stdlib.h>
#include <stdint.h> // for uint64_t
#include <limits.h> // for LONG_MIN and LONG_MAX
#include <time.h>

#define N 8
#define START_BOARD initNode()
#define START_TURN 1
#define START_DEPTH 4
#define START_PLAYER_SIDE X
#define START_SIDE X
#define START_HELP TRUE

#define next(turn) ((turn == X) ? O : X)
#define not(b) ((b == TRUE) ? FALSE : TRUE)

enum {TURN, BOTH, nboards};
typedef enum {FALSE, TRUE} Bool;
typedef enum {X, O, nsides} Side;
typedef uint64_t Board;
typedef uint64_t Mask;

typedef struct Node Node;
struct Node {
    Board board[nboards];
    Side turn;                  // Last move
    short nchildren;
    Node **child;
};

typedef struct {
    Node *node;
    short turn;
    short depth;
    Side playerSide;
    Side side;
    Bool help;
} Game;

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


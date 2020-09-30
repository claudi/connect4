#ifndef DEFS_GUARD
#define DEFS_GUARD

#define N 8

typedef enum {FALSE, TRUE} Bool;
typedef enum {X, O, BOTH, nsides} Side;
typedef char Board [N][N];
// typedef uint64_t Board;

typedef struct Node Node;
struct Node {
    Board board[nsides];
    // Board board[nsides];
    short int nchildren;
    Node **child;
    float heuristic;
};

#endif

#ifndef HEURISTIC_GUARD
#define HEURISTIC_GUARD
#include "heuristic.h"

int heuristic(const Node *node) {
    int val1 = matches(node->board, match1);
    int val2 = matches(node->board, match2);
    int val3 = matches(node->board, match3);
    int val4 = matches(node->board, match4);
    return (val1 + 10*val2 + 100*val3 + 1000*val4);
}

#endif // HEURISTIC_GUARD


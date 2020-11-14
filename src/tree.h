#ifndef TREE_GUARD
#define TREE_GUARD
#include "defs.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Nodes called root or parent are assumed to
 * be initialized with real board and values
 */
Node *initNode(void);
// void createTree(Node *root, const short depth);
Node *createChild(Node *parent, const short child);
void createChildren(Node *parent);
// void printTree(const Node *root);

// TODO: free tree
#endif // TREE_GUARD


#include "defs.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Nodes called root or parent are assumed to
 * be initialized with real board and values
 */
void initNode(Node *node);
void createTree(Node *root, const size_t depth);
Node *createChild(Node *parent, const size_t child);
void createChildren(Node *parent);

// TODO: return values

#include "defs.h"
#include <stdlib.h>

/*
 * Nodes called root or parent are assumed to
 * be initialized with real board and values
 */
void initNode(Node *node);
void printNode(Node *node);
void initTree(Node *root, size_t depth);
void initChild(Node *parent, size_t column);
void initChildren(Node *parent);

// TODO: return values

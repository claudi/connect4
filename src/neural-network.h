#ifndef NEURALNETWORK_GUARD
#define NEURALNETWORK_GUARD
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    short nlayers;
    short *ncells;
    int ***weights;
} Network;

extern Network *network[nsides];

float randcoef(void);
int prodesc(const short dim, const int *u, const int *v);
void printVector(const short dim, const int *v);
void printNetwork(const Network *network);
void initNetworks(FILE *coefsX, FILE *coefsO, const short nlayers, const short *topology);
// Network *initNetwork(const short nlayers, const short *topology);
int *evalNetwork(const Network *network, const int *inputs);


#endif // NEURALNETWORK_GUARD

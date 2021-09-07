#ifndef NEURALNETWORK_GUARD
#define NEURALNETWORK_GUARD
#include "defs.h"

typedef int Num;
typedef size_t Topology[];

typedef struct {
    size_t ncells;
    Num **weights;
} Layer;

typedef struct {
    size_t ninputs;
    size_t nlayers;
    Layer *layers;
} Network;

void testNetwork(void);

#endif // NEURALNETWORK_GUARD


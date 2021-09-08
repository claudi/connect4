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

Num *evaluateNetwork(const Network *network, const Num *input);
Network *initNetwork(const size_t nlayers, const Topology topology);

extern Network *network;

#endif // NEURALNETWORK_GUARD


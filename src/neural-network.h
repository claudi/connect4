#ifndef NEURALNETWORK_GUARD
#define NEURALNETWORK_GUARD
#include "defs.h"

typedef int64_t Num;
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
Bool initNetwork(const size_t nlayers, const Topology topology);

#endif // NEURALNETWORK_GUARD


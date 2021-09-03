#include "neural-network.h"

Network initNetwork(const size_t nlayers, const Topology topology) {
    ASSERT(nlayers > 0);
    ASSERT(topology != NULL);

    Layer *layers = (Layer *) malloc(nlayers * sizeof(Layer));

    for(size_t iter = 0; iter < nlayers; iter++) {
        Num **weights = (Num **) malloc(topology[iter + 1] * sizeof(Num *));
        for(size_t iter_i = 0; iter_i < topology[iter + 1]; iter_i++) {
            weights[iter_i] = (Num *) malloc(topology[iter] * sizeof(Num));
            for(size_t iter_j = 0; iter_j < topology[iter]; iter_j++) {
                weights[iter_i][iter_j] = 0;
            }
        }

        layers[iter] = (Layer) {
            .ncells = topology[iter + 1],
            .weights = weights,
        };
    }

    return (Network) {
        .ninputs = topology[0],
        .nlayers = nlayers,
        .layers = layers,
    };
}


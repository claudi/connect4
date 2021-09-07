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

void printNetwork(const Network *network) {
    printf("Topology with %zu layers\n", network->nlayers);
    printf("\t%zu ", network->ninputs);
    for(size_t iter = 0; iter < network->nlayers; iter++) {
        printf("%2zu ", network->layers[iter].ncells);
    }
    printf("\n");
    printf("Layer 0 with %zu cells\n", network->layers[0].ncells);
    for(size_t cell = 0; cell < network->layers[0].ncells; cell++) {
        printf("\t");
        for(size_t weight = 0; weight < network->ninputs; weight++) {
            printf("%2d ", network->layers[0].weights[cell][weight]);
        }
        printf("\n");
    }
    for(size_t iter = 1; iter < network->nlayers; iter++) {
        printf("Layer %zu with %zu cells\n", iter, network->layers[iter].ncells);
        for(size_t cell = 0; cell < network->layers[iter].ncells; cell++) {
            printf("\t");
            for(size_t weight = 0; weight < network->layers[iter-1].ncells; weight++) {
                printf("%d ", network->layers[iter].weights[cell][weight]);
            }
            printf("\n");
        }
    }
}

Num *evaluateNetwork(const Network *network, const Num *input) {
    ASSERT(network != NULL);
    ASSERT(input != NULL);

    size_t maxWidth = 0;
    if(maxWidth < network->ninputs) {
        maxWidth = network->ninputs;
    }
    for(size_t iter = 0; iter < network->nlayers; iter++) {
        size_t ncells = network->layers[iter].ncells;
        if(maxWidth < ncells) {
            maxWidth = ncells;
        }
    }
    ASSERT(maxWidth > 0);

    Num *prev = (Num *) malloc(maxWidth * sizeof(Num));
    for(size_t iter = 0; iter < network->ninputs; iter++) {
        prev[iter] = input[iter];
    }

    Num *output = (Num *) malloc(maxWidth * sizeof(Num));
    for(size_t iter = 0; iter < network->ninputs; iter++) {
        output[iter] = 0;
    }

    for(size_t cell = 0; cell < network->layers[0].ncells; cell++) {
        for(size_t weight = 0; weight < network->ninputs; weight++) {
            output[cell] += prev[weight] * network->layers[0].weights[cell][weight];
        }
    }

    for(size_t iter = 1; iter < network->nlayers; iter++) {
        for(size_t cell = 0; cell < network->layers[iter].ncells; cell++) {
            output[cell] = 0;
            for(size_t weight = 0; weight < network->layers[iter-1].ncells; weight++) {
                output[cell] += prev[weight] * network->layers[iter].weights[cell][weight];
            }
        }
    }

    return output;
}

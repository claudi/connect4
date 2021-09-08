#include "neural-network.h"

Network *network;
Network *initNetwork(const size_t nlayers, const Topology topology) {
    ASSERT(nlayers > 0);
    ASSERT(topology != NULL);

    Layer *layers = (Layer *) malloc(nlayers * sizeof(Layer));

    size_t count = 0;
    for(size_t iter = 0; iter < nlayers; iter++) {
        Num **weights = (Num **) malloc(topology[iter + 1] * sizeof(Num *));
        for(size_t iter_i = 0; iter_i < topology[iter + 1]; iter_i++) {
            weights[iter_i] = (Num *) malloc(topology[iter] * sizeof(Num));
            for(size_t iter_j = 0; iter_j < topology[iter]; iter_j++) {
                weights[iter_i][iter_j] = count++;
            }
        }

        layers[iter] = (Layer) {
            .ncells = topology[iter + 1],
            .weights = weights,
        };
    }

    Network *network = (Network *) malloc(sizeof(Network));

    *network = (Network) {
        .ninputs = topology[0],
        .nlayers = nlayers,
        .layers = layers,
    };
    return network;
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

Num prodesc(const Num *u, const Num *v, const size_t size) {
    Num result = 0;

    for(size_t iter = 0; iter < size; iter++) {
        result += u[iter] * v[iter];
    }

    return result;
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

    for(size_t cell = 0; cell < network->layers[0].ncells; cell++) {
        output[cell] = prodesc(prev, network->layers[0].weights[cell], network->ninputs);
    }
    for(size_t cell = 0; cell < network->layers[0].ncells; cell++) {
        prev[cell] = output[cell];
    }

    for(size_t iter = 1; iter < network->nlayers-1; iter++) {
        for(size_t cell = 0; cell < network->layers[iter].ncells; cell++) {
            output[cell] = prodesc(prev, network->layers[iter].weights[cell], network->layers[iter-1].ncells);
        }
        for(size_t cell = 0; cell < network->layers[iter].ncells; cell++) {
            prev[cell] = output[cell];
        }
    }


    const size_t iter = network->nlayers-1;
    for(size_t cell = 0; cell < network->layers[iter].ncells; cell++) {
        output[cell] = prodesc(prev, network->layers[iter].weights[cell], network->layers[iter-1].ncells);
    }

    return output;
}

void testNetwork(void) {
    Topology topology = {3, 2, 4, 2};
    size_t nlayers = 3;
    Num input[] = {1, 1, 1};

    Network *network = initNetwork(nlayers, topology);
    printNetwork(network);

    Num *result = evaluateNetwork(network, input);
    printf("Input:\n\t");
    for(size_t iter = 0; iter < network->ninputs; iter++) {
        printf("%2d ", input[iter]);
    }
    printf("\n");
    printf("Result:\n\t");
    for(size_t iter = 0; iter < network->layers[network->nlayers-1].ncells; iter++) {
        printf("%2d ", result[iter]);
    }
    printf("\n");
}


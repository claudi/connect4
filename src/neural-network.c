#include "neural-network.h"

Network *network[nsides];
Network *initNetwork(FILE *coefs, const short nlayers, const short *topology);
int relu(int x) {
    return x;
    return (x >= 0) ? x : 0;
}

// int main(void) {
    // Network *network;

    // network = initNetwork(DEFAULT_NLAYERS, DEFAULT_TOPOLOGY);
    // ASSERT(network != NULL);

    // // printNetwork(network);
    
    // int *inputs = (int *) malloc(network->ncells[0] * sizeof(int));
    // for(short iter = 0; iter < network->ncells[0]; iter++) {
        // inputs[iter] = randcoef();
    // }

    // // printVector(network->ncells[0], inputs);
    // int *output = evalNetwork(network, inputs);
    // // printVector(network->ncells[network->nlayers - 1], output);

    // return 0;
// }

float randcoef(void) {
    return ((float) (rand() % 100)) / (float) 100;
}

void initNetworks(FILE *coefsX, FILE *coefsO, const short nlayers, const short *topology) {
    ASSERT(nlayers > 0);
    ASSERT(topology != NULL);

    network[X] = initNetwork(coefsX, nlayers, topology);
    network[O] = initNetwork(coefsO, nlayers, topology);
}

Network *initNetwork(FILE *coefs, const short nlayers, const short *topology) {
    Network *network = (Network *) malloc(sizeof(Network));

    network->nlayers = nlayers;
    network->ncells = (short *) malloc(nlayers * sizeof(short));
    for(short layer = 0; layer < network->nlayers; layer++) {
        network->ncells[layer] = topology[layer];
    }

    network->weights = (int ***) malloc((nlayers - 1) * sizeof(int **));

    for(short layer = 0; layer < network->nlayers - 1; layer++) {
        network->weights[layer] = (int **) malloc(topology[layer+1] * sizeof(int *));
        for(short cell = 0; cell < network->ncells[layer+1]; cell++) {
            network->weights[layer][cell] = (int *) malloc(topology[layer] * sizeof(int));
        }
    }

    // TODO: Init coeficients
    int coef;
    for(short layer = 0; layer < network->nlayers - 1; layer++) {
        for(short cell = 0; cell < network->ncells[layer+1]; cell++) {
            for(short weight = 0; weight < network->ncells[layer]; weight++) {
                if(fscanf(coefs, "%d", &coef) != 1) {
                    fprintf(stderr, "No s'ha llegit els coeficients \
                                     d'una de les xarxes neuronals \
                                     correctament\n");
                    exit(-1);
                }
                network->weights[layer][cell][weight] = coef;
            }
        }
    }

    fclose(coefs);
    return network;
}

int prodesc(const short dim, const int *u, const int *v) {
    int output = 0;

    for(short iter = 0; iter < dim; iter++) {
        output += u[iter] * v[iter];
    }

    return output;
}

void printVector(const short dim, const int *v) {
    for(short iter = 0; iter < dim; iter++) {
        printf("%d ", v[iter]);
    }
    printf("\n");
}

int *evalNetwork(const Network *network, const int *inputs) {
    int **outputs = (int **) malloc(network->nlayers * sizeof(int *));

    for(short layer = 0; layer < network->nlayers; layer++) {
        outputs[layer] = (int *) malloc(network->ncells[layer] * sizeof(int));
    }

    for(short cell = 0; cell < network->ncells[0]; cell++) {
        outputs[0][cell] = inputs[cell];
    }

    for(short layer = 1; layer < network->nlayers-1; layer++) {
        for(short cell = 0; cell < network->ncells[layer]; cell++) {
            // outputs[layer][cell] = 0;
            // for(short iter = 0; iter < network->ncells[layer-1]; iter++) {
                // outputs[layer][cell] += outputs[layer-1][iter] * network->weights[layer-1][cell][iter];
            // }
            outputs[layer][cell] = relu(prodesc(network->ncells[layer-1], outputs[layer-1], network->weights[layer-1][cell]));
        }
    }

    short layer = network->nlayers - 1;
    for(short cell = 0; cell < network->ncells[layer]; cell++) {
        outputs[layer][cell] = prodesc(network->ncells[layer-1], outputs[layer-1], network->weights[layer-1][cell]);
    }

    return outputs[network->nlayers - 1];
}

void printNetwork(const Network *network) {
    printf("nlayers:\n\t%d\n", network->nlayers);
    printf("\n");

    printf("*ncells:\n\t");
    for(short layer = 0; layer < network->nlayers; layer++) {
        printf("%d ", network->ncells[layer]);
    }
    printf("\n");
    printf("\n");

    printf("***weights:\n");
    for(short layer = 0; layer < network->nlayers - 1; layer++) {
        for(short cell = 0; cell < network->ncells[layer+1]; cell++) {
            printf("\t");
            for(short weight = 0; weight < network->ncells[layer]; weight++) {
                printf("%5.4d ", network->weights[layer][cell][weight]);
            }
            printf("\n");
        }
        printf("\n");
    }

}


#include "architecture.h"

float randcoef(void);
float prodesc(const short dim, const float *u, const float *v);
void printVector(const short dim, const float *v);
float *evalNetwork(const Network *network, const float *inputs);

int main(void) {
    Network *network;

    network = initNetwork(DEFAULT_NLAYERS, DEFAULT_TOPOLOGY);
    ASSERT(network != NULL);

    printNetwork(network);
    
    float *inputs = (float *) malloc(network->ncells[0] * sizeof(float));
    for(short iter = 0; iter < network->ncells[0]; iter++) {
        inputs[iter] = randcoef();
    }

    printVector(network->ncells[0], inputs);
    float *output = evalNetwork(network, inputs);
    printVector(network->ncells[network->nlayers - 1], output);

    return 0;
}

float randcoef(void) {
    return ((float) (rand() % 100)) / (float) 100;
}

Network *initNetwork(const short nlayers, const short *topology) {
    ASSERT(nlayers > 0);
    ASSERT(topology != NULL);

    Network *network = (Network *) malloc(sizeof(Network));

    network->nlayers = nlayers;
    network->ncells = (short *) malloc(nlayers * sizeof(short));
    for(short layer = 0; layer < network->nlayers; layer++) {
        network->ncells[layer] = topology[layer];
    }

    network->weights = (float ***) malloc((nlayers - 1) * sizeof(float **));

    for(short layer = 0; layer < network->nlayers - 1; layer++) {
        network->weights[layer] = (float **) malloc(topology[layer+1] * sizeof(float *));
        for(short cell = 0; cell < network->ncells[layer+1]; cell++) {
            network->weights[layer][cell] = (float *) malloc(topology[layer] * sizeof(float));
        }
    }

    // TODO: Init coeficients
    for(short layer = 0; layer < network->nlayers - 1; layer++) {
        for(short cell = 0; cell < network->ncells[layer+1]; cell++) {
            for(short weight = 0; weight < network->ncells[layer]; weight++) {
                network->weights[layer][cell][weight] = randcoef();
            }
        }
    }

    return network;
}

float prodesc(const short dim, const float *u, const float *v) {
    float output = 0;

    for(short iter = 0; iter < dim; iter++) {
        output += u[iter] * v[iter];
    }

    return output;
}

void printVector(const short dim, const float *v) {
    for(short iter = 0; iter < dim; iter++) {
        printf("%f ", v[iter]);
    }
    printf("\n");
}

float *evalNetwork(const Network *network, const float *inputs) {
    float **outputs = (float **) malloc(network->nlayers * sizeof(float *));

    for(short layer = 0; layer < network->nlayers; layer++) {
        outputs[layer] = (float *) malloc(network->ncells[layer] * sizeof(float));
    }

    for(short cell = 0; cell < network->ncells[0]; cell++) {
        outputs[0][cell] = inputs[cell];
    }

    for(short layer = 1; layer < network->nlayers; layer++) {
        for(short cell = 0; cell < network->ncells[layer]; cell++) {
            // outputs[layer][cell] = 0;
            // for(short iter = 0; iter < network->ncells[layer-1]; iter++) {
                // outputs[layer][cell] += outputs[layer-1][iter] * network->weights[layer-1][cell][iter];
            // }
            outputs[layer][cell] = prodesc(network->ncells[layer-1], outputs[layer-1], network->weights[layer-1][cell]);
        }
    }

    return outputs[network->nlayers - 1];
}

float *evalCNetwork(const CNetwork *network, const float **inputs) {
    float ***outputs = (float ***) malloc(network->nlayers * sizeof(float **));

    for(short layer = 0; layer < network->nlayers; layer++) {
        outputs[layer] = (float **) malloc(network->dimX[layer] * sizeof(float *));
        for(short cell = 0; cell < network->dimX[layer]; cell++) {
            outputs[layer][cell] = (float *) malloc(network->dimY[layer] * sizeof(float));
        }
    }

    for(short cell_i = 0; cell_i < network->dimX[0]; cell_i++) {
        for(short cell_j = 0; cell_j < network->dimY[0]; cell_j++) {
            outputs[0][cell_i][cell_j] = inputs[cell_i][cell_j];
        }
    }

    for(short layer = 1; layer < network->nlayers; layer++) {
        for(short cell_i = 0; cell_i < network->dimX[0]; cell_i++) {
            for(short cell_j = 0; cell_j < network->dimY[0]; cell_j++) {
                outputs[layer][cell_i][cell_j] = 0;
                // CONTINUE HERE
            }
        }
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
                printf("%5.4f ", network->weights[layer][cell][weight]);
            }
            printf("\n");
        }
        printf("\n");
    }

}


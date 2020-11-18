#include "architecture.h"

int main(void) {
    Network *network;

    network = initNetwork(DEFAULT_NINPUTS, DEFAULT_NLAYERS, DEFAULT_NNEURONS);
    ASSERT(network != NULL);

    printNetwork(network);

    return 0;
}

Network *initNetwork(const short ninputs, const short nlayers, const short *nneurons) {
    ASSERT(nlayers > 0);
    ASSERT(nneurons != NULL);
    Network *network = (Network *) malloc(sizeof(Network));

    network->nlayers = nlayers;
    network->ninputs = ninputs;

    network->input = (float *) malloc(ninputs * sizeof(float));
    network->nneurons = (short *) malloc(nlayers * sizeof(short));
    network->neuron = (float **) malloc(nlayers * sizeof(float *));
    network->weight = (float **) malloc(nlayers * sizeof(float *));

    for(short iter = 0; iter < nlayers; iter++) {
        network->nneurons[iter] = nneurons[iter];
        network->neuron[iter] = (float *) malloc(nneurons[iter] * sizeof(float));
        network->weight[iter] = (float *) malloc(nneurons[iter] * sizeof(float));
    }

    //TODO: Assign initial values
    for(short iter = 0; iter < network->ninputs; iter++) {
        network->input[iter] = ((float) (rand() % 100)) / (float) 100;
    }

    for(short iter_i = 0; iter_i < network->nlayers; iter_i++) {
        for(short iter_j = 0; iter_j < network->nneurons[iter_i]; iter_j++) {
            network->neuron[iter_i][iter_j] = ((float) (rand() % 100)) / (float) 100;
            network->weight[iter_i][iter_j] = ((float) (rand() % 100)) / (float) 100;
        }
        printf("\n");
    }

    return network;
}

char *split(char *prefix, short iter) {
    return ( (iter % 10) || (iter == 0) ) ? "" : prefix;
}

void printNetwork(const Network *network) {
    printf("ninputs:   %d\n", network->ninputs);
    printf("nlayers:   %d\n", network->nlayers);
    printf("\n");
    
    printf("input:\t   ");
    for(short iter = 0; iter < network->ninputs; iter++) {
        printf("%s[%2d] %5.4f  ", split("\n\t   ", iter), iter, network->input[iter]);
    }
    printf("\n");
    printf("\n");
    
    printf("nneurons:  ");
    for(short iter = 0; iter < network->nlayers; iter++) {
        printf("[%d] %d  ", iter, network->nneurons[iter]);
    }
    printf("\n");
    printf("\n");

    for(short iter_i = 0; iter_i < network->nlayers; iter_i++) {
        printf("neuron[%d]: ", iter_i);
        for(short iter_j = 0; iter_j < network->nneurons[iter_i]; iter_j++) {
            printf("%s[%3d] %5.4f  ", split("\n\t   ", iter_j), iter_j, network->neuron[iter_i][iter_j]);
        }
        printf("\n");
    }
    printf("\n");

    for(short iter_i = 0; iter_i < network->nlayers; iter_i++) {
        printf("weigth[%d]: ", iter_i);
        for(short iter_j = 0; iter_j < network->nneurons[iter_i]; iter_j++) {
            printf("%s[%3d] %5.4f  ", split("\n\t   ", iter_j), iter_j, network->weight[iter_i][iter_j]);
        }
        printf("\n");
    }
    printf("\n");
}


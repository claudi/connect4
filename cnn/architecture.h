#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DEFAULT_NLAYERS 3
#define DEFAULT_NINPUTS 64
#define DEFAULT_NNEURONS default_neurons
const short default_neurons[DEFAULT_NLAYERS] = {128, 128, 8};

typedef struct Network Network;
struct Network {
    short ninputs;
    short nlayers;
    float *input;       // ninputs
    short *nneurons;    // nlayers
    float **neuron;     // nlayers x nneurons
    float **weight;     // nlayers x nneurons
};

Network *initNetwork(const short ninputs, const short nlayers, const short *nneurons);
void printNetwork(const Network *network);

#ifndef DEBUG
    #define ASSERT(n) {}
#else
    #define ASSERT(n)                                   \
    if(!(n)) {                                          \
        fprintf(stderr, "\n\t  DEBUG INFO  \n");        \
        fprintf(stderr, "\t Failed: %s\n", #n);         \
        fprintf(stderr, "\t     On: %s\n", __DATE__);   \
        fprintf(stderr, "\t     At: %s\n", __TIME__);   \
        fprintf(stderr, "\tIn File: %s\n", __FILE__);   \
        fprintf(stderr, "\tAt Line: %d\n", __LINE__);   \
        fprintf(stderr, "\n");                          \
        exit(1);                                        \
    }
#endif // DEBUG


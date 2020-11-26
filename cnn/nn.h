#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DEFAULT_NLAYERS 4
#define DEFAULT_NINPUTS 64
#define DEFAULT_TOPOLOGY default_neurons
// const short default_neurons[DEFAULT_NLAYERS] = {3, 2, 3};
const short default_neurons[DEFAULT_NLAYERS] = {12, 128, 8, 8};

typedef struct {
    short nlayers;
    short *ncells;
    float ***weights;
} Network;

typedef struct{
    short nlayers;
    short **ncells;
    short *dimX;
    short *dimY;
    float ***weights;
} CNetwork;

Network *initNetwork(const short nlayers, const short *topology);
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


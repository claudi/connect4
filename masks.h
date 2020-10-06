#include "defs.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {connect1, connect2, connect3, connect4, nconnects} Connects;
typedef enum {H, V, R, L, ndirmasks} DirMasks;
typedef enum {M1000, M0100, M0010, M0001, nmasks1} Masks1;
typedef enum {M1100, M1010, M0110, M1001, M0101, M0011, nmasks2} Masks2;
typedef enum {M1110, M1101, M1011, M0111, nmasks3} Masks3;
typedef enum {M1111, nmasks4} Masks4;

void printMask(const Mask mask);
void initMasks(void);


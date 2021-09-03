#ifndef MASKS_GUARD
#define MASKS_GUARD
#include "defs.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Mask main;
    Mask anti;
} SMask;

typedef enum {match1, match2, match3, match4, nmatches} Matches;
typedef enum {H1000, H0100, H0010, H0001,
              R1000, R0100, R0010, R0001,
              L1000, L0100, L0010, L0001,
              V1000, nmasks1} Masks1;
typedef enum {H1100, H1010, H0110, H1001, H0101, H0011,
              R1100, R1010, R0110, R1001, R0101, R0011,
              L1100, L1010, L0110, L1001, L0101, L0011,
              V1100, nmasks2} Masks2;
typedef enum {H1110, H1101, H1011, H0111,
              R1110, R1101, R1011, R0111,
              L1110, L1101, L1011, L0111,
              V1110, nmasks3} Masks3;
typedef enum {H1111, R1111, L1111, V1111, nmasks4} Masks4;

extern SMask *masks[];
extern unsigned masksCnt[];

void initMasks(void);
void freeMasks(void);
void printMask(const Mask mask);
void printMasks();

Bool matchMask(const Board *board, const SMask mask);
unsigned matches(const Board *board, const unsigned length);
unsigned wonBoard(const Board *board);

#endif // MASKS_GUARD


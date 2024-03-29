#ifndef MASKS_GUARD
#define MASKS_GUARD
#include "defs.h"

#define POS_TO_SHIFT(row, col) ((BOARD_SIZE * (row)) + (col))

typedef enum { MATCH1, MATCH2, MATCH3, MATCH4, NMATCHES } Matches;
typedef enum { H1000, H0100, H0010, H0001,
               R1000, R0100, R0010, R0001,
               L1000, L0100, L0010, L0001,
               V1000, NMASKS1 } Masks1;
typedef enum { H1100, H1010, H0110, H1001, H0101, H0011,
               R1100, R1010, R0110, R1001, R0101, R0011,
               L1100, L1010, L0110, L1001, L0101, L0011,
               V1100, NMASKS2 } Masks2;
typedef enum { H1110, H1101, H1011, H0111,
               R1110, R1101, R1011, R0111,
               L1110, L1101, L1011, L0111,
               V1110, NMASKS3 } Masks3;
typedef enum { H1111, R1111, L1111, V1111, NMASKS4 } Masks4;

unsigned matches(const Board *board, const unsigned length);
Mask shift(const short row, const short col);

#endif // MASKS_GUARD


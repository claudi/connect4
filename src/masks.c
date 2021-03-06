#include "masks.h"

SMask **masks;
unsigned *masksCnt;

void __attribute__((constructor)) initMasks(void) {
    masks = (SMask **) malloc(nmatches * sizeof(SMask *));
    masksCnt = (unsigned *) malloc(nmatches * sizeof(unsigned));

    unsigned Hcnt, Rcnt, Lcnt, Vcnt, combinations;
    Hcnt = N*(N - 3);
    Rcnt = (N - 3)*(N - 3);
    Lcnt = (N - 3)*(N - 3);
    Vcnt = (N - 3)*N;

    combinations = (nmasks1 - 1)/3;
    masksCnt[match1] = combinations*Hcnt + combinations*Rcnt + combinations*Lcnt + Vcnt;

    masks[match1] = (SMask *) malloc(masksCnt[match1] * sizeof(SMask));
    unsigned pos = 0;
    // H1000
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,0);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,1) | shift(0,2) | shift(0,3);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H0100
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,1);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(0,2) | shift(0,3);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H0010
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,2);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(0,1) | shift(0,3);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H0001
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,3);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(0,1) | shift(0,2);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // R1000
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,0);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(1,1) | shift(2,2) | shift(3,3);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R0100
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(1,1);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(2,2) | shift(3,3);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R0010
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(2,2);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(1,1) | shift(3,3);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R0001
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(3,3);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(1,1) | shift(2,2);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // L1000
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,3);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(1,2) | shift(2,1) | shift(3,0);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L0100
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(1,2);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,3) | shift(2,1) | shift(3,0);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L0010
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(2,1);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,3) | shift(1,2) | shift(3,0);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L0001
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(3,0);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(0,3) | shift(1,2) | shift(2,1);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // V1000
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < N; col++) {
            masks[match1][pos].main = shift(0,0);
            masks[match1][pos].main <<= pos2Shift(row, col);
            masks[match1][pos].anti = shift(1,0) | shift(2,0) | shift(3,0);
            masks[match1][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    combinations = (nmasks2 - 1)/3;
    masksCnt[match2] = combinations*Hcnt + combinations*Rcnt + combinations*Lcnt + Vcnt;
    masks[match2] = (SMask *) malloc(masksCnt[match2] * sizeof(SMask));
    pos = 0;
    // H1100
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(0,1);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,2) | shift(0,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H1010
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(0,2);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,1) | shift(0,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H0110
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,1) | shift(0,2);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(0,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H1001
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(0,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,1) | shift(0,2);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H0101
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,1) | shift(0,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(0,2);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H0011
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,2) | shift(0,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(0,1);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // R1100
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(1,1);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(2,2) | shift(3,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R1010
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(2,2);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(1,1) | shift(3,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R0110
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(1,1) | shift(2,2);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(3,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R1001
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(3,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(1,1) | shift(2,2);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R0101
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(1,1) | shift(3,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(2,2);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R0011
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(2,2) | shift(3,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(1,1);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // L1100
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(3,0) | shift(2,1);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(1,2) | shift(0,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L1010
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(3,0) | shift(1,2);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(2,1) | shift(0,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L0110
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(2,1) | shift(1,2);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(3,0) | shift(0,3);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L1001
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(3,0) | shift(0,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(2,1) | shift(1,2);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L0101
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(2,1) | shift(0,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(3,0) | shift(1,2);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L0011
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(1,2) | shift(0,3);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(3,0) | shift(2,1);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // V1100
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < N; col++) {
            masks[match2][pos].main = shift(0,0) | shift(1,0);
            masks[match2][pos].main <<= pos2Shift(row, col);
            masks[match2][pos].anti = shift(2,0) | shift(3,0);
            masks[match2][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    combinations = (nmasks3 - 1)/3;
    masksCnt[match3] = combinations*Hcnt + combinations*Rcnt + combinations*Lcnt + Vcnt;
    masks[match3] = (SMask *) malloc(masksCnt[match3] * sizeof(SMask));
    pos = 0;
    // H1110
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(0,1) | shift(0,2);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(0,3);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H1101
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(0,1) | shift(0,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(0,2);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H1011
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(0,2) | shift(0,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(0,1);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // H0111
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,1) | shift(0,2) | shift(0,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(0,0);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // R1110
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(1,1) | shift(2,2);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(3,3);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R1101
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(1,1) | shift(3,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(2,2);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R1011
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(2,2) | shift(3,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(1,1);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // R0111
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(1,1) | shift(2,2) | shift(3,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(0,0);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // L1110
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(3,0) | shift(2,1) | shift(1,2);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(0,3);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L1101
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(3,0) | shift(2,1) | shift(0,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(1,2);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L1011
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(3,0) | shift(1,2) | shift(0,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(2,1);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }
    // L0111
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(2,1) | shift(1,2) | shift(0,3);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(3,0);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    // V1110
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < N; col++) {
            masks[match3][pos].main = shift(0,0) | shift(1,0) | shift(2,0);
            masks[match3][pos].main <<= pos2Shift(row, col);
            masks[match3][pos].anti = shift(3,0);
            masks[match3][pos].anti <<= pos2Shift(row, col);
            pos++;
        }
    }

    combinations = (nmasks4 - 1)/3;
    masksCnt[match4] = combinations*Hcnt + combinations*Rcnt + combinations*Lcnt + Vcnt;
    masks[match4] = (SMask *) malloc(masksCnt[match4] * sizeof(SMask));
    pos = 0;
    // H1111
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match4][pos].main = shift(0,0) | shift(0,1) | shift(0,2) | shift(0,3);
            masks[match4][pos].main <<= pos2Shift(row, col);
            masks[match4][pos].anti = (Mask) 0;
            pos++;
        }
    }

    // R1111
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match4][pos].main = shift(0,0) | shift(1,1) | shift(2,2) | shift(3,3);
            masks[match4][pos].main <<= pos2Shift(row, col);
            masks[match4][pos].anti = (Mask) 0;
            pos++;

        }
    }

    // L1111
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match4][pos].main = shift(3,0) | shift(2,1) | shift(1,2) | shift(0,3);
            masks[match4][pos].main <<= pos2Shift(row, col);
            masks[match4][pos].anti = (Mask) 0;
            pos++;
        }
    }

    // V1111
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < N; col++) {
            masks[match4][pos].main = shift(0,0) | shift(1,0) | shift(2,0) | shift(3,0);
            masks[match4][pos].main <<= pos2Shift(row, col);
            masks[match4][pos].anti = (Mask) 0;
            pos++;
        }
    }
}

void __attribute__((destructor)) freeMasks(void) {
    for(short iter = 0; iter < nmatches; iter++) {
        free(masks[iter]);
    }
    free(masks);
    free(masksCnt);
}

void printMask(const Mask mask) {
    for(short iter_i = (N - 1); iter_i >= 0; iter_i--) {
        for(short iter_j = 0; iter_j < N; iter_j++) {
            printf("%c", (mask & shift(iter_i, iter_j)) ? '1' : '0');
        }
        printf("\n");
    }
    printf("\n");
}

void printMasks() {
    for(Matches iter = 0; iter < nmatches; iter++) {
        for(unsigned length = 0; length < masksCnt[iter]; length++) {
            printMask(masks[iter][length].main);
        }
    }
}

Bool matchMask(const Board *board, const SMask mask) {
    return ((board[TURN] & mask.main) == (mask.main))
        && ((board[BOTH] & mask.anti) == ((Mask) 0));
}

unsigned matches(const Board *board, const unsigned length) {
    ASSERT(length < nmatches);

    unsigned count = 0;
    for(unsigned mask = 0; mask < masksCnt[length]; mask++) {
        count += matchMask(board, masks[length][mask]);
    }
    return count;
}

unsigned wonBoard(const Board *board) {
    return matches(board, match4);
}


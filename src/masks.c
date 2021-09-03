#include "masks.h"

SMask **masks;
unsigned *masksCnt;

void printSMask(const SMask mask) {
    printf("\t(SMask) { .main = (Mask) 0x%16.16zX, .anti = (Mask) 0x%16.16zX },\n", mask.main, mask.anti);
}

void __attribute__((constructor)) initMasks(void) {
    masks = (SMask **) malloc(nmatches * sizeof(SMask *));
    masksCnt = (unsigned *) malloc(nmatches * sizeof(unsigned));

    unsigned Hcnt, Rcnt, Lcnt, Vcnt, combinations;
    Hcnt = N*(N - 3);
    Rcnt = (N - 3)*(N - 3);
    Lcnt = (N - 3)*(N - 3);
    Vcnt = (N - 3)*N;

    printf("SMask *masks1 = {");

    combinations = (nmasks1 - 1)/3;
    masksCnt[match1] = combinations*Hcnt + combinations*Rcnt + combinations*Lcnt + Vcnt;
    masks[match1] = (SMask *) malloc(masksCnt[match1] * sizeof(SMask));
    unsigned pos = 0;
    // H1000
    printf("\n\t// H1000\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,0);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,1) | shift(0,2) | shift(0,3);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // H0100
    printf("\n\t// H0100\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,1);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(0,2) | shift(0,3);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // H0010
    printf("\n\t// H0010\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,2);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(0,1) | shift(0,3);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // H0001
    printf("\n\t// H0001\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,3);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(0,1) | shift(0,2);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }

    // R1000
    printf("\n\t// R1000\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,0);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(1,1) | shift(2,2) | shift(3,3);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // R0100
    printf("\n\t// R0100\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(1,1);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(2,2) | shift(3,3);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // R0010
    printf("\n\t// R0010\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(2,2);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(1,1) | shift(3,3);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // R0001
    printf("\n\t// R0001\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(3,3);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,0) | shift(1,1) | shift(2,2);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }

    // L1000
    printf("\n\t// L1000\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(0,3);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(1,2) | shift(2,1) | shift(3,0);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // L0100
    printf("\n\t// L0100\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(1,2);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,3) | shift(2,1) | shift(3,0);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // L0010
    printf("\n\t// L0010\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(2,1);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,3) | shift(1,2) | shift(3,0);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }
    // L0001
    printf("\n\t// L0001\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match1][pos].main = shift(3,0);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(0,3) | shift(1,2) | shift(2,1);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }

    // V1000
    printf("\n\t// V1000\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < N; col++) {
            masks[match1][pos].main = shift(0,0);
            masks[match1][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match1][pos].anti = shift(1,0) | shift(2,0) | shift(3,0);
            masks[match1][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match1][pos]);
            pos++;
        }
    }

    printf("};\n");

    printf("\n");
    printf("SMask *masks2 = {");

    combinations = (nmasks2 - 1)/3;
    masksCnt[match2] = combinations*Hcnt + combinations*Rcnt + combinations*Lcnt + Vcnt;
    masks[match2] = (SMask *) malloc(masksCnt[match2] * sizeof(SMask));
    pos = 0;
    // H1100
    printf("\n\t// H1100\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(0,1);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,2) | shift(0,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // H1010
    printf("\n\t// H1010\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(0,2);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,1) | shift(0,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // H0110
    printf("\n\t// H0110\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,1) | shift(0,2);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(0,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // H1001
    printf("\n\t// H1001\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(0,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,1) | shift(0,2);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // H0101
    printf("\n\t// H0101\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,1) | shift(0,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(0,2);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // H0011
    printf("\n\t// H0011\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,2) | shift(0,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(0,1);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }

    // R1100
    printf("\n\t// R1100\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(1,1);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(2,2) | shift(3,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // R1010
    printf("\n\t// R1010\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(2,2);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(1,1) | shift(3,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // R0110
    printf("\n\t// R0110\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(1,1) | shift(2,2);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(3,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // R1001
    printf("\n\t// R1001\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(0,0) | shift(3,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(1,1) | shift(2,2);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // R0101
    printf("\n\t// R0101\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(1,1) | shift(3,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(2,2);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // R0011
    printf("\n\t// R0011\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(2,2) | shift(3,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(0,0) | shift(1,1);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }

    // L1100
    printf("\n\t// L1100\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(3,0) | shift(2,1);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(1,2) | shift(0,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // L1010
    printf("\n\t// L1010\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(3,0) | shift(1,2);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(2,1) | shift(0,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // L0110
    printf("\n\t// L0110\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(2,1) | shift(1,2);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(3,0) | shift(0,3);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // L1001
    printf("\n\t// L1001\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(3,0) | shift(0,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(2,1) | shift(1,2);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // L0101
    printf("\n\t// L0101\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(2,1) | shift(0,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(3,0) | shift(1,2);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }
    // L0011
    printf("\n\t// L0011\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match2][pos].main = shift(1,2) | shift(0,3);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(3,0) | shift(2,1);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }

    // V1100
    printf("\n\t// V1100\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < N; col++) {
            masks[match2][pos].main = shift(0,0) | shift(1,0);
            masks[match2][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match2][pos].anti = shift(2,0) | shift(3,0);
            masks[match2][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match2][pos]);
            pos++;
        }
    }

    printf("};\n");

    printf("\n");
    printf("SMask *masks3 = {");

    combinations = (nmasks3 - 1)/3;
    masksCnt[match3] = combinations*Hcnt + combinations*Rcnt + combinations*Lcnt + Vcnt;
    masks[match3] = (SMask *) malloc(masksCnt[match3] * sizeof(SMask));
    pos = 0;
    // H1110
    printf("\n\t// H1110\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(0,1) | shift(0,2);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(0,3);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // H1101
    printf("\n\t// H1101\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(0,1) | shift(0,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(0,2);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // H1011
    printf("\n\t// H1011\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(0,2) | shift(0,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(0,1);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // H0111
    printf("\n\t// H0111\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,1) | shift(0,2) | shift(0,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(0,0);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }

    // R1110
    printf("\n\t// R1110\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(1,1) | shift(2,2);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(3,3);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // R1101
    printf("\n\t// R1101\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(1,1) | shift(3,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(2,2);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // R1011
    printf("\n\t// R1011\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(0,0) | shift(2,2) | shift(3,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(1,1);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // R0111
    printf("\n\t// R0111\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(1,1) | shift(2,2) | shift(3,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(0,0);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }

    // L1110
    printf("\n\t// L1110\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(3,0) | shift(2,1) | shift(1,2);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(0,3);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // L1101
    printf("\n\t// L1101\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(3,0) | shift(2,1) | shift(0,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(1,2);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // L1011
    printf("\n\t// L1011\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(3,0) | shift(1,2) | shift(0,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(2,1);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }
    // L0111
    printf("\n\t// L0111\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match3][pos].main = shift(2,1) | shift(1,2) | shift(0,3);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(3,0);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }

    // V1110
    printf("\n\t// V1110\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < N; col++) {
            masks[match3][pos].main = shift(0,0) | shift(1,0) | shift(2,0);
            masks[match3][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match3][pos].anti = shift(3,0);
            masks[match3][pos].anti <<= POS_TO_SHIFT(row, col);
            printSMask(masks[match3][pos]);
            pos++;
        }
    }

    printf("};\n");

    printf("\n");
    printf("SMask *masks4 = {");


    combinations = (nmasks4 - 1)/3;
    masksCnt[match4] = combinations*Hcnt + combinations*Rcnt + combinations*Lcnt + Vcnt;
    masks[match4] = (SMask *) malloc(masksCnt[match4] * sizeof(SMask));
    pos = 0;
    // H1111
    printf("\n\t// H1111\n");
    for(unsigned row = 0; row < N; row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match4][pos].main = shift(0,0) | shift(0,1) | shift(0,2) | shift(0,3);
            masks[match4][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match4][pos].anti = (Mask) 0;
            printSMask(masks[match4][pos]);
            pos++;
        }
    }

    // R1111
    printf("\n\t// R1111\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match4][pos].main = shift(0,0) | shift(1,1) | shift(2,2) | shift(3,3);
            masks[match4][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match4][pos].anti = (Mask) 0;
            printSMask(masks[match4][pos]);
            pos++;

        }
    }

    // L1111
    printf("\n\t// L1111\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < (N - 3); col++) {
            masks[match4][pos].main = shift(3,0) | shift(2,1) | shift(1,2) | shift(0,3);
            masks[match4][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match4][pos].anti = (Mask) 0;
            printSMask(masks[match4][pos]);
            pos++;
        }
    }

    // V1111
    printf("\n\t// V1111\n");
    for(unsigned row = 0; row < (N - 3); row++) {
        for(unsigned col = 0; col < N; col++) {
            masks[match4][pos].main = shift(0,0) | shift(1,0) | shift(2,0) | shift(3,0);
            masks[match4][pos].main <<= POS_TO_SHIFT(row, col);
            masks[match4][pos].anti = (Mask) 0;
            printSMask(masks[match4][pos]);
            pos++;
        }
    }

    printf("};\n");

    printf("\n");
    printf("SMask *masks[] = {\n");
    for(Matches match = 0; match < nmatches; match++) {
        printf("\tmasks%d,\n", match);
    }
    printf("};\n");

    printf("\n");
    printf("unsigned masksCnt[] = {\n");
    for(Matches match = 0; match < nmatches; match++) {
        printf("\t%u,\n", masksCnt[match]);
    }
    printf("};\n");

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


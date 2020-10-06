#include "masks.h"

Mask ***mask;   // mask[V][connect3][M1101]

void initMasks(void) {
    mask = (Mask ***) malloc(ndirmasks * sizeof(Mask **));
    for(size_t dir = 0; dir < ndirmasks; dir++) {
        mask[dir] = (Mask **) malloc(nconnects * sizeof(Mask *));

        mask[dir][connect1] = (Mask *) malloc(nmasks1 * sizeof(Mask));
        for(size_t masks = 0; masks < nmasks1; masks++) {
            mask[dir][connect1][masks] = (Mask) 0;
        }

        mask[dir][connect2] = (Mask *) malloc(nmasks2 * sizeof(Mask));
        for(size_t masks = 0; masks < nmasks2; masks++) {
            mask[dir][connect2][masks] = (Mask) 0;
        }

        mask[dir][connect3] = (Mask *) malloc(nmasks3 * sizeof(Mask));
        for(size_t masks = 0; masks < nmasks3; masks++) {
            mask[dir][connect3][masks] = (Mask) 0;
        }

        mask[dir][connect4] = (Mask *) malloc(nmasks4 * sizeof(Mask));
        for(size_t masks = 0; masks < nmasks4; masks++) {
            mask[dir][connect4][masks] = (Mask) 0;
        }
    }

    mask[H][connect1][M1000] = shift(0,0);
    mask[H][connect1][M0100] = shift(0,1);
    mask[H][connect1][M0010] = shift(0,2);
    mask[H][connect1][M0001] = shift(0,3);

    mask[V][connect1][M1000] = shift(0,0);
    mask[V][connect1][M0100] = shift(1,0);
    mask[V][connect1][M0010] = shift(2,0);
    mask[V][connect1][M0001] = shift(3,0);

    mask[R][connect1][M1000] = shift(0,0);
    mask[R][connect1][M0100] = shift(1,1);
    mask[R][connect1][M0010] = shift(2,2);
    mask[R][connect1][M0001] = shift(3,3);

    mask[L][connect1][M1000] = shift(0,3);
    mask[L][connect1][M0100] = shift(1,2);
    mask[L][connect1][M0010] = shift(2,1);
    mask[L][connect1][M0001] = shift(3,0);

    mask[H][connect2][M1100] = shift(0,0) | shift(0,1);
    mask[H][connect2][M1010] = shift(0,0) | shift(0,2);
    mask[H][connect2][M0110] = shift(0,1) | shift(0,2);
    mask[H][connect2][M1001] = shift(0,0) | shift(0,3);
    mask[H][connect2][M0101] = shift(0,1) | shift(0,3);
    mask[H][connect2][M0011] = shift(0,2) | shift(0,3);

    mask[V][connect2][M1100] = shift(0,0) | shift(1,0);
    mask[V][connect2][M1010] = shift(0,0) | shift(2,0);
    mask[V][connect2][M0110] = shift(1,0) | shift(2,0);
    mask[V][connect2][M1001] = shift(0,0) | shift(3,0);
    mask[V][connect2][M0101] = shift(1,0) | shift(3,0);
    mask[V][connect2][M0011] = shift(2,0) | shift(3,0);

    mask[R][connect2][M1100] = shift(0,0) | shift(1,1);
    mask[R][connect2][M1010] = shift(0,0) | shift(2,2);
    mask[R][connect2][M0110] = shift(1,1) | shift(2,2);
    mask[R][connect2][M1001] = shift(0,0) | shift(3,3);
    mask[R][connect2][M0101] = shift(1,1) | shift(3,3);
    mask[R][connect2][M0011] = shift(2,2) | shift(3,3);

    mask[L][connect2][M1100] = shift(0,3) | shift(1,2);
    mask[L][connect2][M1010] = shift(0,3) | shift(2,1);
    mask[L][connect2][M0110] = shift(1,2) | shift(2,1);
    mask[L][connect2][M1001] = shift(0,3) | shift(3,0);
    mask[L][connect2][M0101] = shift(1,2) | shift(3,0);
    mask[L][connect2][M0011] = shift(2,1) | shift(3,0);

    mask[H][connect3][M1110] = shift(0,0) | shift(0,1) | shift(0,2);
    mask[H][connect3][M1101] = shift(0,0) | shift(0,1) | shift(0,3);
    mask[H][connect3][M1011] = shift(0,0) | shift(0,2) | shift(0,3);
    mask[H][connect3][M0111] = shift(0,1) | shift(0,2) | shift(0,3);

    mask[V][connect3][M1110] = shift(0,0) | shift(1,0) | shift(2,0);
    mask[V][connect3][M1101] = shift(0,0) | shift(1,0) | shift(3,0);
    mask[V][connect3][M1011] = shift(0,0) | shift(2,0) | shift(3,0);
    mask[V][connect3][M0111] = shift(1,0) | shift(2,0) | shift(3,0);

    mask[R][connect3][M1110] = shift(0,0) | shift(1,1) | shift(2,2);
    mask[R][connect3][M1101] = shift(0,0) | shift(1,1) | shift(3,3);
    mask[R][connect3][M1011] = shift(0,0) | shift(2,2) | shift(3,3);
    mask[R][connect3][M0111] = shift(1,1) | shift(2,2) | shift(3,3);

    mask[L][connect3][M1110] = shift(0,3) | shift(1,2) | shift(2,1);
    mask[L][connect3][M1101] = shift(0,3) | shift(1,2) | shift(3,0);
    mask[L][connect3][M1011] = shift(0,3) | shift(2,1) | shift(3,0);
    mask[L][connect3][M0111] = shift(1,2) | shift(2,1) | shift(3,0);

    mask[H][connect4][M1111] = shift(0,0) | shift(0,1) | shift(0,2) | shift(0,3);
    mask[V][connect4][M1111] = shift(0,0) | shift(1,0) | shift(2,0) | shift(3,0);
    mask[R][connect4][M1111] = shift(0,0) | shift(1,1) | shift(2,2) | shift(3,3);
    mask[L][connect4][M1111] = shift(0,3) | shift(1,2) | shift(2,1) | shift(3,0);
}

void printMask(const Mask mask) {
    for(size_t iter_i = 0; iter_i < N; iter_i++) {
        for(size_t iter_j = 0; iter_j < N; iter_j++) {
            printf("%c", (mask & shift(iter_i, iter_j)) ? '1' : '0');
        }
        printf("\n");
    }
    printf("\n");
}


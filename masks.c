#include "masks.h"

Mask ***mask;   // mask[connect3][V][M1101]
Connects *nmasks;

void initMasks(void) {
    nmasks = (Connects *) malloc(nconnects * sizeof(Connects));
    // nmasks = {nmasks1, nmasks2, nmasks3, nmasks4};
    nmasks[connect1] = nmasks1;
    nmasks[connect2] = nmasks2;
    nmasks[connect3] = nmasks3;
    nmasks[connect4] = nmasks4;

    mask = (Mask ***) malloc(nconnects * sizeof(Mask **));
    for(size_t connect = 0; connect < nconnects; connect++) {
        mask[connect] = (Mask **) malloc(ndirmasks * sizeof(Mask *));
        for(size_t dir = 0; dir < ndirmasks; dir++) {
            mask[connect][dir] = (Mask *) malloc(nmasks[connect] * sizeof(Mask));
            for(size_t masks = 0; masks < nmasks[connect]; masks++) {
                mask[connect1][dir][masks] = (Mask) 0;
            }
        }
    }

    mask[connect1][H][M1000] = shift(0,0);
    mask[connect1][H][M0100] = shift(0,1);
    mask[connect1][H][M0010] = shift(0,2);
    mask[connect1][H][M0001] = shift(0,3);
                     
    mask[connect1][V][M1000] = shift(0,0);
    mask[connect1][V][M0100] = shift(1,0);
    mask[connect1][V][M0010] = shift(2,0);
    mask[connect1][V][M0001] = shift(3,0);
                     
    mask[connect1][R][M1000] = shift(0,0);
    mask[connect1][R][M0100] = shift(1,1);
    mask[connect1][R][M0010] = shift(2,2);
    mask[connect1][R][M0001] = shift(3,3);
                     
    mask[connect1][L][M1000] = shift(0,3);
    mask[connect1][L][M0100] = shift(1,2);
    mask[connect1][L][M0010] = shift(2,1);
    mask[connect1][L][M0001] = shift(3,0);
                     
    mask[connect2][H][M1100] = shift(0,0) | shift(0,1);
    mask[connect2][H][M1010] = shift(0,0) | shift(0,2);
    mask[connect2][H][M0110] = shift(0,1) | shift(0,2);
    mask[connect2][H][M1001] = shift(0,0) | shift(0,3);
    mask[connect2][H][M0101] = shift(0,1) | shift(0,3);
    mask[connect2][H][M0011] = shift(0,2) | shift(0,3);
                     
    mask[connect2][V][M1100] = shift(0,0) | shift(1,0);
    mask[connect2][V][M1010] = shift(0,0) | shift(2,0);
    mask[connect2][V][M0110] = shift(1,0) | shift(2,0);
    mask[connect2][V][M1001] = shift(0,0) | shift(3,0);
    mask[connect2][V][M0101] = shift(1,0) | shift(3,0);
    mask[connect2][V][M0011] = shift(2,0) | shift(3,0);
                     
    mask[connect2][R][M1100] = shift(0,0) | shift(1,1);
    mask[connect2][R][M1010] = shift(0,0) | shift(2,2);
    mask[connect2][R][M0110] = shift(1,1) | shift(2,2);
    mask[connect2][R][M1001] = shift(0,0) | shift(3,3);
    mask[connect2][R][M0101] = shift(1,1) | shift(3,3);
    mask[connect2][R][M0011] = shift(2,2) | shift(3,3);
                     
    mask[connect2][L][M1100] = shift(0,3) | shift(1,2);
    mask[connect2][L][M1010] = shift(0,3) | shift(2,1);
    mask[connect2][L][M0110] = shift(1,2) | shift(2,1);
    mask[connect2][L][M1001] = shift(0,3) | shift(3,0);
    mask[connect2][L][M0101] = shift(1,2) | shift(3,0);
    mask[connect2][L][M0011] = shift(2,1) | shift(3,0);
                     
    mask[connect3][H][M1110] = shift(0,0) | shift(0,1) | shift(0,2);
    mask[connect3][H][M1101] = shift(0,0) | shift(0,1) | shift(0,3);
    mask[connect3][H][M1011] = shift(0,0) | shift(0,2) | shift(0,3);
    mask[connect3][H][M0111] = shift(0,1) | shift(0,2) | shift(0,3);
                     
    mask[connect3][V][M1110] = shift(0,0) | shift(1,0) | shift(2,0);
    mask[connect3][V][M1101] = shift(0,0) | shift(1,0) | shift(3,0);
    mask[connect3][V][M1011] = shift(0,0) | shift(2,0) | shift(3,0);
    mask[connect3][V][M0111] = shift(1,0) | shift(2,0) | shift(3,0);
                     
    mask[connect3][R][M1110] = shift(0,0) | shift(1,1) | shift(2,2);
    mask[connect3][R][M1101] = shift(0,0) | shift(1,1) | shift(3,3);
    mask[connect3][R][M1011] = shift(0,0) | shift(2,2) | shift(3,3);
    mask[connect3][R][M0111] = shift(1,1) | shift(2,2) | shift(3,3);
                     
    mask[connect3][L][M1110] = shift(0,3) | shift(1,2) | shift(2,1);
    mask[connect3][L][M1101] = shift(0,3) | shift(1,2) | shift(3,0);
    mask[connect3][L][M1011] = shift(0,3) | shift(2,1) | shift(3,0);
    mask[connect3][L][M0111] = shift(1,2) | shift(2,1) | shift(3,0);
                     
    mask[connect4][H][M1111] = shift(0,0) | shift(0,1) | shift(0,2) | shift(0,3);
    mask[connect4][V][M1111] = shift(0,0) | shift(1,0) | shift(2,0) | shift(3,0);
    mask[connect4][R][M1111] = shift(0,0) | shift(1,1) | shift(2,2) | shift(3,3);
    mask[connect4][L][M1111] = shift(0,3) | shift(1,2) | shift(2,1) | shift(3,0);
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


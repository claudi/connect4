#include "key.h"

Key keyShift(const short row, const short col) {
    return (((Key) 1) << pos2Shift(row, col));
}

void printKey(const Key key) {
    for(short iter_i = (2*N - 1); iter_i >= 0; iter_i--) {
        for(short iter_j = 0; iter_j < N; iter_j++) {
            printf("%c", (key & keyShift(iter_i, iter_j)) ? '1' : '0');
        }
        printf("\n");
    }
    printf("\n");
}


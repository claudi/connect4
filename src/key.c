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

Key boardToKey(const Board *board) {
    return ((* ((Key *) &board[TURN])) << N*N) + ((Key) board[BOTH]);
}

Key mirrorKey(const Key key) {
    Key result = (Key) 0;
    for(short iter = 0; iter < N; iter++) {
        result |= (key & verticalKeys[iter]) << (N-1 - iter) >> iter;
    }
    return result;
}

Key *verticalKeys;
void __attribute__((constructor)) initKeys(void) {
    verticalKeys = (Key *) malloc(N * sizeof(Key));
    verticalKeys[0] = (Key) 0;
    for(short iter = 0; iter < 2*N; iter++) {
        verticalKeys[0] |= keyShift(iter, 0);
    }

    for(short key = 1; key < N; key++) {
        verticalKeys[key] = verticalKeys[0] << key;
    }
}

void __attribute__((destructor)) freeKeys(void) {
    free(verticalKeys);
}


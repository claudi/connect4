#include "key.h"

static Key *verticalKeys;

static void printKey(const Key key);
static Key mirrorKey(const Key key);
static void initKeys(void);
static void freeKeys(void);

static Key keyShift(const short row, const short col) {
    return (((Key) 1) << POS_TO_SHIFT(row, col));
}

static void printKey(const Key key) {
    for(short iter_i = (2 * BOARD_SIZE - 1); iter_i >= 0; iter_i--) {
        for(short iter_j = 0; iter_j < BOARD_SIZE; iter_j++) {
            printf("%c", (key & keyShift(iter_i, iter_j)) ? '1' : '0');
        }
        printf("\n");
    }
    printf("\n");
}

Key boardToKey(const Board *board) {
    Key key = ((*((Key *) &board[TURN])) << BOARD_SIZE * BOARD_SIZE) + ((Key) board[BOTH]);
    Key mirrored = mirrorKey(key);
    if(mirrored > key) {
        key = mirrored;
    }
    return key;
}

static Key mirrorKey(const Key key) {
    Key result = (Key) 0;
    for(short iter = 0; iter < BOARD_SIZE; iter++) {
        result |= (key & verticalKeys[iter]) << (BOARD_SIZE - 1 - iter) >> iter;
    }
    return result;
}

static Key *verticalKeys;
static void __attribute__((constructor)) initKeys(void) {
    verticalKeys = (Key *) malloc(BOARD_SIZE * sizeof(Key));
    verticalKeys[0] = (Key) 0;
    for(short iter = 0; iter < 2 * BOARD_SIZE; iter++) {
        verticalKeys[0] |= keyShift(iter, 0);
    }

    for(short key = 1; key < BOARD_SIZE; key++) {
        verticalKeys[key] = verticalKeys[0] << key;
    }
}

static void __attribute__((destructor)) freeKeys(void) {
    free(verticalKeys);
}

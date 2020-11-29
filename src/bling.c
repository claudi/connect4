#include "bling.h"

void printGameBoy(char screen[SCREEN_H][SCREEN_W], char side[SIDE_H][SIDE_W], char credits[2][CREDITS_W]);
void printInterface(const Node *game, const short turn);
char *difficulty(const short depth);

void printInterface(const Node *game, const short turn) {
    char screen[SCREEN_H][SCREEN_W];
    for(short height = 0; height < SCREEN_H; height++) {
        for(short width = 0; width < SCREEN_W-1; width++) {
            screen[height][width] = ' ';
        }
    }

    char buffer[7];
    sprintf(buffer, "%6d", turn);
    char turnNumber[3];
    turnNumber[0] = buffer[4];
    turnNumber[1] = buffer[5];
    sprintf(screen[0], "        Turn %s  ", turnNumber);

    char lastMove = showTurn(game->turn);
    char nextMove = showTurn(next(game->turn));
    char emptySlot = '-';
    char slot;
    for(short row = 0; row < N; row++) {
        for(short col = 0; col < N; col++) {
            if(game->board[TURN] & shift(N - row - 1, col)) {
                slot = lastMove;
            } else if(game->board[BOTH] & shift(N - row - 1, col)) {
                slot = nextMove;
            } else {
                slot = emptySlot;
            }
            screen[row + 1][2*col + 1] = slot;
        }
    }
    for(short col = 0; col < N; col++) {
        screen[SCREEN_H-1][2*col + 1] = '0' + col + 1;
    }
    for(short height = 0; height < SCREEN_H; height++) {
        screen[height][SCREEN_W-1] = '\0';
    }

    char side[SIDE_H][SIDE_W];

    Side player = X;
    short depth = 4;
    short pos = 0;
    sprintf(side[pos++], "      Playing as %c      ", showTurn(player));
    sprintf(side[pos++], "    Difficulty %s        ", difficulty(depth));
    sprintf(side[pos++], "                        ");
    sprintf(side[pos++], "1-8 Play on column      ");
    sprintf(side[pos++], " h  Toggle help/stats   ");
    sprintf(side[pos++], " d  Change difficulty   ");
    sprintf(side[pos++], " s  Switch sides        ");
    sprintf(side[pos++], " n  New game            ");
    sprintf(side[pos++], " q  Quit                ");
    // sprintf(side[9], "                        ");

    for(short height = 0; height < SIDE_H; height++) {
        side[height][SIDE_W-1] = '\0';
    }
    char credits[2][CREDITS_W] = {" Art source:               ",
                                  "www.oocities.org/soho/7373/"};

    printGameBoy(screen, side, credits);
}

void printGameBoy(char screen[SCREEN_H][SCREEN_W], char side[SIDE_H][SIDE_W], char credits[2][CREDITS_W]) { 
    char *padding = "     ";
    for(short iter = 0; iter < 80; iter++) {
        printf("\n");
    }
    printf("%s    ___________________________\n", padding);
    printf("%s   |OFFo oON                   |\n", padding);
    printf("%s   | .-----------------------. |\t%s\n", padding, side[0]);
    printf("%s   | |  .-----------------.  | |\t%s\n", padding, side[1]);
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[0], side[2]);
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[1], side[3]);
    printf("%s   | |))|%s|  | |\t%s\n", padding, screen[2], side[4]);
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[3], side[5]);
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[4], side[6]);
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[5], side[7]);
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[6], side[8]);
    printf("%s   | |  |%s|  | |\n", padding, screen[7]);
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[8], credits[0]);
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[9], credits[1]);
    printf("%s   | |  '-----------------'  | |\n", padding);
    printf("%s   | |__GAME BOY_____________/ |\n", padding);
    printf("%s   |          ________         |\n", padding);
    printf("%s   |    .    (Nintendo)        |\n", padding);
    printf("%s   |  _| |_   \"\"\"\"\"\"\"\"    .-.  |\n", padding);
    printf("%s   |-[_   _]-        .-. (   ) |\n", padding);
    printf("%s   |   |_|          (   ) '-'  |\n", padding);
    printf("%s   |    '            '-'   A   |\n", padding);
    printf("%s   |                  B        |\n", padding);
    printf("%s   |          ___    ___       |\n", padding);
    printf("%s   |         (___)  (___)  ,., |\n", padding);
    printf("%s   |        select  start ;:;: |\n", padding);
    printf("%s   |                     ,;:;' /\n", padding);
    printf("%sjgs|                    ,:;:'.'\n", padding);
    printf("%s   '------------------------`\n", padding);
    printf(" > ");
}

char *difficulty(const short depth) {
    if(depth < 3) {
        return "EASY";
    } else if(depth < 5) {
        return "MEDIUM";
    } else if(depth < 7) {
        return "HARD";
    } else {
        return "VERY HARD";
    }
}


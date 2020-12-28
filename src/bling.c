#include "bling.h"

void printGameBoy(char screen[SCREEN_H][SCREEN_W], char side[SIDE_H][SIDE_W], char credits[2][CREDITS_W]);
char *difficulty(const short depth);
char *trimBigNumber(const unsigned num);
char *posPerSec(unsigned positions, double time);
void humanInput(Game *game);

void printInterface(const Game *game) {
    char screen[SCREEN_H][SCREEN_W];
    for(short height = 0; height < SCREEN_H; height++) {
        for(short width = 0; width < SCREEN_W-1; width++) {
            screen[height][width] = ' ';
        }
    }

    char buffer[7];
    sprintf(buffer, "%6d", game->turn);
    sprintf(screen[0], "        Turn %s  ", buffer + 4);

    char lastMove = showTurn(game->node->turn);
    char nextMove = showTurn(next(game->node->turn));
    char emptySlot = '-';
    char slot;
    for(short row = 0; row < N; row++) {
        for(short col = 0; col < N; col++) {
            if(game->node->board[TURN] & shift(N - row - 1, col)) {
                slot = lastMove;
            } else if(game->node->board[BOTH] & shift(N - row - 1, col)) {
                slot = nextMove;
            } else {
                slot = emptySlot;
            }
            screen[row + 1][2*col + 1] = slot;
        }
    }

    // for(short width = 0; width < SCREEN_W-1; width++) {
        // screen[SCREEN_H-2][width] = '_';
    // }
    for(short width = 2; width < SCREEN_W-2; width++) {
        screen[SCREEN_H-1][width] = ':';
        width++;
    }
    // screen[SCREEN_H-1][0] = '(';
    // screen[SCREEN_H-1][SCREEN_W-2] = ')';
    for(short col = 0; col < N; col++) {
        screen[SCREEN_H-1][2*col + 1] = '0' + col + 1;
    }
    for(short height = 0; height < SCREEN_H; height++) {
        screen[height][SCREEN_W-1] = '\0';
    }

    char *exploredPositionsPrint = trimBigNumber(exploredPositions);
    char *posPerSecPrint = posPerSec(exploredPositions, elapsedTime);

    char side[2][SIDE_H][SIDE_W];
    short pos = 0;
    sprintf(side[0][pos++], "      Playing as %c      ", showTurn(game->playerSide));
    sprintf(side[0][pos++], "    Difficulty %s        ", difficulty(game->depth));
    sprintf(side[0][pos++], "                        ");
    sprintf(side[0][pos++], " 1-8 Play on column     ");
    sprintf(side[0][pos++], "   h Toggle help/stats  ");
    sprintf(side[0][pos++], "%4s Position%s explored", exploredPositionsPrint, exploredPositions == 1 ? "" : "s" );
    sprintf(side[0][pos++], "%4s per second         ", posPerSecPrint);
    sprintf(side[0][pos++], "                        ");
    sprintf(side[0][pos++], "                        ");

    pos = 0;
    sprintf(side[1][pos++], "      Playing as %c      ", showTurn(game->playerSide));
    sprintf(side[1][pos++], "    Difficulty %s        ", difficulty(game->depth));
    sprintf(side[1][pos++], "                        ");
    sprintf(side[1][pos++], " 1-8 Play on column     ");
    sprintf(side[1][pos++], "   h Toggle help/stats  ");
    sprintf(side[1][pos++], "  d# Change difficulty  ");
    sprintf(side[1][pos++], "   s Switch sides       ");
    sprintf(side[1][pos++], "   n New game           ");
    sprintf(side[1][pos++], "   q Stop game          ");

    for(short height = 0; height < SIDE_H; height++) {
        side[0][height][SIDE_W-1] = '\0';
        side[1][height][SIDE_W-1] = '\0';
    }

    char credits[2][CREDITS_W] = {" Artwork source:           ",
                                  "www.oocities.org/soho/7373/"};

    printGameBoy(screen, side[game->help], credits);

    // printf("\n\n");
    // for(short height = 0; height < SCREEN_H; height++) {
        // printf("%s\n", screen[height]);
    // }
    // printf("\n");
    // for(short height = 0; height < SIDE_H; height++) {
        // printf("%s\n", side[0][height]);
    // }
    // printf("\n");
    // for(short height = 0; height < SIDE_H; height++) {
        // printf("%s\n", side[1][height]);
    // }
    free(posPerSecPrint);
    free(exploredPositionsPrint);
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
}

char *difficulty(const short depth) {
    if(depth < 3) {
        return "EASY";
    } else if(depth < 5) {
        return "MEDIUM";
    } else if(depth < 7) {
        return "HARD";
    } else {
        return "EXTREME";
    }
}

char *trimBigNumber(const unsigned num) {
    char *buff = (char *) malloc(25 * sizeof(char));
    if(num < 1000) {
        sprintf(buff, "%d", num);
    } else if(num < 1000000) {
        sprintf(buff, "%dK", num / 1000);
    } else {
        sprintf(buff, "%dM", num / 1000000);
    }
    return buff;
}

char *posPerSec(unsigned positions, double time) {
    double seconds = time / ((double) CLOCKS_PER_SEC);
    return trimBigNumber(positions / seconds);
}

void humanInput(Game *game) {
    printInterface(game);
    printf(" > ");
    char *buff = (char *) malloc(255 * sizeof(char));
    scanf("%s", buff);

    char input = buff[0];
    if((input >= '0') && (input <= '9')) {
        short move = atoi(buff);
        if((move <= 0) || (move > N)) {
            humanInput(game);
            // fprintf(stderr, "Invalid column\n");
        } else if(fullColumn(game->node->board, move-1)) {
            humanInput(game);
        } else {
            makeMove(game->node, move-1);
        }
    } else {
        short depth;
        switch(input) {
            case 'h':   // Toggle help/stats
                game->help = not(game->help);
                humanInput(game);
                break;
            case 'd':   // Change difficulty
                depth = atoi(buff + 1);
                if(depth <= 0) {
                    game->depth = 4;
                } else {
                    game->depth = depth;
                }
                humanInput(game);
                break;
            case 'q':   // Quit
                printf("Bye!\n");
                game->node->nchildren = 0;
                break;
            case 's':   // Switch sides
                game->playerSide = next(game->playerSide);
                machineMove(game->node, game->depth, game->side);
                // humanInput(game);
                break;
            case 'n':   // New game
                free(game->node);
                *game = (Game) {initNode(), 1, game->depth, game->playerSide, next(X), game->help};
                break;
            default:    // Other
                // fprintf(stderr, "Invalid input\n");
                humanInput(game);
                break;
        }
    }

    free(buff);
}

Bool keepPlaying(void) {
    printf(" Want to keep on playing? (y/n)\n");
    printf(" > ");

    char *buff = (char *) malloc(255 * sizeof(char));
    scanf("%s", buff);

    Bool answer;

    if(buff[0] == 'y') {
        answer = TRUE;
    } else if(buff[0] == 'n') {
        answer = FALSE;
    } else {
        printf(" Wrong input.");
        answer = keepPlaying();
    }

    free(buff);
    return answer;
}

Game *initGame(void) {
    Game *game = (Game *) malloc(sizeof(Game));
    *game = (Game) {initNode(), 1, DEFAULT_DEPTH, X, X, TRUE};
    elapsedTime = 0;
    return game;
}


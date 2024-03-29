#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bling.h"
#include "board.h"
#include "defs.h"
#include "game.h"
#include "masks.h"
#include "minimax.h"

#define GB_SCREEN_W 18
#define GB_SCREEN_H 10
#define SIDE_W 25
#define SIDE_H 9
#define CREDITS_W 28

#ifdef __linux__
#define COLOR_ON  "\033[0;7m" // inverted background
#define COLOR_OFF "\033[0;0m" // default
#endif // __linux__

static void printGameBoy(char screen[GB_SCREEN_H][GB_SCREEN_W], char side[SIDE_H][SIDE_W], char credits[2][CREDITS_W]);
static char *difficulty(const short depth);
static char *trimBigNumber(const unsigned num);
static char *posPerSec(unsigned positions, double time);
static double secondsElapsed(double time);
static void humanInput(Game *game);

static void printInterface(const Game *game) {
    double elapsedTime = game->stats.elapsedTime;
    unsigned exploredPositions = game->stats.exploredPositions;

    char screen[GB_SCREEN_H][GB_SCREEN_W];
    for(short height = 0; height < GB_SCREEN_H; height++) {
        for(short width = 0; width < GB_SCREEN_W-1; width++) {
            screen[height][width] = ' ';
        }
    }

    char buffer[7];
    snprintf(buffer, 7, "%6d", game->turn);
    snprintf(screen[0], GB_SCREEN_W, "        Turn %s  ", buffer + 4);

    char lastMove = showTurn(game->node->turn);
    char nextMove = showTurn(NEXT(game->node->turn));
    char emptySlot = '-';
    char slot;
    for(short row = 0; row < BOARD_SIZE; row++) {
        for(short col = 0; col < BOARD_SIZE; col++) {
            if(game->node->board[TURN] & shift(BOARD_SIZE - row - 1, col)) {
                slot = lastMove;
            } else if(game->node->board[BOTH] & shift(BOARD_SIZE - row - 1, col)) {
                slot = nextMove;
            } else {
                slot = emptySlot;
            }
            screen[row + 1][2*col + 1] = slot;
        }
    }

    // for(short width = 0; width < GB_SCREEN_W-1; width++) {
        // screen[GB_SCREEN_H-2][width] = '_';
    // }
    for(short width = 2; width < GB_SCREEN_W-2; width++) {
        screen[GB_SCREEN_H-1][width] = ':';
        width++;
    }
    // screen[GB_SCREEN_H-1][0] = '(';
    // screen[GB_SCREEN_H-1][GB_SCREEN_W-2] = ')';
    for(short col = 0; col < BOARD_SIZE; col++) {
        if(col == game->stats.lastMove) {
            screen[GB_SCREEN_H-1][2*col + 1] = '^';
        } else {
            screen[GB_SCREEN_H-1][2*col + 1] = '0' + (char) (col + 1);
        }
    }
    for(short height = 0; height < GB_SCREEN_H; height++) {
        screen[height][GB_SCREEN_W-1] = '\0';
    }

    char *exploredPositionsPrint = trimBigNumber(exploredPositions);
    char *posPerSecPrint = posPerSec(exploredPositions, elapsedTime);
    char *heuristicValue = trimBigNumber(game->stats.lastHeuristic);
    char *difficultyPrint = difficulty(game->depth);

    char side[2][SIDE_H][SIDE_W];
    short pos = 0;
    snprintf(side[0][pos++], SIDE_W, "      Playing as %c      ", showTurn(game->playerSide));
    snprintf(side[0][pos++], SIDE_W, "    Difficulty %s", difficultyPrint);
    snprintf(side[0][pos++], SIDE_W, "                        ");
    snprintf(side[0][pos++], SIDE_W, " 1-8 Play on column     ");
    snprintf(side[0][pos++], SIDE_W, "   h Toggle help/stats  ");
    snprintf(side[0][pos++], SIDE_W, "%4s Position%s explored", exploredPositionsPrint, exploredPositions == 1 ? "" : "s" );
    snprintf(side[0][pos++], SIDE_W, "%4s per second         ", posPerSecPrint);
    snprintf(side[0][pos++], SIDE_W, "%4.1lf seconds elapsed    ", secondsElapsed(elapsedTime));
    snprintf(side[0][pos++], SIDE_W, "%4s Position score", heuristicValue);

    pos = 0;
    snprintf(side[1][pos++], SIDE_W, "      Playing as %c      ", showTurn(game->playerSide));
    snprintf(side[1][pos++], SIDE_W, "    Difficulty %s", difficultyPrint);
    snprintf(side[1][pos++], SIDE_W, "                        ");
    snprintf(side[1][pos++], SIDE_W, " 1-8 Play on column     ");
    snprintf(side[1][pos++], SIDE_W, "   h Toggle help/stats  ");
    snprintf(side[1][pos++], SIDE_W, "  d# Change difficulty  ");
    snprintf(side[1][pos++], SIDE_W, "   s Switch sides       ");
    snprintf(side[1][pos++], SIDE_W, "   n New game           ");
    snprintf(side[1][pos++], SIDE_W, "   q Stop game          ");

    for(short height = 0; height < SIDE_H; height++) {
        side[0][height][SIDE_W-1] = '\0';
        side[1][height][SIDE_W-1] = '\0';
    }

    char credits[2][CREDITS_W] = {" Artwork source:           ",
                                  "www.oocities.org/soho/7373/"};

    printGameBoy(screen, side[game->help], credits);

    // printf("\n\n");
    // for(short height = 0; height < GB_SCREEN_H; height++) {
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
    free(heuristicValue);
}

static void printGameBoy(char screen[GB_SCREEN_H][GB_SCREEN_W], char side[SIDE_H][SIDE_W], char credits[2][CREDITS_W]) {
    const char *padding = "     ";
    for(short iter = 0; iter < 80; iter++) {
        printf("\n");
    }
    printf("%s    ___________________________\n", padding);
    printf("%s   |OFFo oON                   |\n", padding);
    printf("%s   | .-----------------------. |\t%s\n", padding, side[0]);
    printf("%s   | |  .-----------------.  | |\t%s\n", padding, side[1]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[0], side[2]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[1], side[3]);
    printf("%s   | |))|"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[2], side[4]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[3], side[5]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[4], side[6]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[5], side[7]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[6], side[8]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\n", padding, screen[7]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[8], credits[0]);
    printf("%s   | |  |"COLOR_ON"%s"COLOR_OFF"|  | |\t%s\n", padding, screen[9], credits[1]);
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

static char *difficulty(const short depth) {
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

static char *trimBigNumber(const unsigned num) {
    char *buff = (char *) malloc(25 * sizeof(char));
    if(num < 1000) {
        snprintf(buff, 25, "%u", num);
    } else if(num < 1000000) {
        snprintf(buff, 25, "%uK", num / 1000);
    } else {
        snprintf(buff, 25, "%uM", num / 1000000);
    }
    return buff;
}

static char *posPerSec(unsigned positions, double time) {
    double seconds = time / ((double) CLOCKS_PER_SEC);
    return trimBigNumber((unsigned) (((double) positions) / seconds));
}

static double secondsElapsed(double time) {
    return time / ((double) CLOCKS_PER_SEC);
}

static void humanInput(Game *game) {
    printInterface(game);
    printf(" > ");
    char *buff = (char *) malloc(255 * sizeof(char));
    scanf("%s", buff);

    char input = buff[0];
    if((input >= '0') && (input <= '9')) {
        short move = (short) atoi(buff);
        if((move <= 0) || (move > BOARD_SIZE)) {
            humanInput(game);
            // fprintf(stderr, "Invalid column\n");
        } else if(FULL_COLUMN(game->node->board, move-1)) {
            humanInput(game);
        } else {
            makeMove(game->node, move-1);
        }
    } else {
        short depth;
        switch(input) {
            case 'h':   // Toggle help/stats
                game->help = NOT(game->help);
                humanInput(game);
                break;
            case 'd':   // Change difficulty
                depth = (short) atoi(buff + 1);
                if(depth <= 0) {
                    game->depth = 4;
                } else {
                    game->depth = depth;
                }
                humanInput(game);
                break;
            case 'q':   // Quit
                game->node->nchildren = 0;
                break;
            case 's':   // Switch sides
                game->playerSide = NEXT(game->playerSide);
                machineMove(game);
                // humanInput(game);
                break;
            case 'n':   // New game
                resetGame(game);
                game->side = NEXT(game->side);
                break;
            default:    // Other
                // fprintf(stderr, "Invalid input\n");
                humanInput(game);
                break;
        }
    }

    free(buff);
}

static void keepPlaying(Game *game) {
    printf(" Want to keep on playing? (y/n)\n");
    printf(" > ");

    char *buff = (char *) malloc(255 * sizeof(char));
    scanf("%s", buff);

    if(buff[0] == 'y') {
        game->keepPlaying = TRUE;
    } else if(buff[0] == 'n') {
        game->keepPlaying = FALSE;
    } else {
        printf(" Wrong input.");
        keepPlaying(game);
    }

    free(buff);
}

int ascii_main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv) {
    Game *game = initGame();
    do {
        while(game->node->nchildren) {
            if(game->side == game->playerSide) {
                humanInput(game);
            } else {
                machineMove(game);
            }
            game->side = NEXT(game->side);
            game->turn += game->side;
        }
        printInterface(game);
        resetGame(game);
        keepPlaying(game);
    } while(game->keepPlaying);

    free(game->node);
    free(game);
    return EXIT_SUCCESS;
}


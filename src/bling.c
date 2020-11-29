#include "bling.h"

void printGameBoy(char screen[SCREEN_H][SCREEN_W], char side[SIDE_H][SIDE_W], char credits[SIDE_W]);
void printMenu(void);

void printGame(void) {
    char screen[SCREEN_H][SCREEN_W];

    for(short height = 0; height < 1; height++) {
        for(short width = 0; width < SCREEN_W-1; width++) {
            screen[height][width] = ' ';
        }
    }
    for(short height = 1; height < 1 + N; height++) {
        for(short width = 0; width+1 < SCREEN_W-1; width += 2) {
            screen[height][width]   = ' ';
            screen[height][width+1] = (width + height) % 2 ? 'X' : 'O';
        }
        screen[height][SCREEN_W-2] = ' ';
    }
    for(short height = 1 + N; height < SCREEN_H; height++) {
        for(short width = 0; width < SCREEN_W-1; width++) {
            screen[height][width] = ' ';
        }
    }
    ASSERT(turn < 100);

    char side[SIDE_H][SIDE_W] =    {"  Welcome to connect 4  ",
                           " 123456789012345 123456 ",
                           " - - - - - - - - - - -  ",
                           " - - - - - - - - - - -  ",
                           " - - - - - - - - - - -  ",
                           " - - - - - - - - - - -  ",
                           " - - - - - - - - - - -  ",
                           " - - - - - - - - - - -  ",
                           "       ^                "};
    char credits[SIDE_W] =     " Visit www.ascii-art.com";

    printGameBoy(screen, side, credits);
}

void printMenu(void) {
    printGame();
    // char screen[SCREEN_H][SCREEN_W] = {"                 ",
                           // " - - - - - - - - ",
                           // " - - - - - - - - ",
                           // " - - - - - - - - ",
                           // " - - - - - - - - ",
                           // " - - - - - - - - ",
                           // " - - - - - - - - ",
                           // " - - - - - - - - ",
                           // " - - - - - - - - ",
                           // "       ^         "};
    // char side[SIDE_H][SIDE_W] =    {"  Side text       Side  ",
                           // " 123456789012345 123456 ",
                           // " - - - - - - - - - - -  ",
                           // " - - - - - - - - - - -  ",
                           // " - - - - - - - - - - -  ",
                           // " - - - - - - - - - - -  ",
                           // " - - - - - - - - - - -  ",
                           // " - - - - - - - - - - -  ",
                           // "       ^                "};
    // char credits[SIDE_W] =     " Visit www.ascii-art.com";
    // printGameBoy(screen, side, credits);
    int depth;
    scanf("%d", &depth);
}

void printGameBoy(char screen[SCREEN_H][SCREEN_W], char side[SIDE_H][SIDE_W], char credits[SIDE_W]) { 
    char *padding = "     ";
    printf("\n\n");
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
    printf("%s   | |  |%s|  | |\t%s\n", padding, screen[8], credits);
    printf("%s   | |  |%s|  | |\n", padding, screen[9]);
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


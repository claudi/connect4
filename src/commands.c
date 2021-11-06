#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bling.h"
#include "commands.h"
#include "defs.h"
#include "gui.h"
#include "headless.h"

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

typedef struct {
    char *name;
    int (*function)(int argc, char **argv);
} command;

const command commands[] = {
    { "headless", headless_main },
    { "ascii", ascii_main },
    { "gui", gui_main },
};

int handle_commands(int argc, char **argv) {
    const size_t ncommands = ARRAY_SIZE(commands);

    if(argc < 2) {
        fprintf(stderr, "usage: %s <command>\n", argv[0]);
        fprintf(stderr, "where <command> can be any of\n");
        for(size_t iter = 0; iter < ncommands; iter++) {
            fprintf(stderr, "    %s\n", commands[iter].name);
        }
        return EXIT_FAILURE;
    }

    const char *cmd = argv[1];

    for(size_t iter = 0; iter < ncommands; iter++) {
        if(strcmp(cmd, commands[iter].name) == 0) {
            return commands[iter].function(argc, argv);
        }
    }

    return EXIT_SUCCESS;
}


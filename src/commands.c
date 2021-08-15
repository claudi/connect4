#include "commands.h"

command commands[] = {
    { "headless", headless_main },
    { "ascii", ascii_main },
    { "gui", gui_main },
};

int handle_commands(int argc, char **argv) {
    const size_t ncommands = ARRAY_SIZE(commands);
    if(argc < 2) {
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

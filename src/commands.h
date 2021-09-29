#ifndef COMMAND_GUARD
#define COMMAND_GUARD
#include "bling.h"
#include "gui.h"
#include "headless.h"
#include "neural-network.h"

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

typedef struct {
    char *name;
    int (*function)(int argc, char **argv);
} command;

int handle_commands(int argc, char **argv);

#endif // COMMAND_GUARD


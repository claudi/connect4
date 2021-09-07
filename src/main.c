#include "commands.h"

int main(int argc, char **argv) {
    testNetwork();
    return handle_commands(argc, argv);
}


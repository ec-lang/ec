#include <stdbool.h>
#include <stdio.h>

#include "args.h"

#define ECC_VERSION "0.0.1"

int main(int argc, char *argv[])
{
    struct Option option;
    parseArgs(argc, argv, &option);

    if (option.isError || option.isHelp) {
        printf("%s", option.help);
    }

    return 0;
}

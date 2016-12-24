#ifndef ECC_ARGS_H
#define ECC_ARGS_H

typedef struct Option {
    bool isError;
    bool isHelp;
    bool isVersion;
    bool isVerbose;

    char *help;
} Option;

int parseArgs(int argc, char *argv[], Option *option);

#endif // ECC_ARGS_H

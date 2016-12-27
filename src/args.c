#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "args.h"

typedef struct Args {
    int nArgs;
    char **args;

    int iArgs;
    char *pArgs;
} Args;

static char HELP_MESSAGE[] =
"Usage: ecc [options] <file>...\n"
"\n"
"Options:\n"
"  -h --help     Show this screen.\n"
"  --version     Show version.\n"
"  -v            Show commands to run and use verbose output";

static void initArgs(int argc, char *argv[], Args *args)
{
    args->nArgs = argc - 1;
    args->args = argv + 1;
    args->iArgs = 0;
    args->pArgs = args->args[0];
}

static char getChar(Args *args)
{
    if (args->iArgs < args->nArgs) {
        char ch = *args->pArgs++;
        if (ch == '\0') {
            ++args->iArgs;
            args->pArgs = args->args[args->iArgs];
            return getChar(args);
        } else {
            return ch;
        }
    } else {
        return EOF;
    }
}

static void parseLong(Args *args, Option *option)
{
    char buf[4096];
    char *ptr = buf;
    char *end = buf + sizeof(buf);

    for (;;) {
        char ch = getChar(args);
        if (ch == ' ' || ch == EOF) {
            break;
        } else {
            assert(ptr < end);
            *ptr++ = ch;
        }
    }

    *ptr = '\0';

    if (strcmp(buf, "version") == 0) {
        option->isVersion = true;
    } else {
        option->isError = true;
    }
}

static void parseShort(Args *args, Option *option, char next)
{
    switch (next) {
    case 'h':
        option->isHelp = true;
        break;
    case 'v':
        option->isVerbose = true;
        break;
    default:
        option->isError = true;
        break;
    }
}

int parseArgs(int argc, char *argv[], Option *option)
{
    struct Args args_;
    struct Args *args = &args_;
    initArgs(argc, argv, args);

    option->isError = false;
    option->isHelp = false;
    option->isVersion = false;
    option->isVerbose = false;
    option->help = HELP_MESSAGE;

    char ch = getChar(args);
    if (ch == EOF) {
        option->isError = true;
    }

    while (ch != EOF) {
        if (ch == '-') {
            char next = getChar(args);
            if (next == '-') {
                parseLong(args, option);
            } else {
                parseShort(args, option, next);
            }
        }

        ch = getChar(args);
    }

    return 0;
}

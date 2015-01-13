#include "options_parsing.h"
#include "common_headers.h"

#include <getopt.h>

static struct option longopts[] = {
    { "no-fork", no_argument,       NULL, 'f'   },
    { "config",  required_argument, NULL, 'c'   },
    { "help",    no_argument,       NULL, 'h'   },
    { NULL,      0,                 NULL, 0     }
};

static void usage()
{
    fprintf(stderr, "Usage: \n\n");
    fprintf(stderr, "-f, --no-fork - run in foreground,\n");
    fprintf(stderr, "-c, --config  - specify alternative configuration file,\n");
    fprintf(stderr, "-h, --help    - usage, displays this message.\n");
    fprintf(stderr, "\nExample usage:\n\n");
    fprintf(stderr, "./DMServer --no-fork -c /Users/Test/DMServer_configuration.config\n");
}

void ParseOptions(int argc, char **argv)
{
    int ch;

    rMode = BACKGROUND;
    while ((ch = getopt_long(argc, argv, "fc:", longopts, NULL)) != -1)
    {
        switch (ch)
        {
        case 'f':
            fprintf(stderr, "no-fork option selected\n");
            rMode = FOREGROUND;
            break;
        case 'c':
            fprintf(stderr, "new configuration selected\n");
            break;
        default:
            usage();
        }
        argc -= optind;
        argv += optind;
    }
}

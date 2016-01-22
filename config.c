#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/* Mostly a wrapper around getopt() */
glui8 iffy_args_parse( iffy_args_t *target, int argc, char **argv )
{
    memset( target, 0, sizeof( target ) );
    return 0; // success
}

glui8 iffy_config_open( FILE *target, const char *file )
{
    target = NULL;
    return 1; // failure XXX
}

glui8 iffy_config_parse( iffy_options_t *target, FILE *handle )
{
    memset( target, 0, sizeof( target ) );
    return 0; // success
}

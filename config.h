#ifndef IFFY_CONFIG_H
#define IFFY_CONFIG_H
#include <stdio.h>
#include "glk.h"
#include "iffy.h"

glui8 iffy_args_parse( iffy_args_t * target, int argc, char ** argv );
glui8 iffy_config_open( FILE * target, const char * file );
glui8 iffy_config_parse( iffy_options_t * target, FILE * handle );

#endif


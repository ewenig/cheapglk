#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"

/* Initialize the IRC client session */
glui8 iffy_callbacks_init( irc_callbacks_t *target, iffy_options_t *options )
{
    memset( target, 0, sizeof( &target ) );
    return 0; // success
}

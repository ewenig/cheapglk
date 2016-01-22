#include <stdio.h>
#include <stdlib.h>
#include "state.h"

glui8 iffy_init_state( iffy_state_t *target )
{
    target = (iffy_state_t *)malloc( sizeof( iffy_state_t ) );
    if ( target == NULL )
    {
        return 1; // failure
    }

    target->files = (iffy_state_files_t *)malloc( sizeof( iffy_state_files_t ) );
    if ( target->files == NULL )
    {
        return 1; // failure
    }

    target->opts = (iffy_state_options_t *)malloc( sizeof( iffy_state_options_t ) );
    if ( target->opts == NULL )
    {
        return 1; // failure
    }

    return 0;
}

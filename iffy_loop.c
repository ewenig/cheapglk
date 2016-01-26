#include <stdio.h>
#include <stdlib.h>
#include "iffy.h"
#include "iffy_loop.h"

glui8 iffy_loop_tick( void )
{
    if ( !irc_is_connected( state->session ) )
    {
        iffy_err( "IRC isn't connected" );
        return 1;
    }

    struct timeval tv;
    fd_set in_set, out_set;
    int maxfd = 0;

    tv.tv_usec = 250000;
    tv.tv_sec = 0;

    FD_ZERO( &in_set );
    FD_ZERO( &out_set );

    irc_add_select_descriptors( state->session, &in_set, &out_set, &maxfd );

    if ( select( maxfd + 1, &in_set, &out_set, 0, &tv ) < 0 )
    {
        iffy_err( "select() call returned non-zero" );
        return 1;
    }

    if ( irc_process_select_descriptors( state->session, &in_set, &out_set ) )
    {
        iffy_err( "irc_process_select_descriptors() call returned non-zero" );
        return 1;
    }

    return 0;
}

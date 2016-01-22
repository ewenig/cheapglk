#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"

/* Initialize the IRC client session */
glui8 iffy_callbacks_init( irc_callbacks_t *target, iffy_state_options_t *options )
{
    memset( target, 0, sizeof( &target ) );
    return 0; // success
}

void iffy_callback_connect( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    if ( state->opts->pass != NULL )
    {
        int res;
        char *identifyStr;
        identifyStr = malloc( sizeof( state->opts->pass ) + 10 );
        if ( identifyStr == NULL )
        {
            iffy_err( "Couldn't allocate memory for identify string" );
            return;
        }

        *identifyStr = 0;
        strcat( identifyStr, "identify " );
        strcat( identifyStr, state->opts->pass );
        res = irc_cmd_msg( session, "NickServ", identifyStr );
        free( identifyStr );
        if ( res )
        {
            iffy_err( "Couldn't send identify string to NickServ" );
        }
    }

    return;
}

void iffy_callback_quitpart( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // stub function
    return;
}

void iffy_callback_nick( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // stub function
    return;
}

void iffy_callback_umode( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // stub function
    return;
}

void iffy_callback_channel( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // stub function
    return;
}

void iffy_callback_privmsg( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // stub function
    return;
}

void iffy_callback_numeric( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // stub function
    return;
}

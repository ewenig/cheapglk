#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "iffy.h"
#include "glk.h"

// generic handler for IRC input
void iffy_input_handle( const char *input, const char *match, void ( *handler )( const char * ) )
{
    if ( strcmp( input, match ) == 0 )
    {
        handler( input );
    }
}

// output a help message
void iffy_input_help( const char *input )
{
    irc_cmd_msg( state->session, state->opts->channel, "See http://github.com/ewenig/iffy for documentation." );
}

// output a list of games
void iffy_input_list( const char *input )
{
    irc_cmd_msg( state->session, state->opts->channel, "Games:" );

    int i = -1;
    while ( state->games->list[++i] != NULL )
    {
        char *tmp = malloc( sizeof( state->games->list[i] ) + 6 );
        sprintf( tmp, "%4i %s", i + 1, state->games->list[i] );
        irc_cmd_msg( state->session, state->opts->channel, state->games->list[i] );
        free( tmp );
    }
}

// select a game
void iffy_input_load( const char *input )
{
    uint16_t selection;
    selection = strtol( input + 6, (char **)NULL, 10 );
    if ( selection == 0 || errno == ERANGE )
    {
        irc_cmd_msg( state->session, state->opts->channel, "Invalid value for !load." );
    }

    state->games->current = state->games->list[selection - 1];

    char *tmp = malloc( sizeof( state->games->list[selection - 1] + 9 ) );
    sprintf( tmp, "Loaded %s.", state->games->current );
    irc_cmd_msg( state->session, state->opts->channel, tmp );
    free( tmp );
}

// handle game input
void iffy_input_game_cmd( const char *input )
{
    if ( state->input->next == NULL )
    {
        state->input->next = strdup( input + 2 );
    }
    else
    {
        // XXX
    }
}

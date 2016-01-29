#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "iffy.h"
#include "glk.h"

// generic handler for IRC input
void iffy_input_handle( const char *input, const char *match, void ( *handler )( const char * ) )
{
    if ( iffy_strcmp_start( match, input ) == 0 )
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
    glui8 res = iffy_games_refresh( );
    if ( res != 0 )
    {
        irc_cmd_msg( state->session, state->opts->channel, "Error refreshing games list." );
        return;
    }

    irc_cmd_msg( state->session, state->opts->channel, "Games:" );

    if ( state->games->list == NULL )
    {
        return;
    }

    GSList *i = state->games->list;
    int j = 1;
    do
    {
        char *tmp = malloc( sizeof( i->data ) + 6 );
        sprintf( tmp, "%4i %s", j, (char *)i->data );
        irc_cmd_msg( state->session, state->opts->channel, tmp );
        free( tmp );
        j++;
    } while ( ( i = i->next ) != NULL );
}

// select a game
void iffy_input_load( const char *input )
{
    uint16_t selection;
    selection = strtol( input + 9, (char **)NULL, 10 );
    if ( selection == 0 || errno == ERANGE )
    {
        irc_cmd_msg( state->session, state->opts->channel, "Invalid value for !loadgame." );
    }

    state->games->current = (char *)g_slist_nth_data( state->games->list, selection - 1 );
    if ( state->games->current == NULL )
    {
        iffy_errf( "user selected illegal game index %d", selection - 1 );
        irc_cmd_msg( state->session, state->opts->channel, "Invalid game value." );
        return;
    }

    char *tmp = malloc( sizeof( state->games->current ) + 9 );
    sprintf( tmp, "Loaded %s.", state->games->current );
    irc_cmd_msg( state->session, state->opts->channel, tmp );
    free( tmp );

    state->inGame = 1;
}

// handle game input
void iffy_input_game_cmd( const char *input )
{
    if ( state->inGame == 0 )
    {
        irc_cmd_msg( state->session, state->opts->channel, "No game currently selected." );
        return;
    }

    if ( state->input->next == NULL )
    {
        state->input->next = strdup( input + 2 );
    }
    else
    {
        // XXX
        // queue the input I guess
    }
}

// function that only compares until the end of string 1
gint iffy_strcmp_start( const char *a, const char *b )
{
    return strncmp( a, b, strlen( a ) );
}

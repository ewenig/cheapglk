#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iffy.h"

// glui8 iffy_state_init( iffy_state_t *target )
glui8 iffy_state_init( void )
{
    state = (iffy_state_t *)malloc( sizeof( iffy_state_t ) );
    if ( state == NULL )
    {
        return 1; // failure
    }

    state->files = (iffy_state_files_t *)malloc( sizeof( iffy_state_files_t ) );
    if ( state->files == NULL )
    {
        return 1; // failure
    }

    state->opts = (iffy_state_options_t *)malloc( sizeof( iffy_state_options_t ) );
    if ( state->opts == NULL )
    {
        return 1; // failure
    }

    state->games = (iffy_state_games_t *)malloc( sizeof( iffy_state_games_t ) );
    if ( state->games == NULL )
    {
        return 1; // failure
    }

    state->input = (iffy_state_input_t *)malloc( sizeof( iffy_state_input_t ) );
    if ( state->input == NULL )
    {
        return 1; //failure
    }

    state->users = NULL;

    state->acceptingRplNamreply = 0;

    return 0;
}

iffy_user *iffy_user_get( GSList *target )
{
    return (iffy_user *)g_slist_nth_data( state->users, g_slist_position( state->users, target ) );
}

glui8 iffy_games_refresh( void )
{
    // clear out the list of games
    g_slist_free( state->games->list );
    state->games->list = NULL;

    DIR *folder = opendir( state->opts->gamesFolder );
    if ( folder == NULL )
    {
        iffy_err( "Couldn't open games folder" );
        return 1;
    }
    struct dirent *entry;
    while ( ( entry = readdir( folder ) ) != NULL )
    {
        if ( *entry->d_name == '.' )
        {
            continue;
        }
        state->games->list = g_slist_insert( state->games->list, entry->d_name, -1 );
    }
    closedir( folder );
    return 0;
}

void iffy_buf_push_char( char c )
{
    if ( state->sendBuf == NULL )
    {
        state->sendBuf = (char *)malloc( 1024 );
        if ( state->sendBuf == NULL )
        {
            iffy_err( "Couldn't allocate memory for send buffer" );
            exit( 0 );
        }
    }

    if ( c == '\n' )
    {
        irc_cmd_msg( state->session, state->opts->channel, state->sendBuf );
        free( state->sendBuf );
        state->sendBuf = NULL;
        return;
    }

    size_t buflen = strlen( state->sendBuf );
    if ( ( buflen % 1024 ) > 1024 - 5 )
    {
        char *newBuf = (char *)realloc( state->sendBuf, buflen + 1024 );
        if ( newBuf == NULL )
        {
            iffy_err( "Couldn't reallocate memory for send buffer" );
            exit( 0 );
        }
        state->sendBuf = newBuf;
    }

    strncat( state->sendBuf, &c, 1 );
}

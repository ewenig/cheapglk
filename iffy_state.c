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

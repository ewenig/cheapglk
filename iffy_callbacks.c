#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iffy.h"

glui8 iffy_callbacks_init( irc_callbacks_t **target, iffy_state_options_t *options )
{
    *target = malloc( sizeof( irc_callbacks_t ) );
    if ( target == NULL )
    {
        iffy_err( "Couldn't initialize the callbacks struct" );
        return 1;
    }

    memset( *target, 0, sizeof( irc_callbacks_t ) );
    // set the callbacks
    ( *target )->event_connect = iffy_callback_connect;
    ( *target )->event_quit = iffy_callback_quitpart;
    ( *target )->event_part = iffy_callback_quitpart;
    ( *target )->event_umode = iffy_callback_umode;
    ( *target )->event_channel = iffy_callback_channel;
    ( *target )->event_privmsg = iffy_callback_privmsg;
    ( *target )->event_nick = iffy_callback_nick;
    ( *target )->event_numeric = iffy_callback_numeric;

    return 0; // success
}

void iffy_callback_connect( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    int res;

    if ( state->opts->pass != NULL )
    {
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

    res = irc_cmd_join( session, state->opts->channel, 0 );
    if ( res )
    {
        iffy_errf( "Couldn't join %s", state->opts->channel );
    }

    state->acceptingRplNamreply = 1;
    // irc_cmd_names( session, state->opts->channel );

    return;
}

void iffy_callback_quitpart( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // dummy object to help us find the user entry
    iffy_user searchUser = { (char *)origin, 0 };
    GSList *targetUser = g_slist_find_custom( state->users, &searchUser, iffy_users_cmp );

    if ( targetUser == NULL )
    {
        // this shouldn't happen
        iffy_warnf( "Received %s event for untracked user", event );
        return;
    }

    // delete the user entry
    state->users = g_slist_remove( state->users, targetUser );
}

void iffy_callback_umode( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // stub function
    return;
}

void iffy_callback_channel( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // dummy object to help us find the user entry
    iffy_user searchUser = { (char *)origin, 0 };
    GSList *targetUser = g_slist_find_custom( state->users, &searchUser, iffy_users_cmp );

    if ( targetUser == NULL )
    {
        // this shouldn't happen
        iffy_warn( "Received channel event for untracked user" );
        return;
    }

    if ( params[1] != NULL && ( *params[1] == '>' || *params[1] == '!' ) )
    {
        // iffy will ignore any input from a user who doesn't have ops, they're cold like that.
        if ( ( iffy_user_get( targetUser ) )->hasOps )
        {
            // trigger appropriate callbacks
            iffy_input_handle( params[1], ">", iffy_input_game_cmd );
            iffy_input_handle( params[1], "!help", iffy_input_help );
            iffy_input_handle( params[1], "!loadgame", iffy_input_load );
            iffy_input_handle( params[1], "!listgames", iffy_input_list );
        }
    }
}

void iffy_callback_privmsg( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // stub function
    return;
}

void iffy_callback_nick( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count )
{
    // dummy object to help us find the user entry
    iffy_user searchUser = { (char *)origin, 0 };
    GSList *targetUser = g_slist_find_custom( state->users, &searchUser, iffy_users_cmp );

    if ( targetUser == NULL )
    {
        // this shouldn't happen
        iffy_warn( "Received nick event for untracked user" );
        return;
    }

    // update the user entry
    ( iffy_user_get( targetUser ) )->nick = (char *)params[0];
}

void iffy_callback_numeric( irc_session_t *session, unsigned int event, const char *origin, const char **params, unsigned int count )
{
    switch ( event )
    {
    case LIBIRC_RFC_RPL_NAMREPLY:
        if ( state->acceptingRplNamreply )
        {
            int i = -1;
            char **nicksStr;
            nicksStr = g_strsplit( params[count - 1], " ", 0 );
            while ( nicksStr[++i] != NULL )
            {
                iffy_user *newUser;
                newUser = malloc( sizeof( iffy_user ) );
                if ( newUser == NULL )
                {
                    iffy_err( "Couldn't allocate struct for new user" );
                }
                newUser->hasOps = ( *nicksStr[i] == '@' || *nicksStr[i] == '&' ) ? 1 : 0;
                newUser->nick = strdup( ( newUser->hasOps ) ? nicksStr[i] + 1 : nicksStr[i] );

                if ( strcmp( newUser->nick, state->opts->nick ) == 0 )
                {
                    continue;
                }

                state->users = g_slist_insert( state->users, newUser, -1 );
            }
        }
        else
        {
            iffy_warn( "RPL_NAMREPLY called when not accepting response" );
        }
        break;
    case LIBIRC_RFC_RPL_ENDOFNAMES:
        if ( state->acceptingRplNamreply )
        {
            state->acceptingRplNamreply = 0;
        }
        else
        {
            iffy_warn( "RPL_ENDOFNAMES called when not accepting response" );
        }
        break;
    }
    return;
}

// modified from BSD strcmp() implementation
gint iffy_users_cmp( gconstpointer a, gconstpointer b )
{
    char *s1 = ( (iffy_user *)a )->nick, *s2 = ( (iffy_user *)b )->nick;
    while ( *s1++ == *s2++ )
    {
        // nop
    }

    if ( *s1 == 0 )
    {
        return 0;
    }

    return ( *(const unsigned char *)s1 - *(const unsigned char *)( s2 - 1 ) );
}

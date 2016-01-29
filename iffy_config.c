#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include "iffy.h"

/* Mostly a wrapper around getopt() */
glui8 iffy_args_parse( iffy_args_t *target, int argc, char **argv )
{
    target->daemonize = 0;
    target->configFile = NULL;

    // call getopt
    opterr = 0;
    int c;
    while ( ( c = ( getopt( argc, argv, "df:" ) ) ) != -1 )
    {
        switch ( c )
        {
        case 'd':
            target->daemonize = 1;
            break;
        case 'f':
            target->configFile = optarg;
            break;
        case '?':
            if ( optopt == 'f' )
            {
                iffy_err( "Option -f requires a file argument" );
                return 1; // failure
            }
            break;
        }
    }

    if ( target->configFile == NULL )
    {
        iffy_err( "Must specify a config file using -f." );
        return 1; // failure
    }

    return 0; // success
}

glui8 iffy_config_open( GKeyFile **target, const char *file )
{
    gboolean ret;
    GError *error = NULL;

    *target = g_key_file_new( );
    ret = g_key_file_load_from_file( *target, file, G_KEY_FILE_NONE, &error );
    if ( iffy_config_check_err( &ret, error ) )
    {
        return 1;
    }

    return 0; // success
}

glui8 iffy_config_parse( iffy_state_options_t *target, GKeyFile *handle )
{
    GError *error = NULL;

    memset( target, 0, sizeof( &target ) );

    // load in options
    target->server = (char *)g_key_file_get_string( handle, IFFY_IRC_CONFIG, "Server", &error );
    if ( iffy_config_check_err( target->server, error ) )
    {
        return 1;
    }
    target->port = (uint16_t)g_key_file_get_integer( handle, IFFY_IRC_CONFIG, "Port", &error );
    if ( iffy_config_check_err( &( target->port ), error ) )
    {
        return 1;
    }
    target->nick = (char *)g_key_file_get_string( handle, IFFY_IRC_CONFIG, "Nick", &error );
    if ( iffy_config_check_err( target->nick, error ) )
    {
        return 1;
    }
    target->username = (char *)g_key_file_get_string( handle, IFFY_IRC_CONFIG, "Username", &error );
    if ( iffy_config_check_err( target->username, error ) )
    {
        return 1;
    }
    target->pass = (char *)g_key_file_get_string( handle, IFFY_IRC_CONFIG, "Password", &error );
    error = NULL;
    target->channel = (char *)g_key_file_get_string( handle, IFFY_IRC_CONFIG, "Channel", &error );
    if ( iffy_config_check_err( target->channel, error ) )
    {
        return 1;
    }
    target->realName = (char *)g_key_file_get_string( handle, IFFY_IRC_CONFIG, "RealName", &error );
    if ( iffy_config_check_err( target->realName, error ) )
    {
        return 1;
    }
    target->gamesFolder = (char *)g_key_file_get_string( handle, IFFY_FILES_CONFIG, "GamesFolder", &error );
    if ( iffy_config_check_err( target->realName, error ) )
    {
        return 1;
    }

    return 0; // success
}

glui8 iffy_config_check_err( void *ret, GError *error )
{
    if ( ret == NULL || *(glui8 *)ret == 0 )
    {
        iffy_errf( "Error opening config file: %s", error->message );
        return 1;
    }
    return 0;
}

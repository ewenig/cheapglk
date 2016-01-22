#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include "config.h"

/* Mostly a wrapper around getopt() */
glui8 iffy_args_parse( iffy_args_t *target, int argc, char **argv )
{
    target->daemonize = 0;
    target->configFile = NULL;

    // call getopt
    opterr = 0;
    glui8 c;
    while ( ( c = getopt( argc, argv, "df:" ) != 1 ) )
    {
        switch ( c )
        {
        case 'd':
            target->daemonize = 1;
            break;
        case 'f':
            target->configFile = optarg;
        case '?':
            if ( optopt == 'f' )
            {
                iffy_err( "Option -f requires a file argument" );
                return 1; // failure
            }
        }
    }

    return 0; // success
}

glui8 iffy_config_open( GKeyFile *target, const char *file )
{
    gboolean ret;
    GError *error;

    ret = g_key_file_load_from_file( target, file, G_KEY_FILE_NONE, &error );
    if ( iffy_config_check_err( &ret, error ) )
    {
        return 1;
    }

    return 0; // success
}

glui8 iffy_config_parse( iffy_options_t *target, GKeyFile *handle )
{
    GError *error;

    memset( target, 0, sizeof( &target ) );

    // load in options
    target->server = (char *)g_key_file_get_string( handle, IFFY_GROUP_NAME, "Server", &error );
    if ( iffy_config_check_err( target->server, error ) )
    {
        return 1;
    }
    target->port = (uint16_t)g_key_file_get_integer( handle, IFFY_GROUP_NAME, "Port", &error );
    if ( iffy_config_check_err( &( target->port ), error ) )
    {
        return 1;
    }
    target->nick = (char *)g_key_file_get_string( handle, IFFY_GROUP_NAME, "Nick", &error );
    if ( iffy_config_check_err( target->nick, error ) )
    {
        return 1;
    }
    target->username = (char *)g_key_file_get_string( handle, IFFY_GROUP_NAME, "Username", &error );
    if ( iffy_config_check_err( target->username, error ) )
    {
        return 1;
    }
    target->pass = (char *)g_key_file_get_string( handle, IFFY_GROUP_NAME, "Password", &error );
    if ( iffy_config_check_err( target->pass, error ) )
    {
        return 1;
    }
    target->channel = (char *)g_key_file_get_string( handle, IFFY_GROUP_NAME, "Channel", &error );
    if ( iffy_config_check_err( target->channel, error ) )
    {
        return 1;
    }
    target->realName = (char *)g_key_file_get_string( handle, IFFY_GROUP_NAME, "RealName", &error );
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

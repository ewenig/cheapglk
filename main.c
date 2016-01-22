#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include "libircclient.h"
#include "libirc_rfcnumeric.h"
#include "glk.h"
#include "cheapglk.h"
#include "glkstart.h"
#include "iffy.h"

int gli_screenwidth = 80;
int gli_screenheight = 24;
int gli_utf8output = FALSE;
int gli_utf8input = FALSE;

static int inittime = FALSE;

int main( int argc, char *argv[] )
{
    glui8 res; // for testing the result of various functions
    g_set_prgname( "iffy" );

    // initialize program state - declared in iffy.h
    // res = iffy_state_init( state );
    res = iffy_state_init( );
    if ( res != 0 )
    {
        iffy_err( "Couldn't initialize state" );
        return res;
    }

    // Parse the command line arguments.
    iffy_args_t args;
    res = iffy_args_parse( &args, argc, argv );
    if ( res != 0 )
    {
        return res;
    }

    // Read in the configuration file.
    GKeyFile *optionsFile;
    res = iffy_config_open( &optionsFile, args.configFile );
    if ( res != 0 )
    {
        iffy_err( "Couldn't open options file" );
        return res;
    }

    // Parse the configuration file.
    res = iffy_config_parse( state->opts, optionsFile );
    if ( res != 0 )
    {
        iffy_err( "Couldn't parse options file" );
        return res;
    }

    // Set up the callbacks and IRC session.
    irc_callbacks_t *callbacks = NULL;
    iffy_callbacks_init( &callbacks, state->opts );

    irc_session_t *session = irc_create_session( callbacks );
    if ( !session )
    {
        iffy_err( "Couldn't create IRC session" );
        return 1;
    }

    // Set up libircclient session options XXX

    // Connect to the IRC server.
    res = irc_connect( session, state->opts->server, state->opts->port, 0, state->opts->nick,
                       state->opts->username, state->opts->realName );
    if ( res != 0 )
    {
        iffy_err( "Couldn't connect to the IRC network" );
        return res;
    }

    // Initialize some internal data structures.
    gli_initialize_misc( );


    // Call the event loop.
    // XXX Actually call glk_main, and stick the handrolled event loop in idle points.
    irc_run( session );

    // Call the GLK process.
    // glk_main( );
    // glk_exit( );

    /* glk_exit() doesn't return, but the compiler may kvetch if main()
        doesn't seem to return a value. */
    return 0;
}

/* This opens a file for reading or writing. (You cannot open a file
   for appending using this call.)

   This should be used only by glkunix_startup_code().
*/
strid_t glkunix_stream_open_pathname_gen( char *pathname, glui32 writemode, glui32 textmode, glui32 rock )
{
    if ( !inittime )
        return 0;
    return gli_stream_open_pathname( pathname, ( writemode != 0 ), ( textmode != 0 ), rock );
}

/* This opens a file for reading. It is a less-general form of
   glkunix_stream_open_pathname_gen(), preserved for backwards
   compatibility.

   This should be used only by glkunix_startup_code().
*/
strid_t glkunix_stream_open_pathname( char *pathname, glui32 textmode, glui32 rock )
{
    if ( !inittime )
        return 0;
    return gli_stream_open_pathname( pathname, FALSE, ( textmode != 0 ), rock );
}

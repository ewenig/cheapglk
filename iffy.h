#ifndef IFFY_H
#define IFFY_H

#include <sys/types.h>
#include <dirent.h>
#include <glib.h>
#include "libircclient.h"
#include "glk.h"

#define malloc( N ) calloc( 1, N )
#define iffy_err( N ) fputs( "ERROR: " N "\n", stderr )
#define iffy_errf( N, M ) fprintf( stderr, "ERROR: " N "\n", M )
#define iffy_warn( N ) fputs( "WARNING: " N "\n", stderr )
#define iffy_warnf( N, M ) fprintf( stderr, "WARNING: " N "\n", M )

#define IFFY_IRC_CONFIG "irc"
#define IFFY_FILES_CONFIG "folders"
#define IFFY_ADMIN_CONFIG "admin"

typedef struct
{
    char *configFile;
    glui8 daemonize;
} iffy_args_t;

typedef struct
{
    char *server;
    uint16_t port;
    char *nick;
    char *username;
    char *pass;
    char *channel;
    char *realName;
    char *gamesFolder;
} iffy_state_options_t;

typedef struct
{
    char *dataFile;
    char *transcriptFile;
    char *cmdRecordFile;
    char *savedGameFile;
} iffy_state_files_t;

typedef struct
{
    char *nick;
    gboolean hasOps;
} iffy_user;

typedef struct
{
    GSList *list;
    char *current;
} iffy_state_games_t;

typedef struct
{
    char *next;
} iffy_state_input_t;

typedef struct
{
    iffy_state_files_t *files;
    iffy_state_options_t *opts;
    iffy_state_games_t *games;
    iffy_state_input_t *input;

    irc_session_t *session;
    GSList *users;

    gboolean acceptingRplNamreply;
    gboolean inGame;

    char *sendBuf;
} iffy_state_t;

iffy_state_t *state;

#include "iffy_callbacks.h"
#include "iffy_state.h"
#include "iffy_config.h"
#include "iffy_input.h"
#include "iffy_loop.h"

#endif

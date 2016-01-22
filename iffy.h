#ifndef IFFY_H
#define IFFY_H

#include <glib.h>
#include "glk.h"

#define malloc( N ) calloc( 1, N )
#define iffy_err( N ) fputs( "ERROR: " N "\n", stderr )
#define iffy_errf( N, M ) fprintf( stderr, "ERROR: " N "\n", M )
#define iffy_warn( N ) fputs( "WARNING: " N "\n", stderr )
#define iffy_warnf( N, M ) fprintf( stderr, "WARNING: " N "\n", M )

#define IFFY_GROUP_NAME "iffy"

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
    iffy_state_files_t *files;
    iffy_state_options_t *opts;
    GSList *users;
    gboolean acceptingRplNamreply;
} iffy_state_t;

iffy_state_t *state;

#include "iffy_callbacks.h"
#include "iffy_state.h"
#include "iffy_config.h"

#endif

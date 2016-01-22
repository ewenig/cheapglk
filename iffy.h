#ifndef IFFY_H
#define IFFY_H

#define malloc( N ) calloc( 1, N )
#define iffy_err( N ) fputs( "ERROR: " N, stderr )
#define iffy_errf( N, M ) fprintf( stderr, N, M )

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
    iffy_state_files_t *files;
    iffy_state_options_t *opts;
} iffy_state_t;

iffy_state_t *state;

#endif

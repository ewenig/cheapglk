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
} iffy_options_t;

#endif

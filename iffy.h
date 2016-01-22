#ifndef IFFY_H
#define IFFY_H

typedef struct {
    char * configFile;
    glui8 daemonize;
} iffy_args_t;

typedef struct {
    char * server;
    uint16_t port;
    char * nick;
    char * username;
    char * pass;
    char * channel;
    char * realName;
} iffy_options_t;

#endif


#ifndef IFFY_H
#define IFFY_H

typedef struct {
    char * configFile;
    uint8 daemonize;
} iffy_args_h;

typedef struct {
    char * network;
    uint16 port;
    char * nick;
    char * pass;
    char * channel;
} iffy_options_h;

#endif


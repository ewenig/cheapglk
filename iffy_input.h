#ifndef IFFY_INPUT_H
#define IFFY_INPUT_H
#include <stdio.h>
#include <stdlib.h>
#include "iffy.h"

void iffy_input_handle( const char *input, const char *match, void ( *handler )( const char * ) );
void iffy_input_help( const char *input );
void iffy_input_list( const char *input );
void iffy_input_load( const char *input );
void iffy_input_game_cmd( const char *input );
gint iffy_strcmp_start( const char *a, const char *b );

#endif

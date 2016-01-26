#ifndef IFFY_STATE_H
#define IFFY_STATE_H
#include <stdio.h>
#include <stdlib.h>
#include "glk.h"
#include "iffy.h"

glui8 iffy_state_init( void );
iffy_user *iffy_user_get( GSList *target );

#endif

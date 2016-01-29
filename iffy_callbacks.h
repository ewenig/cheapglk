#ifndef IFFY_CALLBACKS_H
#define IFFY_CALLBACKS_H
#include "glk.h"
#include "libircclient.h"
#include "libirc_rfcnumeric.h"
#include "iffy.h"

glui8 iffy_callbacks_init( irc_callbacks_t **target, iffy_state_options_t *options );
void iffy_callback_connect( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count );
void iffy_callback_join( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count );
void iffy_callback_quitpart( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count );
void iffy_callback_umode( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count );
void iffy_callback_channel( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count );
void iffy_callback_privmsg( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count );
void iffy_callback_nick( irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count );
void iffy_callback_numeric( irc_session_t *session, unsigned int event, const char *origin, const char **params, unsigned int count );
gint iffy_users_cmp( gconstpointer a, gconstpointer b );

#endif

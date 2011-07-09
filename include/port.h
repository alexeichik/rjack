#ifndef PORT_INCLUDED
#define PORT_INCLUDED

#include "rjack.h"

VALUE RJack_Port_free(VALUE self);
VALUE RJack_Port_name(VALUE self);
VALUE RJack_Port_get_buffer(VALUE self, VALUE nframes);

#endif
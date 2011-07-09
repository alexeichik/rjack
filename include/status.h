#ifndef STATUS_INCLUDED
#define STATUS_INCLUDED

#include "rjack.h"

VALUE RJack_Status_to_s(VALUE self);
VALUE RJack_Status_name_not_unique_p(VALUE self);

#endif
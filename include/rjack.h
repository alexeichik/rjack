#ifndef RJACK_INCLUDED
#define RJACK_INCLUDED

#include "ruby.h"
//#include "ruby/intern.h"
#include "stdio.h"
#include <jack/jack.h>
#include "client.h"
#include "status.h"
#include "port.h"
#include "buffer.h"

VALUE mRJack;
VALUE cClient;
VALUE cStatus;
VALUE cPort;
VALUE cBuffer;

#endif
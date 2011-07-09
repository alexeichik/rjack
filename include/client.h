#ifndef CLIENT_INCLUDED
#define CLIENT_INCLUDED

#include "rjack.h"

typedef struct {
    void* r_client_ptr;
    jack_nframes_t nframes;
} RJack_Client_Process_Struct;

VALUE RJack_Client_name(VALUE self);
VALUE proc(RJack_Client_Process_Struct* cps);
int RJack_Client_process(jack_nframes_t nframes, void *r_client_ptr);
VALUE RJack_Client_on_process(VALUE self);
void RJack_Client_shutdown(void *block);
VALUE RJack_Client_on_shutdown(VALUE self);
VALUE RJack_Client_register_port(VALUE self, VALUE port_name);
VALUE RJack_Client_activate(VALUE self);
VALUE RJack_Client_ports(VALUE self);
VALUE RJack_Client_connect_ports(VALUE self, VALUE source_port, VALUE destination_port);
VALUE RJack_Client_close(VALUE self);

#endif
#include "client.h"

VALUE RJack_Client_name(VALUE self) {
    jack_client_t *client;
    Data_Get_Struct(self, jack_client_t, client);
    return rb_str_new2(jack_get_client_name(client));
}

VALUE proc(RJack_Client_Process_Struct* cps) {
    VALUE r_client =  *((VALUE*) cps->r_client_ptr);
    VALUE block = rb_iv_get(r_client, "@process_callback");
    rb_funcall(block, rb_intern("call"), 1, INT2FIX(cps->nframes));
    return Qnil;
}

int RJack_Client_process(jack_nframes_t nframes, void *r_client_ptr) {
    RJack_Client_Process_Struct* cps = ALLOC(RJack_Client_Process_Struct);
    cps->r_client_ptr = r_client_ptr;
    cps->nframes = nframes;
    VALUE thread = rb_thread_create(proc, cps);
    return 0;
}

VALUE RJack_Client_on_process(VALUE self) {
    rb_need_block();
    VALUE* self_ptr = ALLOC(VALUE);
    *self_ptr = self;
    rb_global_variable(self_ptr);
    jack_client_t *client;
    Data_Get_Struct(self, jack_client_t, client);
    VALUE block = rb_block_proc();
    rb_iv_set(self, "@process_callback", block);
    jack_set_process_callback(client, RJack_Client_process, self_ptr);
    return self;
}

void RJack_Client_shutdown(void *block) {
    VALUE *r_block = (VALUE*) block;
    rb_funcall(*r_block, rb_intern("call"), 0);
}

VALUE RJack_Client_on_shutdown(VALUE self) {
    jack_client_t *client;
    Data_Get_Struct(self, jack_client_t, client);
    rb_need_block();
    VALUE block = rb_block_proc();
    rb_global_variable(&block);
    jack_on_shutdown (client, RJack_Client_shutdown, &block);
    return self;
}

VALUE RJack_Client_register_port(VALUE self, VALUE port_name) {
    char* converted_port_name = RSTRING_PTR(port_name);
    jack_client_t *client;
    Data_Get_Struct(self, jack_client_t, client);
    jack_port_t *port = jack_port_register(client, converted_port_name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    VALUE wrapped_port = port == NULL ? Qnil : Data_Wrap_Struct(cPort, 0, NULL, port);
    return wrapped_port;
}

VALUE RJack_Client_activate(VALUE self) {
    jack_client_t *client;
    Data_Get_Struct(self, jack_client_t, client);
    if (jack_activate(client)) return Qfalse;
    else return self;
}

VALUE RJack_Client_ports(VALUE self) {
    jack_client_t *client;
    Data_Get_Struct(self, jack_client_t, client);
    char** ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
    VALUE result = rb_ary_new2(2);
    if (ports == NULL) return result;
    rb_ary_push(result, Data_Wrap_Struct(cPort, 0, NULL, jack_port_by_name(client, ports[0])));
    rb_ary_push(result, Data_Wrap_Struct(cPort, 0, NULL, jack_port_by_name(client, ports[1])));
    return result;
}

VALUE RJack_Client_connect_ports(VALUE self, VALUE source_port, VALUE destination_port) {
    jack_client_t *client;
    Data_Get_Struct(self, jack_client_t, client);
    jack_port_t* raw_source_port;
    jack_port_t* raw_destination_port;
    Data_Get_Struct(source_port, jack_port_t, raw_source_port);
    Data_Get_Struct(destination_port, jack_port_t, raw_destination_port);
    printf(jack_port_name(raw_source_port));
    printf(jack_port_name(raw_destination_port));
    if (jack_connect(client, jack_port_name(raw_source_port), jack_port_name(raw_destination_port))) {
		return Qfalse;
	}
	return self;
}

VALUE RJack_Client_close(VALUE self) {
    jack_client_t *client;
    Data_Get_Struct(self, jack_client_t, client);
    jack_client_close(client);
    return self;
}
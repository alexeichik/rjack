#include "rjack.h"

VALUE RJack_client_open(int argc, VALUE *argv, VALUE obj) {
    VALUE client_name, options, server_name;
    jack_options_t converted_options = JackNullOption;
    jack_status_t* status = ALLOC(jack_status_t);
    rb_scan_args(argc, argv, "12", &client_name, &options, &server_name);
    char* converted_client_name = RSTRING_PTR(client_name);
    char* converted_server_name = NULL;
    if (NIL_P(options)) {
        converted_options = JackNullOption;
    }
    else {
//        converted_options = (jack_options_t) FIX2INT(options); WRONG
    }
    if (!NIL_P(server_name)) {
        converted_server_name = RSTRING_PTR(server_name);
    }
    jack_client_t *client = jack_client_open(converted_client_name, converted_options, status, converted_server_name);
    VALUE result = rb_ary_new2(2);
    VALUE wrapped_client = client == NULL ? Qnil : Data_Wrap_Struct(cClient, 0, NULL, client);
    rb_ary_push(result, wrapped_client);
    rb_ary_push(result, Data_Wrap_Struct(cStatus, 0, NULL, status));
    return result;
}

void Init_rjack() {
    mRJack = rb_define_module("RJack");
    rb_define_module_function(mRJack, "client_open", RJack_client_open, -1);
    rb_extend_object(mRJack, mRJack);
    rb_require("pavel/rjack_ext");
    VALUE mRJackExt = rb_const_get(rb_cObject, rb_intern("RJackExt"));
    rb_extend_object(mRJack, mRJackExt);

    cClient = rb_define_class_under(mRJack, "Client", rb_cObject);
    rb_define_method(cClient, "name", RJack_Client_name, 0);
    rb_define_method(cClient, "on_process", RJack_Client_on_process, 0);
    rb_define_method(cClient, "on_shutdown", RJack_Client_on_shutdown, 0);
    rb_define_method(cClient, "register_port", RJack_Client_register_port, 1);
    rb_define_method(cClient, "activate", RJack_Client_activate, 0);
    rb_define_method(cClient, "ports", RJack_Client_ports, 0);
    rb_define_method(cClient, "connect_ports", RJack_Client_connect_ports, 2);
    rb_define_method(cClient, "close", RJack_Client_close, 0);

    cStatus = rb_define_class_under(mRJack, "Status", rb_cObject);
    rb_define_method(cStatus, "to_s", RJack_Status_to_s, 0);
    rb_define_method(cStatus, "name_not_unique?", RJack_Status_name_not_unique_p, 0);

    cPort = rb_define_class_under(mRJack, "Port", rb_cObject);
    rb_define_method(cPort, "name", RJack_Port_name, 0);
    rb_define_method(cPort, "free", RJack_Port_free, 0);
    rb_define_method(cPort, "get_buffer", RJack_Port_get_buffer, 1);

    cBuffer = rb_define_class_under(mRJack, "Buffer", rb_cObject);
    rb_define_method(cBuffer, "[]=", RJack_Buffer_set_at, 2);
}
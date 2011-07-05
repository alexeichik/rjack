#include "ruby.h"
#include <jack/jack.h>


VALUE mRJack;
VALUE cClient;
VALUE cStatus;

VALUE RJack_testing() {
   printf("testing succeed");
   return Qnil;
}

VALUE RJack_client_open(int argc, VALUE* argv, VALUE self) {
    printf("RJack_client_open()");
    VALUE client_name, options, server_name;
    jack_options_t converted_options = JackNullOption;
    char* converted_client_name = RSTRING_PTR(client_name);
    char* converted_server_name = NULL;
    jack_status_t* status = ALLOC(jack_status_t);
    rb_scan_args(argc, argv, "12", &client_name, &options, &server_name);
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
    rb_ary_push(result, Data_Wrap_Struct(cClient, 0, NULL, client));
    rb_ary_push(result, Data_Wrap_Struct(cClient, 0, NULL, status));
    return result;
}

//void initialize_simple_client() {
//    printf("initialize_simple_client");
//    VALUE mSC = rb_define_module("SC");
//    rb_define_method(mSC, "main", SC_main, 0);
//}

void Init_rjack() {
    printf("Init_rjack()");
    mRJack = rb_define_module("RJack");
    rb_define_method(mRJack, "testing", RJack_testing, 0);
    rb_define_method(mRJack, "client_open", RJack_client_open, -2);
    rb_extend_object(mRJack, mRJack);
    rb_require("pavel/rjack_ext");
    VALUE mRJackExt = rb_const_get(rb_cObject, rb_intern("RJackExt"));
    rb_extend_object(mRJack, mRJackExt);

    cClient = rb_define_class_under(mRJack, "Client", rb_cObject);
    cStatus = rb_define_class_under(mRJack, "Status", rb_cObject);

//    initialize_simple_client();
}

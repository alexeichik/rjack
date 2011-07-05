#include "ruby.h"
#include "stdio.h"
#include <jack/jack.h>


VALUE mRJack;
VALUE cClient;
VALUE cStatus;

VALUE RJack_testing() {
   printf("testing succeed");
   return Qnil;
}

static VALUE RJack_client_open(int argc, VALUE *argv, VALUE obj) {
    printf("RJack_client_open\n");
    VALUE client_name, options, server_name;
    jack_options_t converted_options = JackNullOption;
    jack_status_t* status = ALLOC(jack_status_t);
    rb_scan_args(argc, argv, "12", &client_name, &options, &server_name);
    char* converted_client_name = RSTRING_PTR(client_name);
    char* converted_server_name = NULL;
    if (NIL_P(options)) {
        printf("use JackNullOption\n");
        converted_options = JackNullOption;
    }
    else {
        printf("not implemented\n");
//        converted_options = (jack_options_t) FIX2INT(options); WRONG
    }
    if (!NIL_P(server_name)) {
        printf("using non default server name");
        converted_server_name = RSTRING_PTR(server_name);
    }
    printf("converted_client_name = %s\n", converted_client_name);
    jack_client_t *client = jack_client_open(converted_client_name, converted_options, status, converted_server_name);
    VALUE result = rb_ary_new2(2);
    VALUE wrapped_client = client == NULL ? Qnil : Data_Wrap_Struct(cClient, 0, NULL, client);
    rb_ary_push(result, wrapped_client);
    rb_ary_push(result, Data_Wrap_Struct(cStatus, 0, NULL, status));
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    return result;
}

//void initialize_simple_client() {
//    printf("initialize_simple_client");
//    VALUE mSC = rb_define_module("SC");
//    rb_define_method(mSC, "main", SC_main, 0);
//}

VALUE RJack_Status_to_s(VALUE self) {
    jack_status_t* status;
    char str[100];
    str[0] = 0;
    strcat(str, "RJack::Status<");
    Data_Get_Struct(self, jack_status_t, status);
    if (*status & JackFailure)       strcat(str, "JackFailure");
    if (*status & JackNameNotUnique) strcat(str, "JackNameNotUnique");
    if (*status & JackServerStarted) strcat(str, "JackServerStarted");
    if (*status & JackServerFailed)  strcat(str, "JackServerFailed");
    if (*status & JackNoSuchClient)  strcat(str, "JackNoSuchClient");
    if (*status & JackLoadFailure)   strcat(str, "JackLoadFailure");
    if (*status & JackInitFailure)   strcat(str, "JackInitFailure");
    if (*status & JackShmFailure)    strcat(str, "JackShmFailure");
    if (*status & JackVersionError)  strcat(str, "JackVersionError");
    if (*status & JackBackendError)  strcat(str, "JackBackendError");
    if (*status & JackClientZombie)  strcat(str, "JackClientZombie");
    strcat(str, ">");
    return rb_str_new2(str);
}

void Init_rjack() {
    printf("Init_rjack()");

    mRJack = rb_define_module("RJack");
    rb_define_method(mRJack, "testing", RJack_testing, 0);
    rb_define_module_function(mRJack, "client_open", RJack_client_open, -1);
    rb_extend_object(mRJack, mRJack);
    rb_require("pavel/rjack_ext");
    VALUE mRJackExt = rb_const_get(rb_cObject, rb_intern("RJackExt"));
    rb_extend_object(mRJack, mRJackExt);

    cClient = rb_define_class_under(mRJack, "Client", rb_cObject);


    cStatus = rb_define_class_under(mRJack, "Status", rb_cObject);
    rb_define_method(cStatus, "to_s", RJack_Status_to_s, 0);



//    initialize_simple_client();
}

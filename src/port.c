#include "rjack.h"

VALUE RJack_Port_free(VALUE self) {
    jack_port_t* raw_port;
    Data_Get_Struct(self, jack_port_t, raw_port);
    free(raw_port);
    return self;
}

VALUE RJack_Port_name(VALUE self) {
    jack_port_t* raw_port;
    Data_Get_Struct(self, jack_port_t, raw_port);
    return rb_str_new2(jack_port_name(raw_port));
}

VALUE RJack_Port_get_buffer(VALUE self, VALUE nframes) {
    jack_port_t* raw_port;
    Data_Get_Struct(self, jack_port_t, raw_port);
    jack_default_audio_sample_t* buffer = (jack_default_audio_sample_t*)jack_port_get_buffer(raw_port, FIX2INT(nframes));
    return Data_Wrap_Struct(cBuffer, 0, NULL, buffer);
}

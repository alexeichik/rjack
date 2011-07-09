#include "rjack.h"

VALUE RJack_Buffer_set_at(VALUE self, VALUE index, VALUE value) {
    jack_default_audio_sample_t* raw_buffer;
    Data_Get_Struct(self, jack_default_audio_sample_t, raw_buffer);
    raw_buffer[FIX2INT(index)] = (float)NUM2DBL(value);
    return value;
}
#include "status.h"

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

VALUE RJack_Status_name_not_unique_p(VALUE self) {
    jack_status_t* status;
    Data_Get_Struct(self, jack_status_t, status);
    if (*status & JackNameNotUnique) return Qtrue;
    return Qfalse;
}
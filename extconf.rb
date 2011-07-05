require 'mkmf'

#$configure_args["--with-cflags"] = `pkg-config --cflags --libs jack`

$configure_args["--with-jack-lib"] = "/usr/local/lib/jack"
dir_config("jack")
have_library("jack")

create_makefile "pavel/rjack"

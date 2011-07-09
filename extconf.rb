require 'mkmf'

#$configure_args["--with-cflags"] = `pkg-config --cflags --libs jack`

$configure_args["--with-rjack-include"] = File.expand_path("../include", __FILE__)
have_header("rjack")

$configure_args["--with-jack-lib"] = "/usr/local/lib/jack"
have_library("jack")

create_makefile "pavel/rjack", "src"

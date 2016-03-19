
CFLAGS+=-O
CFLAGS+=-Wall -Werror
#CFLAGS+=-Wno-unused-function

LDFLAGS+=-lm

.PHONY: all clean world

all:: http_server 

http_server: http_server.o wrapper.o in_out.o serv.o http.o
	$(LINK.c) -o $@ $^

clean::
	rm -f *.o http_server

world:: clean all

in_out.c:: in_out.h
wrapper.c:: wrapper.h

http_server.o:: http_server.c serv.h wrapper.h in_out.h
serv.c:: serv.h wrapper.h http.h
http.c:: http.h

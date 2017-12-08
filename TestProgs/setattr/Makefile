CC=gcc
CFLAGS=-I. -g -Wall
DEPS = NULL

%.0: %/c $(DEPS)
	$(CC) -c -0 $@ $< $(CFLAGS)

setattr: setattr.o
	gcc -o setattr setattr.o -I.

CC=gcc
CFLAGS=-I. -g -Wall
DEPS = NULL

%.0: %/c $(DEPS)
	$(CC) -c -0 $@ $< $(CFLAGS)

listattr: listattr.o
	gcc -o listattr listattr.o -I.

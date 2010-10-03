## Copyright Michael Banack 2010

CC=gcc
CFLAGS=-std=gnu99 -Wall -O3 -fomit-frame-pointer -m32

OBJECTS=priv.o env.o

all: suwrap

suwrap: suwrap.c ${OBJECTS}
	${CC} ${CFLAGS} suwrap.c ${OBJECTS} -o suwrap

priv.o: priv.c priv.h

env.o: env.c env.h

clean:
	rm -f suwrap *.o

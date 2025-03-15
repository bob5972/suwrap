# Makefile -- Part of suwrap
#
# Copyright (c) 2010-2020 Michael Banack <github@banack.net>
#
# MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

CC=gcc
CFLAGS=-std=gnu99 -Wall -O2 -fomit-frame-pointer
#CFLAGS:=${CFLAGS} -m32

OBJECTS=priv.o env.o

all: suwrap

suwrap: suwrap.c ${OBJECTS}
	${CC} ${CFLAGS} suwrap.c ${OBJECTS} -o suwrap

priv.o: priv.c priv.h

env.o: env.c env.h

clean:
	rm -f suwrap *.o

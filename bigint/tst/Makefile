#
# Makefile for big integer test
#

BUILD = ../build

CC = gcc
CFLAGS = -g -Wall -I$(BUILD)/include
LDFLAGS = -g -Wall -L$(BUILD)/lib
LDLIBS = -lbigint

all:		testbip

install:	all
		mkdir -p $(BUILD)/bin
		cp testbip $(BUILD)/bin

testbip:	testbip.o support.o
		$(CC) $(LDFLAGS) -o testbip testbip.o support.o $(LDLIBS)

testbip.o:	testbip.c
		$(CC) $(CFLAGS) -o testbip.o -c testbip.c

support.o:	support.c
		$(CC) $(CFLAGS) -o support.o -c support.c

clean:
		rm -f *~ testbip.o support.o testbip

#
# Makefile for big integer library
#

BUILD = ../build

CC = gcc
CFLAGS = -g -Wall

all:		support.h bigint.h libbigint.a

install:	all
		mkdir -p $(BUILD)/include
		cp support.h $(BUILD)/include
		cp bigint.h $(BUILD)/include
		mkdir -p $(BUILD)/lib
		cp libbigint.a $(BUILD)/lib

libbigint.a:	bigint.o
		ar -crs libbigint.a bigint.o

bigint.o:	bigint.c bigint.h support.h
		$(CC) $(CFLAGS) -o bigint.o -c bigint.c

clean:
		rm -f *~ bigint.o libbigint.a

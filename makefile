include Makefile_ext
CC = gcc
CFLAGS = -g -Wall -pedantic
INCLUDES = types.h vertex.h bstree.h
EXE = p4_e1



all: $(EXE)

p4_e1: p4_e1.o bstree.o vertex.o
	$(CC) -o $@ $^ $(CFLAGS)

p4_e1.o: p4_e1.c $(INCLUDES)
	$(CC) -c $< bstree.c vertex.c $(CFLAGS)
	
clean: 
	rm -rf *.o $(EXE)
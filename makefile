CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -L./
LDLIBS = -lstack 
OBJ = vertex.c graph.c 
INCLUDE = vertex.h graph.h types.h

p2_e1a = p2_e1a.o 
p2_e1b = p2_e1b.o vertex.o

all: p2_e1a p2_e1b

p2_e1a: $(p2_e1a)
	$(CC) $(CFLAGS) -o p2_e1a $(p2_e1a) $(LDFLAGS) $(LDLIBS)
p2_e1b: $(p2_e1b)
	$(CC) $(CFLAGS) -o p2_e1b $(p2_e1b) $(LDFLAGS) $(LDLIBS)
p2_e1a.o: p2_e1a.c types.h 
	$(CC) $(CFLAGS) -c p2_e1a.c 
p2_e1b.o: p2_e1b.c vertex.c vertex.h
	$(CC) $(CFLAGS) -c p2_e1b.c vertex.c 

pruebastack: pruebastack.o 
	$(CC) $(CFLAGS) -o pruebastack pruebastack.o stack.o 

pruebastack.o: stack.c stack.h types.h
	$(CC) $(CFLAGS) -c pruebastack.c stack.c
run:
	./p2_e1a grades1.txt grades2.txt 
	./p2_e1b cities1.txt cities2.txt
runv:
	valgrind --leak-check=full ./p2_e1a grades1.txt grades2.txt 
	valgrind --leak-check=full ./p2_e1b cities1.txt cities2.txt
clean:
	rm -rf *.o p2_e1a p2_e1b
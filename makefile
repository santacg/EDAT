CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -L./
LDLIBS = -lstack 
OBJ = vertex.c graph.c 
INCLUDE = vertex.h graph.h types.h

p2_e1a = p2_e1a.o 
p2_e1b = p2_e1b.o vertex.o
p2_e2 = p2_e2.o vertex.o graph.o

all: p2_e1a p2_e1b p2_e2

p2_e1a: $(p2_e1a)
	$(CC) $(CFLAGS) -o p2_e1a $(p2_e1a) $(LDFLAGS) $(LDLIBS)
p2_e1b: $(p2_e1b)
	$(CC) $(CFLAGS) -o p2_e1b $(p2_e1b) $(LDFLAGS) $(LDLIBS)
p2_e2: $(p2_e2)
	$(CC) $(CFLAGS) -o p2_e2 $(p2_e2) $(LDFLAGS) $(LDLIBS)
p2_e1a.o: p2_e1a.c types.h 
	$(CC) $(CFLAGS) -c p2_e1a.c 
p2_e1b.o: p2_e1b.c vertex.c vertex.h
	$(CC) $(CFLAGS) -c p2_e1b.c vertex.c
p2_e2.o: p2_e2.c vertex.c vertex.h graph.c graph.h
	$(CC) $(CFLAGS) -c p2_e2.c vertex.c graph.c



pruebastack: pruebastack.o 
	$(CC) $(CFLAGS) -o pruebastack pruebastack.o stack.o 

pruebastack.o: stack.c stack.h types.h
	$(CC) $(CFLAGS) -c pruebastack.c stack.c
run:
	./p2_e1a grades1.txt grades2.txt 
	./p2_e1b cities1.txt cities2.txt
	./p2_e2 g2.txt 100 700
runv:
	valgrind --leak-check=full ./p2_e1a grades1.txt grades2.txt 
	valgrind --leak-check=full ./p2_e1b cities1.txt cities2.txt
	valgrind --leak-check=full ./p2_e2 g2.txt 100 700
clean:
	rm -rf *.o p2_e1a p2_e1b p2_e2
CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -L./
LDLIBS = -lstack


p2_e1a = p2_e1a.o

all: p2_e1a

p2_e1a: $(p2_e1a)
	$(CC) $(CFLAGS) -o p2_e1a $(p2_e1a) $(LDFLAGS) $(LDLIBS)
p2_e1a.o: p2_e1a.c types.h 
	$(CC) $(CFLAGS) -c p2_e1a.c
clean:
	rm -rf *.o p2_e1a
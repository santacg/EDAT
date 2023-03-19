CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -L./
LDLIBS = -lstack   
INCLUDES = types.h stack.h file_utils.h 
EXE = p2_e1a p2_e1b p2_e2 p2_e1a_fdoble p2_e1b_fdoble p2_e2_fdoble

p2_e1a = p2_e1a.o 
p2_e1b = vertex.o
p2_e2 = vertex.o graph.o

p2_e1a_fdoble = stack.o files_utils.o
p2_e1b_fdoble = vertex.o stack.o files_utils.o
p2_e2_fdoble = vertex.o graph.o stack.o files_utils.o

all: $(EXE)

#ejecucion con la pila suministrada
p2_e1a: p2_e1a.o 
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(CFLAGS)
p2_e1b: p2_e1b.o $(p2_e1b)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(CFLAGS)
p2_e2: p2_e2.o $(p2_e2)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(CFLAGS)

p2_e1a.o: p2_e1a.c types.h 
	$(CC) -c $< $(CFLAGS)
p2_e1b.o: p2_e1b.c vertex.h types.h
	$(CC) -c $< vertex.c $(CFLAGS)
p2_e2.o: p2_e2.c vertex.h graph.h types.h
	$(CC) -c $< vertex.c graph.c $(CFLAGS)

#ejecución con la pila implementada del ejercicio 3
p2_e2_fdoble: p2_e2.o $(p2_e2_fdoble)
	$(CC) -o $@ $^ $(CFLAGS)
p2_e1b_fdoble: p2_e1b.o $(p2_e1b_fdoble)
	$(CC) -o $@ $^ $(CFLAGS)
p2_e1a_fdoble: p2_e1a.o $(p2_e1a_fdoble)
	$(CC) -o $@ $^ $(CFLAGS)

p2_e2_fdoble.o: p2_e2.c vertex.h graph.h $(INCLUDES)
	$(CC) -c $< vertex.c graph.c files_utils.c stack.c $(CFLAGS)
p2_e1b_fdoble.o: p2_e1b.c vertex.h $(INCLUDES)
	$(CC) -c $< vertex.c stack.c files_utils.c $(CFLAGS)
p2_e1a_fdoble.o: p2_e1a.c $(INCLUDES)
	$(CC) -c $< stack.c files_utils.c $(CFLAGS)


run:
	./p2_e1a grades1.txt grades2.txt 
	./p2_e1b cities1.txt cities2.txt
	./p2_e2 g2.txt 100 700
run_fdoble:
	./p2_e1a_fdoble grades1.txt grades2.txt 
	./p2_e1b_fdoble cities1.txt cities2.txt
	./p2_e2_fdoble g2.txt 100 700

runv:
	valgrind --leak-check=full ./p2_e1a grades1.txt grades2.txt 
	valgrind --leak-check=full ./p2_e1b cities1.txt cities2.txt
	valgrind --leak-check=full ./p2_e2 g2.txt 100 700
runv_fdoble:
	valgrind --leak-check=full ./p2_e1a_fdoble grades1.txt grades2.txt 
	valgrind --leak-check=full ./p2_e1b_fdoble cities1.txt cities2.txt
	valgrind --leak-check=full ./p2_e2_fdoble g2.txt 100 700

clean:
	rm -rf *.o $(EXE)
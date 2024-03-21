#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAX_CHAR 256

int main(int argc, char const **argv)
{
    FILE *f = NULL;
    Graph *graph = NULL;

    if( argc != 2) return EXIT_FAILURE;
	
    graph = graph_init();
    if (!graph) return EXIT_FAILURE;
    
    f = fopen(argv[1], "r");

    if (graph_readFromFile(f, graph) == ERROR) return EXIT_FAILURE;

    if (!f) return EXIT_FAILURE;

    if (graph_print(stdout, graph) == -1) return EXIT_FAILURE;

    graph_free(graph);
    fclose(f);

    return EXIT_SUCCESS;
}

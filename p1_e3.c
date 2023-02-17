#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAX_CHAR 256

int main(int argc, char const **argv)
{
    FILE *f = NULL;
    Graph *graph = NULL;

    if( argc != 2) return 1;
	
    graph = graph_init();
    if (!graph) return 1;
    
    f = fopen(argv[1], "r");

    if (graph_readFromFile(f, graph) == ERROR) return 1;

    if (!f) return 1;

    if (graph_print(stdout, graph) == -1) return 1;

    graph_free(graph);
    fclose(f);

    return 0;
}

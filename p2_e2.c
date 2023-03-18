#include "stack.h"
#include "file_utils.h"
#include "vertex.h"
#include "graph.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    FILE *f = NULL;
    Graph *g = NULL;
    Vertex *v = NULL;
    long id_org = 0, id_dest = 0;

    if (argc != 4)
        return EXIT_FAILURE;

    f = fopen(argv[1], "r");
    if (!f)
        return EXIT_FAILURE;

    g = graph_init();
    if (!g)
    {
        fclose(f);
        return EXIT_FAILURE;
    }

    if (graph_readFromFile(f, g) == ERROR)
    {
        graph_free(g);
        fclose(f);
        return EXIT_FAILURE;
    }

    graph_print(stdout, g);

    id_org = atol(argv[2]);
    id_dest = atol(argv[3]);

    fprintf(stdout, "Output:\n");
    if (graph_depthSearch(g, id_org, id_dest) == ERROR)
    {
        graph_free(g);
        fclose(f);
        return EXIT_FAILURE;
    }

    graph_free(g);
    fclose(f);

    return EXIT_SUCCESS;
}
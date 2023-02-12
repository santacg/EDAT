#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAX_CHAR 256

int main () {
    Graph *g = NULL;
    int i = 0;
    char aux[MAX_CHAR] = "\0";
    int result = 0;
    long *array = NULL;
    g = graph_init();
    if (!g) return 1;

    strcpy(aux, "id:111 tag:MADRID state:WHITE");
    if (graph_newVertex(g, aux) == ERROR) return 1;
    fprintf(stdout, "Inserting MADRID... result...: 1\n");

    strcpy(aux, "id:222 tag:TOLEDO state:WHITE");
    if (graph_newVertex(g, aux) == ERROR) return 1;
    fprintf(stdout, "Inserting TOLEDO... result...: 1\n");

    if (graph_newEdge(g, 222, 111) == ERROR) return 1;
    fprintf(stdout, "Inserting edge: 222 --> 111\n");

    if (graph_connectionExists(g, 111, 222) == TRUE) return 1;
    fprintf(stdout, "111 --> 222? No\n");

    if (graph_connectionExists(g, 222, 111) == FALSE) return 1;
    fprintf(stdout, "222 --> 111? Yes\n");

    result = graph_getNumberOfConnectionsFromId(g, 111);
    fprintf(stdout, "Number of connections from 111: %d\n", result);

    result = graph_getNumberOfConnectionsFromTag(g, "TOLEDO");
    fprintf(stdout, "Number of connections from Toledo: %d\n", result);
    
    array = graph_getConnectionsFromTag(g, "TOLEDO");
    for (i = 0; i < 1; i++) {
        fprintf(stdout, "Connections from Toledo: %ld\n", array[i]);
    }

    return 0;
}
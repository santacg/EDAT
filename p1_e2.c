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
    if (graph_newVertex(g, aux) == OK) {
        result = 1;
    }
    else if (graph_newVertex(g, aux) == ERROR) {
        result = 0;
    }
    fprintf(stdout, "Inserting MADRID... result...: %d\n", result);

    strcpy(aux, "id:222 tag:TOLEDO state:WHITE");
    if (graph_newVertex(g, aux) == OK) {
        result = 1;
    }
    else if (graph_newVertex(g, aux) == ERROR) {
        result = 0;
    }
    fprintf(stdout, "Inserting TOLEDO... result...: %d\n", result);;

    if (graph_newEdge(g, 222, 111) == ERROR) {
        fprintf(stdout, "Error inserting edge");
        graph_free(g);   
        return 1;
    }
    fprintf(stdout, "Inserting edge: 222 --> 111\n");

    if (graph_connectionExists(g, 111, 222) == TRUE) {
        strcpy(aux, "Yes");
    }
    else if (graph_connectionExists(g, 111, 222) == FALSE) {
        strcpy(aux, "No");
    }
    fprintf(stdout, "111 --> 222? %s\n", aux);

    if (graph_connectionExists(g, 222, 111) == TRUE) {
        strcpy(aux, "Yes");
    }
    else if (graph_connectionExists(g, 222, 111) == FALSE) {
        strcpy(aux, "No");
    }
    fprintf(stdout, "222 --> 111? %s\n", aux);

    result = graph_getNumberOfConnectionsFromId(g, 111);
    fprintf(stdout, "Number of connections from 111: %d\n", result);

    result = graph_getNumberOfConnectionsFromTag(g, "TOLEDO");
    fprintf(stdout, "Number of connections from Toledo: %d\n", result);
    
    array = graph_getConnectionsFromTag(g, "TOLEDO");
    fprintf(stdout, "Connections from Toledo: ");
    for (i = 0; i < graph_getNumberOfConnectionsFromTag(g, "TOLEDO"); i++) {
        fprintf(stdout, "%ld ", array[i]);
    }

    fprintf(stdout, "\n");

    if (graph_print(stdout, g) == -1) {
        fprintf(stdout, "Error printing graph");
        graph_free(g);
        return 1;
    }

    free(array);
    graph_free(g);

    return 0;
}
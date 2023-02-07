#include <stdio.h>
#include "graph.h"

#define MAX_VTX 4096
struct _Graph {
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};

Graph * graph_init() {
    Graph * g = NULL;
    int i = 0, j = 0;

    g = (Graph *) malloc (sizeof(Graph));
    if (!g) return NULL;

    for (i = 0; i < MAX_VTX; i++) {
        g->vertices[i] = NULL;
    }

    for (i = 0; i < MAX_VTX; i++) {
        for (j = 0; j < MAX_VTX; j++) {
            g->connections[i][j] = FALSE;
        }
    }

    g->num_vertices = 0;
    g->num_edges = 0;

    return g;
}

/* Frees a graph */
void graph_free(Graph *g){
    int i = 0, j = 0;
    if (!g) return;

    for (i = 0; i < MAX_VTX; i++) {
        vertex_free(g->vertices[i]);
    }

    free(g);
}

/* Inserts a new vertex in a graph */
Status graph_newVertex(Graph *g, char *desc){
    
}

/* Creates an edge between to vertices of a graph */
Status graph_newEdge(Graph *g, long orig, long dest){
    
}

/* Checks if a graph contains a vertex */
Bool graph_contains(const Graph *g, long id){
    
}

/* eturns the total number of vertices in a graph */
int graph_getNumberOfVertices(const Graph *g){
    
}

/* Returns the total number of edges  * in the graph */
int graph_getNumberOfEdges(const Graph *g){
    
}

/* Determines if there is a connection between a pair of vertices */
Bool graph_connectionExists(const Graph *g, long orig, long dest){
    
}

/* Gets the number of connections starting at a given vertex */
int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
    
}

/* Returns an array with the ids of all the vertices which a given vertex connects to */
long *graph_getConnectionsFromId(const Graph *g, long id){
    
}

/* Gets the number of connections starting at a given vertex */
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){
    
}

/* Returns an array with the ids of all the vertices which a given vertex connects to */
long *graph_getConnectionsFromTag(const Graph *g, char *tag){
    
}

/* Prints a graph */
int graph_print (FILE *pf, const Graph *g){
    
}

/* Reads a graph definition from a text file */
Status graph_readFromFile (FILE *fin, Graph *g){
    
}

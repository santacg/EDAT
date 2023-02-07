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
    Vertex *v = NULL;
    int i = 0, cmp = 0;
    if (!g || !desc) return ERROR;

    v = vertex_initFromString(desc);
    if (!v) return ERROR;

    /* Graph contain*/
    for (i = 0; i < g->num_vertices; i++) {
        if (g->vertices[i] != NULL) {
            cmp = vertex_cmp(g->vertices[i], v);
            if (cmp == 0) {
                return ERROR;
            }   
        }
    }

    if (i < MAX_VTX) {
        g->vertices[i] == v;
        g->num_vertices++;
        return OK;
    }

    return ERROR;
}

/* Creates an edge between to vertices of a graph */
Status graph_newEdge(Graph *g, long orig, long dest){
    int i = 0, j = 0;
    Bool flag1 = FALSE, flag2 = FALSE;
    if (!g || orig < 0 || dest < 0) return ERROR;

    while (i < g->num_vertices && (vertex_getId(g->vertices[i]) != orig)) {
        if (vertex_getId(g->vertices[i]) == orig) {
            flag1 = TRUE;
            break;
        }
        i++;
    }

    while (j < g->num_vertices && (vertex_getId(g->vertices[j]) != dest)) {
        if (vertex_getId(g->vertices[j]) == dest) {
            flag2 = TRUE;
            break;
        }
        j++;
    }

    if (flag1 == FALSE || flag2 == FALSE) return ERROR;

    g->connections[i][j] = TRUE;
    g->num_edges++;

    return OK;
    
}

/* Checks if a graph contains a vertex */
Bool graph_contains(const Graph *g, long id) {
    int i = 0, cmp = 0;

    if(!g || id < 0) return FALSE;
    
    for (i = 0; i < g->num_vertices; i++) {
        if (g->vertices[i] != NULL) {
            if (vertex_getId(g->vertices[i]) == id) {
                return TRUE;
            } 
        }
    }
    
    return FALSE;
}

/* eturns the total number of vertices in a graph */
int graph_getNumberOfVertices(const Graph *g){
    if (!g) return -1;

    return g->num_vertices;
}

/* Returns the total number of edges  * in the graph */
int graph_getNumberOfEdges(const Graph *g){
    if (!g) return -1;

    return g->num_edges;
}

/* Determines if there is a connection between a pair of vertices */
Bool graph_connectionExists(const Graph *g, long orig, long dest){
    
    if (!g || orig < 0 || dest < 0) return FALSE;

    if (g->connections[orig][dest] == TRUE) {
        return TRUE;
    }

    return FALSE;
}

/* Gets the number of connections starting at a given vertex */
int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
    int i = 0, n = 0;
    
    if (!g || id < 0) return -1;

    for (i = 0; i < g->num_vertices; i++) {
        if (g->connections[id][i] == TRUE) {
            n++;
        }
    }

    return n;
}

/* Returns an array with the ids of all the vertices which a given vertex connects to */
long *graph_getConnectionsFromId(const Graph *g, long id){
    int i = 0, n_vertices = 0;
    long *array = NULL;
    
    if (!g || id < 0) return NULL;

    n_vertices = graph_getNumberOfConnectionsFromId(g, id);

    array = (long *) malloc (sizeof(long) * n_vertices);
    if (!array) return -1;

    for (i = 0; i < n_vertices; i++) {
        array[i] = vertex_getId(g->vertices[i]);
    }

    return array;

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

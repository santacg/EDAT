#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAX_VTX 4096
#define MAX_CHAR 256
#define LINE 1000

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
    int i = 0;
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
        g->vertices[i] = v;
        g->num_vertices++;
        return OK;
    }

    return ERROR;
}

/* Gets a vertex from the graph with a given id*/
Vertex *graph_getVertexFromId(const Graph *g, long id, int *pos) {
    int i = 0;
    long vertex_id = 0;

    if (!g || id < 0) return NULL;

    for (i = 0; i < g->num_vertices; i++) {
        vertex_id = vertex_getId(g->vertices[i]);
        if (id == vertex_id) {
            *pos = i;
            return g->vertices[i];
        }
    }

    return NULL;
}

/* Gets a vertex from the graph with a give tag */
Vertex *graph_getVertexFromTag(const Graph *g, char *tag, int *pos) {
    int i = 0;
    char aux[MAX_CHAR] = "\0";
    
    if (!g || !tag) return NULL;
    
    for (i = 0; i < g->num_vertices; i++) {
        strcpy(aux, vertex_getTag(g->vertices[i]));
        if (strcmp(aux, tag) == 0) {
            *pos = i;
            return g->vertices[i];
        }
    }

    return NULL;

}

/* Creates an edge between to vertices of a graph */
Status graph_newEdge(Graph *g, long orig, long dest){
    int pos0 = 0, pos1 = 0;
    
    if (!g || orig < 0 || dest < 0) return ERROR;

    if (graph_getVertexFromId(g, orig, &pos0) == NULL) return ERROR;

    if (graph_getVertexFromId(g, dest, &pos1) == NULL) return ERROR;
    
    if (g->connections[pos0][pos1] == TRUE) return ERROR;

    g->connections[pos0][pos1] = TRUE;
    g->num_edges++;

    return OK;
    
}

/* Checks if a graph contains a vertex */
Bool graph_contains(const Graph *g, long id) {
    int i = 0;

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
    if (!g) return O_ERROR;

    return g->num_vertices;
}

/* Returns the total number of edges  * in the graph */
int graph_getNumberOfEdges(const Graph *g){
    if (!g) return O_ERROR;

    return g->num_edges;
}

/* Determines if there is a connection between a pair of vertices */
Bool graph_connectionExists(const Graph *g, long orig, long dest){
    int pos0 = 0, pos1 = 0;
    if (!g || orig < 0 || dest < 0) return FALSE;

    if (graph_getVertexFromId(g, orig, &pos0) == NULL) return FALSE;
    if (graph_getVertexFromId(g, dest, &pos1) ==  NULL) return FALSE;

    if (g->connections[pos0][pos1] == TRUE) return TRUE;

    return FALSE;
}

/* Gets the number of connections starting at a given vertex */
int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
    int i = 0, pos = 0, n = 0;
    
    if (!g || id < 0) return O_ERROR;

    if (graph_getVertexFromId(g, id, &pos) == NULL) return O_ERROR;

    for (i = 0; i < g->num_vertices; i++) {
        if (g->connections[pos][i] == TRUE) {
            n++;
        }
    }
    return n;
}

/* Returns an array with the ids of all the vertices which a given vertex connects to */
long *graph_getConnectionsFromId(const Graph *g, long id){
    int i = 0, j = 0, n = 0, pos = 0;
    long id_dest = 0;
    long *array = NULL;
    
    if (!g || id < 0) return NULL;

    n = graph_getNumberOfConnectionsFromId(g, id);

    array = (long *) malloc (sizeof(long) * n);
    if (!array) {
        free(array);
        return NULL;
    }
    
    if (graph_getVertexFromId(g, id, &pos) == NULL) {
        free(array);
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++) {
        if (g->connections[pos][i] == TRUE) {
            id_dest = vertex_getId(g->vertices[i]);
            array[j] = id_dest;
            j++;
        }
    }

    return array;

}

/* Gets the number of connections starting at a given vertex */
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){
    int i = 0, pos = 0, n = 0;
    
    if (!g || !tag) return O_ERROR;

    if (graph_getVertexFromTag(g, tag, &pos) == NULL) return O_ERROR;

    for (i = 0; i < g->num_vertices; i++) {
        if (g->connections[pos][i] == TRUE) {
            n++;
        }
    }
    return n;
}

/* Returns an array with the ids of all the vertices which a given vertex connects to */
long *graph_getConnectionsFromTag(const Graph *g, char *tag){
    int i = 0, n = 0, j = 0, pos = 0;
    long id_dest = 0;
    long *array = NULL;
    
    if (!g || !tag) return NULL;

    n = graph_getNumberOfConnectionsFromTag(g, tag);
    array = (long *) malloc(sizeof(long) * n);
    if (!array) {
        free(array);
        return NULL;
    } 

    if (graph_getVertexFromTag(g, tag, &pos) == NULL) {
        free(array);
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++) {
        if (g->connections[pos][i] == TRUE) {
            id_dest = vertex_getId(g->vertices[i]);
            array[j] = id_dest;
            j++;
        }
    }

    return array;
         
}

/* Prints a graph */
int graph_print (FILE *pf, const Graph *g) {
    int i = 0, j = 0, pos = 0;
    long id = 0;
    long *array = NULL;
    int n = 0, n_connections = 0;
    if (!pf || !g) return O_ERROR;

    for (i = 0; i < g->num_vertices; i++) {
        vertex_print(pf, g->vertices[i]);
        fprintf(pf, ": ");
        n++;
        id = vertex_getId(g->vertices[i]);
        array = graph_getConnectionsFromId(g, id);
        n_connections = graph_getNumberOfConnectionsFromId(g, id);
        for (j = 0; j < n_connections; j++) {
            vertex_print(pf, graph_getVertexFromId(g, array[j], &pos));
            fprintf(pf, " ");
            n++;
        }
        fprintf(pf, "\n");
        free(array);
    }

    return n;
}

/* Reads a graph definition from a text file */
Status graph_readFromFile (FILE *fin, Graph *g) {
    int i = 0;
    int n = 0;
    char aux[MAX_CHAR];
    long id_orig = 0, id_dest = 0;

    if (!fin || !g) return ERROR;

    fscanf(fin, "%d", &n);

    while (fgets(aux, LINE, fin) && i < n+1) {
        if (strncmp("id", aux, 2) == 0) {
            graph_newVertex(g, aux);
        }
        i++;
    }

    while (fscanf(fin, "%ld %ld", &id_orig, &id_dest) != -1) {
        graph_newEdge(g, id_orig, id_dest);
    }

    return OK;
}




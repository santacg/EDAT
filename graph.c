#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "stack.h"

#define MAX_VTX 4096
#define MAX_CHAR 256
#define LINE 1000

struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};

/* START [Private_functions] */
int graph_findVertexByTag(const Graph *, char *tag);

/**
 * @brief Creates an edge between to vertices of a graph.
 *
 * If any of the two vertices does not exist in the graph the edge is
 * not created.
 *
 * @param g Pointer to the graph.
 * @param origIx index of the origin vertex.
 * @param destIx index of the destination vertex.
 *
 * @return OK if the edge could be added to the graph, ERROR otherwise.
 **/
Status graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx);

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @param g Pointer to the graph.
 * @param ix index of the origin vertex.
 *
 * @return Returns the total number of connections starting at
 * vertex with index ix, or -1 if there is any error.
 **/
int graph_getNumConnections(const Graph *g, int ix);

/**
 * @brief Returns an array with the ids of all the vertices which a
 * given vertex connects to.
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param ix index of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which
 * the vertex with index ix is connected, or NULL if there is any error.
 */
long *graph_getConnections(const Graph *g, int ix);

void graph_setVertexState(Graph *g, Label l);
/* END [Private_functions] */

Graph *graph_init()
{
    Graph *g = NULL;
    int i = 0, j = 0;

    g = (Graph *)malloc(sizeof(Graph));
    if (!g)
        return NULL;

    for (i = 0; i < MAX_VTX; i++)
    {
        g->vertices[i] = NULL;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        for (j = 0; j < MAX_VTX; j++)
        {
            g->connections[i][j] = FALSE;
        }
    }

    g->num_vertices = 0;
    g->num_edges = 0;

    return g;
}

/* Frees a graph */
void graph_free(Graph *g)
{
    int i = 0;
    if (!g)
        return;

    for (i = 0; i < g->num_vertices; i++)
    {
        vertex_free(g->vertices[i]);
    }

    free(g);
}

/* Inserts a new vertex in a graph */
Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *v = NULL;

    if (!g || !desc)
        return ERROR;

    v = vertex_initFromString(desc);
    if (!v)
        return ERROR;

    if (graph_contains(g, vertex_getId(v)) == TRUE)
    {
        vertex_free(v);
        return ERROR;
    }

    if (graph_isFull(g) == TRUE)
    {
        vertex_free(v);
        return ERROR;
    }

    g->vertices[g->num_vertices] = v;
    vertex_setIndex(v, g->num_vertices);
    g->num_vertices++;

    return OK;
}

/* Returns TRUE if the graph is full, FALSE if not. */
Bool graph_isFull(const Graph *g)
{
    if (!g)
        return TRUE;

    if (g->num_vertices >= MAX_VTX)
    {
        return TRUE;
    }

    return FALSE;
}

/* Gets a vertex from the graph with a given id*/
Vertex *graph_getVertexFromId(const Graph *g, long id)
{
    int i = 0;
    long vertex_id = 0;

    if (!g || id < 0)
        return NULL;

    for (i = 0; i < g->num_vertices; i++)
    {
        vertex_id = vertex_getId(g->vertices[i]);
        if (id == vertex_id)
        {
            return g->vertices[i];
        }
    }

    return NULL;
}

/* Gets a vertex from the graph with a given tag */
Vertex *graph_getVertexFromTag(const Graph *g, char *tag)
{
    int i = 0;

    if (!g || !tag)
        return NULL;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(tag, vertex_getTag(g->vertices[i])) == 0)
        {
            return g->vertices[i];
        }
    }

    return NULL;
}

/* Gets a vertex from the graph with a given index */
Vertex *graph_getVertexFromIndex(const Graph *g, int ix)
{

    if (!g || ix < 0 || ix > MAX_VTX)
        return NULL;

    return g->vertices[ix];
}

/* Creates an edge between to vertices of a graph */
Status graph_newEdge(Graph *g, long orig, long dest)
{
    int pos0 = 0, pos1 = 0;

    if (!g || orig < 0 || dest < 0)
        return ERROR;

    pos0 = vertex_getIndex(graph_getVertexFromId(g, orig));
    pos1 = vertex_getIndex(graph_getVertexFromId(g, dest));

    if ((pos0 == RET_ERROR) || (pos1 == RET_ERROR))
        return ERROR;

    if (graph_connectionExists(g, orig, dest) == TRUE)
        return ERROR;

    g->connections[pos0][pos1] = TRUE;
    g->num_edges++;

    return OK;
}

Status graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx)
{

    if (!g || origIx < 0 || destIx < 0)
        return ERROR;

    if (graph_connectionExists(g, origIx, destIx) == TRUE)
        return ERROR;

    if (graph_contains(g, origIx) == FALSE || graph_contains(g, destIx) == FALSE)
        return ERROR;

    g->connections[origIx][destIx] = TRUE;
    return OK;
}

/* Checks if a graph contains a vertex */
Bool graph_contains(const Graph *g, long id)
{

    if (!g || id < 0)
        return FALSE;

    if (!graph_getVertexFromId(g, id))
        return FALSE;

    return TRUE;
}

/* Returns the total number of vertices in a graph */
int graph_getNumberOfVertices(const Graph *g)
{
    if (!g)
        return RET_ERROR;

    return g->num_vertices;
}

/* Returns the total number of edges  * in the graph */
int graph_getNumberOfEdges(const Graph *g)
{
    if (!g)
        return RET_ERROR;

    return g->num_edges;
}

/* Determines if there is a connection between a pair of vertices */
Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    int pos0 = 0, pos1 = 0;
    if (!g || orig < 0 || dest < 0)
        return FALSE;

    pos0 = vertex_getIndex(graph_getVertexFromId(g, orig));
    pos1 = vertex_getIndex(graph_getVertexFromId(g, dest));

    if ((pos0 == RET_ERROR) || (pos1 == RET_ERROR))
        return ERROR;

    if (g->connections[pos0][pos1] == TRUE)
        return TRUE;

    return FALSE;
}

/* Gets the number of connections starting at a given vertex */
int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int i = 0, pos = 0, n = 0;

    if (!g || id < 0)
        return RET_ERROR;

    pos = vertex_getIndex(graph_getVertexFromId(g, id));

    if (graph_contains(g, id) == FALSE)
        return RET_ERROR;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos][i] == TRUE)
        {
            n++;
        }
    }
    return n;
}

/* Returns an array with the ids of all the vertices which a given vertex connects to */
long *graph_getConnectionsFromId(const Graph *g, long id)
{
    int i = 0, j = 0, n = 0, pos = 0;
    long id_array = 0;
    long *array = NULL;

    if (!g || id < 0)
        return NULL;

    n = graph_getNumberOfConnectionsFromId(g, id);

    array = (long *)malloc(sizeof(long) * n);
    if (!array)
        return NULL;

    pos = vertex_getIndex(graph_getVertexFromId(g, id));
    if (pos == RET_ERROR)
    {
        free(array);
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos][i] == TRUE)
        {
            id_array = vertex_getId(g->vertices[i]);
            array[j] = id_array;
            j++;
        }
    }

    return array;
}

/* Gets the number of connections starting at a given vertex */
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int i = 0, pos = 0, n = 0;

    if (!g || !tag)
        return RET_ERROR;

    pos = vertex_getIndex(graph_getVertexFromTag(g, tag));
    if (pos == RET_ERROR)
        return RET_ERROR;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos][i] == TRUE)
        {
            n++;
        }
    }
    return n;
}

/* Returns an array with the ids of all the vertices which a given vertex connects to */
long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int i = 0, n = 0, j = 0, pos = 0;
    long id_dest = 0;
    long *array = NULL;

    if (!g || !tag)
        return NULL;

    n = graph_getNumberOfConnectionsFromTag(g, tag);
    array = (long *)malloc(sizeof(long) * n);
    if (!array)
        return NULL;

    pos = vertex_getIndex(graph_getVertexFromTag(g, tag));
    if (pos == RET_ERROR)
    {
        free(array);
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[pos][i] == TRUE)
        {
            id_dest = vertex_getId(g->vertices[i]);
            array[j] = id_dest;
            j++;
        }
    }

    return array;
}

/* Gets the number of connections starting at a given vertex */
int graph_getNumConnections(const Graph *g, int ix)
{
    int i = 0, n = 0;

    if (!g || ix < 0)
        return RET_ERROR;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[ix][i] == TRUE)
        {
            n++;
        }
    }
    return n;
}

/* Returns an array with the ids of all the vertices which a given vertex connects to */
long *graph_getConnections(const Graph *g, int ix)
{
    int i = 0, j = 0, n = 0;
    long id_array = 0;
    long *array = NULL;

    if (!g || ix < 0)
        return NULL;

    n = graph_getNumConnections(g, ix);

    array = (long *)malloc(sizeof(long) * n);
    if (!array)
        return NULL;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[ix][i] == TRUE)
        {
            id_array = vertex_getId(g->vertices[i]);
            array[j] = id_array;
            j++;
        }
    }

    return array;
}

/* Prints a graph */
int graph_print(FILE *pf, const Graph *g)
{
    int i = 0, j = 0;
    long id = 0;
    long *array = NULL;
    int n = 0, n_connections = 0;
    if (!pf || !g)
        return RET_ERROR;

    for (i = 0; i < g->num_vertices; i++)
    {
        vertex_print(pf, g->vertices[i]);
        n++;
        fprintf(pf, ": ");
        id = vertex_getId(g->vertices[i]);
        array = graph_getConnectionsFromId(g, id);
        n_connections = graph_getNumberOfConnectionsFromId(g, id);
        for (j = 0; j < n_connections; j++)
        {
            vertex_print(pf, graph_getVertexFromId(g, array[j]));
            n++;
            fprintf(pf, " ");
        }
        fprintf(pf, "\n");
        free(array);
    }

    return n;
}

/* Reads a graph definition from a text file */
Status graph_readFromFile(FILE *fin, Graph *g)
{
    int i = 0;
    int n = 0;
    char aux[MAX_CHAR];
    long id_orig = 0, id_dest = 0;

    if (!fin || !g)
        return ERROR;

    fscanf(fin, "%d", &n);

    while (i < n + 1)
    {
        fgets(aux, LINE, fin);
        if (strncmp("id", aux, 2) == 0)
        {
            graph_newVertex(g, aux);
        }
        i++;
    }

    while (fscanf(fin, "%ld %ld", &id_orig, &id_dest) != -1)
    {
        graph_newEdge(g, id_orig, id_dest);
    }

    return OK;
}

void graph_setVertexState(Graph *g, Label l)
{
    int i = 0;

    if (!g || l == ERROR_VERTEX)
        return;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_setState(g->vertices[i], l) == ERROR)
            return;
    }
}

Status graph_depthSearch(Graph *g, long from_id, long to_id)
{
    Vertex *vf = NULL;
    Vertex *vt = NULL;
    Vertex *vo = NULL;
    Stack *s = NULL;
    Status st = OK;
    int i = 0, n = 0, ix = 0;
    long *array = NULL;

    if (!g || from_id < 0 || to_id < 0)
        return ERROR;

    graph_setVertexState(g, WHITE);

    vf = graph_getVertexFromId(g, from_id);
    if (!vf)
        return ERROR;

    vt = graph_getVertexFromId(g, to_id);
    if (!vt)
        return ERROR;

    s = stack_init();
    if (!s)
        return ERROR;

    if (stack_push(s, vf) == ERROR)
    {
        stack_free(s);
        return ERROR;
    }

    while (stack_isEmpty(s) == FALSE && st == OK)
    {
        vo = stack_pop(s);
        if (!vo)
        {
            st = ERROR;
        }
        ix = vertex_getIndex(vo);
        n = graph_getNumConnections(g, ix);
        if (n == RET_ERROR)
        {
            st = ERROR;
        }
        array = graph_getConnections(g, ix);
        if (!array)
        {
            st = ERROR;
        }

        if (vertex_print(stdout, vo) == RET_ERROR)
        {
            st = ERROR;
        }
        fprintf(stdout, "\n");

        if (vertex_cmp(vo, vt) == 0)
        {
            vertex_setState(vo, BLACK);
            free(array);
            break;
        }
        else
        {
            if (vertex_getState(vo) == WHITE)
            {
                vertex_setState(vo, BLACK);
            }
            for (i = 0; i < n; i++)
            {
                vo = graph_getVertexFromId(g, array[i]);
                if (vertex_getState(vo) == WHITE)
                {
                    if (stack_push(s, vo) == ERROR)
                    {
                        st = ERROR;
                    }
                    // if (vertex_cmp(vo, vt) == 0)
                    // {
                    //     break;
                    // }
                }
            }
        }
        free(array);
    }

    while (stack_isEmpty(s) == FALSE)
    {
        stack_pop(s);
    }
    stack_free(s);
    if (st == ERROR)
    {
        free(array);
    }
    return st;
}

#include <string.h>
#include "vertex.h"
#include <string.h>
#define TAG_LENGTH 64

/* Vertex TAD implementation */
struct _Vertex
{
  long id;
  char tag[TAG_LENGTH];
  Label state;

  int index;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField(Vertex *v, char *key, char *value);

Status vertex_setField(Vertex *v, char *key, char *value)
{
  if (!key || !value)
    return ERROR;

  if (strcmp(key, "id") == 0)
  {
    return vertex_setId(v, atol(value));
  }
  else if (strcmp(key, "tag") == 0)
  {
    return vertex_setTag(v, value);
  }
  else if (strcmp(key, "state") == 0)
  {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr)
{
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr)
    return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v)
    return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token)
  {
    p = strchr(token, ':');
    if (!p)
      continue;

    *p = '\0';
    key = token;
    value = p + 1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/**  rest of the functions in vertex.h **/

/* Constructor. Initialize a vertex */
Vertex *vertex_init()
{
  Vertex *v = NULL;

  v = (Vertex *)malloc(sizeof(Vertex));

  if (!v)
    return NULL;

  v->id = 0;
  v->tag[0] = '\0';
  v->state = WHITE;
  v->index = 0;

  return v;
}

/* Destructor. Free the dynamic memory reserved for a vertex */
void vertex_free(void *v)
{
  if (!v)
    return;

  free(v);
}

/* Gets the vertex id */
long vertex_getId(const Vertex *v)
{
  if (!v)
    return EXIT_FAILURE;

  return v->id;
}

/* Gets the vertex tag */
const char *vertex_getTag(const Vertex *v)
{
  if (!v)
    return NULL;

  return v->tag;
}

/* Gets the state of a given vertex */
Label vertex_getState(const Vertex *v)
{
  if (!v)
    return ERROR_VERTEX;

  return v->state;
}

/* Gets the index of a given vertex */
int vertex_getIndex(const Vertex *v)
{
  if (!v)
    return RET_ERROR;

  return v->index;
}

/* Modifies the id of a given vertex */
Status vertex_setId(Vertex *v, const long id)
{
  if (!v || id < 0)
    return ERROR;

  v->id = id;
  return OK;
}

/* Modifies the tag of a given vertex */
Status vertex_setTag(Vertex *v, const char *tag)
{
  int len = 0;
  if (!v || !tag)
    return ERROR;

  len = strlen(tag);
  if (len > TAG_LENGTH)
    return ERROR;

  if (!strcpy(v->tag, tag))
    return ERROR;

  return OK;
}

/* Modifies the state of a given vertex */
Status vertex_setState(Vertex *v, const Label state)
{
  if (!v)
    return ERROR;

  v->state = state;
  return OK;
}

/* Modifies the state of a given vertex */
Status vertex_setIndex(Vertex *v, const int index)
{
  if (!v)
    return ERROR;

  v->index = index;
  return OK;
}

/* Compares two vertices */
int vertex_cmp(const void *v1, const void *v2)
{
  const Vertex *vertex1 = NULL;
  const Vertex *vertex2 = NULL;
  vertex1 = (const Vertex *)v1;
  vertex2 = (const Vertex *)v2;
  int cmp = 0;
  long id1 = 0, id2 = 0;
  const char *tag1 = NULL;
  const char *tag2 = NULL;
  if (!v1 || !v2)
    return 0;

  id1 = vertex_getId(vertex1);
  id2 = vertex_getId(vertex2);

  tag1 = vertex_getTag(vertex1);
  tag2 = vertex_getTag(vertex2);

  if (id1 == id2)
  {
    cmp = strcmp(tag1, tag2);
    return cmp;
  }
  else if (id1 < id2)
  {
    return RET_ERROR;
  }
  else if (id1 > id2)
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/* Reserves memory for a vertex where it copies the data from the vertex src */
void *vertex_copy(const void *src)
{
  Vertex *dst = NULL;
  Status status = OK;

  if (!src)
    return NULL;

  dst = vertex_init();
  if (!dst)
    return NULL;

  status = vertex_setId(dst, vertex_getId(src));
  if (status == ERROR)
  {
    vertex_free(dst);
    return NULL;
  }
  status = vertex_setState(dst, vertex_getState(src));
  if (status == ERROR)
  {
    vertex_free(dst);
    return NULL;
  }
  status = vertex_setTag(dst, vertex_getTag(src));
  if (status == ERROR)
  {
    vertex_free(dst);
    return NULL;
  }

  status = vertex_setIndex(dst, vertex_getIndex(src));
  if (status == ERROR)
  {
    vertex_free(dst);
    return NULL;
  }

  return dst;
}

/* Prints in pf the data of a vertex */
int vertex_print(FILE *pf, const void *v)
{
  const Vertex *vertex = NULL;
  vertex = (Vertex *)v;
  int index_aux = 0;
  long id_aux = 0;
  const char *tag_aux = NULL;
  Label state_aux = ERROR_VERTEX;

  if (!pf || !v)
    return RET_ERROR;

  id_aux = vertex_getId(vertex);
  if (id_aux == RET_ERROR)
  {
    return RET_ERROR;
  }

  tag_aux = vertex_getTag(vertex);
  if (tag_aux == NULL)
  {
    return RET_ERROR;
  }
  state_aux = vertex_getState(vertex);

  index_aux = vertex_getIndex(vertex);

  return fprintf(pf, "[%ld, %s, %d, %d]", id_aux, tag_aux, state_aux, index_aux);
}
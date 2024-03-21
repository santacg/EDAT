#include <string.h>
#include "vertex.h"
#include <string.h>
<<<<<<< HEAD
#define TAG_LENGTH 64 

/* Vertex TAD implementation */
struct _Vertex {
  long id;
  char tag[TAG_LENGTH];
  Label state;
=======
#define TAG_LENGTH 64

/* Vertex TAD implementation */
struct _Vertex
{
  long id;
  char tag[TAG_LENGTH];
  Label state;

  int index;
>>>>>>> EDAT-P2/master
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
<<<<<<< HEAD
Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
=======
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
>>>>>>> EDAT-P2/master
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
<<<<<<< HEAD
Vertex *vertex_initFromString(char *descr){
=======
Vertex *vertex_initFromString(char *descr)
{
>>>>>>> EDAT-P2/master
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
<<<<<<< HEAD
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;
=======
  if (!descr)
    return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v)
    return NULL;
>>>>>>> EDAT-P2/master

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
<<<<<<< HEAD
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;
=======
  while (token)
  {
    p = strchr(token, ':');
    if (!p)
      continue;

    *p = '\0';
    key = token;
    value = p + 1;
>>>>>>> EDAT-P2/master

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/**  rest of the functions in vertex.h **/

/* Constructor. Initialize a vertex */
<<<<<<< HEAD
Vertex * vertex_init () {
  char tag[TAG_LENGTH] = "\0";
  Vertex * v = NULL;

  v = (Vertex *) malloc(sizeof(Vertex));

  if (!v) return NULL;

  v->id = 0;
  if (!strcpy(v->tag, tag)) return NULL;
  v->state = WHITE;
=======
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
>>>>>>> EDAT-P2/master

  return v;
}

/* Destructor. Free the dynamic memory reserved for a vertex */
<<<<<<< HEAD
void vertex_free (void * v) {
  if (!v) return;
=======
void vertex_free(void *v)
{
  if (!v)
    return;
>>>>>>> EDAT-P2/master

  free(v);
}

/* Gets the vertex id */
<<<<<<< HEAD
long vertex_getId (const Vertex * v){
  if (!v) return EXIT_FAILURE;
=======
long vertex_getId(const Vertex *v)
{
  if (!v)
    return EXIT_FAILURE;
>>>>>>> EDAT-P2/master

  return v->id;
}

/* Gets the vertex tag */
<<<<<<< HEAD
const char* vertex_getTag (const Vertex * v){
  if (!v) return NULL;
=======
const char *vertex_getTag(const Vertex *v)
{
  if (!v)
    return NULL;
>>>>>>> EDAT-P2/master

  return v->tag;
}

/* Gets the state of a given vertex */
<<<<<<< HEAD
Label vertex_getState (const Vertex * v){
=======
Label vertex_getState(const Vertex *v)
{
>>>>>>> EDAT-P2/master
  if (!v)
    return ERROR_VERTEX;

  return v->state;
<<<<<<< HEAD
  
}

/* Modifies the id of a given vertex */
Status vertex_setId (Vertex * v, const long id){
  if (!v || id < 0) return ERROR;
=======
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
>>>>>>> EDAT-P2/master

  v->id = id;
  return OK;
}

/* Modifies the tag of a given vertex */
<<<<<<< HEAD
Status vertex_setTag (Vertex * v, const char * tag){
  int len = 0;
  if (!v || !tag)
    return ERROR;
  
  len = strlen(tag);
  if (len > TAG_LENGTH) return ERROR;
    
  if(strcpy(v->tag, tag) != NULL) {
    return OK;
  }
    
  return ERROR;
  
}

/* Modifies the state of a given vertex */
Status vertex_setState (Vertex * v, const Label state){
  if (!v) return ERROR;
  
=======
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

>>>>>>> EDAT-P2/master
  v->state = state;
  return OK;
}

<<<<<<< HEAD
/* Compares two vertices */
int vertex_cmp (const void * v1, const void * v2){
  const Vertex * vertex1 = NULL;
  const Vertex * vertex2 = NULL;
  vertex1 = (const Vertex *) v1;
  vertex2 = (const Vertex *) v2; 
=======
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
>>>>>>> EDAT-P2/master
  int cmp = 0;
  long id1 = 0, id2 = 0;
  const char *tag1 = NULL;
  const char *tag2 = NULL;
<<<<<<< HEAD
  if (!v1 || !v2) return 0;
  
  id1 = vertex_getId(vertex1);
  id2 = vertex_getId(vertex2);
  
  tag1 = vertex_getTag(vertex1);
  tag2 = vertex_getTag(vertex2);
  
  if (id1 == id2) {
    cmp = strcmp(tag1, tag2);
    return cmp;
  }
  else if (id1 < id2) {
    return O_ERROR;
  }
  else if (id1 > id2) {
    return EXIT_SUCCESS;
  }

  return 0;
}

/* Reserves memory for a vertex where it copies the data from the vertex src */
void * vertex_copy (const void * src){
  Vertex * dst = NULL;
  Status status = OK;
  
=======
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

>>>>>>> EDAT-P2/master
  if (!src)
    return NULL;

  dst = vertex_init();
  if (!dst)
<<<<<<< HEAD
=======
    return NULL;

  status = vertex_setId(dst, vertex_getId(src));
  if (status == ERROR)
>>>>>>> EDAT-P2/master
  {
    vertex_free(dst);
    return NULL;
  }
<<<<<<< HEAD
  
  status = vertex_setId(dst, vertex_getId(src));
  if(status == ERROR) {
    vertex_free(dst);
    return NULL;
  }
  status = vertex_setState(dst, vertex_getState(src));
  if(status == ERROR) {
=======
  status = vertex_setState(dst, vertex_getState(src));
  if (status == ERROR)
  {
>>>>>>> EDAT-P2/master
    vertex_free(dst);
    return NULL;
  }
  status = vertex_setTag(dst, vertex_getTag(src));
<<<<<<< HEAD
  if(status == ERROR) {
=======
  if (status == ERROR)
  {
    vertex_free(dst);
    return NULL;
  }

  status = vertex_setIndex(dst, vertex_getIndex(src));
  if (status == ERROR)
  {
>>>>>>> EDAT-P2/master
    vertex_free(dst);
    return NULL;
  }

  return dst;
}

/* Prints in pf the data of a vertex */
<<<<<<< HEAD
int vertex_print (FILE * pf, const void * v){
  const Vertex * vertex = NULL;
  vertex = (Vertex *) v;
  long id_aux = 0;;
  const char *tag_aux = NULL;
  Label state_aux = ERROR_VERTEX;

  if(!pf || !v) return O_ERROR;

  id_aux = vertex_getId(vertex);
  if (id_aux == O_ERROR) {
    return O_ERROR;
  }
 
  tag_aux = vertex_getTag(vertex);
  if (tag_aux == NULL) {
    return O_ERROR;
  }
  state_aux = vertex_getState(vertex);
  
  
  return fprintf(pf, "[%ld, %s, %d]", id_aux, tag_aux, state_aux); 

=======
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
>>>>>>> EDAT-P2/master
}
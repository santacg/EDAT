#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2  // multiply the stack capacity

struct _Stack
{
    void **item;  /*!<Static array of elements*/
    int top;      /*!<index of the top element in the stack*/
    int capacity; /*!<xcapacity of the stack*/
};

Stack *stack_init()
{
    Stack *s = NULL;

    s = (Stack *)malloc(sizeof(Stack));
    if (!s)
        return NULL;

    s->item = (void *)malloc(sizeof(void *) * INIT_CAPACITY);
    if (!s->item)
    {
        free(s);
        return NULL;
    }

    s->top = -1;
    s->capacity = INIT_CAPACITY;

    return s;
}

void stack_free(Stack *s)
{
    if (!s)
        return;
    free(s->item);
    free(s);
}

Status stack_push(Stack *s, const void *ele)
{
    void *aux = NULL;
    if (!s || !ele)
        return ERROR;

    if (s->top == (s->capacity - 1))
    {
        aux = realloc(s->item, FCT_CAPACITY * sizeof(void *) * s->capacity);

        if (aux == NULL)
            return ERROR;
        s->capacity = s->capacity * FCT_CAPACITY;
        s->item = aux;
    }

    s->top++;
    s->item[s->top] = (void *)ele;

    return OK;
}

void *stack_pop(Stack *s)
{
    void *e = NULL;

    if (!s || stack_isEmpty(s) == TRUE)
        return NULL;

    e = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;

    return e;
}

void *stack_top(const Stack *s)
{
    if (!s || stack_isEmpty(s) == TRUE)
        return NULL;

    return s->item[s->top];
}

Bool stack_isEmpty(const Stack *s)
{
    if (!s)
        return TRUE;

    if (s->top == -1)
        return TRUE;

    return FALSE;
}

size_t stack_size(const Stack *s)
{
    if (!s)
        return EXIT_FAILURE;

    return s->top;
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)
{
    int n = 0, ele = 0;


    if (!fp || !s)
        return RET_ERROR;

    ele = s->top;
    while (ele > -1)
    {
        f(fp, s->item[ele]);
        fprintf(stdout, "\n");
        n++;
        ele--;
    }

    return n;
}